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
    materials = new Material[6] {
        Material("Copper", 1.68E-8),
        Material("Silver", 1.59E-8),
        Material("Gold", 2.44E-8),
        Material("Aluminium", 2.65E-8),
        Material("Wolfram", 5.60E-8),
        Material("Nikiel", 6.99E-8),
         };
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
        targetResistance();
        break;
    default:
        break;
    }
    encoderCounter = 0;
    menu->setOpt(encoderCounter);
}

void Run::targetResistance(){
    encoderCounter = 0;
    int intPart = 0;
    int dotPart = 0 ;
    int materialIndex = 0;
    int materialSize = sizeof(*materials)/sizeof(materials);
    double resistance = 0;
    double diameter = 0;
    double perimeter = 0;
    double length = 0;
    int coils = 0;
    menu->printResistance(0);
    while(digitalRead(BTN) == previousBtn){}
    while(digitalRead(BTN) != 0){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            intPart = encoderCounter;
            menu->printResistance(double(intPart), 1);
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    while(digitalRead(BTN) == previousBtn){}
    while(digitalRead(BTN) != 0){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            dotPart = encoderCounter;
            resistance = double((double)intPart + (double)dotPart/100);
            menu->printResistance(resistance, 1);
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    while(digitalRead(BTN) == previousBtn){}
    while(digitalRead(BTN) != 0){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > materialSize)
                encoderCounter = 0;
            materialIndex = encoderCounter;
            String materialResistance = sciNotation(materials[materialIndex].value);
            menu->printMaterial(materials[materialIndex].name, materialResistance);
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    menu->printResistance(diameter, 0, "Wire Diameter");
    while(digitalRead(BTN) == previousBtn){}
    while(digitalRead(BTN) != 0){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 1000;
            if(encoderCounter > 1001)
                encoderCounter = 0;
            dotPart = encoderCounter;
            diameter = double((double)dotPart/100);
            menu->printResistance(diameter, 1, "Wire Diameter");
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    menu->printResistance(diameter, 0, "Coil Perimeter");
    while(digitalRead(BTN) == previousBtn){}
    while(digitalRead(BTN) != 0){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 1000;
            if(encoderCounter > 1001)
                encoderCounter = 0;
            dotPart = encoderCounter;
            perimeter = double((double)dotPart/100);
            menu->printResistance(perimeter, 1, "Coil Perimeter");
            updateScreen = false;
        }
    }

    length = (resistance*1000*PI*(diameter/100*diameter/100))/(4*materials[materialIndex].value);
    coils = length / perimeter;
    while(digitalRead(BTN) == previousBtn){}
    menu->printCoils(coils, length/100);
    while(digitalRead(BTN) != 0){}

    windCoils(coils, 60);
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

void Run::setDirection(int direction){
    if(direction) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
    }
}

void Run::windCoils(int maxRounds, int speed) {
    int direction = 1;
    encoderCounter = 0;
    menu->printDirection(direction);
    while(digitalRead(BTN) == previousBtn){}
    while(digitalRead(BTN) != 0){
        if( updateScreen) {
            direction = !direction;
            menu->printDirection(direction);
            updateScreen = false;
        }
    }
    setDirection(direction);
    encoderCounter = 0;
    menu->onBtnClick();
    detachInterrupt(digitalPinToInterrupt(CLK));
    // long readTime;
    // long lastReadTime = 0;
    int prevOut = 0;
    int oldSpeed = 0;
    menu->printRun(map(speed, 100, 255, 0, 100), 0, direction);
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
                menu->printRun(speedTemp, counter, direction);
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

String Run::sciNotation(double num){
    int zeros = 0;
    double helper = num;
    while((int) helper == 0){
        helper *= 10;
        zeros++;
    }
    String res = String(helper);
    res.concat("E-");
    res.concat(zeros);
    return res;
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