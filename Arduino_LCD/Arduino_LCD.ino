String receivedData = ""; // Declare a string to store received data

// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(115200); // Set the baud rate to match ESP32

    // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Ready!");
}

void loop() {
  while (Serial.available()) {
    String inputString = Serial.readStringUntil('\n'); // Read a line from the serial monitor
    Serial.println(inputString);
    if (inputString.startsWith("LCD:")) {
      lcd.clear(); // Clear the LCD screen
      lcd.setCursor(0, 0); // Set the cursor to the beginning of the first line
      lcd.print(inputString.substring(4)); // Print the string on the LCD (excluding "LCD:")
    }
  }
}
