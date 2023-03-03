#include <Servo.h>

/************************************************** VARIABLES ***************************************************/

bool lightsOn; //lightsOn is self explanatory.

bool activeSearch; // activeSearch is the state where the lights are on and it is actively moving to find the player.
bool passiveSearch; //passiveSearch is when the lights are on and the head is idely moving. Both search modes are controlled by timers.

Servo headServo;

/************************************************** FUNCTIONS ***************************************************/

void setupServo() {
    headServo.attach(9); // attaches the servo on pin 9
}

char lastDirection;

//moves the servo in direction. l = counterclockwise, r = clockwise, n = don't move
void moveHead(char direction){
    if (not (direction == lastDirection)){
        headServo.writeMicroseconds(1500);
        switch (direction){
        case 'l':
            headServo.writeMicroseconds(1400);
        break;
        
        case 'r':
            headServo.writeMicroseconds(1600);
        break;

        default:
            break;
        }
    }
    
}
