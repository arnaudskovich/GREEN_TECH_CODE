#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 20, TXPin = 21;
static const uint32_t GPSBaud = 9600;

extern TinyGPSPlus gps;
extern SoftwareSerial ss;

void initGPS();
String getGPSDateForLoRa();
String getGPSPositionForLoRa();
