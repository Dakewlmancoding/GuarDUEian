#include <DueTimer.h>


#include "Libraries/LeftandRightReadings.h" // Ultrasonic Sensor Head Turning/Red RGB Light code
#include "Libraries/rgbAnimations.h" // All RGB animations
#include "Libraries/movingHead.h" // All servo stuff



/************************************************** VARIABLES ***************************************************/

int threatLevel; //the three threat levels. 0 is off (only seeing if player walks in front of it). 1 is passive (the lights are on and the head is idely moving). 2 is active (the lights are on and it is actively moving to find the player.)
unsigned long playerLastSightedTime; //time in microseconds since it's seen the player

//timers start at 6 b/c servos!!
DueTimer threatTimer = DueTimer(6); //the timer to switch the threat level

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
    break;
    
    case 1:
        eyeOn(200);
    break;

    case 2:
        eyeOn(200);
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
