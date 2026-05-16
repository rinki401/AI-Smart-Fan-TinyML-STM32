# AI-Based Smart Fan with Auto-Cooling & Load Prediction

An edge-AI powered smart appliance designed for the ESP32-S3 (Xtensa LX7) SoC. This project integrates on-device TinyML inference to predict user comfort and dynamically manage fan speed, cutting power consumption while maintaining real-time responsiveness (<10 ms latency).

## 🚀 Key Features
* **Edge-AI Inference:** Deployed a quantized TinyML model running locally on ESP32-S3 to analyze temporal data from 3 sensor streams (Temperature/Humidity, Ambient Light, and PIR Motion).
* **Deterministic Control:** Real-time motor speed adjustments via adaptive PWM control loops.
* **Safety-Critical Fail-safes:** Built-in motor over-temperature monitoring via software interrupts and threshold callbacks.
* **Telemetry & OTA:** Complete MQTT pipeline for reporting thermal load metrics and receiving Over-The-Air (OTA) runtime parameter tuning.

## 🛠️ Tech Stack & Hardware
* **Microcontroller:** ESP32-S3 (Xtensa LX7 dual-core)
* **Development Framework:** ESP-IDF (Embedded C)
* **Sensors:** DHT22 (Temp/Humidity), PIR (Motion), Photoresistor (Light)
* **Actuator:** DC Fan driven via MOSFET/PWM logic
* **Protocols:** MQTT, UART, I2C

---

## 🧠 System Architecture

```text
[DHT22 Sensor]   ---\
[PIR Sensor]     ----> [Sensor Fusion Layer] -> [TinyML Inference Engine] -> [Adaptive PWM Control] -> [DC Motor]
[Light Sensor]   ---/                                   |
                                                        v
                                             [MQTT Telemetry Pipeline]
