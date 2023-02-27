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

const byte lightPin = 8; // Red RGB light strips pin

const int maxDistCM = 30; // Sets the maximum distance for the sensor (in CM)

// US SENSORS
    /*
    * Format: name(Trigger, Echo, maxCM) (maxCM ended up causing issues for some reason)
    */
UltraSonicDistanceSensor sensorLeft(leftTrig, leftEcho);
UltraSonicDistanceSensor sensorRight(rightTrig, rightEcho);

// INTS
    /*
    * Stores the readings of the left and right US sensors
    */
int leftReadRAW, rightReadRAW;
int leftRead, rightRead;

// BOOLEANS
    /*
    * moveRight = is moving right
    * moveLeft = is moving left
    */
bool moveRight, moveLeft;

    /*
    * lightsOn is self explanatory.
    * activeSearch is the state where the lights are on and it is actively moving to find the player.
    * passiveSearch is when the lights are on and the head is idely moving. Both search modes are controlled by timers.
    */
bool lightsOn, activeSearch, passiveSearch;

/************************************************** FUNCTIONS ***************************************************/

    /*
    * getLRDistReadings()
    * Gets readings from the left and right sensors if there is motion within the range of 0 and maxDistCM
    */

void getLRDistReadings() {
    leftReadRAW = sensorLeft.measureDistanceCm();

    if (leftReadRAW < maxDistCM)
    {
        leftRead = leftReadRAW;
    } else {
        leftRead = -1;
    }

    rightReadRAW = sensorRight.measureDistanceCm();

    if (rightReadRAW < maxDistCM)
    {
        rightRead = rightReadRAW;
    } else {
        rightRead = -1;
    }
}

    /*
    * checkMoveHead()
    * Uses LRDistReadings to set moveRight and moveLeft
    */

void checkMoveHead() {
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
}

    /*
    * moveHead()
    * Test code for head moving (displays output in the Serial Monitor, doesn't use motors yet)
    */
void moveHead(){
    if (moveLeft or moveRight) {
        if (not lightsOn){
            lightsOn = true;
            digitalWrite(lightPin, HIGH);
        }
        
        if (moveLeft) {
            Serial.println("Moving Left!");
        } else if (moveRight) {
            Serial.println("Moving Right!");
        }
        
    } else {
        if (lightsOn){
            lightsOn = false;
            digitalWrite(lightPin, LOW);
        }
        Serial.print("Left: ");
        Serial.print(leftRead);

        Serial.print(", Right: ");
        Serial.println(rightRead);
    }
}