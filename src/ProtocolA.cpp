#include <string.h>
#include "ProtocolA.h"

/**
 * Frame constructor
 * 
 * @param: data to populate frame payload 
 * @param: length of data
 * @param: type i.e. SOH
 */
ProtocolA::ProtocolA(uint8_t data[], uint16_t length, uint8_t type)
{
    this->prepareFrame(PROTA_BASE_FRAME_LENGTH + length);
    this->setHeader(type);
    this->setLength(length);
    this->setData(data, length); 
    this->setCrc();
    this->setFooter(PROTA_ETX);
}

/**
 * Frame constructor
 * 
 * @param: raw frame
 * @param: length of supplied raw frame
 */
ProtocolA::ProtocolA(uint8_t frame[], uint16_t frameLength)
{
    this->prepareFrame(frameLength);
    memcpy(this->frame, frame, frameLength);
}

/**
 * Base command frame constructor
 * 
 * @param: command code
 */
ProtocolA::ProtocolA(uint8_t command)
{
    this->prepareFrame(PROTA_BASE_COMMAND_FRAME_LENGTH);
    this->setHeader(PROTA_SOH);
    this->setLength(0x01);
    this->setCommand(command);
    this->setCrc();
    this->setFooter(PROTA_ETX);
}

/**
 * Command frame constructor with data
 * 
 * @param: command code
 * @param: data array
 * @param: length of data array
 */
ProtocolA::ProtocolA(uint8_t command, uint8_t data[], uint8_t dataLength)
{
    uint8_t payload[dataLength + 1];
    payload[0] = command;
    memcpy(&payload[1], data, dataLength);
    ProtocolA(payload, dataLength + 1, PROTA_SOH);
}

/**
 * Destructor
 */
ProtocolA::~ProtocolA()
{
    delete[] this->frame;
}

/**
 * Create raw frame array
 * 
 * @param: requested size
 */
void ProtocolA::prepareFrame(uint16_t frameLength)
{
    this->frame = new uint8_t[frameLength];
    this->frameLength = frameLength;
}

/**
 * Get frame header
 * 
 * @return: header byte
 */
uint8_t ProtocolA::getHeader()
{
    return this->frame[0];
}

/**
 * Set frame header
 * 
 * @param: header byte
 */
void ProtocolA::setHeader(uint8_t header)
{
    this->frame[0] = header;
}

/**
 * Get frame length
 * 
 * @return: frame length
 */
uint8_t ProtocolA::getLength()
{
    return this->frame[1];
}

/**
 * Set frame length
 * 
 * @param: frame length
 */
void ProtocolA::setLength(uint8_t length)
{
    this->frame[1] = length;
}

/**
 * Set command
 * 
 * @param: command byte
 */
void ProtocolA::setCommand(uint8_t command)
{
    this->frame[2] = command;
}

/**
 * Set frame data/payload
 * 
 * @param: data array
 * @param: array length
 */
void ProtocolA::setData(uint8_t data[], uint16_t length)
{
    for (int i=0; i<length; i++)
    {
        this->frame[2 + i] = data[i];
    }
}

/**
 * Get status byte
 */
uint8_t ProtocolA::getStatus()
{
    return this->frame[2];
}

/**
 * Set frame footer
 * 
 * @param: footer byte
 */
void ProtocolA::setFooter(uint8_t footer)
{
    this->frame[this->frameLength - 1] = footer;
}

/**
 * Calculate checksum
 */
uint8_t ProtocolA::calculateCrc()
{
    uint8_t csum = 0;
    for (int i=1; i<this->frameLength-2; i++)
    {
        csum -= this->frame[i] & 0xff;
    }
    return csum;
}

/**
 * Set checksum value
 */
void ProtocolA::setCrc()
{
    this->frame[this->frameLength - 2] = this->calculateCrc();
}

/**
 * Verify checksum value
 */
bool ProtocolA::checkCrc()
{
    return this->frame[this->frameLength - 2] == this->calculateCrc();
}

/**
 * Get frame bytes
 */
uint8_t* ProtocolA::getFrame()
{
    return this->frame;
}

/**
 * Get frame bytes length
 */
uint16_t ProtocolA::getFrameLength()
{
    return this->frameLength;
}
