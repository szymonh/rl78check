#ifndef PROTOCOLA_H
#define PROTOCOLA_H

#include <stdint.h>

#define PROTA_SOH 0x01
#define PROTA_STX 0x02
#define PROTA_ETX 0x03
#define PROTA_ETB 0x17

#define PROTA_STAT_COMMAND_NUMBER_ERROR 0x04
#define PROTA_STAT_PARAMETER_ERROR 0x05
#define PROTA_STAT_ACK 0x06
#define PROTA_STAT_PROTECT_ERROR 0x10
#define PROTA_STAT_NACK 0x15 

#define PROTA_CMD_RESET 0x00
#define PROTA_CMD_BAUD_RATE_SET 0x9A
#define PROTA_CMD_SILICON_SIGNATURE 0xC0
#define PROTA_CMD_GET_SECURITY 0xA1

#define PROTA_BASE_FRAME_LENGTH 0x04
#define PROTA_BASE_COMMAND_FRAME_LENGTH 0x05

/******************************************************************************
* Definitions
******************************************************************************/

class ProtocolA
{
    protected:        
        uint8_t *frame;
        uint16_t frameLength;

        void prepareFrame(uint16_t frameLength);
        uint8_t calculateCrc();

        uint8_t getHeader();

        void setFooter(uint8_t);

    public:
        ProtocolA(uint8_t payload[], uint16_t payloadLength, uint8_t type);
        ProtocolA(uint8_t frame[], uint16_t length);
        ProtocolA(uint8_t command);
        ProtocolA(uint8_t command, uint8_t data[], uint8_t dataLength);
        virtual ~ProtocolA();

        bool checkCrc();
        void setCrc();

        uint8_t* getFrame();
        uint16_t getFrameLength();

        uint8_t getData();
        uint8_t getStatus();
        uint8_t getLength();

        void setHeader(uint8_t);
        void setData(uint8_t[], uint16_t);
        void setCommand(uint8_t);
        void setLength(uint8_t);
};

#endif // PROTOCOLA_H