#include <Arduino.h>
#include <DueServo.h>
// Hi this is where laser shoot code will go

const int laserServo = 6;

const uint16_t neutral = 1500;
const uint16_t moved = 500;

void setupLaserServo() {
    initServo(laserServo,900); // attaches the servo on pin 5
}

void pleaseWork() {
    writeMicros(laserServo, moved);
}