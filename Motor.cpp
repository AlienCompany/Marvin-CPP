//
// Created by ferna on 05/07/2018.
//

#include "Motor.h"

Motor::Motor(int pin, int offset, int angle) : pin(pin), offset(offset), angle(angle) {
    servo = new Servo();
}

Motor::Motor(int pin, int offset) : Motor(pin, offset, 0){}

Motor::Motor(int pin) : Motor(pin, 0){}

void Motor::init() {
    motorOn();
}

void Motor::motorOff() {
    servo->detach();
    pinMode(pin, INPUT);
}

void Motor::motorOn() {
    servo->attach(pin);
    update();
}

void Motor::setOffset(int offset) {
    Motor::offset = offset;
    update();
}

void Motor::addAngle(int angle) {
    setAngle(Motor::angle + angle);
}

void Motor::setAngle(int angle) {
    Motor::angle = angle;
    update();
}

void Motor::update() {
    if(servo->attached()) {
        servo->write(angle + offset);
    }
}

int Motor::getOffset() const {
    return offset;
}


int Motor::getAngle() const {
    return angle;
}

