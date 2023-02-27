#include <Adafruit_NeoMatrix.h>
#include <gamma.h>

#include <DueTimer.h>
#include "Libraries/LeftandRightReadings.h" // lightPin comes from here

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