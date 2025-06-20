# EMITTER

This folder contains the EMITTER firmware for the AirVigil project. The EMITTER is an Arduino-based IoT device that collects environmental data and transmits it via LoRa to a RECEIVER or gateway.

## Features
- Reads data from environmental sensors (DHT, MQ sensors, GPS)
- Formats and sends data packets over LoRa
- Handles GPS location and timestamping
- Configurable via PlatformIO

## Hardware
- Board: ATmega328P (Arduino-compatible)
- Sensors: DHT (temperature/humidity), MQ (gas), GPS module
- LoRa module (868.1 MHz)

## Main Components
- `src/lora.cpp` — LoRa communication logic
- `src/gps.cpp` — GPS data handling
- `src/dht.cpp` — DHT sensor reading
- `platformio.ini` — PlatformIO configuration

## Setup & Build
1. Install [PlatformIO](https://platformio.org/)
2. Connect your hardware (ATmega328P, sensors, LoRa module)
3. Configure `platformio.ini` if needed (upload port, libraries)
4. Build and upload:
   ```bash
   pio run --target upload
   ```

## How it Works
- The EMITTER reads sensor and GPS data, formats it, and sends it via LoRa.
- It can parse and respond to commands received over LoRa.

---
This EMITTER is designed to work with the RECEIVER and BACKEND in the AirVigil project. 