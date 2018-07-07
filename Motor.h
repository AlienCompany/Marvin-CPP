//
// Created by ferna on 05/07/2018.
//

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include <Servo.h>

class Motor{
private:
    Servo* servo;
    int pin;
    int offset = 0;
    int angle = 0;

public:

    Motor(int pin, int offset, int angle);
    Motor(int pin, int offset);
    Motor(int pin);

    void init();

    void motorOff();
    void motorOn();

    void addAngle(int angle);

    int getOffset() const;

    void setOffset(int offset);

    int getAngle() const;

    void setAngle(int angle);

    void update();
};


#endif //MOTOR_H
