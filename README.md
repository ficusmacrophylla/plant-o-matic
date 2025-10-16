# 🌿 Plant-O-Matic (TOPSOILER)

An **Arduino-based autonomous irrigation and lighting system** designed to maintain ideal soil conditions for your plants through periodic moisture monitoring, pump control, and light cycles. Version 0.2 of the firmware incorporates power-saving sensor management, OLED status display, and safety wiring checks.

---

## 📖 Overview

Plant-O-Matic automates plant watering by sensing soil moisture and activates a pump only when needed. It also manages a grow light cycle and outputs real-time status on an OLED display, making it a self-sufficient smart plant system.

---

## 🧠 Core Firmware Features

- **Automated Soil Moisture Sensing:** Checks moisture every 8 hours, maps readings to 0-100% scale.
- **Pump Control:** Waters plants for a configurable duration when moisture falls below threshold.
- **Grow Light Cycling:** Toggles light on/off every 8 hours to simulate natural lighting conditions.
- **OLED Status Display:** Shows version, moisture values (current + previous two readings), plant status emoji, and cycle time.
- **Wiring Check:** Validates sensor, pump, and light wiring on startup with user feedback.
- **Power Saving:** Sensor power controlled strategically, reducing wear and preserving accuracy.
- **Serial Debugging:** Logs data and system states when in DEBUG mode.

---

## 🔌 Hardware Setup

| Component           | Connected To          |
|---------------------|-----------------------|
| Soil Moisture Sensor | Analog Pin A0         |
| Sensor Power        | Digital Pin 2           |
| Pump (via transistor) | Digital Pin 7           |
| Grow Light (LED strip) | Digital Pin 9           |
| OLED Display (I2C)   | SDA: A4, SCL: A5       |
| Serial Monitor       | 9600 baud rate          |

---

## ⚙️ Deploying Firmware

1. Clone the repo and open `AutoPlant.ino` in Arduino IDE.
2. Select Arduino Nano or UNO board and set the correct COM port.
3. Upload the firmware.
4. Open serial monitor at 9600 baud to read logs.
5. The system will run automatically checking moisture, cycling water and light, and updating the display.

---

## 🗺️ Roadmap

- **v0.2 (Current):**  
  - Automated moisture reading and pump activation  
  - OLED display integration  
  - Wiring validation and sensor power management  

- **v0.3:**  
  - Circular button menu for manual irrigation control and configuration  
  - Add empty-tank sensor with hardware failsafe to prevent dry-run pump damage  

- **v0.4:**  
  - Wi-Fi module integration for web-based status dashboard and remote control  
  - Data logging and alert notifications  

- **v0.5:**  
  - Advanced lighting management, including UV support and multi-stage light cycles  
  - Integration with home automation platforms  

- **v1.0:**  
  - Full mobile app and Telegram bot integration for real-time monitoring and control  
  - Expanded sensor suite: temperature, pH, nutrient levels  

- **Beyond v1.0:**  
  - Modular sensor/actuator expansion  
  - AI-based irrigation optimization algorithms  
  - Cloud connectivity and data analytics  

---

## 🧰 Required Materials

- Arduino Nano or UNO (ATmega328P)  
- 5V Micro Pump  
- Soil Moisture Sensor (Analog)  
- Transistor or Relay Module for Pump Control  
- 5V LED Strip (Grow Light)  
- OLED Display (SSD1306, 128×32, I²C)  
- Assorted wires, breadboard, power supply  

---

## 🧾 License

This project is released under the **GNU GPL v3.0** license — free to use, modify, and share with attribution.

---

🌱 *Happy gardening with intelligent automation!*
