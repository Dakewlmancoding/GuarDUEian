
#include <DueTimer.h>
#include "Libraries/LeftandRightReadings.h" // Ultrasonic Sensor Head Turning/Red RGB Light code
#include "Libraries/rgbAnimations.h" // All RGB animations
#include "Libraries/movingHead.h"" // All RGB animations

void setup(){
    Serial.begin(115200);
    Serial.println("Hello World");
    setupLights(lightPin);
}

void loop() {
    updateLRDistReadings();
    checkMoveHead();
    if (not moveHead(moveLeft,moveRight))
    {
        Serial.print("Left: ");
        Serial.print(leftRead);
        Serial.print(" Right: ");
        Serial.println(rightRead);
    }
    
}