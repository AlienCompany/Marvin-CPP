/* @author  Vogel Hugues (HVogel)
 * @date    4/7/2018
 * @version 1.0
 *
 * MAX7219 DOC: https://www.sparkfun.com/datasheets/Components/General/COM-09622-MAX7219-MAX7221.pdf
 *
 * @section DESCRIPTION
 * Contrôler un MAX7219
 */

#ifndef UNTITLED_MAX7219_H
#define UNTITLED_MAX7219_H

#include <Arduino.h>

enum MAX7219_ADDRESS {
    ADDR_NO_OP = 0x00,
    ADDR_DIGIT_0 = 0x01,
    ADDR_DIGIT_1 = 0x02,
    ADDR_DIGIT_2 = 0x03,
    ADDR_DIGIT_3 = 0x04,
    ADDR_DIGIT_4 = 0x05,
    ADDR_DIGIT_5 = 0x06,
    ADDR_DIGIT_6 = 0x07,
    ADDR_DIGIT_7 = 0x08,
    ADDR_DECODE_MODE = 0x09,
    ADDR_INTENSITY = 0x0A,
    ADDR_SCAN_LIMIT = 0x0B,
    ADDR_SHUTDOWN = 0x0C,        // power-down mode = 0 / normal mode = 1

    ADDR_DISPLAY_TEST = 0x0F
};

enum MAX7219_TEST {
    NORMAL_OPERATION = 0x00,
    DISPLAY_TEST_MODE = 0x01
};


class MAX7219 {
private:

    const uint8_t PIN_CLK;
    const uint8_t PIN_CS;
    const uint8_t PIN_DIN;

    bool isInit = false;
    bool shutdown = false;
    uint8_t brightness = 0x03;
    MAX7219_TEST testMode = NORMAL_OPERATION;
    uint8_t decodeMode = 0x00;
    uint8_t scanLimit = 0x07;

    /*
     * Envoi sucsessivement les 8 bytes
     */
    void writeByte(uint8_t DATA);

    void writeDecodeMode();

    void writeBrightness();

    void writeScanLimit();

    void writeShutDown();

    void writeTestMode();

public:
    MAX7219(uint8_t PIN_CLK, uint8_t PIN_CS, uint8_t PIN_DIN);

    void init();

    void write(MAX7219_ADDRESS address, uint8_t data);

    void writeDigit(uint8_t digitNumber, uint8_t dataLigne);

    // data_char must be array with 8 byte
    void writeCharacter(const uint8_t *data_char);

    bool isShutdown() const;

    void setShutdown(bool isShutdown);

    uint8_t getBrightness() const;

    void setBrightness(uint8_t brightness);

    MAX7219_TEST getTestMode() const;

    void setTestMode(MAX7219_TEST testMode);

    uint8_t getDecodeMode() const;

    void setDecodeMode(uint8_t decodeMode);

    uint8_t getScanLimit() const;

    void setScanLimit(uint8_t scanLimit);

    virtual ~ MAX7219() = default;
};


#endif //UNTITLED_MAX7219_H
