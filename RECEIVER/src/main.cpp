// Include necessary libraries
#include <Arduino.h>
#include <Esp.h>
#include "lora.h"
#include "server.h"

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial)
    ; // Wait for serial port to connect. Needed for native USB port only

  Serial.println("LoRa Bidirectional Communication (868.1 MHz)");
  ESP.wdtEnable(10);
  initLoRa();
  setupServer();
}

void loop()
{
  String data = getData();

  if (data == "")
    return;

  // Sending remotely
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("WIFI NOT AVAILABLE");
  }
  else
  {
    bool sent_ = sendDataToServer(data, REMOTE_BACKEND_URL);
    Serial.println(sent_ ? "DATA SENT TO REMOTE SERVER" : "UNABLE TO REACH REMOTE SERVER");
  }

  // Sending locally
  if (WiFi.softAPIP().toString() == "0.0.0.0")
  {
    Serial.println("AP NOT AVAILABLE");
  }
  else
  {
    bool sent = sendDataToServer(data, LOCAL_BACKEND_URL);
    Serial.println(sent ? "DATA SENT TO LOCAL SERVER" : "UNABLE TO REACH LOCAL SERVER");
  }
  ESP.wdtFeed();
}