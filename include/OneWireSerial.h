#ifndef ONEWIRESERIAL_H
#define ONEWIRESERIAL_H

#define OWS_BAUD_RATE 115200
#define OWS_WAIT_SHORT 10
#define OWS_WAIT_LONG 100
#define OWS_SINGLE_WIRE_UART 0x3A

#include <arduino.h>

/******************************************************************************
* Definitions
******************************************************************************/

class OneWireSerial : public Stream 
{
    private:
        uint16_t tool0Pin;
        uint16_t resetPin;
        HardwareSerial serial;

    public:
        OneWireSerial(uint16_t tool0Pin, uint16_t resetPin, HardwareSerial serial);
        virtual ~OneWireSerial();

        void reset();
        void begin(uint8_t mode = OWS_SINGLE_WIRE_UART);
        void end();
        virtual size_t write(uint8_t byte);
        int read();

        virtual int available();
        virtual void flush();
        virtual int peek();

        using Print::write;
};

#endif // ONEWIRESERIAL_H