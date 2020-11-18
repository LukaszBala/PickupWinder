#include <Arduino.h>
#include <Wire.h>
#include "Config.h"
#include "Run.h"

using namespace std;  
// bool updateScreen;
// int encoderCounter = 0;
Run* runner;

void isr();
void initWinder();
void(* resetFunc) (void) = 0;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(hallPin, INPUT);

  pinMode(BTN, INPUT);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(backBtn, INPUT);

  initWinder();
}

void loop() {

  runner->printMenu();

}



void initWinder(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  for( int i = 0; i < 3; i++){
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, HIGH);

    if(i == 0)
      delay(500);
    else
      delay(250);

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);

    if(i < 2)
      delay(250);
  }
  // updateScreen = false;
  // encoderCounter = 0;

  runner = new Run();

  // attachInterrupt(digitalPinToInterrupt(CLK), isr, LOW);
  attachInterrupt(digitalPinToInterrupt(backBtn), resetFunc, HIGH);

  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
}