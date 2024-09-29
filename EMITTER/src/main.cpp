#include <Arduino.h>
#include "lora.h"
#include "gps.h"
#include "dht.h"
#include "sensor.h"

#define minDelayForData 100

// Variables for handling user input
String inputMessage = ""; // Stores the message input by the user
String receiverCommand;
String autoMessage = "";
volatile bool messageReady = false; // Flag to indicate when a complete message is ready to send
volatile bool autoSend = false;
volatile unsigned int delayBetweenData = 1000;

// LOOP CHRONO
long loopStart, loopEnd;

void setup()
{
    // Initialize serial communication
    Serial.begin(9600);
    while (!Serial)
        ; // Wait for serial port to connect. Needed for native USB port only
    initLoRa();
    initGPS();
    dhtSensor.begin();
    initializeMQ();
}

void loop()
{
    // If a complete message is ready, send it
    if (messageReady)
    {
        sendMessage(inputMessage); // Call function to send the message
        inputMessage = "";         // Clear the input message buffer
        messageReady = false;      // Reset the message ready flag
    }

    // Check for any incoming LoRa data
    int packetSize = LoRa.parsePacket();

    // If a packet is received
    if (packetSize)
    {
        receiveMessage(&receiverCommand); // Call function to handle the received message
        handleAction();
        receiverCommand = "";
    }
}

void handleAction()
{
    String messageToSend = "AIR_VIGIL_R:::";
    String cmd = receiverCommand;
    int action;
    String actionData;
    // TRY TO PARSE RECEIVED DATA
    if (airVigilCommandParser(receiverCommand, &action, &actionData))
    {
        actionData.trim();
        messageToSend.concat(action);
        messageToSend.concat(":::");

        switch (action)
        {
        case GET_ONE_GAS:
            messageToSend.concat(actionData.length() == 0 ? "INCORRECT DATA RECEIVED" : getOneGasForLoRa(actionData));
            break;

        case GET_ALL_GAS:
            messageToSend.concat(getAllGasForLoRa());
            break;

        case GET_TEMP_AND_HUM:
            messageToSend.concat(getTAndHForLora());
            break;

        case GET_POS:
            messageToSend.concat(getGPSPositionForLoRa());
            break;

        case GET_DATE:
            messageToSend.concat(getGPSDateForLoRa());
            break;

        case GET_POS_AND_DATE:
            messageToSend.concat(getGPSDateForLoRa());
            messageToSend.concat(";");
            messageToSend.concat(getGPSPositionForLoRa());
            break;

            // case AUTO_SEND:
            //     if (actionData.length() == 0)
            //     {
            //         messageToSend.concat(autoSend);
            //     }
            //     else
            //     {
            //         autoSend = actionData == "1";
            //         messageToSend.concat("DONE");
            //     }

            //     break;

            // case DELAY_BETWEEN_DATA:
            //     int dataIntVersion = max(minDelayForData, actionData.toInt());
            //     if (actionData.length() == 0)
            //     {
            //         messageToSend.concat(delayBetweenData);
            //     }
            //     else
            //     {
            //         delayBetweenData = dataIntVersion;
            //         if (delayBetweenData == minDelayForData)
            //             messageToSend.concat("DELAY SET TO MIN:::");
            //         messageToSend.concat("DONE");
            //     }
            //     break;

        case GET_FOR_BACKEND:
            messageToSend.concat(getAllGasForLoRa());
            messageToSend.concat("::");
            messageToSend.concat(getTAndHForLora());
            messageToSend.concat("::");
            messageToSend.concat(getGPSPositionForLoRa());
            break;

        default:
            messageToSend.concat("INVALID ACTION");
            break;
        }
    }
    else
    {
        Serial.println("PARSE FAILED");
        messageToSend.concat("INCORRECT DATA RECEIVED");
    }

    messageToSend.concat(":::END");

    sendMessage(messageToSend);
}