// library for neopixel LEDs
#include <Adafruit_NeoPixel.h>

// specifies AVR microcontroller (arduino, as opposed to other models with different microcontrollers)
#ifdef __AVR__
  #include <avr/power.h>
#endif

// which pin is outputs to LEDs
#define PIN 12

// define how many rings there are
int number_of_rings = 1;

// define how many LEDs there are in each
int number_of_leds = 12;

// set red value
int red = 255;

// number of pixels (i.e. LEDs in ring, put number of LEDs in array times number arrays)
#define NUMPIXELS number_of_leds * number_of_rings

// parameters are number of pixels, which pin, pixel type (Neo, Green, Red, Blue), kHz datastream (800 kHz)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.fill(pixels.Color(red, 0, 0), 0, number_of_leds);
  pixels.show();

}
