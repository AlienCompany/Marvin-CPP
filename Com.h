//
// Created by hugues on 11/06/2018.
//
#include <Arduino.h>

#ifndef TEST2_COM_H
#define TEST2_COM_H

enum CommandesId : uint8_t {


    TEST_COMMANDE_ALLUMER_LED = 0xF1, // data = time ms
    TEST_COMMANDE_RESAVE = 0xF2, // data = time ms
};

struct Commande{
    CommandesId id;
    uint32_t data;
};

struct Commande_16{
    CommandesId id;
    uint16_t data0;
    uint16_t data1;
};

struct Commande_8{
    CommandesId id;
    uint8_t data0;
    uint8_t data1;
    uint8_t data2;
    uint8_t data3;
};

void onResave(Commande &commande);

void checkResave();

void sendCommande(CommandesId id, uint32_t data);
void sendCommande(CommandesId id, uint16_t data0, uint16_t data1);
void sendCommande(CommandesId id, uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3);
void sendCommandeByte(uint8_t *c, uint8_t length);

Commande_16 to_16(Commande &commande);
Commande_8 to_8(Commande &commande);


#endif //TEST2_COM_H
