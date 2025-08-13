// library for neopixel LEDs
#include <Adafruit_NeoPixel.h>

// specifies AVR microcontroller (arduino, as opposed to other models with different microcontrollers)
#ifdef __AVR__
#include <avr/power.h>
#endif

// which pin is outputs to LEDs
#define PIN 12

// define how many rings there are
int number_of_rings = 2;

// define how many LEDs there are in each
int number_of_leds = 7;

// number of pixels (i.e. LEDs in ring, put number of LEDs in array times number arrays)
#define NUMPIXELS number_of_leds* number_of_rings

// parameters are number of pixels, which pin, pixel type (Neo, Green, Red, Blue), kHz datastream (800 kHz)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


// for individual ring timings (long and short durations)
unsigned long start_count_long;   // takes initial start of Millis() for long condition
unsigned long start_count_short;  // same for short
unsigned long accumulator_long;   // counter from beggining of programme for long condition
unsigned long accumulator_short;  // same for short

// Assign the periods for the on/off state in milliseconds
const unsigned long long_period = 2500;
const unsigned long short_period = 500;

bool lng = true;  // set boolean to switch between states
bool sht = true;

// make boolean for the overall condition that will change whether a ring is in the 'long' or 'short' state
bool switching = true;

// need a time register and accumulator for the long period that will control the state 'switching'
unsigned long start_count_global;
unsigned long accumulator_global;

// set the period for 'switching'
const unsigned long global_period = 10000; // (test with small value first i.e. 20s)

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  start_count_long = millis();  // set start time for comparison of duration against accumulator
  start_count_short = millis();
  start_count_global = millis();
}

void loop() {

  accumulator_long = millis();  // set accumultaor to current millisecond after start of programme
  accumulator_short = millis();
  accumulator_global = millis();
  

  // make loop for when 'switching' == flase or true
  if (switching == false)
  {
    // put one condition here
      if (lng == true)  // check state of booleans
    {
      pixels.fill(pixels.Color(0, 0, 255), 0, 7); // parameters: RGB, starting pixel, number of pixels to fill from starting pixel
      pixels.show();
    } else {
      pixels.fill(pixels.Color(0, 0, 0), 0, 7);
      pixels.show();
    }
    if (sht == true) {
      pixels.fill(pixels.Color(0, 0, 255), 7, 7);
      pixels.show();
    } else {
      pixels.fill(pixels.Color(0, 0, 0), 7, 7);
      pixels.show();
    }
  } else {
    // put other condition here
      if (lng == true)  // check state of booleans
    {
      pixels.fill(pixels.Color(0, 0, 255), 7, 7); // parameters: RGB, starting pixel, number of pixels to fill from starting pixel
      pixels.show();
    } else {
      pixels.fill(pixels.Color(0, 0, 0), 7, 7);
      pixels.show();
    }
    if (sht == true) {
      pixels.fill(pixels.Color(0, 0, 255), 0, 7);
      pixels.show();
    } else {
      pixels.fill(pixels.Color(0, 0, 0), 0, 7);
      pixels.show();
    }
  }


  

  if (accumulator_long - start_count_long >= long_period)  // compare elapsed duration
  {
    lng = !lng;  // switch state of bools
    start_count_long = accumulator_long;
  }

  if (accumulator_short - start_count_short >= short_period) {
    sht = !sht;
    start_count_short = accumulator_short;
  }

  // Do time calculation here for the 'switching' boolean
  if (accumulator_global - start_count_global >= global_period) {
    switching = !switching;
    start_count_global = accumulator_global;
  }

 Serial.println(switching);

}