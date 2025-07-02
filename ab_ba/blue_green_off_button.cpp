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

unsigned long start_count;   // takes initial start of Millis() 

unsigned long accumulator;   // counter from beggining of programme 

// Assign the periods for the colours in milliseconds
const unsigned long period = 250;
const unsigned long delay_period = 1500;
int intensity = 100;

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
  start_count = millis();  // set start time for comparison of duration against accumulator
  pinMode(button, INPUT);
}

void loop() {
  if (but_val == 1){
    accumulator = millis();  // set accumultaor to current millisecond after start of programme

    if (accumulator - start_count <= period){ // for first period show blue
      pixels.fill(pixels.Color(0, 0, intensity), 0, number_of_leds*2);
      pixels.show();
    }
    if ((accumulator - start_count > period) && (accumulator - start_count <= period*2)){ // after first period and before second show green
      pixels.fill(pixels.Color(0, intensity, 0), 0, number_of_leds*2);
      pixels.show();
    }
    if ((accumulator - start_count > period*2) && (accumulator - start_count <= period*3)){ // after second period and before 5x period show nothing. If period is one second it will be 1 sec blue, 1 sec green 3 sec nothing
      pixels.fill(pixels.Color(0, 0, 0), 0, number_of_leds*2);
      pixels.show();
    }
    if (accumulator - start_count > (period*3+delay_period)){
      start_count = accumulator;
    }
  }
  if (but_val == 2){
    accumulator = millis();  // set accumultaor to current millisecond after start of programme

    if (accumulator - start_count <= period){
      pixels.fill(pixels.Color(0, intensity, 0), 0, number_of_leds*2);
      pixels.show();
    }
    if ((accumulator - start_count > period) && (accumulator - start_count <= period*2)){
      pixels.fill(pixels.Color(0, 0, intensity), 0, number_of_leds*2);
      pixels.show();
    }
    if ((accumulator - start_count > period*2) && (accumulator - start_count <= period*3)){
      pixels.fill(pixels.Color(0, 0, 0), 0, number_of_leds*2);
      pixels.show();
    }
    if (accumulator - start_count > (period*3+delay_period)){
      start_count = accumulator;
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



