#include <SPI.h>
#include <LoRa.h>

// Define LoRa module pins
#define SS_PIN 10  // Slave Select pin
#define RST_PIN 9  // Reset pin
#define DIO0_PIN 7 // DIO0 pin (used for receive callback)

// Define LoRa frequency (868.1 MHz for Europe)
#define LORA_FREQUENCY 868.1E6 // Frequency in Hz

// PIN TO USE AS INTERRUPT WHEN A MESSAGE IS RECEIVED AND IS FOR US
#define notifyPin 3 // 3 on both (receiver and emitter) by default

// TODO clearly define possible actions
#define GET_ONE_GAS 1
#define GET_ALL_GAS 2
#define GET_TEMP_AND_HUM 3
#define GET_POS 4
#define GET_DATE 5
#define GET_POS_AND_DATE 6
#define AUTO_SEND 7
#define DELAY_BETWEEN_DATA 8
#define GET_FOR_BACKEND 9

/*
L'emetteur doit pouvoir:
- recevoir les commandes
- interpréter les commandes
- préparer les réponses
- les envoyer
- automatiser l'envoi
*/

void initLoRa();
void receiveMessage(String *messageContainer);
void sendMessage(String message);
bool airVigilCommandParser(String message, int *action, String *data);
void handleAction();