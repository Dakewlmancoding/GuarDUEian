//Lib to turn on the music UNO

/************************************************** VARIABLES ***************************************************/

const int musicPin = 35;


/************************************************** FUNCTIONS ***************************************************/

void musicSetup(){
    pinMode(musicPin, OUTPUT);
    digitalWrite(musicPin,LOW);
}


void musicOn(){
    digitalWrite(musicPin,HIGH);
}

void musicOff(){
    digitalWrite(musicPin,LOW);
}