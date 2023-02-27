#include <Adafruit_NeoMatrix.h>
#include <gamma.h>
/*
#include <bitswap.h>
#include <chipsets.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <color.h>
#include <dmx.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <FastLED.h>
#include <fastpin.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <fastspi.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>
*/

/************************************************** VARIABLES ***************************************************/




/************************************************** FUNCTIONS ***************************************************/


void setupLights(byte lightPin){
    pinMode(lightPin, OUTPUT);
    digitalWrite(lightPin, LOW);
}