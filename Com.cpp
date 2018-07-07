//
// Created by hugues on 11/06/2018.
//

#include "Com.h"

void checkResave(){
    while(Serial.available()){
        Commande commande;
        Serial.readBytes((byte *) &commande, sizeof(Commande));
        onResave(commande);
    }
}

void sendCommande(CommandesId id, uint32_t data){
    sendCommande(id, (uint16_t)(data >> 16),(uint16_t) data);
}

void sendCommande(CommandesId id, uint16_t data0, uint16_t data1){
    sendCommande(id, (uint8_t)(data0 >> 8), (uint8_t)data0, (uint8_t)(data1 >> 8), (uint8_t)data1);
}

void sendCommande(CommandesId id, uint8_t data0, uint8_t data1, uint8_t data2, uint8_t data3){
    checkResave();
    Serial.write(id);
    Serial.write(data0);
    Serial.write(data1);
    Serial.write(data2);
    Serial.write(data3);
}

Commande_16 to_16(Commande &commande){
    return (Commande_16&) commande;
}
Commande_8 to_8(Commande &commande){
    return (Commande_8&) commande;
}