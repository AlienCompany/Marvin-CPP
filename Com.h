//
// Created by hugues on 11/06/2018.
//
#include <Arduino.h>

#ifndef TEST2_COM_H
#define TEST2_COM_H

enum CommandesUltraSoundId {
    NEAR_OBJECT = 0x01,
    NO_NEAR_OBJECT = 0x02
};

enum MotorId {
    MOTOR_HIP = 0x01,
    MOTOR_KNEE = 0x02,
    MOTOR_ANKLE = 0x03,
    MOTOR_FOOT = 0x04,
};

enum ButtonId {
    BUTTON_MATRIX = 0x01,
    BUTTON_MOTOR = 0x02,
    BUTTON_MATRIX2 = 0x03
};

enum CommandesId : uint8_t {
    COMMANDE_BUTTON = 0x01, // data is number button
    COMMANDE_LEG = 0x02, // data1 = motorId, data2 = angleMoteur
    COMMANDE_ULTRASON = 0x03,


    TEST_COMMANDE_ALLUMER_LED = 0xF1, // data = time ms
    TEST_COMMANDE_RESAVE = 0xF2,
};

struct Commande {
    CommandesId id;
    uint32_t data;
};

struct Commande_16 {
    CommandesId id;
    uint16_t data0;
    uint16_t data1;
};

struct Commande_8 {
    CommandesId id;
    uint8_t data0;
    uint8_t data1;
    uint8_t data2;
    uint8_t data3;
};

void onReceive(Commande &commande);

void checkReceive();

void sendCommande(CommandesId id, uint32_t data = 0x00);

void sendCommande(CommandesId id, uint16_t data0, uint16_t data1);

void sendCommande(CommandesId id, uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3);

void sendCommandeByte(uint8_t *c, uint8_t length);

Commande_16 to_16(Commande &commande);

Commande_8 to_8(Commande &commande);


#endif //TEST2_COM_H
