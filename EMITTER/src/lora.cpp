#include "lora.h"

void initLoRa()
{
    Serial.println("LoRa Bidirectional Communication (868.1 MHz)");

    // Configure LoRa transceiver module
    LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);

    // Initialize LoRa
    if (!LoRa.begin(LORA_FREQUENCY))
    {
        Serial.println("LoRa initialization failed. Check your connections.");
        while (1)
            ; // If failed, do nothing
    }
    // Set LoRa parameters
    LoRa.setSpreadingFactor(12);     // Set spreading factor (6-12). Higher SF increases range but decreases data rate
    LoRa.setSyncWord((int)14092024); // Set sync word to ensure communication only between nodes with the same sync word

    Serial.println("LoRa initialization successful.");
}

// Function to send a LoRa message
void sendMessage(String message)
{
    Serial.print("Sending message: ");
    Serial.println(message);

    LoRa.beginPacket();  // Start the LoRa packet
    LoRa.print(message); // Add the message to the packet
    LoRa.endPacket();    // Finish the packet and send it
}

// Function to receive and process a LoRa message
void receiveMessage(String *messageContainer)
{
    String message = ""; // Variable to store the received message

    // Read the packet
    while (LoRa.available())
    {
        message += (char)LoRa.read(); // Read each byte and add it to the message string
    }

    // Print the received message
    Serial.print("Received message: ");
    Serial.println(message);

    // Print the RSSI (Received Signal Strength Indicator)
    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi()); // Get and print the RSSI of the received packet
    *messageContainer = message;
}

bool airVigilCommandParser(String message, int *action, String *data)
{
    // A message should look like AIR_VIGIL_E:::ACTION?(::DATA)
    // DATA SHOULD BE PRESENT ONLY IF SETTING
    int parseStartIndex = message.indexOf(":::");

    if (parseStartIndex == -1)
        return false;

    // ADDING ::: OFFSET
    parseStartIndex += 3;

    int actionAndDataSeperatorIndex = message.indexOf("::", parseStartIndex);
    // IF NO DATA PRESENT
    if (actionAndDataSeperatorIndex == -1)
    {
        *action = message.substring(parseStartIndex).toInt();
        *data = "";
    }
    else
    {

        *action = message.substring(parseStartIndex, actionAndDataSeperatorIndex).toInt();
        // ADDING :: OFFSET
        actionAndDataSeperatorIndex += 2;
        *data = message.substring(actionAndDataSeperatorIndex);
    }

    return true;
}