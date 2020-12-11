#include <Arduino.h>
#include "util.h"

/**
 * Print supplied byte array contents as hex
 * 
 * @param: byte array to print
 * @param: size of input byte array
 * @param: optional prefix for text line
 * @param: optional suffix with a new line
 */
void prettyPrint(uint8_t byteArray[], uint16_t byteArraySize, String prefix, bool addNewLine)
{
    char buff[4];
    
    Serial.print(prefix);

    for (int i=0; i<byteArraySize; i++)
    {
        sprintf(buff, "%02x ", byteArray[i]);
        Serial.print(buff);
    }

    if (addNewLine)
    {
        Serial.println();
    }
}