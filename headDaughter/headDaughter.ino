#include <ArduinoBLE.h>
#include "Libraries/rgbAnimations.h"

/** VARIABLES GETTING PASSED */
int threatLevel = 2; // 0, 1, or 2
bool moveLeft;
bool moveRight;
bool canSeePlayer;

void connectToDue(){
    while (true){
        due = BLE.available();
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
    BLECharacteristic dueWrite = dueService.characteristic(1);
    BLECharacteristic dueRead = dueService.characteristic(0);
    
    //DEMO!!!!
    dueWrite.writeValue("100");
    delay(1000);
    dueWrite.writeValue("000");
}


void setup(){
    setupLights(); 
}

void loop(){
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

    default:
        break;
    }   
}

 
