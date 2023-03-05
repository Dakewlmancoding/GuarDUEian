#include <Arduino.h>
#include <DueServo.h>
// Hi this is where laser shoot code will go

const int laserServo = 6;

const uint16_t neutral = 1500;
const uint16_t max = 2500;
const uint16_t min = 500;

void setupLaserServo() {
    initServo(laserServo,800); // attaches the servo on pin 6
    writeMicros(laserServo, neutral);
}

int ServoPos = 0;
void pleaseWork() {
    ServoPos++;
    if (ServoPos >=3){
        ServoPos = 0;
    }
    switch (ServoPos){
    case 0:
    case 2:
        writeMicros(laserServo, neutral);
    break;
    
    case 1:
        writeMicros(laserServo, min);
    break;

    case 3:
        writeMicros(laserServo, max);
    break;
    }
}