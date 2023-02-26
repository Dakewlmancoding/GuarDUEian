#include <DueTimer.h>
#include <HCSR04.h>

const byte leftTrig = 2;
const byte leftEcho = 3;
const byte rightTrig = 10;
const byte rightEcho = 11;

const byte lightPin = 8;

const int maxDistCM = 30;


//Trigger, echo, maxCM
UltraSonicDistanceSensor sensorLeft(leftTrig, leftEcho);
UltraSonicDistanceSensor sensorRight(rightTrig, rightEcho);

void setup(){
    Serial.begin(115200);
    Serial.println("Hello World");

    pinMode(lightPin, OUTPUT);
    digitalWrite(lightPin, LOW);

}


int leftRead, rightRead;
int leftReadRAW, rightReadRAW;

bool moveRight, moveLeft;
bool lightsOn, activeSearch, passiveSearch; //lightsOn is self explanatory. Active search is the state where the lights are on and it is actively moving to find the player. Passive Search is when the lights are on and the head is idely moving. Both search modes are controlled by timers.



void loop() {

    getLRDistReadings();
    checkMoveHead();
    moveHead();
    
}



void getLRDistReadings() {
    leftReadRAW = sensorLeft.measureDistanceCm();

    if (leftReadRAW < 30)
    {
        leftRead = leftReadRAW;
    } else {
        leftRead = -1;
    }

    rightReadRAW = sensorRight.measureDistanceCm();

    if (rightReadRAW < 30)
    {
        rightRead = rightReadRAW;
    } else {
        rightRead = -1;
    }
}


// Uses LRDistReadings to set moveRight and moveLeft
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

//code to move the head CURRENTLY TEST CODE
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