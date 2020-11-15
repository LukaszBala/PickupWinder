#include <Arduino.h>
#include <i2c/LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Config.h"
#include "Menu.h"

using namespace std;  

LiquidCrystal_I2C lcd(0x27, 16, 2);

int speed = 0;
String speedStr;
int oldSpeed = 0;
int hall = 0;
int oldHall = 0;
int counter = 0;
bool updateScreen = false;
int encoderCounter = 0;

int Previous_Output;
int btnPressed = 0;
int previousBtn = 0;
Menu* menu;

void reset();
void isr();
void initWinder();

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
  if(digitalRead(backBtn) == 1)
    reset();

  if(updateScreen)
  {
    menu->setOpt(encoderCounter);
    encoderCounter = menu->getOpt();
    menu->printMenu();
    updateScreen = false;
  }
  btnPressed = digitalRead(BTN);
  if(btnPressed == 0 && btnPressed != previousBtn){
    menu->onBtnClick();
    updateScreen = true;
  }
  previousBtn = btnPressed;

  // if (digitalRead(DT) != Previous_Output)
  //  {
  //    if (digitalRead(CLK) != Previous_Output)
  //    {
  //      encoderCounter++;
  //      menu->setOpt(encoderCounter);
  //      encoderCounter = menu->getOpt();
  //      menu->printMenu();
  //    }
  //     else
  //    {
  //      encoderCounter--;
  //      menu->setOpt(encoderCounter);
  //      encoderCounter = menu->getOpt();
  //      menu->printMenu();
  //    }
  //  }

  //  Previous_Output = digitalRead(DT);

  
  // speed = 150;//Odczytanie wartości z ADC   
  // hall = digitalRead(hallPin);
  // // speed = map(speed, 0, 1023, 60, 255);//Przeskalowanie wartości
  
  // String str = String(speed);
  // if (speed > 100) 
  //   analogWrite(enA, speed);
  // else
  //   analogWrite(enA, 0);
  // oldSpeed = speed;
  // if(hall != oldHall && hall == 0) {
  //   counter++;
  //   lcd.clear();
  //   lcd.print(counter);
  // }
  // oldHall = hall;

}

void reset(){

  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);

  for(int i = 0; i < 3; i++){
    digitalWrite(greenLed, HIGH);
    digitalWrite(redLed, HIGH);
    
    delay(100);

    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, LOW);

    if(i < 2)
      delay(100);
  }

  menu->setup();

  speed = 0;
  speedStr = "";
  oldSpeed = 0;
  hall = 0;
  oldHall = 0;
  counter = 0;
  // Previous_Output = 0;
  encoderCounter = 0;
  btnPressed = 0;
  previousBtn = 0;

  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
}

void isr(){
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 5) {
    if (digitalRead(DT) == LOW)
    {
      encoderCounter-- ;
    }
    else {
      encoderCounter++ ;
    }

    updateScreen = true;
  }
  lastInterruptTime = interruptTime;
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

  menu = new Menu(&lcd);
  attachInterrupt(digitalPinToInterrupt(CLK), isr, LOW);

  Previous_Output = digitalRead(DT);

  speed = 0;
  speedStr = "";
  oldSpeed = 0;
  hall = 0;
  oldHall = 0;
  counter = 0;
  // Previous_Output = 0;
  encoderCounter = 0;
  btnPressed = 0;
  previousBtn = 0;

  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
}