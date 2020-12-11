#include <Arduino.h>

#include "RL78.h"
#include "OneWireSerial.h"
#include "util.h"

#define PROMPT "Press any key to continue .."

uint16_t TOOL0_PIN = PA9;  // set to Serial TX
uint16_t RESET_PIN = PB15;


OneWireSerial oneWireSerial = OneWireSerial(TOOL0_PIN, RESET_PIN, Serial1);
RL78 rl78 = RL78(&oneWireSerial);

uint8_t ledState = HIGH;

/**
 * Print MCU signature
 */
void printSignature()
{
    Serial.println("Silicon signature");

    uint8_t data[22];
    rl78.getSiliconSignature(data, sizeof(data));

    prettyPrint(&data[0], 3, "DEC: ");
    prettyPrint(&data[3], 10, "DEV: ");
    prettyPrint(&data[13], 3, "CEN: ");
    prettyPrint(&data[16], 3, "DEN: ");
    prettyPrint(&data[19], 3, "VER: ");

    Serial.println();
}

/**
 * Print flash memory security config
 */
void printSecurityConfig()
{
    Serial.println("MCU Security");

    uint8_t data[8];
    rl78.getSecurity(data, sizeof(data));

    prettyPrint(&data[0], 1, "FLG: ");
    prettyPrint(&data[1], 1, "BOT: ");
    prettyPrint(&data[2], 1, "SSL: ");
    prettyPrint(&data[3], 1, "SSH: ");
    prettyPrint(&data[4], 1, "SEL: ");
    prettyPrint(&data[5], 1, "SEH: ");
    Serial.println();

    Serial.println("Security flag properties");
    Serial.println((data[0] & 0x10) ? "\tProgramming enabled" : "\tProgramming disabled");
    Serial.println((data[0] & 0x4)  ? "\tBlock erase enabled" : "\tBlock erase disabled");
    Serial.println((data[0] & 0x2)  ? "\tBoot block cluster rewrite enabled" : "\tBoot block cluster disabled");
    Serial.println((data[0] & 0x1)  ? "\tBoot area exchange flag provided" : "\tBoot area exchange flag not provided");

    Serial.println();
}

/**
 * Arduino setup
 */
void setup() {
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(TOOL0_PIN, OUTPUT);
    pinMode(RESET_PIN, OUTPUT);
    digitalWrite(TOOL0_PIN, HIGH);
    digitalWrite(RESET_PIN, HIGH);

    Serial.println(PROMPT);
}

/**
 * Arduino loop
 */
void loop() {
    if (Serial.available())
    {
        ledState = ledState == HIGH ? LOW : HIGH;
        digitalWrite(LED_BUILTIN, ledState);

        if (rl78.begin())
        {
            printSignature();
            printSecurityConfig();
            rl78.end();
        }
        else
        {
            Serial.println("Failed to communicate with target");
            Serial.println("Please verify connections and retry");
        }

        while (Serial.available())
        {
            Serial.read();
        }

        Serial.println(PROMPT);
    }
}