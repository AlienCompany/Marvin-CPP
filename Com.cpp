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
    checkResave();
    for(int i=0;i<length;i++)
        Serial.write(c[i]);
}

Commande_16 to_16(Commande &commande){
    return (Commande_16&) commande;
}
Commande_8 to_8(Commande &commande){
    return (Commande_8&) commande;
}