🌀 AI-Enabled Smart Fan (TinyML)
This project implements an intelligent cooling system using TinyML on the STM32F103 (BluePill). The system doesn't just use static thresholds; it uses a trained machine learning model to predict the optimal fan speed based on environmental factors.

🚀 Key Features
Intelligent Control: Fan speed is modulated via PWM based on TinyML model inference.

Bare-Metal Efficiency: Entire system runs without an OS (RTOS-less) for maximum performance.

Real-time Monitoring: Sensor data and AI predictions are streamed over UART for live debugging.

🧠 TinyML Implementation
Input: Temperature & Humidity (via ADC/I2C).

Inference: On-device prediction using a quantized neural network model.

Output: 8-bit PWM signal to the Fan motor driver.

🛠️ Hardware Setup
MCU: STM32F103C8T6

Sensor: DHT11 or Thermistor

Actuator: DC Fan with L293D or MOSFET driver
