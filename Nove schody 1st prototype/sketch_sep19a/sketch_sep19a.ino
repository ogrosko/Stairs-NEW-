#include <Button.h>
#include <Timer.h>
#include <LEDFader.h>

#define PULLUP false
#define INVERT false
#define DEBOUNCE_MS 20 

// constants won't change. They're used here to
// set pin numbers:
//const int buttonPin1 = 3;
//const int buttonPin2 = 4;
//const int buttonPin3 = 5;

const int LDR1 = 1;
const int LDR2 = 2;

const int DARKNESS_TRESHOLD = 600; //[0-1024]

const int FADE_IN_DURATION = 850;
const int FADE_OUT_DURATION = 5000;

Timer timer1;
Timer timer2;
LEDFader led1 = LEDFader(6);
LEDFader led2 = LEDFader(9);

Button pir1(3, PULLUP, INVERT, DEBOUNCE_MS);
Button pir2(4, PULLUP, INVERT, DEBOUNCE_MS);
Button pir3(5, PULLUP, INVERT, DEBOUNCE_MS);

//int pirState1 = 0;
//int pirState2 = 0;

int ldrState1 = 0;
int ldrState2 = 0;

int led1OffPointer;
int led2OffPointer;

void setup() {
  //pinMode(buttonPin1, INPUT);
  //pinMode(buttonPin2, INPUT);
  //Serial.begin(9600);
}

void loop() {
  pir1.read();
  pir2.read();
  pir3.read();
  
  // read the state of the photoresistors
  ldrState1 = analogRead(LDR1);
  ldrState2 = analogRead(LDR2);
  
  //if is dark enviroment
  if(ldrState1 < DARKNESS_TRESHOLD) {
    if  (led1.is_fading() == false) {
      if (pir1.wasPressed() || pir2.wasPressed()) {
        if (led1OffPointer) timer1.stop(led1OffPointer);
        led1.fade(255, FADE_IN_DURATION); 
      }
      
      if (led1.get_value() == 255) {
        led1OffPointer = timer1.after(15000, turnLedOff1);
      }
    }
    else {
      if (pir1.wasPressed() || pir2.wasPressed()) {
        led1.stop_fade();
        led1.fade(255, FADE_IN_DURATION); 
      }
    }
  }
  else {//if is bright enviroment
    if (led1.is_fading() == false && led1.get_value() == 255) {
      led1.fade(0, FADE_IN_DURATION);
    }
  }
  
  
  //--------------------------------------
  if(ldrState2 < DARKNESS_TRESHOLD) {
    if  (led2.is_fading() == false) {
      if (pir3.wasPressed()) {
        led2.fade(255, FADE_IN_DURATION); 
      }
      
      if (led2.get_value() == 255) {
        led2OffPointer = timer2.after(13000, turnLedOff2);
      }
    }
    else {
      if (pir2.wasPressed()) {
        led2.stop_fade();
        led2.fade(255, FADE_IN_DURATION); 
      }
    }
  }
  else {//if is bright enviroment
    if (led2.is_fading() == false && led2.get_value() == 255) {
      led2.fade(0, FADE_IN_DURATION);
    }
  }
  
  led1.update();
  led2.update();
  timer1.update();
  timer2.update();
}

void turnLedOff1() {
  led1.fade(0, FADE_OUT_DURATION);
}

void turnLedOff2() {
  led2.fade(0, FADE_OUT_DURATION);
}

