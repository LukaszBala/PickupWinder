#include "Run.h"


Run *pointerToClass; 
bool updateScreen = false;
int encoderCounter = 0;

static void outsideInterruptHandler(void) { 
  pointerToClass->interruptLaunch();
}

Run::Run(){
    speed = 0;
    counter = 0;
    prevOut = 0;
    maxRounds = 0;
    buttonPressed = 0;
    menu = new Menu();
    // this->encoderCounter = encoderCounter;
    // this->updateScreen = updateScreen;
    btnPressed = 0;
    previousBtn = 0;
    pointerToClass = this;
    attachInterrupt(digitalPinToInterrupt(CLK), outsideInterruptHandler, LOW);
}

void Run::printMenu(){
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
        detachInterrupt(digitalPinToInterrupt(CLK));
        windCoils();
        attachInterrupt(digitalPinToInterrupt(CLK), outsideInterruptHandler, LOW);
        updateScreen = true;
    }
    previousBtn = btnPressed;
}

void Run::windCoils(){
    while(maxRounds == 0 || counter < maxRounds)
        {
            if (digitalRead(DT) != prevOut)
            {
                if (digitalRead(CLK) != prevOut)
                {
                    if(speed < 255)
                        speed++;
                }
                else
                {
                    if(speed > 0)
                        speed--;
                }
            }

            prevOut = digitalRead(DT);

            hall = digitalRead(hallPin);

            String str = String(speed);
            if (speed > 100) 
                analogWrite(enA, speed);
            else
                analogWrite(enA, 0);
            oldSpeed = speed;
            if(hall != oldHall && hall == 0) {
                counter++;
                menu->printRun(counter);
            }
            oldHall = hall;

            if(digitalRead(BTN) == 0 ){
                if(buttonPressed > 0){
                    if(millis() - buttonPressed > 1000)
                    break;
                }
            } else {
                buttonPressed = millis();
            }
            
        }
}

void Run::interruptLaunch(){
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
    if (!updateScreen)
      updateScreen = true;
  }
  lastInterruptTime = interruptTime;
}