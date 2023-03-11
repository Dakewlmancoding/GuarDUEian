#include <Arduino.h>
#include <DueServo.h>


/************************************************** VARIABLES ***************************************************/

const int laserServo = 6;

const uint16_t neutral = 1200;
const uint16_t moved = 500;

/************************************************** FUNCTIONS ***************************************************/

void setupLaserServo() {
    initServo(laserServo,800); // attaches the servo on pin 6
    writeMicros(laserServo, neutral);
}

// Moves the tab to reveal the laser
void moveTab() {
    Serial.println("Shooting!");
    writeMicros(laserServo, moved);
}

// Resets tab to neutral to hide laser
void resetTab() {
    writeMicros(laserServo, neutral);
}