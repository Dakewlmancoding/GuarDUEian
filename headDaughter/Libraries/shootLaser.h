#include <Servo.h>
// Hi this is where laser shoot code will go
Servo laserServo;

const uint16_t neutral = 1500;
//const uint16_t max = 2500;
const uint16_t min = 500;

void setupLaserServo() {
    laserServo.attach(6);
    laserServo.writeMicroseconds(neutral);
}

void moveTab() {
    laserServo.writeMicroseconds(neutral);
}

void resetTab() {
    laserServo.writeMicroseconds(min);
}