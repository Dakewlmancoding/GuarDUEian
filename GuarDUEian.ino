#include <DueTimer.h>
#include <HCSR04.h>

const byte leftTrig = 2;
const byte leftEcho = 3;
const byte rightTrig = 10;
const byte rightEcho = 11;

const int maxDistCM = 30;

//Trigger, echo, maxCM
UltraSonicDistanceSensor sensorLeft(leftTrig, leftEcho);
UltraSonicDistanceSensor sensorRight(rightTrig, rightEcho);

void setup(){
    Serial.begin(115200);
    Serial.println("Hello World");

}

int leftRead, rightRead;
int leftReadRAW, rightReadRAW;

bool moveRight, moveLeft;


void loop() {

    getLRDistReadings();
    moveHead();
}

void getLRDistReadings() {
    leftReadRAW = sensorLeft.measureDistanceCm();

    if (leftReadRAW < 30)
    {
        leftRead = leftReadRAW;
    } else {
        leftRead = -1;
    }

    rightReadRAW = sensorRight.measureDistanceCm();

    if (rightReadRAW < 30)
    {
        rightRead = rightReadRAW;
    } else {
        rightRead = -1;
    }
}


// Uses LRDistReadings to move head left or right 
void moveHead() {
        if ((leftRead > 0) or (rightRead > 0))
    {
        if((leftRead < 0) and (rightRead > 0)) {
            moveRight = true;
            moveLeft = false;
        } else if((leftRead > 0) and (rightRead < 0)) {
            moveLeft = true;
            moveRight = false;
        } else {
            moveLeft = false;
            moveRight = false;
        }
    }

    if (moveLeft or moveRight) {
        if (moveLeft) {
            Serial.println("Moving Left!");
        } else if (moveRight) {
            Serial.println("Moving Right!");
        }
        
        
    } else {
        Serial.print("Left: ");
        Serial.print(leftRead);

        Serial.print(", Right: ");
        Serial.println(rightRead);
    }
}
    