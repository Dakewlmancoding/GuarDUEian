
#include <DueTimer.h>
#include "Libraries/LeftandRightReadings.h" // Ultrasonic Sensor Head Turning/Red RGB Light code
#include "Libraries/rgbAnimations.h" // All RGB animations
#include "Libraries/movingHead.h" // All RGB animations

/************************************************** VARIABLES ***************************************************/

int threatLevel; //the three threat levels. 0 is off (only seeing if player walks in front of it). 1 is passive (the lights are on and the head is idely moving). 2 is active (the lights are on and it is actively moving to find the player.)
unsigned long playerLastSightedTime; //time in microseconds since it's seen the player


DueTimer lightTimer = DueTimer(0); // the timer set to the framerate of the lights
DueTimer threatTimer = DueTimer(1); //the timer to switch the threat level

/************************************************** FUNCTIONS ***************************************************/

void updateThreat(){
    if (threatLevel > 0){
        threatLevel--;
    }
}

/************************************************** BUILT IN FUNCS ***************************************************/

void setup() {
    Serial.begin(115200);
    Serial.println("Hello World");
    
    //timers
    threatTimer.attachInterrupt(updateThreat);

    //lightTimerStuff


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

    if(threatLevel > 0) {
        eyeOn(200); // input is the framerate in ms
    } else {
        eyeOff();
    }

    Serial.println(threatLevel);
    

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
