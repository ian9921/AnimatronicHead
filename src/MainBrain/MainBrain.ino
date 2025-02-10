#include <Servo.h>
#include <Key.h>
#include <Keypad.h>

#include <Arduino_BuiltIn.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket

#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    13
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 20

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);


const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
//variables for blinking effect
const int delayConst = 10; //how long a blink should last
int blinkDelay = delayConst;

Servo servo;
Servo servo2;

int s1State[90];
int s2State[90];

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

  servo.attach(12);
  servo.write(10);

  servo2.attach(11);
  servo2.write(170);
  Serial.begin(57600);

  for(int i = 0; i < 90; i++){
    s1State[i] = 135 - i;
    s2State[i] = 45 + i;
  }
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  const uint32_t orange = strip.Color(255, 64, 0);
  const uint32_t red = strip.Color(255, 0, 0);
  const uint32_t off = strip.Color(0, 0, 0);
  const int r = 255, g = 64, b = 15;
  
  static int blink = 10; //stores random number for if we should blink
  const int chance = 20; //chances of blink occuring

  static uint32_t oldEye;
  static uint32_t eye; //color to make the eyes, controlls blinking effect
  
  static bool manual = 0; //bool dictating manual control of eyes or automatic, 0 = auto
  static bool eyeControl; 
  bool temp = 1;
  static bool binBlink = 0;

  //CHECK FOR INPUTS

  char key = customKeypad.getKey();
  Serial.println(key);
  if (key == '*'){
    manual = !manual;
    Serial.println(manual);
  }

  Serial.println(manual);
  if (manual == 0){
    blinkDelay --; 
    if (blinkDelay <= 0){ //when delay is done after previous blink, see if we blink again
      blink = random(0, chance);
      blinkDelay = delayConst;
    }

    oldEye = eye;
    if (blink == 0) { //if we generated zero, we blink
      eye = off;
    }
    else 
    {
      eye = red;
    }

    if (eye != oldEye){
      blinkS(servo, servo2);
    }
        
  } else {
    //key = customKeypad.getKey();
    
    if (key == '7'){
      binBlink = !binBlink;
    }
    oldEye = eye;
    if (binBlink == 0) { //if button is pressed, we blink
      eye = off;
    }
    else 
    {
      eye = red;
    }
    if (eye != oldEye){
      blinkS(servo, servo2);
    }  
  }
  flicker(r, g, b, 10);
  eyes(eye, 11, LED_COUNT); //write the results of the blink


  //end of lights, start of servos
  //turnServo();
}

//simple test function to make sure the servo is properly configured
void turnServo(){
  for(int angle = 10; angle < 100; angle++)  
  {                                  
    servo.write(angle);           
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(int angle = 90; angle > 10; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  } 
}

void blinkS(Servo lid1, Servo lid2){
  static bool openClosed = 1; //1 = open, 
  
  if (openClosed == 0){
    for (int angle = 0; angle < 90; angle++){
      lid1.write(s1State[angle]);
      lid2.write(s2State[angle]);
      delay(1);
    }
  } else {
    for (int angle = 90; angle > 0; angle--){
      lid1.write(s1State[angle]);
      lid2.write(s2State[angle]);
      delay(1);
    }
  }
  openClosed = !openClosed;
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

