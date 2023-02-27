#include <Adafruit_NeoPixel.h>


/************************************************** VARIABLES ***************************************************/

const int eyePin = 8; // Eye data in pin
const int numLeds = 57;
const int eyeBrightness = 100;
Adafruit_NeoPixel eyeRings = Adafruit_NeoPixel(numLeds, eyePin, NEO_GRB + NEO_KHZ800);


/************************************************** FUNCTIONS ***************************************************/


void setupLights(){
    eyeRings.begin();
    eyeRings.setBrightness(eyeBrightness);
    //eyeRings.Color(0, 0, 255);
    eyeRings.show();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return eyeRings.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return eyeRings.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return eyeRings.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<eyeRings.numPixels(); i++) {
      eyeRings.setPixelColor(i, Wheel((i+j) & 255));
    }
    eyeRings.show();
    delay(wait);
  }
}
