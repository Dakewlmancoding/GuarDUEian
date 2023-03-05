#include <DueTimer.h>

#include "Libraries/LeftandRightReadings.h" // Ultrasonic Sensor Head Turning/Red RGB Light code
#include "Libraries/rgbAnimations.h" // All RGB animations
#include "Libraries/movingHead.h" // All servo stuff
#include "Libraries/shootLaser.h" // Laser shooting


/************************************************** VARIABLES ***************************************************/

int threatLevel; //the three threat levels. 0 is off (only seeing if player walks in front of it). 1 is passive (the lights are on and the head is idely moving). 2 is active (the lights are on and it is actively moving to find the player.)
unsigned long playerLastSightedTime; //time in microseconds since it's seen the player

//timers start at 6 b/c servos!!
DueTimer threatTimer = DueTimer(6); //the timer to switch the threat level
DueTimer idleTimer = DueTimer(7); //the timer to switch the idle direction
DueTimer shootTimer = DueTimer(8); //the timer to decide when the laser shoots
char idleDirection;

int shootIteration = 0; // Iterative variable for counting sec until shoot
const int shootEvery = 6; // Duration between when the laser will shoot at threat level 2

/************************************************** FUNCTIONS ***************************************************/

void updateThreat(){
    if (threatLevel > 0){
        threatLevel--;
    }
    if(threatLevel != 2) {
        shootTimer.stop();
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

void updateShoot() {
    if(shootIteration <= (shootEvery/2)) {
        // Low pitch sound
        shootIteration++;
    } else if((shootIteration <= (shootEvery/2)) && (shootIteration < shootEvery)) {
        // High pitch sound
        shootIteration++;
    } else if(shootIteration == shootEvery) {
        // Pause head motion
        moveLeft = false;
        moveRight = false;

        // Blow fan
        // Shooty sound pew pew
        eyeShoot(); // Change eye LED animation from idle
        // Servo to shoot laser
        // (?) Get light level from photocell fAST
        // Check to see if player got hit and react

        shootIteration = 0;
    }
}

// Helps timer durations a lot easier to read by converting microseconds to seconds
int microToSec(int l) {
    l = l * 100000;
    return l;
}

// Helps animation durations a lot easier to read by converting milliseconds to seconds
int milliToSec(int l) {
    l = l * 1000;
    return l;
}

/************************************************** BUILT IN FUNCS ***************************************************/

void setup() {
    Serial.begin(115200);
    Serial.println("Hello World");

    //timers
    threatTimer.attachInterrupt(updateThreat);
    idleTimer.attachInterrupt(updateIdle);
    shootTimer.attachInterrupt(updateShoot);

    idleTimer.start(microToSec(3));

    setupServo();
    setupLights();
}

int beginLoopThreatLevel;

void loop() {
    beginLoopThreatLevel = threatLevel;
    updateLRDistReadings();
    checkMoveHead();
   // pleaseWork();

    if (canSeePlayer()){
        threatTimer.stop();
        threatTimer.start(microToSec(20));
        shootTimer.start(microToSec(1));

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
        eyeOn(milliToSec(200));
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
