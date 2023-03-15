#include <Arduino.h>
#include <DueServo.h>

/************************************************** VARIABLES ***************************************************/
const int headServo = 7;

const uint16_t stop = 1500;
const uint16_t left = 500;
const uint16_t right = 2500;

/************************************************** FUNCTIONS ***************************************************/


void setupServo() {
    initServo(headServo,900); // attaches the servo on pin 7
}

char lastDirection;
//moves the servo in direction. l = counterclockwise, r = clockwise, n = don't move
void moveHead(char direction){
    SerialUSB.print(direction);
    SerialUSB.println(" in MoveHead");
    if (not (direction == lastDirection)){
        lastDirection = direction;
        switch (direction){
        case 'l':
            writeMicros(headServo, left);
            Serial.println("Moving Left");
        break;
        
        case 'r':
            writeMicros(headServo, right);
            Serial.println("Moving Right");
        break;

        default:
            writeMicros(headServo, stop); //stop
            //headServo.write(90);
            Serial.println("Stopping...");
        break;
        }
    }
    
}