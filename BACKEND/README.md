# BACKEND

This folder contains the backend server for the AirVigil project. It is a Flask-based web application that collects, stores, and serves environmental sensor data from IoT devices.

## Features
- Receives environmental data from devices (temperature, humidity, CO, CO2, etc.)
- Stores data in a MongoDB database
- Provides endpoints for data visualization and dashboarding
- Supports city-based filtering and data refresh

## Main Endpoints
- `GET /` — Home page with city selection
- `POST /add-data` — Add new environmental data (expects JSON)
- `GET /dashboard` — Get summarized data grouped by device
- `GET/POST /fetch-data` — Fetch recent data, optionally filtered by city
- `GET /refresh-data` — Fetch the latest data entry

## Setup
1. Ensure you have Python 3.8+ and MongoDB running locally.
2. Install dependencies:
   ```bash
   pip install flask flask-cors pymongo
   ```
3. Run the server:
   ```bash
   python app.py
   ```

The server will be available at `http://localhost:5000/` by default.

## Folder Structure
- `app.py` — Main Flask application
- `templates/` — HTML templates
- `static/` — Static files (CSS, JS, etc.)
- `data/` — (Optional) Data files
- `lib/`, `bin/`, `lib64/`, `__pycache__/` — Virtual environment and dependencies

---
This backend is designed to work with the EMITTER and RECEIVER IoT devices in the AirVigil project. 