#include <Arduino_BuiltIn.h>

// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket

#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    12

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 20

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


//variables for blinking effect
const int delayConst = 10; //how long a blink should last
int blinkDelay = delayConst;


// setup() function -- runs once at startup --------------------------------
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(255); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  const uint32_t orange = strip.Color(255, 64, 0);
  const uint32_t red = strip.Color(255, 0, 0);
  const uint32_t off = strip.Color(0, 0, 0);
  const int r = 255, g = 64, b = 15;
  
  int blink = 10; //stores random number for if we should blink
  const int chance = 20 //chances of blink occuring

  static uint32_t eye; //color to make the eyes, controlls blinking effect
  
  blinkDelay --; 
  if (blinkDelay <= 0){ //when delay is done after previous blink, see if we blink again
    blink = random(0, chance);
    blinkDelay = delayConst;
  }

  if (blink == 0) { //if we generated zero, we blink
    eye = off;
  }
  else 
  {
    eye = red;
  }

  
  flicker(r, g, b, 10);
  eyes(eye, 11, LED_COUNT); //write the results of the blink
}

void eyes(uint32_t color, int first, int last) {
  for (int i = first; i < last; i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void flicker(int r, int g, int b, int last) {
  //int r = 226, g = 121, b = 35;

  for(int i=0; i<(last+1); i++) {
    int flicker = random(0,55);
    int r1 = r-flicker;
    int g1 = g-flicker;
    int b1 = b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    strip.setPixelColor(i,r1,g1, b1);
  }
  strip.show();
  delay(random(10,113));
}

