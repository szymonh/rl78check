#include <OneWireSerial.h>

/**
 * OneWireSerial constructor
 * 
 * @param: Tool 0 pin (should match HW Serial TX pin)
 * @param: Reset pin
 * @param: Hardware serial instance
 */
OneWireSerial::OneWireSerial(uint16_t tool0Pin_, uint16_t resetPin_, HardwareSerial serial_) : serial{serial_}
{
    this->tool0Pin = tool0Pin_;
    this->resetPin = resetPin_;
}

/**
 * OneWireSerial destructor
 */
OneWireSerial::~OneWireSerial()
{
    end();
}

/**
 * Prepare one wire serial interface
 */
void OneWireSerial::begin(uint8_t mode)
{
    this->reset();
    this->write(mode);
    delay(OWS_WAIT_SHORT);
}

/**
 * Clean-up
 */
void OneWireSerial::end()
{
    this->serial.end();
    pinMode(this->tool0Pin, INPUT_PULLUP);
    pinMode(this->resetPin, INPUT_PULLUP);
}

/**
 * Read a single byte
 * 
 * @returns: byte read or error code
 */
int OneWireSerial::read()
{
    return this->serial.read();
}

/**
 * Write a single byte
 * 
 * @param: data byte
 * @retuns: error code
 */
size_t OneWireSerial::write(uint8_t byte)
{
    return this->serial.write(byte);
}

/**
 * Check if data is available
 * 
 * @returns: status
 */
int OneWireSerial::available()
{
    return this->serial.available();
}

/**
 * Flush data
 */
void OneWireSerial::flush()
{
    this->serial.flush();
}

/**
 * Peek
 */
int OneWireSerial::peek()
{
    return this->serial.peek();
}

/**
 * Perform one wire serial reset
 */
void OneWireSerial::reset()
{
    pinMode(this->resetPin, OUTPUT);
    pinMode(this->tool0Pin, OUTPUT);

    digitalWrite(this->resetPin, LOW);
    digitalWrite(this->tool0Pin, LOW);
    delay(OWS_WAIT_LONG);

    digitalWrite(this->resetPin, HIGH);
    delay(OWS_WAIT_SHORT);

    digitalWrite(this->tool0Pin, HIGH);
    delay(OWS_WAIT_SHORT);

    this->serial.setHalfDuplex();
    this->serial.begin(OWS_BAUD_RATE);
}