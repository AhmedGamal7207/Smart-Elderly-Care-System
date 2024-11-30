/* ***************************************************PACKAGES*************************************************** */
#include "DFRobot_AHT20.h" // Temperature Sesnor
#include <ESP32Servo.h>  // Servo Motor
#include <Keypad.h> // Keypad
#include <WiFi.h> // Wifi
#include <Firebase_ESP_Client.h> // Firebase
#include <addons/TokenHelper.h> // Firebase Feedback Messages (Token Management)
#include <addons/RTDBHelper.h> // Firebase Real Time Data Base
#include "ESPAsyncWebServer.h" // To make a local connection between 2 ESPs using WIFI
#include <NTPClient.h> // NTP server to get the real date and time
#include <WiFiUdp.h> // Wifi library to access NTP server
#include "time.h" // Time package

/* ***************************************************KEYPAD*************************************************** */
char keys[3][3] = { // 2D array that defining all keys in the keypad
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'}
};

byte rowPins[3] = {17, 16, 33}; // The pins numbers for R1, R2, R3
byte colPins[3] = {26, 25, 27}; // The pins numbers for C1, C2, C3

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 3, 3); // // Our Keypad

/* ***************************************************DATE AND TIME*************************************************** */
const char* ntpServer = "pool.ntp.org"; // NTP server to use
const long gmtOffset_sec = 3 * 3600;  // 3 because of GMT+3 (Egypt) "3600 seconds = 1 hour"
const int daylightOffset_sec = 3600;  // Summer Time

WiFiUDP ntpUDP; // Wifi client for ntp server
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec); // This is the NTP Client Object
String dateNow = "";
/* ***************************************************SERVO*************************************************** */
Servo myServo; // Our Servo Motor
int servoPin = 4 ; // Servo Motor Pin

/* ***************************************************SENSORS*************************************************** */
const int flamePin = 14; // Flame Sensor Pin
const int forcePin = 32;  // Force Sensor Pin
const int ldrPin = 15; // LDR pin
const int soilPin = 34; // Soil Moisture Sensor Pin
const int irPin = 18; // IR Sensor Pin
const int rainPin=5; // Rain Sensor Pin
const int heartPin = 35; // Heart Rate Sensor Pin
const int motionPin = 13; // Motion Sensor Pin
const int gasPin=19;  // Gas Sensor Pin

DFRobot_AHT20 aht20; // Our Temperature Sensor

/* ***************************************************OUTPUT*************************************************** */
const int ledPin = 2; // Led Pin
const int buzzerPin =12 ; // Buzzer Pin

/* ***************************************************WIFI*************************************************** */
const char* ssid = "Rana"; // Connect to this network
const char* password = "mondler169";

/* ***************************************************ACCESS POINT*************************************************** */
const char* ssidAP = "ESP32-Access-Point"; // Create access point with this name
const char* passwordAP = "123456789"; // The password for the created access point

AsyncWebServer server(80); // Create AsyncWebServer object on port 80

String robotMessage = "Stop"; // We will use this string to control the robot using the HTTP server

/* ***************************************************FIREBASE*************************************************** */
String USER_EMAIL = "old123@gmail.com";
String USER_PASSWORD = "";
String userID = ""; // To store UserID after signing in

FirebaseData fbdo; // Firebase Data Object (Used to convert data From and To JSON before sending and recieving from firebase)
FirebaseAuth auth; // Firebase Auth Object (Used to handle Authentication(Email and Password))
FirebaseConfig config; // Firebase Config Object (Used to set the Settings of Firebase (For EX: API Key))

#define API_KEY "AIzaSyA_GMjy0Q6s9Gj3Pai5spLoEfMR77jB_ew" // API Key for Elderly Care Project
#define DATABASE_URL "https://elderly-care-2d133-default-rtdb.firebaseio.com/" // RTDB Link from Firebase

String espPath = ""; // String to store path of ESP data in RTDB Firebase
String pythonPath = ""; // String to store path of Python data in RTDB Firebase
String flutterPath = ""; // String to store path of Flutter data in RTDB Firebase
String fullPath = ""; // Store the path with Date and Time
String currentPath = ""; // Store the path with Date and Current

/* ***************************************************END OF DECLARATION*************************************************** */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // Beginning the Serial Communication and set the Baud Rate (Speed of Connection) = 115200

  /* ***************************************************INPUT PINS*************************************************** */
  pinMode(flamePin, INPUT);
  pinMode(forcePin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(soilPin, INPUT);
  pinMode(irPin, INPUT);
  pinMode(rainPin, INPUT);
  pinMode(heartPin, INPUT);
  pinMode(motionPin, INPUT);
  pinMode(gasPin, INPUT);

  aht20.begin(); // Temperature Sensor

  /* ***************************************************OUTPUT PINS*************************************************** */
  pinMode(ledPin,OUTPUT);
  pinMode(buzzerPin,OUTPUT);

  myServo.attach(servoPin);
  myServo.write(70);
  /* ***************************************************FUNCTIONS*************************************************** */
  createAP(ssidAP,passwordAP);
  delay(100);
  connectToWifi(ssid,password);
  startFirebase();
  startDateTime();
  dateNow = getDate();
  Serial.println("Setup Was Ended Successfully!");
  
}
/* ***************************************************END OF SETUP*************************************************** */

void loop() {
  // put your main code here, to run repeatedly:
  timeClient.update(); // Update the time from the NTP server
  String timeNow = timeClient.getFormattedTime();
 
  if(Firebase.ready()){ // All program starts if all set up and the user signed in
    fullPath = espPath+dateNow+"/"+timeNow+"/"; // Update full path with current Date and Time
    setStringFB(currentPath+"timeNow/",timeNow); // Store time in the current data

    checkRequest();

    checkAmbulance();

    float tempValue = getTemperature();

    float humValue = getHumidity();

    int flameValue = getFlame();

    int forceValue = getForce();

    int ldrValue = getLdr();

    int soilValue = getSoil();

    int irValue = getIr();

    int rainValue = getRain();

    int motionValue = getMotion();

    int gasValue = getGas();

    float heartValue = getHeart();

    if(ldrValue == 0 && motionValue == 1){
      printLCD("ROOM");
      alarm();
    }
    else{
      closeAlarm();
    }
    
    if(forceValue >= 2500){
      printLCD("STAIRS");
      alarm();
    }
    else{
      closeAlarm();
    }

    if(flameValue == 0){
      printLCD("FIRE");
      alarm();
    }
    else{
      closeAlarm();
    }

    if(gasValue == 0){
      printLCD("GAS DETECTED");
      alarm();
    }
    else{
      closeAlarm();
    }

    if(irValue == 0){ // Reversed
      printLCD("Door Opened");
      myServo.write(180);
      delay(2000);
      myServo.write(70);
      printLCD("Door Closed");
    }
    else{
      myServo.write(70);
    }
  }
}
/* ***************************************************END OF LOOP*************************************************** */

/* ***************************************************Wifi Functions*************************************************** */
// Function to manage connecting to Wifi
void connectToWifi(const char* ssid, const char* password){ 
  WiFi.begin(ssid, password); // Start connection to WIFI

  Serial.print("Connecting to "); 
  Serial.print(ssid);
  printLCD("Connecting");
  while (WiFi.status() != WL_CONNECTED) { // While connecting (not connected)
    delay(1000);
    Serial.print("."); // Print dot every second (Connecting .....)
  }

  // After being connected successfully
  Serial.println("\nConnected to WiFi"); // Print connected
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print IP
  
}

void createAP(const char* ssidAP, const char* passwordAP){

  Serial.print("Setting AP (Access Point)…"); // Setting the ESP as an access point

  WiFi.softAP(ssidAP, passwordAP); // Start the AP (Hotspot)

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP); // Get Access Point IP Address

  server.on("/robot", HTTP_GET, [](AsyncWebServerRequest *request){ // When AP is requested with /robot
    request->send_P(200, "text/plain", RobotMessage().c_str()); // Send the message in RobotMessage Function
  });

   server.begin();
}

// Function to be used to contact with the Robot another ESP
String RobotMessage(){
  return robotMessage;
}
/* ***************************************************Keypad Functions*************************************************** */
// Function to recieve password from keypad
String getPassword(){ 

  String enteredPassword = ""; // String to store the input password
  bool entering = true; // Boolean to indicate weather the user finished entering the password or not
  
  startInputAlarm(); // Indicator to start entering password
  Serial.print("Enter Password: ");
  printLCD("Enter Password");
  while(entering){
      char key = keypad.getKey(); // Get the pressed key in the keypad
      if(key){ // If you pressed any key
        if(enteredPassword.length() != 6){ // If the user didn't enter 6 digits
        digitalWrite(buzzerPin,HIGH);
        delay(50);
        digitalWrite(buzzerPin,LOW);
        enteredPassword += key; // Concatenate on the entered password
        Serial.print(key);
      }
      else{ // The user entered 6 digits
        entering = false; // Break the while loop
        startInputAlarm();
        Serial.print("\n");
        printLCD(" ");
        return enteredPassword; // Return the entered password
      }
   }
    delay(100);
  }
}
/* ***************************************************Alarm Functions*************************************************** */
 // Buzzer emits Correct Sound
void correctInputAlarm(){
    digitalWrite(ledPin,HIGH);
    digitalWrite(buzzerPin,HIGH);
    delay(1000); // Turn ON Buzzer for 1 Second
    digitalWrite(buzzerPin,LOW); // Turn OFF Buzzer
    delay(1000); // Wait for another second
    digitalWrite(ledPin,LOW); // // Turn OFF LED after 2 Seconds
}

 // Buzzer emits Wrong Sound
void wrongInputAlarm(){
  for(int i = 0; i < 3; i++){
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
  delay(500);
  }
}

// Buzzer prompts the user to take an action
void startInputAlarm(){ 
  for(int i = 0; i < 2; i++){
  digitalWrite(buzzerPin,HIGH);
  delay(100);
  digitalWrite(buzzerPin,LOW);
  delay(100);
  }
}

// Calling for help function
void alarm(){ 
  digitalWrite(ledPin,HIGH);
  digitalWrite(buzzerPin,HIGH);
  delay(1500);
  digitalWrite(ledPin,LOW);
  digitalWrite(buzzerPin,LOW);
  delay(1500);
  digitalWrite(ledPin,HIGH);
  digitalWrite(buzzerPin,HIGH);
  delay(1500);
  digitalWrite(ledPin,LOW);
  digitalWrite(buzzerPin,LOW);
  delay(1500);
  digitalWrite(ledPin,HIGH);
  digitalWrite(buzzerPin,HIGH);
  delay(1500);
  digitalWrite(ledPin,LOW);
  digitalWrite(buzzerPin,LOW);
  delay(1500);
  printLCD(" ");
}

// Closing alarm
void closeAlarm(){ 
  digitalWrite(ledPin,LOW);
  digitalWrite(buzzerPin,LOW);
}

void printLCD(String warning){
  Serial.println(" ");
  Serial.println("LCD:"+warning);
}
/* ***************************************************Firebase Functions*************************************************** */
// Function to manage initializing the Firebase
void startFirebase(){
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION); // Print the Version of Firebase

  config.api_key = API_KEY; // Set the API Key of the Project

  USER_PASSWORD = getPassword(); // Gets the user password from the Keypad

  /* Authentication */
  auth.user.email = USER_EMAIL; // Set the User Email
  auth.user.password = USER_PASSWORD; // Set the User Password

  /* Configuration */
  Firebase.reconnectWiFi(true); // If WIFI is disconnected at any time, reconnect.
  fbdo.setResponseSize(4096); // Sets the size (in bytes) of the transferred data (between ESP and Firebase)

  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback; // To manage Firebase Authentication Tokens

  Firebase.begin(&config, &auth);
  delay(5000);

  if(Firebase.ready()){ // If Firebase Started
    Serial.println("Firebase Authenticated Successfully");
    correctInputAlarm();
    printLCD("Logged In");
    userID = auth.token.uid.c_str(); // Get the user's unique ID (UID)
    espPath = "ESP/"+userID+"/";
    pythonPath = "PYTHON/"+userID+"/";
    flutterPath = "FLUTTER/"+userID+"/";
    currentPath = espPath+"current"+"/";
  }
  else{
    Serial.println("Firebase Could Not Authenticate");
    printLCD("ERROR!");
    wrongInputAlarm();
    startFirebase();
  }
}


// Function to set int value on Firebase
bool setIntFB(String path, int value){
  if (Firebase.RTDB.setInt(&fbdo, path, value)){
        /*Serial.println("Data Inserted Successfully");
        Serial.println("PATH: " + fbdo.dataPath());*/
        return true;
      }
      else {
        Serial.println("Failed to send Value: "+String(value)+" to Path: "+path);
        Serial.println("REASON: " + fbdo.errorReason());
        delay(1000);
        return false;
      }
}

// Function to set int value from Firebase
int getIntFB(String path){
  if (Firebase.RTDB.get(&fbdo, path)) {
    if (fbdo.dataType() == "int") { // Check if the returned type is int
      int returned_value = fbdo.intData();
      return returned_value;
    }
  } 
  else {
    Serial.println("Error getting data from Path: "+path);
    Serial.println("Reason: " + fbdo.errorReason());
    delay(1000);
    return 0;
  }
}

// Function to set string value on Firebase
bool setStringFB(String path, String value){
  if (Firebase.RTDB.setString(&fbdo, path, value)){
    /*Serial.println("Data Inserted Successfully");
    Serial.println("PATH: " + fbdo.dataPath());*/
    return true;
  }
  else {
    Serial.println("Failed to send Value: " + value + " to Path: " + path);
    Serial.println("REASON: " + fbdo.errorReason());
    delay(1000);
    return false;
  }
}

// Function to get string value from Firebase
String getStringFB(String path){
  if (Firebase.RTDB.get(&fbdo, path)) {
    if (fbdo.dataType() == "string") { // Check if the returned type is string
      String stringValue_FB = fbdo.stringData();

      /*Serial.print("String Value from Firebase: ");
      Serial.println(stringValue_FB);*/
      return stringValue_FB;
    }
  } 
  else {
    Serial.println("Error getting data from Firebase");
    Serial.println("Reason: " + fbdo.errorReason());
    return ""; // Return an empty string or handle the error as needed
  }
}

bool setFloatFB(String path, float value){
  if (Firebase.RTDB.setFloat(&fbdo, path, value)){
    /*Serial.println("Data Inserted Successfully");
    Serial.println("PATH: " + fbdo.dataPath());*/
    return true;
  }
  else {
    Serial.println("Failed to send Value: " + String(value) + " to Path: " + path);
    Serial.println("REASON: " + fbdo.errorReason());
    delay(1000);
    return false;
  }
}

// Function to get float value from Firebase
float getFloatFB(String path){
  if (Firebase.RTDB.getFloat(&fbdo, path)) {
    if (fbdo.dataType() == "float") {
      float floatValue_FB = fbdo.floatData();

      /*Serial.print("Float Value from Firebase: ");
      Serial.println(floatValue_FB);*/
      return floatValue_FB;
    }
  } 
  else {
    Serial.println("Error getting data from Firebase");
    Serial.println("Reason: " + fbdo.errorReason());
    return 0.0; // Return a default value or handle the error as needed
  }
}

// Function to check if the old man request help
void checkRequest(){
  String requestState = getStringFB(flutterPath+"request"); // Check request variable on firebase
  if(requestState == "yes"){ // If Yes:

    printLCD("REQUESTED");
    alarm(); // Call for help
    setStringFB(flutterPath+"request","no");
  }
  else{ // If no
    digitalWrite(ledPin,LOW); // Turn OFF LED
    digitalWrite(buzzerPin,LOW); // Turn OFF Buzzer
  }
}

// Function to check if the old man request help
void checkAmbulance(){
  String requestState = getStringFB(flutterPath+"ambulance"); // Check request variable on firebase
  if(requestState == "yes"){ // If Yes:
    robotMessage = "HELP";
    alarm(); // Call for help
    setStringFB(flutterPath+"ambulance","no");
  }
  else{ // If no
    digitalWrite(ledPin,LOW); // Turn OFF LED
    digitalWrite(buzzerPin,LOW); // Turn OFF Buzzer
    robotMessage = "STOP";

  }
}

/* ***************************************************DATE AND TIME*************************************************** */
// Function to start date and time
void startDateTime(){
  timeClient.begin();
  timeClient.update();
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

// Function to get the data dd\mm\yyyy
String getDate(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return "date";
  }

  char dayNumBuffer[20];
  strftime(dayNumBuffer, sizeof(dayNumBuffer), "%d", &timeinfo); // Extract day in string format
  String dayNum = String(dayNumBuffer);

  char monthBuffer[20];
  strftime(monthBuffer, sizeof(monthBuffer), "%B", &timeinfo); // Extract month name in string format
  String month = String(monthBuffer);
  String monthNum = String(getMonthNumber(month)); // convert from month name to month num

  char yearBuffer[20];
  strftime(yearBuffer, sizeof(yearBuffer), "%Y", &timeinfo); // Extract year number in string format
  String year = String(yearBuffer);

  String date = dayNum+"\\"+monthNum+"\\"+year; // dd\mm\yyyy
  return date;
}

String months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
// Function to convert from Month Name to Month Number
int getMonthNumber(String target) {
  for (int i = 0; i < 12; i++) {
    if (months[i] == target) {
      return i+1; // Return the index when the target element is found + 1 (Januare index 0 + 1 = 1 "Month Num")
    }
  }
  return -1; // Return -1 if the element is not found in the array
}
/* ***************************************************SENSORS*************************************************** */

float getTemperature(){
  if(aht20.startMeasurementReady(true)){
    float temp = aht20.getTemperature_C();
    //setFloatFB(fullPath+"tempSensor",temp);
    setFloatFB(currentPath+"tempSensor",temp);
    return temp;
  }
}

float getHumidity(){
  if(aht20.startMeasurementReady(true)){
    float hum = aht20.getHumidity_RH();
    //setFloatFB(fullPath+"humSensor",hum);
    setFloatFB(currentPath+"humSensor",hum);
    return hum;
  }
}

int getFlame(){
  int flame = digitalRead(flamePin);
  //setIntFB(fullPath+"flameSensor",flame);
  setIntFB(currentPath+"flameSensor",flame);
  return flame;
}

int getForce(){
  int force = analogRead(forcePin);
  //setIntFB(fullPath+"forceSensor",force);
  setIntFB(currentPath+"forceSensor",force);
  return force;
}

int getLdr(){
  int ldr = digitalRead(ldrPin); // Reading the value of LDR
  //setIntFB(fullPath+"ldrSensor",ldr);
  setIntFB(currentPath+"ldrSensor",ldr);
  return ldr;
}

int getSoil(){
  int soil = analogRead(soilPin); 
  //setIntFB(fullPath+"soilSensor",soil);
  setIntFB(currentPath+"soilSensor",soil);
  return soil;
}

int getIr(){
  int ir = digitalRead(irPin);
  //setIntFB(fullPath+"irSensor",ir);
  //setIntFB(currentPath+"irSensor",ir);
  return ir;
}

int getRain(){
  int rain = digitalRead(rainPin);
  //setIntFB(fullPath+"rainSensor",rain);
  setIntFB(currentPath+"rainSensor",rain);
  return rain;
}

int getMotion(){
  int motion = digitalRead(motionPin);
  //setIntFB(fullPath+"motionSensor",motion);
  setIntFB(currentPath+"motionSensor",motion);
  return motion;
}

int getGas(){
  int gas = digitalRead(gasPin);
  //setIntFB(fullPath+"gasSensor",gas);
  setIntFB(currentPath+"gasSensor",gas);
  return gas;
}

float getHeart(){
  float heart;
  int sum = 0;
  // Get average of 20 measurements
  for (int i = 0; i < 20; i++)
    sum += analogRead(35);
  heart = sum / 20.00;
  heart = map(heart, 0, 4095, 0, 120);
  //setFloatFB(fullPath+"heartSensor",heart);
  setFloatFB(currentPath+"heartSensor",heart);
  return heart;
}