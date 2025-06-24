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
int number_of_leds = 16;

// number of pixels (i.e. LEDs in ring, put number of LEDs in array times number arrays)
#define NUMPIXELS number_of_leds* number_of_rings

// parameters are number of pixels, which pin, pixel type (Neo, Green, Red, Blue), kHz datastream (800 kHz)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long start_count_long;   // takes initial start of Millis() for long condition
unsigned long start_count_short;  // same for short
unsigned long accumulator_long;   // counter from beggining of programme for long condition
unsigned long accumulator_short;  // same for short

// Assign the periods for the on/off state in milliseconds
const unsigned long long_period = 2500;
const unsigned long short_period = 500;

bool lng = true;  // set boolean to switch between states
bool sht = true;

/////////////////////////////////////////////////////////
/// FOR BUTTONS /////////////////////////////////////////
/////////////////////////////////////////////////////////

int button = 8; // set pin for button

int but_val = 0; // set value for button presses. Will be 0, 1 or 2

unsigned long but_time = 0; // to hold time from last button press

unsigned long debounce = 200UL; // need delay to not register multiple presses

int reading; // empty variable for reading from button (will be HIGH when pressed)





void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  start_count_long = millis();  // set start time for comparison of duration against accumulator
  start_count_short = millis();
  pinMode(button, INPUT);
}

void loop() {

  if (but_val == 1){
    accumulator_long = millis();  // set accumultaor to current millisecond after start of programme
    accumulator_short = millis();

   if (lng == true)  // check state of booleans
   {
     pixels.fill(pixels.Color(0, 0, 255), 0, number_of_leds*2); // parameters: RGB, starting pixel, number of pixels to fill from starting pixel
     pixels.show();
   } else {
     pixels.fill(pixels.Color(0, 0, 0), 0, number_of_leds*2);
     pixels.show();
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
  }

  if (but_val == 2){
    accumulator_long = millis();  // set accumultaor to current millisecond after start of programme
    accumulator_short = millis();

   if (sht == true) {
     pixels.fill(pixels.Color(0, 0, 255), 0, number_of_leds*2);
     pixels.show();
   } else {
     pixels.fill(pixels.Color(0, 0, 0), 0, number_of_leds*2);
     pixels.show();
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
  }
  if (but_val == 3){
    pixels.fill(pixels.Color(0, 0, 0), 0, number_of_leds*number_of_rings); // parameters: RGB, starting pixel, number of pixels to fill from starting pixel
    pixels.show();
  }

  reading = digitalRead(button);

  if (reading == HIGH && but_val != 3 && millis() - but_time > debounce){
   but_val += 1;
   but_time = millis();
  }
  else if (reading == HIGH && but_val == 3 && millis() - but_time > debounce){
   but_val = 1;
   but_time = millis();
  }

}

