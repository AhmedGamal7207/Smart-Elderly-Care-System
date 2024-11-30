# Elderly Care System Project

This repository contains the code for the **Elderly Care System** built with ESP32, Firebase, and various sensors to monitor the environment and the health of elderly people. The system uses different sensors such as temperature, humidity, flame, force, and others to detect changes in the environment, and it can trigger alarms when necessary.

## Features

- **Temperature and Humidity Monitoring**: The system uses a DFRobot AHT20 sensor to measure temperature and humidity.
- **Motion Detection**: Using motion and flame sensors, the system detects if there is any unusual activity.
- **Firebase Integration**: Firebase is used to store and retrieve data from the real-time database.
- **Keypad Security**: A keypad is used to enter a password, ensuring that only authorized users can access specific features.
- **Servo Control**: A servo motor is used to control doors based on sensor input.
- **Alarms and Notifications**: The system triggers alarms for various events like fire, gas detection, and unauthorized access.

## Setup

### Requirements
1. **ESP32 Board**: This project uses the ESP32 microcontroller.
2. **Sensors**: The following sensors are used:
   - DFRobot AHT20 (Temperature and Humidity)
   - Flame Sensor
   - Force Sensor
   - LDR (Light Dependent Resistor)
   - Soil Moisture Sensor
   - IR Sensor
   - Rain Sensor
   - Heart Rate Sensor
   - Motion Sensor
   - Gas Sensor
3. **WiFi**: The system connects to a Wi-Fi network for Firebase and NTP server integration.
4. **Firebase Setup**: Firebase is used for real-time data storage.

### Libraries Required
- `DFRobot_AHT20` for temperature sensor
- `ESP32Servo` for controlling the servo motor
- `Keypad` for the keypad input
- `WiFi` for Wi-Fi connectivity
- `Firebase_ESP_Client` for Firebase interaction
- `ESPAsyncWebServer` for web server functionality
- `NTPClient` for getting the current time
- `WiFiUdp` and `time` libraries for NTP server communication

### Setup Steps

1. **Install Required Libraries**:
   - Install the required libraries via the Arduino Library Manager or manually download them from GitHub.

2. **Firebase Configuration**:
   - Set up your Firebase project and configure the `API_KEY` and `DATABASE_URL` in the code.

3. **Wi-Fi Setup**:
   - Define your Wi-Fi credentials in the code (`ssid` and `password`).

4. **Sensor Wiring**:
   - Connect all the sensors to the specified pins on the ESP32 board.

5. **Upload the Code**:
   - Upload the code to the ESP32 using the Arduino IDE.

### Firebase Configuration

To use Firebase with this project, make sure to:
- Set up Firebase Realtime Database.
- Create a new Firebase project and retrieve your **API Key**.
- Use Firebase authentication to securely access your data.

### NTP Configuration

The system uses the **NTP client** to get the current date and time. The time is used for logging and to trigger events at specific times.

## Code Overview

### Key Sections

- **Wi-Fi Setup**: Handles connecting to Wi-Fi and creating an access point (AP) if Wi-Fi is not available.
- **Sensor Readings**: Reads various sensors like temperature, flame, force, LDR, and others to detect environmental conditions.
- **Firebase Integration**: Stores sensor data and real-time information to Firebase Realtime Database.
- **Alarm Handling**: Triggers alarms for events like fire, gas leakage, or unauthorized access based on sensor readings.
- **Servo Control**: Opens or closes the door based on the IR sensor reading.

## Example Usage

### Keypad Password Entry
A keypad is used to enter a password for accessing certain features. The user can enter a 6-digit password, and the system will provide feedback through the buzzer and LED indicators.

### Alarm System
The system triggers alarms for various events like:
- **Fire Detection**: If the flame sensor detects a fire, an alarm is triggered.
- **Gas Detection**: If the gas sensor detects gas leakage, an alarm is triggered.
- **Motion Detection**: If unauthorized motion is detected, the system will trigger the alarm.

### Door Control
If the IR sensor detects an open door, the servo motor is activated to close the door after 2 seconds.

