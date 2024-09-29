#include "dht.h"

DHT dhtSensor(DHT_PIN, DHT_TYPE);

void readDhtToSerial()
{
    float t = dhtSensor.readTemperature();
    float h = dhtSensor.readHumidity();
    Serial.print(t);
    Serial.print(" °C | ");
    Serial.print(h);
    Serial.print(" %RH \n");
}

void readDht(float *t, float *h)
{
    *t = dhtSensor.readTemperature();
    *h = dhtSensor.readHumidity();
}

String getTAndHForLora()
{
    String data = "";
    float t, h;
    readDht(&t, &h);
    data.concat(t);
    data.concat(";");
    data.concat(h);
    return data;
}