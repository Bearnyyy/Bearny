#include <FastLED.h>
#include <OneButton.h>

#define NUM_LEDS  10
#define LED_PIN   13
#define BTN_PIN   4

CRGB leds[NUM_LEDS];

uint8_t color = 32;
uint8_t hue = 0;
uint8_t patternCounter = 0;

OneButton btn = OneButton(BTN_PIN, true, true);

void setup() {
  
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
    FastLED.setCorrection(TypicalPixelString);
  Serial.begin(57600);
   btn.attachLongPressStart(nextPattern); //changes the modes
   btn.attachClick(nextColor); //changes the base color
}

void loop() {

  switch (patternCounter) {
    case 0:
      baseColor();
      break;
    case 1:
      rainbow();
      break;
  }
  
  FastLED.show();
  btn.tick();
  //delay(50);
}

void nextPattern() {
  patternCounter = (patternCounter + 1) % 2;
}
void nextColor() {
  color = color + 32; 
}
//--------------------------------------------------------      Modes
void baseColor(){ 
    uint8_t oneBeat = beatsin8(30, 200, 255, 0, 0); //sin1
    uint8_t twoBeat = beatsin8(60, 200, 255, 0, 0); //sin2
    uint8_t treeBeat = beatsin8(90, 200, 255, 0, 0); //sin2
      uint8_t sinBeat = (oneBeat + twoBeat + treeBeat)/3;  
  fill_solid(leds, NUM_LEDS, CHSV(color, 255, sinBeat));   //base color with alternating/breathing brightnes
}

void rainbow()  {
    uint8_t oneBeat = beatsin8(30, 200, 255, 0, 0); //sin1
    uint8_t twoBeat = beatsin8(60, 200, 255, 0, 0); //sin2
    uint8_t treeBeat = beatsin8(90, 200, 255, 0, 0); //sin2
      uint8_t sinBeat = (oneBeat + twoBeat + treeBeat)/3;  
      
for (int i = NUM_LEDS/2; i < NUM_LEDS; i++) {  //front
    leds[ (NUM_LEDS-1) - i ] = CHSV(hue + (i * 10), 255, sinBeat);
 }
   for (int j = NUM_LEDS/2; j < NUM_LEDS; j++) { //back
    leds[j] = CHSV(hue + (j * 10), 255, sinBeat);
 }    

  EVERY_N_MILLISECONDS(15){
    hue++;
  } 
}
