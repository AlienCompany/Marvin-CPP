#include <Arduino.h>
#include "HcSr04.h"

HcSr04 *ultraSon;

void setup(){

    Serial.begin(9600);
    ultraSon = new HcSr04(13,12);
    ultraSon->init();

};

void loop(){

  Serial.println(ultraSon->measureDistance());

};