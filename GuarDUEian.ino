
#include <DueTimer.h>
#include "Libraries/LeftandRightReadings.h" // Ultrasonic Sensor Head Turning/Red RGB Light code
#include "Libraries/rgbAnimations.h" // All RGB animations

void setup(){
    Serial.begin(115200);
    Serial.println("Hello World");

    pinMode(lightPin, OUTPUT);
    digitalWrite(lightPin, LOW);
}

void loop() {
    getLRDistReadings();
    checkMoveHead();
    moveHead(); 
}