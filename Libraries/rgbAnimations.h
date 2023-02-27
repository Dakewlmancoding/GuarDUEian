#include <Adafruit_NeoPixel.h>


/************************************************** VARIABLES ***************************************************/

byte dataLight;
const int numLeds = 57;
const int eyeBrightness = 100;
Adafruit_NeoPixel eyeRings = Adafruit_NeoPixel(numLeds, dataLight, NEO_GRB + NEO_KHZ800);


/************************************************** FUNCTIONS ***************************************************/


void setupLights(byte lightPin){
    dataLight = lightPin;
    eyeRings.begin();
    eyeRings.setBrightness(eyeBrightness);
    eyeRings.Color(0, 0, 255);
    eyeRings.show();
}

void setAllPixels() {
    for()
}