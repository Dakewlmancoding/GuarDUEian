#include <Adafruit_NeoPixel.h>


/************************************************** VARIABLES ***************************************************/

const int eyePin = 9; // Eye data in pin
const int numLeds = 57;
const int eyeBrightness = 10;
Adafruit_NeoPixel eyeRings = Adafruit_NeoPixel(numLeds, eyePin, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis; // Used in animation
int frame = 0; // Used in animation

const int ring1 = 20; // Number of lights in the outer ring
const int ring2 = 16;
const int ring3 = 12;
const int ring4 = 8; // Number of lights in the inner ring 

const uint32_t darkBlue = eyeRings.Color(3, 0, 100);
const uint32_t blue = eyeRings.Color(0, 200, 220);
const uint32_t midBlue = eyeRings.Color(0, 210, 230);
const uint32_t lightBlue = eyeRings.Color(0, 235, 255);

/************************************************** FUNCTIONS ***************************************************/

// Runs in setup - general matrix startup stuff and it forces the eye to show as off
void setupLights(){
    eyeRings.begin();
    eyeRings.setBrightness(eyeBrightness);
    eyeRings.fill(eyeRings.Color(0, 0, 0));
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
}

// Draws the frames for the eye animation
void eyeOn(int framerate) {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= framerate) {
    switch(frame) {
      case 0: 
        drawFrame(2, 0, ring1, blue, (ring1 + ring2 + ring3), ring4, lightBlue, 120); 
        frame++;
        break;
      case 1:
        drawFrame(1, (ring1+ ring2), ring3, midBlue, 0, 0, blue, 200); 
        frame++;
        break;
      case 2:
        drawFrame(2, ring1, ring2, blue, (ring1 + ring2 + ring3), ring4, lightBlue, 200);
        frame++;
        break;
      case 3:
        drawFrame(2, 0, ring1, blue, (ring1 + ring2), ring3, lightBlue, 120);
        frame = 0;
        break;
    }
    previousMillis = currentMillis;
  }
}

// Forces the eye off very aggressively 
void eyeOff() {
  eyeRings.clear();
  eyeRings.fill(eyeRings.Color(0, 0, 0));
  eyeRings.show();
}

// Eye animation for shooting
void eyeShoot() {
  eyeRings.clear();
  eyeRings.fill(lightBlue);
  eyeRings.show();
}