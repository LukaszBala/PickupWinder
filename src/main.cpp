#include <Arduino.h>
#include <Wire.h>
#include "Config.h"
#include "Run.h"

using namespace std;  
Run* runner;

void isr();
void initWinder();
void(* resetFunc) (void) = 0;

void setup() {
  TCCR1B = TCCR1B & B11111000 | B00000001;
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

  runner = new Run();

  attachInterrupt(digitalPinToInterrupt(backBtn), resetFunc, HIGH);

  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
}