#include "gps.h"

TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);

void initGPS()
{
    ss.begin(GPSBaud);
    Serial.println("GPS STARTED");
}

// THIS FUNCTION UPDATES GPS INFORMATION
bool updateGPS()
{
    while (ss.available() > 0)
    {
        if (gps.encode(ss.read()))
            return true;
    }

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        Serial.println(F("No GPS detected: check wiring."));
    }

    return false;
}

String getGPSDateForLoRa()
{
    String date = "";

    if (updateGPS() && gps.time.isValid())
    {
        if (gps.time.hour() < 10)
            date.concat(F("0"));
        date.concat(gps.time.hour());
        date.concat(F(":"));
        if (gps.time.minute() < 10)
            date.concat(F("0"));
        date.concat(gps.time.minute());
        date.concat(F(":"));
        if (gps.time.second() < 10)
            date.concat(F("0"));
        date.concat(gps.time.second());
        date.concat(F("."));
        if (gps.time.centisecond() < 10)
            date.concat(F("0"));
        date.concat(gps.time.centisecond());
    }

    else
    {
        date.concat(F("INVALID"));
    }

    return date;
}

String getGPSPositionForLoRa()
{
    String position = "";

    if (updateGPS() && gps.location.isValid())
    {
        position.concat(gps.location.lat());
        position.concat(F(","));
        position.concat(gps.location.lng());
    }

    else
    {
        position.concat(F("INVALID"));
    }

    return position;
}