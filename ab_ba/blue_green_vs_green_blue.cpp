// library for neopixel LEDs
#include <Adafruit_NeoPixel.h>

// specifies AVR microcontroller (arduino, as opposed to other models with different microcontrollers)
#ifdef __AVR__
#include <avr/power.h>
#endif

// this is a test

// which pin is outputs to LEDs
#define PIN 12

// define how many rings there are
int number_of_rings = 2;

// define how many LEDs there are in each
int number_of_leds = 7;

// define duration for colours
int col_duration_val = 250;
// define duration for off state
int del_val = 1500; 

int intensity = 100;

// number of pixels (i.e. LEDs in ring, put number of LEDs in array times number arrays)
#define NUMPIXELS number_of_leds* number_of_rings

// parameters are number of pixels, which pin, pixel type (Neo, Green, Red, Blue), kHz datastream (800 kHz)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  pixels.begin();
}

void loop() {
  pixels.fill(pixels.Color(0, 0, intensity), 0, 7); // rgb, starting led, how many leds from starting led
  pixels.fill(pixels.Color(0, intensity, 0), 7, 7);
  pixels.show();
  delay(col_duration_val);

  pixels.fill(pixels.Color(0, intensity, 0), 0, 7);
  pixels.fill(pixels.Color(0, 0, intensity), 7, 7);
  pixels.show();
  delay(col_duration_val);

  pixels.clear();
  pixels.show();
  delay(del_val);
}



