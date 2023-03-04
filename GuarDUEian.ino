#include <DueTimer.h>

#include "Libraries/LeftandRightReadings.h" // Ultrasonic Sensor Head Turning/Red RGB Light code
#include "Libraries/rgbAnimations.h" // All RGB animations
#include "Libraries/movingHead.h" // All servo stuff



/************************************************** VARIABLES ***************************************************/

int threatLevel; //the three threat levels. 0 is off (only seeing if player walks in front of it). 1 is passive (the lights are on and the head is idely moving). 2 is active (the lights are on and it is actively moving to find the player.)
unsigned long playerLastSightedTime; //time in microseconds since it's seen the player

//timers start at 6 b/c servos!!
DueTimer threatTimer = DueTimer(6); //the timer to switch the threat level
DueTimer idleTimer = DueTimer(7); //the timer to switch the threat level
char idleDirection;

/************************************************** FUNCTIONS ***************************************************/

void updateThreat(){
    if (threatLevel > 0){
        threatLevel--;
    }
}

void updateIdle(){
    switch (random(0,2)) {
    case 0:
        idleDirection = 'n';
    break;
    
    case 1:
        idleDirection = 'l';
    break;

    case 2:
        idleDirection = 'r';
    break;

    default:
        break;
    }
}

/************************************************** BUILT IN FUNCS ***************************************************/

void setup() {
    Serial.begin(115200);
    Serial.println("Hello World");

    //timers
    threatTimer.attachInterrupt(updateThreat);
    idleTimer.attachInterrupt(updateIdle);
    idleTimer.start(3000000);

    setupServo();
    setupLights();
}

int beginLoopThreatLevel;

void loop() {
    beginLoopThreatLevel = threatLevel;
    updateLRDistReadings();
    checkMoveHead();

    if (canSeePlayer()){
        threatTimer.stop();
        threatTimer.start(20000000);

        if (not (threatLevel == 2)) {
            threatLevel = 2;
        } 
    }

    Serial.println(threatLevel);

    switch (threatLevel){
    case 0:
        eyeOff();
        moveHead('n');
    break;

    case 1:
        eyeOn(200);
        moveHead(idleDirection);
    break;

    case 2:
        eyeOn(200);
        if (moveRight){
            moveHead('r');
        } else if (moveLeft){
            moveHead('l');
        } else{
            moveHead('n');
        }
    break;

    default:
        break;
    }

}

/*
if (moveLeft or moveRight){

    }else{
        Serial.print("Left: ");
        Serial.print(leftRead);
        Serial.print(" Right: ");
        Serial.println(rightRead);
    }
*/
