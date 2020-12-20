#include "Run.h"


Run *pointerToClass; 
bool updateScreen = false;
int encoderCounter = 0;

static void outsideInterruptHandler(void) { 
  pointerToClass->interruptLaunch();
}

Run::Run(){
    counter = 0;
    buttonPressed = 0;
    menu = new Menu();
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
        previousBtn = btnPressed;
        runOption();
        menu->printMenu();
        updateScreen = false;
    }
    previousBtn = btnPressed;
}

void Run::runOption(){
    switch (menu->getOpt())
    {
    case 1:
        windCoils();
        break;
    case 2:
        autoStop();
        break; 
    case 3:
        break;
    default:
        break;
    }
    encoderCounter = 0;
    menu->setOpt(encoderCounter);
}

void Run::autoStop(){
    int maxRounds = 0;
    encoderCounter = 0;
    menu->printAuto(maxRounds);
    while(digitalRead(BTN) == previousBtn){}
    while(digitalRead(BTN) != 0){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            maxRounds = encoderCounter;
            menu->printAuto(maxRounds);
            updateScreen = false;
        }
    }
    menu->onBtnClick();
    windCoils(maxRounds, 200);
}

void Run::windCoils(int maxRounds, int speed) {
    detachInterrupt(digitalPinToInterrupt(CLK));
    // long readTime;
    // long lastReadTime = 0;
    int prevOut = 0;
    int oldSpeed = 0;
    menu->printRun(map(speed, 100, 255, 0, 100), 0);
    while(maxRounds == -1 || counter < maxRounds)
        {
            if (digitalRead(DT) != prevOut)
            {
                if (digitalRead(CLK) != prevOut)
                {
                     if(speed < 255)
                        speed += 2;
                    if(speed > 255)
                        speed = 255;
                }
                else
                {
                    if(speed > 100)
                        speed -= 2;
                }
            }
            prevOut = digitalRead(DT);
            
            // readTime = millis();
            // if (readTime - lastReadTime > 5) {
            //     if (digitalRead(DT) == HIGH)
            //     {
            //         if(speed < 255)
            //             speed += 2;
            //         if(speed > 255)
            //             speed = 255;
            //     }
            //     else
            //     {
            //         if(speed > 100)
            //             speed -= 2;
            //     }
            // }
            // lastReadTime = readTime;


            prevOut = digitalRead(DT);

            hall = digitalRead(hallPin);

            // analogWrite(enA,speed);
            if (speed > 100) 
                analogWrite(enA, speed);
            else
                analogWrite(enA, 0);
            int speedTemp = map(speed, 100, 255, 0, 100);
            if((oldSpeed != speedTemp) || (hall != oldHall && hall == 0)) {
                if(hall != oldHall && hall == 0)
                    counter++;
                menu->printRun(speedTemp, counter);
            }
            oldHall = hall;
            oldSpeed = speedTemp;

            if(digitalRead(BTN) == 0 ){
                if(buttonPressed > 0){
                    if(millis() - buttonPressed > 1000)
                    break;
                }
            } else {
                buttonPressed = millis();
            }
        }
        buttonPressed = 0;
        counter = 0;
        speed = 0;
        maxRounds = 0;
        analogWrite(enA,0);
        attachInterrupt(digitalPinToInterrupt(CLK), outsideInterruptHandler, LOW);
}

void Run::interruptLaunch(){
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if(digitalRead(BTN) != 0){
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
  }
  lastInterruptTime = interruptTime;
}