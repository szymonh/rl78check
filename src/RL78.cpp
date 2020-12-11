#include <Arduino.h>

#include "OneWireSerial.h"
#include "ProtocolA.h"
#include "RL78.h"
#include "util.h"

/**
 * Main constructor
 * 
 * @param: pointer to OneWireSerial instance
 */
RL78::RL78(OneWireSerial *serial)
{
    this->serial = serial;
}

/**
 * Destructor
 */
RL78::~RL78()
{
    this->end();
}

/**
 * Prepare communication with the MCU
 * 
 * @returns: status flag
 */
bool RL78::begin()
{
    this->serial->begin();
    return this->setBaudRate() == PROTA_STAT_ACK;
}

/**
 * Clean-up
 */
void RL78::end()
{
    this->serial->end();
}

/**
 * Build and execute a Protocol A command
 * 
 * @param: command code
 * @returns: status byte
 */
uint8_t RL78::execCommand(uint8_t command)
{
    ProtocolA cmd = ProtocolA(command);
    this->serial->write(cmd.getFrame(), cmd.getFrameLength());

    uint8_t buff[5];
    this->serial->readBytes(buff, sizeof(buff));

    ProtocolA resp = ProtocolA(buff, sizeof(buff));
    if (!resp.checkCrc())
    {
        return 0xff;
    }

    return resp.getStatus();
}

/**
 * Build and execute a Protocol A command
 * In case of success also collect following data frame
 * 
 * @param: command code
 * @param: byffer for data frame contents
 * @param: length of the buffer
 * @return: status byte
 */
uint8_t RL78::execCommand(uint8_t command, uint8_t buffer[], uint8_t bufferLength)
{
    uint8_t status = this->execCommand(command);

    if (status == PROTA_STAT_ACK)
    {
        uint8_t frameBuffer[bufferLength + 4];
        this->serial->readBytes(frameBuffer, sizeof(frameBuffer));
        memcpy(buffer, &frameBuffer[2], bufferLength);
    }

    return status;
}

/**
 * Execute MCU reset command
 * 
 * @returns: status byte
 */
uint8_t RL78::reset()
{
    return this->execCommand(PROTA_CMD_RESET);
}

/**
 * Set serial communication baud rate to 115200 bps
 * 
 * @returns: status byte
 */
uint8_t RL78::setBaudRate()
{
    uint8_t baudData[] = {PROTA_CMD_BAUD_RATE_SET, 0x00, 0x15};
    ProtocolA setBaudRateCmd = ProtocolA(baudData, sizeof(baudData), PROTA_SOH);
    this->serial->write(setBaudRateCmd.getFrame(), setBaudRateCmd.getFrameLength());

    uint8_t buffer[7];
    memset(buffer, 0, sizeof(buffer));
    this->serial->readBytes(buffer, sizeof(buffer));
    return buffer[2];
}

/**
 * Get silicon signature command
 * 
 * @param: buffer for result data
 * @param: buffer size
 * @returns: status byte
 */
uint8_t RL78::getSiliconSignature(uint8_t buffer[], uint8_t bufferLength)
{
    return this->execCommand(PROTA_CMD_SILICON_SIGNATURE, buffer, bufferLength);
}

/**
 * Get security
 * 
 * @param: buffer for result data
 * @param: buffer size
 * @returns: status byte
 */
uint8_t RL78::getSecurity(uint8_t buffer[], uint8_t bufferLength)
{
    return this->execCommand(PROTA_CMD_GET_SECURITY, buffer, bufferLength);
}