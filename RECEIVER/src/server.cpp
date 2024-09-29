#include "server.h"

String cities[] = {"Adidogome", "Zanguera", "Hedzranawoe", "Aeroport", "CIMTOGO", "Contour global", "Adewui"};
String devices[] = {"emitter_1", "emitter_2", "emitter_3", "emitter_4", "emitter_5"};

void startWifi();
void startAp();
void parseDataStringToJson(String dataString, JsonDocument &doc);

void setupServer()
{
    WiFi.mode(WIFI_AP_STA);
    startAp();
    startWifi();
    Serial.println();
}

void startWifi()
{
    Serial.println("Connecting to WiFi");

    WiFi.begin(WL_SSID, WL_PASS);
    int startedAt = millis();
    int isNowAt = millis();
    // Wait for 10s
    while (WiFi.status() != WL_CONNECTED && (isNowAt - startedAt < 10000))
    {
        delay(500);
        Serial.print(".");
        isNowAt = millis();
    }
    Serial.println("");
    Serial.printf("Connected to '%s' network with IP Address: ", WL_SSID.c_str());
    Serial.println(WiFi.localIP());
}

void startAp()
{
    Serial.println("Sarting access point");
    WiFi.softAP(AP_SSID, AP_PASS);
    Serial.println("");
    Serial.printf("Access point started as '%s' AP IP Address: ", AP_SSID.c_str());
    Serial.println(WiFi.softAPIP());
}

bool sendDataToServer(String dataString, String url)
{
    WiFiClient client;
    HTTPClient http;

    http.begin(client, url);
    http.addHeader("Content-Type", "application/json");

    JsonDocument data;

    parseDataStringToJson(dataString, data);

    if (!data["CO"])
        return false;

    String httpData;

    serializeJson(data, httpData);

    int httpResponseCode = http.POST(httpData);

    Serial.println(httpResponseCode);

    return httpResponseCode == 201;
}

// Parses data received from measuring device
void parseDataStringToJson(String dataString, JsonDocument &doc)
{
    // definfing limitation variables
    int currentStartIndex, currentEndIndex;

    // Writing CO value to doc
    currentStartIndex = dataString.indexOf("CO ") + 3;
    currentEndIndex = dataString.indexOf(";", currentStartIndex);
    doc["CO"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing AL value to doc
    currentStartIndex = dataString.indexOf("AL ") + 3;
    currentEndIndex = dataString.indexOf(";", currentStartIndex);
    doc["AL"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing CO2 value to doc
    currentStartIndex = dataString.indexOf("CO2 ") + 4;
    currentEndIndex = dataString.indexOf(";", currentStartIndex);
    doc["CO2"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing TLN value to doc
    currentStartIndex = dataString.indexOf("TLN ") + 4;
    currentEndIndex = dataString.indexOf(";", currentStartIndex);
    doc["TLN"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing NH4 value to doc
    currentStartIndex = dataString.indexOf("NH4 ") + 4;
    currentEndIndex = dataString.indexOf(";", currentStartIndex);
    doc["NH4"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing ACT value to doc
    currentStartIndex = dataString.indexOf("ACT ") + 4;
    currentEndIndex = dataString.indexOf("::", currentStartIndex);
    doc["ACT"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing temperature to doc
    currentStartIndex = currentEndIndex + 2;
    currentEndIndex = dataString.indexOf(";", currentStartIndex);
    doc["temperature"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing humidity to doc
    currentStartIndex = currentEndIndex + 1;
    currentEndIndex = dataString.indexOf("::", currentStartIndex);
    doc["humidity"] = dataString.substring(currentStartIndex, currentEndIndex).toFloat();

    // Writing position to doc
    // TODO ... parse real position

    // For latitude
    // currentStartIndex = currentEndIndex + 2;
    // currentEndIndex = dataString.indexOf(",", currentStartIndex);
    // doc["lat"] = dataString.substring(currentStartIndex, currentEndIndex);
    doc["lat"] = random(5000, 2000000);

    // For longitude
    // currentStartIndex = currentEndIndex + 1;
    // currentEndIndex = dataString.indexOf("::", currentStartIndex);
    // doc["lon"] = dataString.substring(currentStartIndex, currentEndIndex);
    doc["lon"] = random(5000, 20000000);

    // For Date
    // currentStartIndex = currentEndIndex + 2;
    // currentEndIndex = dataString.indexOf("::", currentStartIndex);
    // doc["date"] = dataString.substring(currentStartIndex, currentEndIndex);
    // doc["date"] = __TIMESTAMP__;

    doc["device_id"] = devices[random(0, 5)];

    doc["city"] = cities[random(0, 7)];
}