#include <Timer.h>
#include <LEDFader.h>

// constants won't change. They're used here to
// set pin numbers:
const int buttonPin1 = 3;
const int buttonPin2 = 4;
const int buttonPin3 = 5;

const int LDR1 = 1;
const int LDR2 = 2;

const int DARKNESS_TRESHOLD = 750; //[0-1024]

const int FADE_IN_DURATION = 500;
const int FADE_OUT_DURATION = 5000;

Timer timer;
LEDFader led1 = LEDFader(6);
LEDFader led2 = LEDFader(9);


int buttonState1 = 0;
int buttonState2 = 0;

int ldrState1 = 0;
int ldrState2 = 0;

int led1OffPointer;
int led2OffPointer;

void setup() {
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1) | digitalRead(buttonPin2);
  buttonState2 = digitalRead(buttonPin3);
  
  // read the state of the photoresistors
  ldrState1 = analogRead(LDR1);
  ldrState2 = analogRead(LDR2);
  Serial.print("LDR1: ");
  Serial.println(ldrState1);
  Serial.print("LDR2: ");
  Serial.println(ldrState2);
  
  //if is dark enviroment
  if(ldrState1 < DARKNESS_TRESHOLD) {
    if  (led1.is_fading() == false) {
      if (buttonState1 == HIGH) {
        if (led1OffPointer) timer.stop(led1OffPointer);
        led1.fade(255, FADE_IN_DURATION); 
      }
      
      if (led1.get_value() == 255) {
        led1OffPointer = timer.after(2000, turnLedOff1);
      }
    }
    else {
      if (buttonState1 == HIGH) {
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
      if (buttonState2 == HIGH) {
        led2.fade(255, FADE_IN_DURATION); 
      }
      
      if (led2.get_value() == 255) {
        led2OffPointer = timer.after(2000, turnLedOff2);
      }
    }
    else {
      if (buttonState2 == HIGH) {
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
  timer.update();
}

void turnLedOff1() {
  led1.fade(0, FADE_OUT_DURATION);
}

void turnLedOff2() {
  led2.fade(0, FADE_OUT_DURATION);
}

