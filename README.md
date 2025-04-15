# 🧙‍♂️ MagiQuest Wand to Home Assistant Bridge

This simple ESP32-based project uses an IR receiver to detect **MagiQuest wand** signals and sends **on/off webhooks** to Home Assistant based on wand activity.

> ⚠️ **Important Compatibility Note**  
> This project requires **ESP32 Arduino Core version 2.0.x**. The `IRremoteESP8266` library does **not** work with ESP32 3.x or higher at this time.

## 📦 What It Does

- Listens for **IR signals** using the `IRremoteESP8266` library.
- Filters for the **MagiQuest protocol only** (ignores rolling codes).
- Alternates between sending **"on"** and **"off"** HTTP POST requests to specified Home Assistant endpoints.

## 🛠️ Hardware Required

- ESP32 (DevKit-style board)
- IR Receiver (e.g., TSOP38238)
- Magic wand (from MagiQuest or similar)

## 🔧 Setup

1. Flash the code to your ESP32 using PlatformIO or Arduino IDE.
2. Edit the following fields in the code:
   - `ssid` and `password`: Your Wi-Fi credentials
   - `on_endpoint` and `off_endpoint`: Your Home Assistant webhooks
3. Connect your IR receiver to **GPIO 35**.
4. Wave your MagiQuest wand!

## 🔁 Behavior

- Each valid MagiQuest signal toggles an internal state (`on` or `off`).
- The corresponding webhook is sent to Home Assistant.
- The wand essentially becomes a toggle switch!

## 📚 Libraries Used

- [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266)
- WiFi and HTTPClient (built-in with ESP32 Arduino Core)
