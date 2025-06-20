# AirVigil Project

AirVigil is an end-to-end IoT solution for environmental monitoring. It consists of custom hardware (EMITTER and RECEIVER devices) and a backend server to collect, store, and visualize environmental data such as temperature, humidity, and air quality metrics.

## Project Structure
- **BACKEND/** — Flask-based server for data collection, storage (MongoDB), and dashboarding
- **EMITTER/** — Arduino-based device that senses environmental data and transmits it via LoRa
- **RECEIVER/** — ESP8266-based device that receives LoRa data and forwards it to the backend

## How It Works
1. **EMITTER** devices collect sensor and GPS data, then send it via LoRa radio.
2. **RECEIVER** devices listen for LoRa messages, parse the data, and forward it to the backend server over WiFi (HTTP).
3. The **BACKEND** receives, stores, and provides endpoints for data visualization and analysis.

## Technologies Used
- **LoRa** for long-range, low-power wireless communication
- **Arduino/PlatformIO** for embedded firmware
- **ESP8266** for WiFi connectivity
- **Flask** (Python) for the backend server
- **MongoDB** for data storage

## Getting Started
### Backend
1. Go to the `BACKEND/` folder
2. Install dependencies:
   ```bash
   pip install flask flask-cors pymongo
   ```
3. Start MongoDB and run the server:
   ```bash
   python app.py
   ```

### EMITTER & RECEIVER
1. Go to the respective folder (`EMITTER/` or `RECEIVER/`)
2. Install [PlatformIO](https://platformio.org/)
3. Connect your hardware (see folder READMEs for details)
4. Build and upload the firmware:
   ```bash
   pio run --target upload
   ```

## Architecture Diagram
```
[EMITTER] --LoRa--> [RECEIVER] --WiFi/HTTP--> [BACKEND] --(Dashboard/DB)
```

## Use Cases
- Air quality monitoring in urban or industrial areas
- Real-time environmental data collection for research or public health

---
See the `README.md` in each folder for more details on setup and usage. 