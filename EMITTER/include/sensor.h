#ifndef _SENSOR_H

#define _SENSOR_H

#include <MQUnifiedsensor.h>

#define board "Arduino UNO" // The board name
#define voltage 3.3         // change to match the voltage supplied to the sensor
#define sensor_pin A0       // analog pin to use for data reading from sensor
#define adc_resolution 10   // The resolution of the board  analog to digital converter
#define sensorType "MQ-135"
#define clean_air_ratio 3.6 // used to calibrate the sensor

extern String GAS_ORDER[];

void initializeMQ();

float readOneGas(String gas);

void readAllGas(float *readings);

String getAllGasForLoRa();

String getOneGasForLoRa(String gas);

#endif