#ifndef _DHT_SENSOR_

#define _DHT_SENSOR_

#include <DHT.h>

#define DHT_PIN 2
#define DHT_TYPE DHT11

extern DHT dhtSensor;

void readDhtToSerial();

void readDht(float *t, float *h);

String getTAndHForLora();

#endif