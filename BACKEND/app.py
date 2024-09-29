from flask import Flask, request, jsonify, render_template
from flask_cors import CORS
from pymongo import MongoClient
import datetime
from time import sleep

app = Flask(__name__)
CORS(app)

# MongoDB setup
client = MongoClient("mongodb://localhost:27017/")
db = client.airvigil_db
devices_collection = db.devices
env_data_collection = db.environmental_data


@app.route("/", methods=["GET"])
def home():
    cities = env_data_collection.distinct("city")
    return render_template("home.html", cities=cities)


@app.route("/add-data", methods=["POST"])
def add_data():
    data = request.json
    data["date"] = datetime.datetime.utcnow()  # Add timestamp
    env_data_collection.insert_one(data)  # Save environmental data
    return jsonify({"message": "Data saved successfully"}), 201


@app.route("/dashboard", methods=["GET"])
def dashboard():
    # Example query: Summarize the data
    data = list(
        env_data_collection.aggregate([{
            "$group": {
                "_id": "$device_id",
                "avg_temperature": {
                    "$avg": "$temperature"
                },
                "avg_humidity": {
                    "$avg": "$humidity"
                },
                "avg_CO": {
                    "$avg": "$CO"
                },
                "avg_CO2": {
                    "$avg": "$CO2"
                },
            }
        }]))
    return jsonify(data), 200


@app.route("/fetch-data", methods=["GET", "POST"])
def fetch_data():
    # Fetch all data
    city_filter = request.args.get("city")
    selection_filter = {
        "city": city_filter
    } if (city_filter and city_filter.lower() != "all") else {}
    print(selection_filter, city_filter)
    data = env_data_collection.find(selection_filter, {
        "_id": 0
    }).sort({
        "date": -1
    }).limit(20).to_list()

    data.reverse()

    return jsonify(data), 200


@app.route("/refresh-data", methods=["GET"])
def refresh_data():
    # Fetch the latest data
    latest_data = list(env_data_collection.find().sort("date", -1).limit(1))
    return jsonify(latest_data), 200


if __name__ == "__main__":
    app.run(host="0.0.0.0", debug=True)
