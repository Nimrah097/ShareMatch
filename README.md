# KickScore
# IoT-Based Smart Football Game

This project is an interactive **IoT Football Game Prototype** built using Arduino components.  
It automatically detects goals using **ultrasonic sensors**, updates live scores on an **LCD display**, and controls **servo motors** to simulate player movement.  

## 🚀 Features

- Automatic goal detection using **ultrasonic sensors**
- Real-time score display on **16x2 I2C LCD**
- **Servo-controlled players** that move continuously during play
- Game ends automatically when a player scores 5 goals
- Compact and fully automated design with easy setup

---

## 🧠 Components Used

| Component | Description |
|------------|-------------|
| Arduino UNO | Main microcontroller for the system |
| Ultrasonic Sensors (HC-SR04) | Detect ball crossing into the goal area |
| Servo Motors | Simulate player or kicker movement |
| 16x2 I2C LCD | Display real-time scores |
| Breadboard & Jumper Wires | Circuit assembly |
| Power Supply | Provides power to components |

---

## 🧩 Required Libraries

Make sure the following Arduino libraries are installed before uploading the code:

```cpp
#include <Servo.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
