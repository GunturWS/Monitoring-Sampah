# Smart Trash Monitoring System

A simple IoT-based system to monitor trash bin levels in real-time using **ESP32**, **HC-SR04 ultrasonic sensor**, **RTC module**, **OLED display**, **LCD**, and **Blynk**. The system provides real-time data and alerts when the trash bin is full, and allows for maintenance tracking via the Blynk app.

## Features
- **Ultrasonic Sensor**: Measures the distance to the trash bin to determine how full it is.
- **Real-Time Clock (RTC)**: Logs the time when the trash bin reaches full capacity.
- **Blynk Dashboard**: Displays real-time trash bin status and sends notifications when full.
- **OLED & LCD Displays**: Show trash bin fullness and maintenance status.
- **Maintenance Button**: Allows users to mark the bin as emptied or needing attention.

## Components
- **ESP32**: Main microcontroller that processes data.
- **HC-SR04 Ultrasonic Sensor**: Detects trash level by measuring distance.
- **RTC Module**: Records the time when the trash is full.
- **OLED & LCD Displays**: Show the status of the trash bin.
- **Blynk App**: Displays real-time data and notifies when the bin is full.
- **Wi-Fi**: For connecting the ESP32 to the Blynk cloud.

## How It Works
1. The **ultrasonic sensor** measures the distance to the trash.
2. The **RTC** records the time when the trash bin is full.
3. The **ESP32** processes the data and sends it to the **Blynk app**.
4. The **OLED** and **LCD** displays show the current status of the bin.
5. Notifications are sent via Blynk when the trash bin is full.

## Setup

### Hardware
- ESP32
- HC-SR04 Ultrasonic Sensor
- RTC Module
- OLED Display
- LCD Display
- Jumper Wires
- Breadboard

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- Blynk App ([iOS](https://apps.apple.com/us/app/blynk-iot/id1492010087) | [Android](https://play.google.com/store/apps/details?id=co.blynk.android))

### Steps
1. **Connect hardware**: Wire up the ultrasonic sensor, RTC, and displays to the ESP32.
2. **Blynk setup**: Create a Blynk project and add widgets for displaying data.
3. **Upload the code**: Upload the Arduino code to the ESP32, which will send the data to the Blynk app.
4. **Monitor**: Use the Blynk app to view real-time data and get notifications when the trash is full.

## License
This project is licensed under the MIT License.

---

Enjoy monitoring your trash bins in a smart way! 🚮💡
