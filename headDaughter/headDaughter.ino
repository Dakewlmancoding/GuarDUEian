#include <ArduinoBLE.h>
#include "Libraries/rgbAnimations.h"
#include "Libraries/LeftandRightReadings.h"

int threatLevel; // 0, 1, or 2

BLEDevice due;
BLECharacteristic dueWrite;
BLECharacteristic dueRead;

unsigned long prevMillis = millis();
void timer(int duration, void funct()) {
    if (duration != 0){
        unsigned long currentMillis = millis();
        Serial.print(currentMillis - prevMillis);
        Serial.print(" < ");
        Serial.println(duration*1000);
        if (currentMillis - prevMillis >= (duration*1000)) {
            funct();
            prevMillis = millis();
        }
    } else{
        prevMillis = millis();
    }
}

void connectToDue(){
    BLE.scan();
    while (true){
        due = BLE.available();
        Serial.println(due.localName());
        if (due.localName() == "HC-06"){
            BLE.stopScan();
            Serial.println("Found it!");
            if (due) {
                Serial.println("Connecting ...");
                if (due.connect()) {
                    Serial.println("Connected");
                    break;
                } else {
                    Serial.println("Failed to connect!");
                return;
                }
            }
        }
    }
    Serial.println(due.localName());
    due.discoverAttributes();

    BLEService dueService = due.service(3);
    dueWrite = dueService.characteristic(1);
    dueRead = dueService.characteristic(0);
}

void updateThreat(){
    Serial.println("Updating Threat!");
    if (threatLevel > 0){
        threatLevel--;
    }
    Serial.println(threatLevel);
}

void setup(){
    setupLights(); 
    delay(4000);
    Serial.println("Starting!");
    if (!BLE.begin()) {
        Serial.println("failed!");
        while (1);
    }

    Serial.println("BLE Central scan");
    connectToDue();
}

bool standbyThreatTimer = false;

void loop(){
    updateLRDistReadings();
    checkMoveHead();

    if (canSeePlayer()){
        dueWrite.writeValue("100");
        Serial.println("I see you!!");
        threatLevel = 2;
        timer(0,updateThreat);
        standbyThreatTimer = true;
    }else if (moveRight){
        dueWrite.writeValue("010");
    }else if (moveLeft){
        dueWrite.writeValue("001");
    } else{
        dueWrite.writeValue("000");
    }

    if (not canSeePlayer()){
        timer(20,updateThreat);
    }
    

    Serial.println(threatLevel);
    switch (threatLevel){
    case 0:
        eyeOff();
        lightsOff();
    break;

    case 1:
        eyeOn(200);
        lightsOff();
    break;

    case 2:
        eyeOn(200);
        lightsOn();
    break;
    }   
}
