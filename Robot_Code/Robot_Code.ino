#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

// Here
unsigned long previousMillis = 0;
const long interval = 5000; 

const int trigPin = 15;
const int echoPin = 23;

int distance;

const int motor1Pin1 = 18; // IN1 Pin of L298N for Motor 1
const int motor1Pin2 = 19; // IN2 Pin of L298N for Motor 1
const int motor2Pin2 = 2; // IN1 Pin of L298N for Motor 2 (Different pin)
const int motor2Pin1 = 22; // IN2 Pin of L298N for Motor 2 (Different pin)
const int enablePin1 = 5;  // ENA Pin of L298N for Motor 1
const int enablePin2 = 21; // ENB Pin of L298N for Motor 2 (Different pin)


void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(115200); 

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);
  
  analogWrite(enablePin1, 255); // Enable Motor 1 driver
  analogWrite(enablePin2, 255); // Enable Motor 2 driver

  // Initially stop both motors
  motorStop();

}

void loop() {
  // Here
  unsigned long currentMillis = millis();
  // Here
  if(currentMillis - previousMillis >= interval) {
     // Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED ){ 
      String results = httpGETRequest("http://192.168.4.1/robot");
      Serial.println("RESULT =  " + results);
      if(results == "STOP"){
        Serial.println("The robot must stop");
        motorStop();
      }
      else if(results == "HELP"){
        Serial.println("The robot must COME NOW");
        while(1){
          int distance = calculate_distance();
          if(distance > 10){
            motorForward();
          }
          else{
            motorStop();
            break;
          }
          delay(50);
        }
        
      }
      // Here
      // save the last HTTP GET Request
      previousMillis = currentMillis;
    }
    else {
      Serial.println("WiFi Disconnected");
    }
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
  
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; // Message
  
  if (httpResponseCode>0) {
    /*Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);*/
    payload = http.getString();
  }
  else {
    /*Serial.print("Error code: ");
    Serial.println(httpResponseCode);*/
  }
  // Free resources
  http.end();

  return payload;
}

int calculate_distance(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  int duration = pulseIn(echoPin, HIGH); // Calculate the time consumed until the echoPin recieves HIGH
  
  int distance = duration * 0.0343 / 2;

  return distance;
}


void motorBackward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void motorForward() {
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void motorTurn1() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
}

void motorTurn2() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
}

void motorStop() {
  Serial.println("Robot is not moving");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

