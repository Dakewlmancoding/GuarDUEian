/************************************************** VARIABLES ***************************************************/

const byte lightPin = 8; // Red RGB light strips pin

bool lightsOn; //lightsOn is self explanatory.

bool activeSearch; // activeSearch is the state where the lights are on and it is actively moving to find the player.
bool passiveSearch; //passiveSearch is when the lights are on and the head is idely moving. Both search modes are controlled by timers.


/************************************************** FUNCTIONS ***************************************************/

//currently does light stuff. for testing!
bool moveHead(bool moveLeft, bool moveRight){
    if (moveLeft or moveRight) {
        if (not lightsOn){
            lightsOn = true;
            digitalWrite(lightPin, HIGH);
        }
        
        if (moveLeft) {
            Serial.println("Moving Left!");
            return moveLeft;
        } else if (moveRight) {
            Serial.println("Moving Right!");
            return moveRight;
        }
        
    } else {
        if (lightsOn){
            lightsOn = false;
            digitalWrite(lightPin, LOW);
        }
        return false;
    }
}