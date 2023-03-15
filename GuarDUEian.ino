#include <DueTimer.h>

#include "Libraries/movingHead.h" // All servo stuff
#include "Libraries/song.h" // The music

/************************************************** VARIABLES ***************************************************/

int threatLevel; //the three threat levels. 0 is off (only seeing if player walks in front of it). 1 is passive (the lights are on and the head is idely moving). 2 is active (the lights are on and it is actively moving to find the player.)
unsigned long playerLastSightedTime; //time in microseconds since it's seen the player

DueTimer threatTimer = DueTimer(6); //the timer to switch the threat level
DueTimer idleTimer = DueTimer(7); //the timer to switch the idle direction
DueTimer shootTimer = DueTimer(8); //the timer to decide when the laser shoots
char idleDirection;

int shootIteration = 0; // Iterative variable for counting sec until shoot
const int shootEvery = 5; // Duration between when the laser will shoot at threat level 2
bool shootLaser;

int lastThreatLevel;
char headStatus[4]; //canSeePlayer,moveLeft,moveRight
bool moveRight;
bool moveLeft;
bool canSeePlayer;
bool ranResets;

/************************************************** FUNCTIONS ***************************************************/


//updates the threat level. If it can't see the player actively (level 2) turns off the laser timer
void updateThreat(){
    Serial.println("Updating Threat!");
    if (threatLevel > 0){
        threatLevel--;
    }
    Serial.println(threatLevel);
    if(threatLevel != 2) {
        shootTimer.stop();
        shootIteration = 0;
    }
}

//picks a random direction to move in during passive search mode (threat level 1)
void updateIdle(){
    SerialUSB.println("Updating Idle");
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


//code to shoot the laser. Moved to Nano/head and not fully implented
void updateShoot() {
    Serial.print("Shooting in... ");
    Serial.println((shootEvery - shootIteration));

    if(shootIteration <= (shootEvery/2)) {
        if(shootIteration == 0) {
            shootLaser = false;
        }
        // Low pitch sound
        shootIteration++;

    } else if(shootIteration != shootEvery) {
        // High pitch sound
        shootIteration++;

    } else if(shootIteration == shootEvery) {
        // Pause head motion
        moveLeft = false;
        moveRight = false;
        // Blow fan
        shootLaser = true;
         // Change eye LED animation from idle
        // Servo to shoot laser
        // (?) Get light level from photocell fAST
        // Check to see if player got hit and react

        shootIteration = 0;
    }
}

// Make timer durations easier to read
int secToMicro(int s) {
    return s*1000000;
}

// Make animation durations easier to read
int secToMilli(int s) {
    return s * 1000;
}

/************************************************** BUILT IN FUNCS ***************************************************/

void setup() {
    SerialUSB.begin(115200);
    SerialUSB.println("Hello World");

    Serial2.begin(115200); //Mozzi Synth Uno
    
    Serial3.begin(9600); //bluetooth
    //Serial.println(Serial3.readString());


    //timers
    threatTimer.attachInterrupt(updateThreat);
    idleTimer.attachInterrupt(updateIdle);
    //shootTimer.attachInterrupt(updateShoot); timer to shoot the laser. Not implemented

    idleTimer.start(secToMicro(3));

    setupServo();
}


void loop() {
    //SerialUSB.println("top");
    if (Serial3.available()){ //this is the cursed bool that works occasionally
        SerialUSB.println("Reading");
        Serial3.readBytes(headStatus,4); //gets info from Nano/head
        SerialUSB.println(headStatus);
        canSeePlayer = headStatus[0]-'0';
        moveRight = headStatus[1]-'0';
        moveLeft = headStatus[2]-'0';
        threatLevel = headStatus[3]-'0';
        /*
        SerialUSB.print(canSeePlayer);
        SerialUSB.print(moveRight);
        SerialUSB.print(moveLeft);
        SerialUSB.println(threatLevel);
        */
    } else{
        SerialUSB.println("Read Failed! :(");
    }
    SerialUSB.print("Threat Level = ");
    SerialUSB.println(threatLevel);

    //switch statement to do events related to what threat level its at
    lastThreatLevel = threatLevel;
    switch (threatLevel){
    case 0:
        SerialUSB.println("Case 0");
        if (not ranResets){
        stopSong();
        resetSong();
        moveHead('n');
        ranResets = true;
        }
    break;

    case 1:
        SerialUSB.println("Case 1");
        updateSong();
        moveHead(idleDirection);
        ranResets = false;
    break;

    case 2:
        SerialUSB.println("Case 2");
        updateSong();
        if (moveRight){
            moveHead('r');
        } else if (moveLeft){
            moveHead('l');
        } else{
            moveHead('n');
        }
        ranResets = false;
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
