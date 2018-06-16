#include <FastLED.h>
#include <Wire.h>
#include "Adafruit_Trellis.h"

//for when the stepper and trellis arent mounted anymore
//LEDS (data) should be in PIN 6
//LEDS ground to GND on Arduino
//LEDS power to 5V on Arduino 
// Comment out for prod to save memory
//#define DEBUG 1

// LEDs
const int LED_PIN = 6;
int isFire = false;
const int LED_START = 31;
const int NUM_LEDS = 231;

// Hex LEDs
const int HEX_LED_START = 211;  // TODO: figure this out
const int HEX_LED_R = 255;
const int HEX_LED_G = 255;
const int HEX_LED_B = 255;

// Thermometer
const int THERMO_START = 0; // First thermo led
const int THERMO_LEVELS[] = {3, 10, 17, 24, 31};
const int THERMO_DELAY = 100; // Delay for slide effect
const int THERMO_COLOR_R = 255;
const int THERMO_COLOR_G = 0;
const int THERMO_COLOR_B = 0;
int thermoLevel = 0;

//How long is each effect on for
long effectTime = 600000;  //10 minutes

CRGB leds[NUM_LEDS];
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0);


void setup() {
  Serial.begin(9600);
  #ifdef DEBUG
    Serial.println("2018 Chairmans starting");
    Serial.println("Start LED");
  #endif

  // LEDs
  FastLED.addLeds<NEOPIXEL,LED_PIN>(leds, NUM_LEDS);
  setAll(255, 0, 0);
  delay(100);
  setHexLEDs(true);
  
  Serial.println("Startup success\n");
}
void loop() {

  setAll(255,0,0);
 /* BIG COMMENT START
  int effect = 0;

  if(effect == 0){
    //cycle colors
    int part = 0;
    setAll(255,0,0);
    
    for(int i = 0; i < NUM_LEDS; i++){        //effect #0 (idk)
      if(part == 0){
        setPortion(255,0,0,i,10);
        part++;
      }else if(part == 1){
        setPortion(255,125,0,i,10);
        part++;
      }else if(part == 2){
        setPortion(255,255,0,i,10);
        part++;
      }else if(part == 3){
        setPortion(0,255,0,i,10);
        part++;
      }else if(part == 4){
        setPortion(0,0,255,i,10);
        part++;
      }else if(part == 5){
        setPortion(120,0,255,i,10);
        part = 0;
      }
    }
    delay(effectTime);
    ledReset(); 
    effect++;
  }else if(effect == 1){        //effect #1 (blue)
    //All blue LEDs
    setBackgroundRGB(0, 0, 255);
    setHexRGB(0, 0, 255);
    setThermoRGB(5, 0, 0, 255);
    delay(effectTime); 
    ledReset();
    effect++;
  }else if(effect == 2){        //effect #1 (green)
    //All green LEDs
    setBackgroundRGB(0, 255, 0);
    setHexRGB(0, 255, 0);
    setThermoRGB(5, 0, 255, 0);
    delay(effectTime); 
    ledReset();
    effect++;
  }else if(effect == 3){        //effect #1 (white)
    //All white LEDs
    setBackgroundRGB(255, 255, 255);
    setHexRGB(255, 255, 255);
    setThermoRGB(5, 255, 255, 255);
    delay(effectTime); 
    ledReset();
    effect++;
  }else if(effect == 4){        //effect #1 (fireLEDS)
    //Fire LEDs
    fireLEDs(false);
    isFire = true; 
    delay(effectTime); 
    ledReset();
    effect++;
  }else{
    effect = 0;
  }
  */
  //BIG COMMENT END
}    

/**
 * Set the background LEDs to fire
 */
void fireLEDs(bool showUpdate) {
  for (int i = LED_START; i < HEX_LED_START; i++) {
    
      leds[i] = getRandomFireColor();
        FastLED.show();
     
  }
}
/**
 * sets the background leds to off
 */
 void quenchLEDs(bool showUpdate) {
  for (int i = LED_START; i < HEX_LED_START; i++) {
    leds[i].setRGB(0,0,0);
    FastLED.show();
    }
   FastLED.show();
  }
/**
 * Returns a CRGB color for fire
 */
CRGB getRandomFireColor() {
  int brightness = random(0,20);
  int r = random(150, 200);
  int g = random(0, 20);
  int b = random(0, 3);
  return CRGB(r+brightness*2, g+brightness, b+brightness);
}

/**
 * Set the hex LEDs
 * bool on
 *  true = LEDs on
 *  false = LEDs off
 */
void setHexLEDs(bool on) {
  #ifdef DEBUG
    Serial.print("set hex ");
    Serial.println(on);
  #endif
  if (on) {
    // Turn on
    setPortion(HEX_LED_R, HEX_LED_G, HEX_LED_B, HEX_LED_START, NUM_LEDS);
  } else {
    // Turn off
    setPortion(0, 0, 0, HEX_LED_START, NUM_LEDS);
  }
}

/**
 * Set all LEDs to one color
 * int r, g, b - color
 */
void setAll(int r, int g, int b) {
  setPortion(0, 0, 0, LED_START, NUM_LEDS);
}

/**
 * Set a prtion of LEDs to a color
 * int r, g, b - color
 * int start - first LED
 * int finish - last led
 */
void setPortion(int r, int g, int b, int start, int finish) {
  #ifdef DEBUG
    Serial.print("setPortion: ");
    Serial.print(start);
    Serial.print(" | ");
    Serial.println(finish);
  #endif
  for (int i = start; i < finish; i++) {
    leds[i].setRGB( r, g, b);
  }
  FastLED.show();
}

/**
 * Set a portion of LEDs with a delay between each LED
 * creates a slide effect
 * int r, g, b - color
 * int start - first LED
 * int finish - las led
 */
void setPortion(int r, int g, int b, int start, int finish, int wait) {
  #ifdef DEBUG
    Serial.print("setPortion");
    Serial.print(start);
    Serial.print(" | ");
    Serial.println(finish);
  #endif
  for (int i = start; i < finish; i++) {
    leds[i].setRGB( r, g, b);
    FastLED.show();
    delay(wait);
  }
}

/**
 * Set the thermometer LEDs
 * int level - level to set
 *  0 to 5
 *  0 = off
 *  1-5 = thermo levels
 */
void setThermo(int level) {
  thermoLevel = level % 6;
  #ifdef DEBUG
    Serial.print("Set thermo level: ");
    Serial.println(level);
  #endif
  if (thermoLevel == 0) {
    // Set all thermo LEDs to off
    setPortion(0, 0, 0, 0, LED_START);
  } else {
    // Set thermo leds
    int lowBound = THERMO_START;
    if (level > 1) {
      lowBound = THERMO_LEVELS[level-2];
    }
    setPortion(THERMO_COLOR_R, THERMO_COLOR_G, THERMO_COLOR_B, lowBound, THERMO_LEVELS[level-1], THERMO_DELAY);
  } 
}

void setThermoRGB(int level, int R, int G, int B){
thermoLevel = level % 6;
  if (thermoLevel == 0) {
    // Set all thermo LEDs to off
    setPortion(0, 0, 0, 0, LED_START);
  } else {
    // Set thermo leds
    int lowBound = THERMO_START;
    if (level > 1) {
      lowBound = THERMO_LEVELS[level-2];
    }
    setPortion(R, G, B, lowBound, THERMO_LEVELS[level-1], THERMO_DELAY);
  } 
}

void setHexRGB(int R, int G, int B){
  setPortion(R, G, B, HEX_LED_START, NUM_LEDS);
}

void setBackgroundRGB(int R, int G, int B){
  setPortion(R, G , B, LED_START, HEX_LED_START);
}

void ledReset(){
 for (int i = LED_START; i < NUM_LEDS; i++) {
    leds[i].setRGB(0,0,0);
    FastLED.show();
  }
}