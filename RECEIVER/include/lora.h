#ifndef _LORA_H_
#define _LORA_H_

#include <SPI.h>  // Required for SPI communication
#include <LoRa.h> // LoRa library for Arduino

// Define LoRa module pins
#define SS_PIN 15  // Slave Select pin
#define RST_PIN -1 // Reset pin (not used in this setup)
#define DIO0_PIN 5 // DIO0 pin (used for receive callback)

// Define LoRa frequency (868.1 MHz for Europe)
#define LORA_FREQUENCY 868.1E6 // Frequency in Hz

#define GET_ONE_GAS "AIR_VIGIL_E:::1::TLN"
#define GET_ALL_GAS "AIR_VIGIL_E:::2"
#define GET_TEMP_AND_HUM "AIR_VIGIL_E:::3"
#define GET_POSITION "AIR_VIGIL_E:::4"
#define GET_DATE "AIR_VIGIL_E:::5"
#define GET_POSITION_AND_DATE "AIR_VIGIL_E:::6"
#define GET_AUTO_SEND "AIR_VIGIL_E:::7"
#define ENABLE_AUTO_SEND "AIR_VIGIL_E:::7::1"
#define DISABLE_AUTO_SEND "AIR_VIGIL_E:::7::0"
#define GET_DELAY_BETWEEN_DATA "AIR_VIGIL_E:::8"
#define SET_DELAY_BETWEEN_DATA "AIR_VIGIL_E:::8::5000"
#define GET_DATA_FOR_BACKEND "AIR_VIGIL_E:::9"

void initLoRa();
void receiveMessage(String *messageContainer);
void sendMessage(String message);
void receiveMessage();
String getData();

#endif