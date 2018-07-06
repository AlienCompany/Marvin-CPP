#include <Arduino.h>
#include "HcSr04.h"

HcSr04 *ultraSon;

void setup(){

    ultraSon = new HcSr04(6,7);
    ultraSon->init();

};

void loop(){

  ultraSon->measureDistance();

};