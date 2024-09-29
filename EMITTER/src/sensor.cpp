#include "sensor.h"

MQUnifiedsensor sensor(board, voltage, adc_resolution, sensor_pin, sensorType);

String GAS_ORDER[] = {"CO", "AL", "CO2", "TLN", "NH4", "ACT"};

float calibrateToGetR0();

void initializeMQ()
{
    Serial.println("INITIALIZING MQ135");

    pinMode(sensor_pin, INPUT);

    sensor.setRegressionMethod(1);

    sensor.init();

    float R0 = calibrateToGetR0();

    sensor.setR0(R0);

    Serial.println(" DONE");
}

float calibrateToGetR0()
{
    float _RO = 0;

    for (int i = 1; i <= 10; i++)
    {
        sensor.update(); // Read sensor_pin to get data
        _RO += sensor.calibrate(clean_air_ratio);
        Serial.print(".");
    }

    if (isinf(_RO))
    {
        Serial.println("GOT INFINITE R0 CHECK FOR OPEN CIRCUIT");
        Serial.println("PAUSED IN SETUP");
        while (1)
            ;
    }

    if (_RO == 0)
    {
        Serial.println("GOT 0 FOR R0 CHECK FOR SENSOR_PIN SHORT TO GROUND");
        Serial.println("PAUSED IN SETUP");
        while (1)
            ;
    }

    return _RO;
}

float readOneGas(String gas)
{
    float reading;

    sensor.update();

    if (gas.startsWith("CO"))
    {
        sensor.setA(605.18);
        sensor.setB(-3.937);
    }
    else if (gas.startsWith("AL"))
    {
        sensor.setA(77.255);
        sensor.setB(-3.18);
    }
    else if (gas.startsWith("CO2"))
    {
        sensor.setA(110.47);
        sensor.setB(-2.862);
    }
    else if (gas.startsWith("TLN"))
    {
        sensor.setA(44.947);
        sensor.setB(-3.445);
    }
    else if (gas.startsWith("NH4"))
    {
        sensor.setA(102.2);
        sensor.setB(-2.473);
    }
    else if (gas.startsWith("ACT"))
    {
        sensor.setA(34.668);
        sensor.setB(-3.369);
    }

    else
    {
        Serial.println("UNKNOWN GAS");
        return float(INFINITY);
    }

    reading = sensor.readSensor();

    return reading;
}

void readAllGas(float *readings)
{

    sensor.update();

    // FOR CO
    sensor.setA(605.18);
    sensor.setB(-3.937);
    readings[0] = sensor.readSensor();

    // FOR ALCOHOL
    sensor.setA(77.255);
    sensor.setB(-3.18);
    readings[1] = sensor.readSensor();

    // FOR CO2
    sensor.setA(110.47);
    sensor.setB(-2.862);
    readings[2] = sensor.readSensor();

    // FOR TOLUEN
    sensor.setA(44.947);
    sensor.setB(-3.445);
    readings[3] = sensor.readSensor();

    // FOR NH4
    sensor.setA(102.2);
    sensor.setB(-2.473);
    readings[4] = sensor.readSensor();

    // FOR ACETON
    sensor.setA(34.668);
    sensor.setB(-3.369);
    readings[5] = sensor.readSensor();
}

String getAllGasForLoRa()
{
    float readings[6];

    readAllGas(readings);

    String data = "";

    for (int i = 0; i < 6; i++)
    {
        data.concat(GAS_ORDER[i]);
        data.concat(" ");
        data.concat(readings[i]);
        if (i != 5)
            data.concat(";");
    }

    return data;
}

String getOneGasForLoRa(String gas)
{
    String data = "";
    data.concat(gas);
    data.concat(" ");
    data.concat(readOneGas(gas));
    return data;
}