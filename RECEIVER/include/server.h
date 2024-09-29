#ifndef _SERVER_H_
#define _SERVER_H_

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

const String WL_SSID = "test";
const String WL_PASS = "00000000";

const String AP_SSID = "AIRVIGIL-AP";
const String AP_PASS = "booleanIs0Or1";

#define REMOTE_BACKEND_URL "http://192.168.12.1:5000/add-data" // TODO remember to put real one
#define LOCAL_BACKEND_URL "http://vigil.center:5000/add-data"
#define DELAY_BETWEEN_DATA 10000

struct SERVER_DATA
{
    unsigned short dataType;
    String gases;
    String tempAndHum;
    String posAndDate;
};

typedef struct SERVER_DATA SERVER_DATA;

void setupServer();
bool sendDataToServer(String dataString, String url);

#endif
