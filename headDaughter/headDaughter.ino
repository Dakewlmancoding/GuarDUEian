#include <ArduinoBLE.h>
#include "Libraries/rgbAnimations.h"

// Arduino Nano 
// Bools being Passed: MoveLeft, MoveRight, LookingAtPlayer, int ThreatLevel

int threatLevel = 2;

void setup(){
   setupLights(); 
}

void loop(){
    switch (threatLevel){
    case 0:
        eyeOff();
        lightsOff();
    break;

    case 1:
        eyeOn(200);
        lightsOff();
    break;

    case 2:
        eyeOn(200);
        lightsOn();
    break;

    default:
        break;
    }   
}

 
