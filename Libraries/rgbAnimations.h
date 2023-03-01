#include <Adafruit_NeoPixel.h>


/************************************************** VARIABLES ***************************************************/

const int eyePin = 8; // Eye data in pin
const int numLeds = 57;
const int eyeBrightness = 10;
Adafruit_NeoPixel eyeRings = Adafruit_NeoPixel(numLeds, eyePin, NEO_GRB + NEO_KHZ800);

const int ring1 = 20; // Number of lights in the outer ring
const int ring2 = 16;
const int ring3 = 12;
const int ring4 = 8;
const int ring5 = 1; // Number of lights in the inner ring 

const uint32_t darkBlue = eyeRings.Color(3, 0, 100);
const uint32_t blue = eyeRings.Color(0, 200, 220);
const uint32_t midBlue = eyeRings.Color(0, 210, 230);
const uint32_t lightBlue = eyeRings.Color(0, 235, 255);

/************************************************** FUNCTIONS ***************************************************/


void setupLights(){
    eyeRings.begin();
    eyeRings.setBrightness(eyeBrightness);
    //eyeRings.Color(0, 0, 255);
    eyeRings.show();
}

// Draws an individual ring on the LED strip
void drawRing(int previousRings, int size, uint32_t color) {
  for(int i = previousRings; i < (previousRings + size); i++) {
    eyeRings.setPixelColor(i, color);
  }
}

//Draws a full frame of animations (+ all the necessary showing and clearing) with 1 or 2 rings based off numRings
void drawFrame(int numRings, int previousRings, int size, uint32_t color, int previousRings2, int size2, uint32_t color2, int framerate) {
  eyeRings.clear();
  eyeRings.fill(darkBlue);
  drawRing(previousRings, size, color);
  if(numRings = 2) {
    drawRing(previousRings2, size2, color2);
  }
  eyeRings.show();
  delay(framerate);
}

// now i make it do what I want to do
void doLights() {
  drawFrame(2, 0, ring1, blue, (ring1 + ring2 + ring3), ring4, lightBlue, 120); 
  drawFrame(1, (ring1+ ring2), ring3, midBlue, 0, 0, blue, 200); 
  drawFrame(2, ring1, ring2, blue, (ring1 + ring2 + ring3), ring4, lightBlue, 200);
  drawFrame(2, 0, ring1, blue, (ring1 + ring2), ring3, lightBlue, 120);  
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
