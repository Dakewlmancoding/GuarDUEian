#include <HCSR04.h>

    /************************
    * LeftandRightReadings.h
    * HANDLES THE CODE FOR 2 ULTRASONIC SENSORS (LEFT & RIGHT)
    * USED FOR HEAD TURNING (DOESN'T INCLUDE SERVO MOTOR CODES AS OF NOW)
    * RGB STRIPS ON/OFF BASED OFF ACTIVITY OF SENSORS
    *************************/

/************************************************** VARIABLES ***************************************************/

// PINS & CONSTANTS
const byte leftTrig = 2; //sensorLeft Trig pin
const byte leftEcho = 3; //sensorLeft Echo pin
const byte rightTrig = 10; //sensorRight Trig pin
const byte rightEcho = 11; //sensorRight Echo pin

const int maxDistCM = 30; // Sets the maximum distance for the sensor (in CM)

// US SENSORS
    
//Format: name(Trigger, Echo)
UltraSonicDistanceSensor sensorLeft(leftTrig, leftEcho);
//Format: name(Trigger, Echo)
UltraSonicDistanceSensor sensorRight(rightTrig, rightEcho);

// INTS
int leftReadRAW, rightReadRAW;
//Stores the readings of the left and right US sensors. -1 if out of range
int leftRead, rightRead;

// BOOLEANS
//whether the head should be moving left or right
bool moveRight, moveLeft;


/************************************************** FUNCTIONS ***************************************************/

//updates the varables leftRead and rightRead. If they are greater than maxDistCM, sets them to -1
void updateLRDistReadings() {
    leftReadRAW = sensorLeft.measureDistanceCm();

    if (leftReadRAW < maxDistCM){
        leftRead = leftReadRAW;
    } else {
        leftRead = -1;
    }

    rightReadRAW = sensorRight.measureDistanceCm();

    if (rightReadRAW < maxDistCM){
        rightRead = rightReadRAW;
    } else {
        rightRead = -1;
    }
}


//Checks whether or not the head should move to follow the player, based on the most recent readings of leftRead and rightRead, and sets moveRight and/or moveLeft accordingly
void checkMoveHead() {
        if ((leftRead > 0) or (rightRead > 0)){
        if((leftRead < 0) and (rightRead > 0)) {
            moveRight = true;
            moveLeft = false;
        } else if((leftRead > 0) and (rightRead < 0)) {
            moveLeft = true;
            moveRight = false;
        } else {
            moveLeft = false;
            moveRight = false;
            //!!!!!NOTE THAT THERE CAN BE A CASE WHERE THE PLAYER LEAVES RANGE!!!!!
        }
    }
}

//if both sensors have a reading, the guardian can see the player (true)
bool canSeePlayer(){
    if ((leftRead > 0) and (rightRead > 0)){
        return true;
    } else {
        return false;
    }
}