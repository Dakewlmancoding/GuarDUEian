#include <ArduinoBLE.h>
#include "Libraries/rgbAnimations.h"

/** VARIABLES GETTING PASSED */
int threatLevel = 2; // 0, 1, or 2
bool moveLeft;
bool moveRight;
bool canSeePlayer;

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

 
