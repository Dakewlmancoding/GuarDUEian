#include <Adafruit_NeoPixel.h>



/************************************************** VARIABLES ***************************************************/

byte dataLight;
const int numLeds = 51;
const int eyeBrightness = 100;
Adafruit_NeoPixel eyeRings = Adafruit_NeoPixel(numLeds, dataLight, NEO_GRB + NEO_KHZ800);


/************************************************** FUNCTIONS ***************************************************/


void setupLights(byte lightPin){
    dataLight = lightPin;
    eyeRings.begin();
    eyeRings.setBrightness(eyeBrightness);
    eyeRings.show();
}
