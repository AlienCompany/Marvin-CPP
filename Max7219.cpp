//
// Created by hvogel on 7/5/18.
//

#include "Max7219.h"

// PRIVATE

void MAX7219::writeByte(uint8_t DATA) {
    for (uint8_t i = 0x80; i; i >>= 1) {
        // fist time    i = 1000 0000
        // second time  i = 0100 0000
        // ...
        // last time    i = 0000 0001
        digitalWrite(PIN_CLK, LOW);
        digitalWrite(PIN_DIN, DATA & i); // Extracting a bit data
        digitalWrite(PIN_CLK, HIGH);
    }
}

void MAX7219::writeDecodeMode() {
    write(ADDR_DECODE_MODE, decodeMode);
}

void MAX7219::writeBrightness() {
    write(ADDR_INTENSITY, brightness);
}

void MAX7219::writeScanLimit() {
    write(ADDR_SCAN_LIMIT, scanLimit);
}

void MAX7219::writeShutDown() {
    write(ADDR_SHUTDOWN, shutdown ? (char) 0x00 : (char) 0x01);
}

void MAX7219::writeTestMode() {
    write(ADDR_DISPLAY_TEST, testMode);
}


// PUBLIC

MAX7219::MAX7219(uint8_t PIN_CLK, uint8_t PIN_CS, uint8_t PIN_DIN) : PIN_CLK(PIN_CLK), PIN_CS(PIN_CS), PIN_DIN(PIN_DIN) {

}

void MAX7219::init() {
    pinMode(PIN_CLK, OUTPUT);
    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_DIN, OUTPUT);
    delay(50);
    writeDecodeMode();
    writeBrightness();
    writeScanLimit();
    writeShutDown();
    writeTestMode();
    isInit = true;
}

void MAX7219::write(MAX7219_ADDRESS address, uint8_t data) {
    digitalWrite(PIN_CS, LOW);
    writeByte(address);
    writeByte(data);
    digitalWrite(PIN_CS, HIGH);
}

void MAX7219::writeDigit(const uint8_t digitNumber, const uint8_t dataLigne) {
    write((MAX7219_ADDRESS) (digitNumber + 1), dataLigne);
}

void MAX7219::writeCharacter(const uint8_t *data_char) {
    for (uint8_t i = 0; i < 8; i++) {
        writeDigit(i, data_char[i]);
    }
}

bool MAX7219::isShutdown() const {
    return shutdown;
}


void MAX7219::setShutdown(bool isShutdown) {
    MAX7219::shutdown = isShutdown;
    if (isInit) writeShutDown();
}

uint8_t MAX7219::getBrightness() const {
    return brightness;
}

void MAX7219::setBrightness(uint8_t brightness) {
    MAX7219::brightness = brightness;
    if(isInit) writeBrightness();
}

MAX7219_TEST MAX7219::getTestMode() const {
    return testMode;
}

void MAX7219::setTestMode(MAX7219_TEST testMode) {
    MAX7219::testMode = testMode;
    if(isInit) writeTestMode();
}

uint8_t MAX7219::getDecodeMode() const {
    return decodeMode;
}

void MAX7219::setDecodeMode(uint8_t decodeMode) {
    MAX7219::decodeMode = decodeMode;
    if(isInit) writeDecodeMode();
}

uint8_t MAX7219::getScanLimit() const {
    return scanLimit;
}

void MAX7219::setScanLimit(uint8_t scanLimit) {
    MAX7219::scanLimit = scanLimit;
    if(isInit) writeScanLimit();
}
