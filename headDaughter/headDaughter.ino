/************************************************** VARIABLES ***************************************************/

#include <ArduinoBLE.h>
//#include "Libraries/shootLaser.h"
#include "Libraries/rgbAnimations.h"
#include "Libraries/LeftandRightReadings.h"

int threatLevel; // 0, 1, or 2
int shootIteration = 0; // Iterative variable for counting sec until shoot
const int shootEvery = 5; // Duration between when the laser will shoot at threat level 2


BLEDevice due; //the HC-06 on the due
BLECharacteristic dueWrite; //the characteristic that posts itself to the due's Serial3
BLECharacteristic dueRead; //the characteristic that posts from due's Serial3 NOT USED

unsigned long prevMillis = millis();


/************************************************** FUNCTIONS ***************************************************/
//dueTimer for nano, kinda
void timer(int duration, void funct()) {
    if (duration != 0){
        unsigned long currentMillis = millis();
        /*
        Serial.print(currentMillis - prevMillis);
        Serial.print(" < ");
        Serial.println(duration*1000);
        */

        if (currentMillis - prevMillis >= (duration*1000)) {
            funct();
            prevMillis = millis();
        }
    } else{
        prevMillis = millis();
    }
}

//makes sure the due is still connected. If not, reconnects WARNING: This method of reconnection halts everything else... 
void checkDueConnection(){
    if (not due.connected()){
        Serial.println("Warning! Due disconnected!!");
        while (true)
        {
            if (due.connect()){
                Serial.println("Due reconnected!");
                break;
            }
            
        }
        
    }
}


//connects to the HC-06 connected to Serial3 of the due by using its MAC address, then verifying the connection with the name (HC-06)
void connectToDue(){
    if (!BLE.begin()) {
        Serial.println("failed!");
        while (1);
    }

    Serial.println("BLE Central scan");
    StartScan:
    Serial.println(BLE.scanForAddress("98:DA:60:05:82:2C"));
    while (true){
        due = BLE.available();
        Serial.println(due.address());
        //Serial.println(due.localName());
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
                    goto StartScan;
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

//updates the threat level
void updateThreat(){
    Serial.println("Updating Threat!");
    if (threatLevel > 0){
        threatLevel--;
    }
    Serial.println(threatLevel);
}

//updates the laser. Never implented
void updateShoot() {
    Serial.print("Shooting in... ");
    Serial.println((shootEvery - shootIteration));

    if(shootIteration <= (shootEvery/2)) {
        if(shootIteration == 0) {
            //resetTab();
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
        //moveTab();
         // Change eye LED animation from idle

        shootIteration = 0;
    }
}

//this is a stupid function to do something that BLE should already do. Necessary b/c the write value method only takes a constant...
int writeToDue(){
    char message1, message2, message3, message4;
    switch (canSee){ // using switches as if elses for speed
    case true:
        message1 = '1';
    break;
    
    default:
        message1 = '0';
    break;
    }
    switch (moveLeft){
    case true:
        message2 = '1';
    break;
    
    default:
        message2 = '0';
    break;
    }
    switch (moveRight){
    case true:
        message3 = '1';
    break;
    
    default:
        message3 = '0';
    break;
    }
    switch (threatLevel){
    case 0:
        message4 = '0';
    break;

    case 1:
        message4 = '1';
    break;

    case 2:
        message4 = '2';
    break;
    
    }

    Serial.println("Sending to Due: ");
    Serial.print(message1);
    Serial.print(message2);
    Serial.print(message3);
    Serial.println(message4);
    
    switch (message1)
    {
    case '1':
        switch (message4)
        {
        case '0':
            dueWrite.writeValue("1000");
        break;
        
        case '1':
            dueWrite.writeValue("1001");
        break;

        case '2':
            dueWrite.writeValue("1002");
        break;

        default:
            break;
        }
        break;
    
    case '0':
        switch (message2)
        {
        case '1':
            switch (message4)
            {
            case '0':
                dueWrite.writeValue("0100");
            break;
            
            case '1':
                dueWrite.writeValue("0101");
            break;

            case '2':
                dueWrite.writeValue("0102");
            break;

            default:
                break;
            }
        break;
        
        case '0':
        switch (message3)
        {
        case '1':
            switch (message4)
            {
            case '0':
                dueWrite.writeValue("0010");
            break;
            
            case '1':
                dueWrite.writeValue("0011");
            break;

            case '2':
                dueWrite.writeValue("0012");
            break;

            default:
                break;
            }
            break;
        
        case '0':
        switch (message4)
        {
        case '0':
            dueWrite.writeValue("0000");
        break;
        
        case '1':
            dueWrite.writeValue("0001");
        break;

        case '2':
            dueWrite.writeValue("0002");
        break;

        default:
            break;
        }
        break;
        default:
            break;
        }
        break;


        default:
            break;
        }
    break;
    
    default:
        break;
    }
    return 1;
}


/************************************************** BUILT IN FUNCS ***************************************************/
void setup(){
    Serial.println("Starting!");
    setupLights(); 
    delay(4000);
    Serial.begin(115200);
    connectToDue();
}

void loop(){
    updateLRDistReadings();
    debugReadings();
    checkMoveHead();
    if (canSee){
        threatLevel = 2;
        timer(0,updateThreat);
    }
    

    checkDueConnection();
    writeToDue();

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