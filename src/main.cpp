#include <Arduino.h>
#include <i2c/LiquidCrystal_I2C.h>
#include <Wire.h>
#include "Menu.h"

#define hallPin 2

#define redLed 3
#define backBtn 4
#define greenLed 5

#define enA 6
#define in1 7
#define in2 8

#define BTN 10
#define DT 11
#define CLK 12

using namespace std;  


LiquidCrystal_I2C lcd(0x27, 16, 2);

int speed = 0;
String speedStr;
int oldSpeed = 0;
int hall = 0;
int oldHall = 0;
int counter = 0;

int Previous_Output;
int Encoder_Count = 0;
int btnPressed = 0;
int previousBtn = 0;
Menu* menu;

void reset();

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

  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);

  // Set initial rotation direction
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  menu = new Menu(&lcd);

  
  Previous_Output = digitalRead(DT);
  lcd.print(Previous_Output);
  
  
}
void loop() {
  if(digitalRead(backBtn) == 1)
    reset();

  if (digitalRead(DT) != Previous_Output)
   {
     if (digitalRead(CLK) != Previous_Output)
     {
       Encoder_Count ++;
       menu->opt = Encoder_Count;
       menu->printMenu();
     }
      else
     {
       Encoder_Count--;
       menu->opt = Encoder_Count;
       menu->printMenu();
     }
   }

   Previous_Output = digitalRead(DT);

  //  btnPressed = digitalRead(BTN);

  //  if (btnPressed == 0)
  //  {
  //    lcd.clear(); 
  //    lcd.setCursor(0, 1); 
  //    lcd.print("Switch pressed");
  //  }

  
  speed = 150;//Odczytanie wartości z ADC   
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
  menu->setup();
  speed = 0;
  speedStr = "";
  oldSpeed = 0;
  hall = 0;
  oldHall = 0;
  counter = 0;

  // Previous_Output = 0;
  Encoder_Count = 0;
  btnPressed = 0;
  previousBtn = 0;
}