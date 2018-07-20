//
// Created by hugues on 11/06/2018.
//

#include "Com.h"

bool debugReceive(Commande commande);

void checkReceive(){
    while(Serial.available()){
        Commande commande;
        Serial.readBytes((byte *) &commande, sizeof(Commande));
        if(!debugReceive(commande)) onReceive(commande);
    }
}

bool debugReceive(Commande commande) {

    switch (commande.id){
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
    }
    return false;
}

void sendCommande(CommandesId id, uint32_t data){
    Commande c = {id, data};
    sendCommandeByte((uint8_t *)&c, sizeof(Commande));
}

void sendCommande(CommandesId id, uint16_t data0, uint16_t data1){
    Commande_16 c = {id, data0, data1};
    sendCommandeByte((uint8_t *)&c, sizeof(Commande_16));
}

void sendCommande(CommandesId id, uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3){
    Commande_8 c = {id, data0, data1, data2, data3};
    sendCommandeByte((uint8_t *)&c, sizeof(Commande_8));
}
void sendCommandeByte(uint8_t *c, uint8_t length){
    checkReceive();
    for(int i=0;i<length;i++)
        Serial.write(c[i]);
}

Commande_16 to_16(Commande &commande){
    return (Commande_16&) commande;
}
Commande_8 to_8(Commande &commande){
    return (Commande_8&) commande;
}

void d_sendDebug(CommandesId id) {
    sendCommande(id,0);
}

void d_sendDebug(CommandesId id, String s0) {
    d_sendDebug(id,s0,"","","");
}

void d_sendDebug(CommandesId id, String s0, String s1) {
    d_sendDebug(id,s0,s1,"","");
}

void d_sendDebug(CommandesId id, String s0, String s1, String s2) {
    d_sendDebug(id,s0,s1,s2,"");
}

void d_sendDebug(CommandesId id, String s0, String s1, String s2, String s3) {
    sendCommande(id,s0.length(), s1.length(), s2.length(), s3.length());
    Serial.print(String() += s0 += s1 += s2 += s3);
}

void d_newScop(String name) {
    d_scope* newScope = new d_scope(name);
    d_scopes.pushBack(newScope);
    d_sendDebug(COMMANDE_DEBUG_SCOP,name,String(newScope->id));
}

int32_t d_getLastScope(String name, d_scope *&res) {
    for(uint16_t i = d_scopes.getLength()-1;i >= 0; i--){
        res = d_scopes.get(i);
        if(name.equals(res->name)) return i;
    }
    return -1;
}

void log(String type, String fileName, String functionName, String msg) {
    d_sendDebug(COMMANDE_DEBUG_LOG,type,fileName,functionName,msg);
}

void d_delScop(String name) {
    d_scope *scope;
    int32_t index = d_getLastScope(name, scope);
    if(index == -1) {
        log("ERROR", "com.cpp", "d_delScop",String("Scope '") += name += "' n'exist pas");

        return;
    }
    d_sendDebug(COMMANDE_DEBUG_DEL_SCOP, name, String(scope->id));
    delete scope;
    d_scopes.set(index, d_scopes.removeLast());
}

void d_addVar(String scop, String name, d_types type, void *valuePtr, String value) {
    d_sendDebug(COMMANDE_DEBUG_ADD_VAR, scop, name, String() += type, value);

}

void d_addVar(String scop, String name, uint64_t &value) {
    d_addVar(scop,name,UINT64_T, &value, String() += value);
}

void d_addVar(String scop, String name, uint32_t &value) {
    d_addVar(scop,name,UINT32_T, &value, String() += value);
}

void d_addVar(String scop, String name, uint16_t &value) {
    d_addVar(scop,name,UINT16_T, &value, String() += value);
}

void d_addVar(String scop, String name, uint8_t &value) {
    d_addVar(scop,name,UINT8_T, &value, String() += value);
}

void d_addVar(String scop, String name, int64_t &value) {
    d_addVar(scop,name,INT64_T, &value, String() += value);
}

void d_addVar(String scop, String name, int32_t &value) {
    d_addVar(scop,name,INT32_T, &value, String() += value);
}

void d_addVar(String scop, String name, int16_t &value) {
    d_addVar(scop,name,INT16_T, &value, String() += value);
}

void d_addVar(String scop, String name, int8_t &value) {
    d_addVar(scop,name,INT8_T, &value, String() += value);
}

void d_addVar(String scop, String name, float &value) {
    d_addVar(scop,name,FLOAT, &value, String() += value);
}

void d_addVar(String scop, String name, double &value) {
    d_addVar(scop,name,DOUBLE, &value, String() += value);
}

void d_addVar(String scop, String name, char &value) {
    d_addVar(scop,name,CHAR, &value, String() += value);
}
