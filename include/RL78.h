#ifndef RL78_H
#define RL78_H

#include "OneWireSerial.h"

class RL78
{
    private:
        OneWireSerial *serial;

        uint8_t execCommand(uint8_t);
        uint8_t execCommand(uint8_t, uint8_t [], uint8_t);

    public:
        RL78(OneWireSerial*);
        ~RL78();

        uint8_t setBaudRate();
        uint8_t reset();
        
        uint8_t getSiliconSignature(uint8_t [], uint8_t);
        uint8_t getSecurity(uint8_t [], uint8_t);

        bool begin();
        void beginOcd();
        void end();
};

#endif // RL78_H