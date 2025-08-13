#include <Adafruit_NeoPixel.h>

#define PIN 12
#define NUM_RINGS 2
#define LEDS_PER_RING 7
#define NUMPIXELS NUM_RINGS * LEDS_PER_RING

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Pattern durations
const unsigned long SHORT_DURATION = 500;
const unsigned long LONG_DURATION  = 2500;

// Each ring needs its own state
struct RingState {
  int startLED;  // Starting pixel index
  bool ledOn;    // Whether LEDs are currently ON or OFF
  bool shortPhase;  // Whether in short or long phase
  unsigned long lastChangeTime;
  unsigned long currentDuration;

  void update(unsigned long now) {
    if (now - lastChangeTime >= currentDuration) {
      ledOn = !ledOn;

      // Only change phase when turning ON
      if (ledOn) {
        shortPhase = !shortPhase;
        currentDuration = shortPhase ? SHORT_DURATION : LONG_DURATION;
      }

      lastChangeTime = now;

      // Update the LED ring state
      if (ledOn) {
        pixels.fill(pixels.Color(0, 0, 255), startLED, LEDS_PER_RING);
      } else {
        pixels.fill(pixels.Color(0, 0, 0), startLED, LEDS_PER_RING);
      }
      pixels.show();
    }
  }
};

RingState ring1 = {0, true, true, 0, SHORT_DURATION};             // Start with 0.5s ON
RingState ring2 = {LEDS_PER_RING, true, false, 0, LONG_DURATION}; // Start with 2.5s ON

void setup() {
  pixels.begin();
  ring1.lastChangeTime = millis();
  ring2.lastChangeTime = millis();
}

void loop() {
  unsigned long now = millis();
  ring1.update(now);
  ring2.update(now);
}
