# RECEIVER

This folder contains the RECEIVER firmware for the AirVigil project. The RECEIVER is an ESP8266-based IoT device that receives environmental data via LoRa from EMITTER devices and forwards it to the backend server.

## Features
- Receives data packets from EMITTERs via LoRa
- Parses and processes environmental and location data
- Connects to WiFi and/or starts an Access Point
- Forwards data to a remote or local backend server via HTTP
- Configurable via PlatformIO

## Hardware
- Board: ESP8266 (d1_mini)
- LoRa module (868.1 MHz)

## Main Components
- `src/main.cpp` — Main application logic (receives, parses, and forwards data)
- `src/lora.cpp` — LoRa communication logic
- `src/server.cpp` — WiFi/AP and HTTP communication logic
- `platformio.ini` — PlatformIO configuration

## Setup & Build
1. Install [PlatformIO](https://platformio.org/)
2. Connect your hardware (ESP8266, LoRa module)
3. Configure `platformio.ini` if needed (upload port, libraries)
4. Build and upload:
   ```bash
   pio run --target upload
   ```

## How it Works
- The RECEIVER listens for LoRa messages from EMITTERs.
- It parses the received data, connects to WiFi or AP, and sends the data to the backend server.
- Supports both remote and local backend endpoints.

---
This RECEIVER is designed to work with the EMITTER and BACKEND in the AirVigil project. 