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
char headStatus[3]; //canSeePlayer,moveLeft,moveRight
bool moveRight;
bool moveLeft;
bool canSeePlayer;
bool ranResets;

/************************************************** FUNCTIONS ***************************************************/


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
    Serial.begin(115200);
    Serial.println("Hello World");

    Serial2.begin(115200); //Mozzi Synth Uno
    
    Serial3.begin(9600); //bluetooth
    Serial.println(Serial3.readString());


    //timers
    threatTimer.attachInterrupt(updateThreat);
    idleTimer.attachInterrupt(updateIdle);
    //shootTimer.attachInterrupt(updateShoot);

    idleTimer.start(secToMicro(3));

    setupServo();
}


void loop() {
    if (Serial3.available()){
        Serial3.readBytes(headStatus,3);
        Serial.println(headStatus);
        canSeePlayer = headStatus[0]-'0';
        moveRight = headStatus[1]-'0';
        moveLeft = headStatus[2]-'0';
    }
    switch (canSeePlayer) {
    case 1:
        threatTimer.stop();
        threatTimer.start(secToMicro(20));
        //shootTimer.start(secToMicro(1));
        threatLevel = 2;
        ranResets = false;
        break;
    }


    //Serial.println(threatLevel);

    lastThreatLevel = threatLevel;
    Serial3.print(threatLevel);
    switch (threatLevel){
    case 0:
        if (not ranResets){
        stopSong();
        resetSong();
        moveHead('n');
        threatTimer.stop();
        ranResets = true;
        }
    break;

    case 1:
        updateSong();
        moveHead(idleDirection);
    break;

    case 2:
        updateSong();
        if (moveRight){
            moveHead('r');
        } else if (moveLeft){
            moveHead('l');
        } else{
            moveHead('n');
        }
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
