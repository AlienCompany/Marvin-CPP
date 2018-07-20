//
// Created by hugues on 11/06/2018.
//
#include <Arduino.h>
#include "ArrayAutoSize.h"

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

    COMMANDE_DEBUG_SCOP = 0xD0,
    COMMANDE_DEBUG_DEL_SCOP = 0xD1,
    COMMANDE_DEBUG_ADD_VAR = 0xD2,
    COMMANDE_DEBUG_DEL_VAR = 0xD3,
    COMMANDE_DEBUG_ONCHANGE_VAR = 0xD4,
    COMMANDE_DEBUG_LOG = 0xD5,

    COMMANDE_DEBUG_SET_VAR = 0xE5,
    COMMANDE_DEBUG_PAUSE = 0xE1,
    COMMANDE_DEBUG_PLAY = 0xE0,
    COMMANDE_DEBUG_STOPTIME = 0xE0,
};
enum d_types: uint8_t{
    UINT64_T = 0x01,
    UINT32_T = 0x02,
    UINT16_T = 0x03,
    UINT8_T = 0x04,
    INT64_T = 0x05,
    INT32_T = 0x06,
    INT16_T = 0x07,
    INT8_T = 0x08,
    CHAR = 0x09,
    DOUBLE = 0x0A,
    FLOAT = 0x0B,
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
struct d_var{
    String name;
    d_types types;
    void* varPtr;
};

uint16_t nbScope = 0;

struct d_scope{
    d_scope(String name){
        d_scope::name = name;
        id = nbScope++;
        vars = ArrayAutoSize<d_var>();
    }
    d_scope(){
        d_scope("");
    }
    uint16_t id;
    String name;
    ArrayAutoSize<d_var> vars;
};

d_scope d_globalScope = d_scope();
ArrayAutoSize<d_scope*> d_scopes = ArrayAutoSize<d_scope*>();

void onReceive(Commande &commande);

void checkReceive();

void sendCommande(CommandesId id, uint32_t data = 0x00);

void sendCommande(CommandesId id, uint16_t data0, uint16_t data1);

void sendCommande(CommandesId id, uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3);

void sendCommandeByte(uint8_t *c, uint8_t length);

Commande_16 to_16(Commande &commande);

Commande_8 to_8(Commande &commande);

void d_sendDebug(CommandesId id);
void d_sendDebug(CommandesId id, String s0);
void d_sendDebug(CommandesId id, String s0, String s1);
void d_sendDebug(CommandesId id, String s0, String s1, String s2);
void d_sendDebug(CommandesId id, String s0, String s1, String s2, String s3);

void d_newScop(String name);
int32_t d_getLastScope(String name, d_scope* &res);

void log(String type, String fileName, String functionName, String msg);

void d_delScop(String name);
void d_addVar(String scop, String name, d_types type, void* valuePtr, String value);
void d_addVar(String scop, String name, uint64_t &value);
void d_addVar(String scop, String name, uint32_t &value);
void d_addVar(String scop, String name, uint16_t &value);
void d_addVar(String scop, String name, uint8_t &value);
void d_addVar(String scop, String name, int64_t &value);
void d_addVar(String scop, String name, int32_t &value);
void d_addVar(String scop, String name, int16_t &value);
void d_addVar(String scop, String name, int8_t &value);
void d_addVar(String scop, String name, float &value);
void d_addVar(String scop, String name, double &value);
void d_addVar(String scop, String name, char &value);

#endif //TEST2_COM_H
