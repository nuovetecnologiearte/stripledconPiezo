#include <FastLED.h>

#define NUM_LEDS  15
#define LED_PIN   5

CRGB leds[NUM_LEDS];
uint8_t paletteIndex = 0;

DEFINE_GRADIENT_PALETTE( RPM_gp ) { 
0,0,0,0,
//63 ,18,157,4, 
//127, 17, 174,242,
//179, 107, 15, 221,
//200, 235, 63, 196,
//238, 255, 0, 0, 
//255, 255, 0, 0,
};

const byte POTH            = A0;
int throttle     = 0;
int rpm         = 0;

CRGBPalette16 myPAL = RPM_gp;

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear();
  Serial.begin(115200);
  Serial.println (" ");
  Serial.println ("Throttle Test");
  }

void loop() {
  fadeToBlackBy(leds, NUM_LEDS, 5);
  throttle = analogRead(POTH); //0 to 1023
  rpm = map(throttle, 0, 200, NUM_LEDS,0);
  rpm = constrain(rpm, 0, NUM_LEDS);
  fill_palette (leds, rpm, paletteIndex, 255 / NUM_LEDS, myPAL, 255, LINEARBLEND);
  FastLED.show();
  Serial.print(throttle);
  Serial.print("- throttle       led - ");
  Serial.println(rpm);
}