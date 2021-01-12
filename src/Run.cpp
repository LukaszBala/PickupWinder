#include "Run.h"

volatile bool updateScreen = false;
volatile int encoderCounter = 0;
volatile bool intBtnPressed = false;

static void interruptLaunch(){
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if(digitalRead(BTN) != LOW){
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

static void interruptBtn() {
    intBtnPressed = true;
}

Run::Run(){
    counter = 0;
    buttonPressed = 0;
    menu = new Menu();
    btnPressed = 0;
    previousBtn = 0;
    attachInterrupt(digitalPinToInterrupt(CLK), interruptLaunch, LOW);
    attachInterrupt(digitalPinToInterrupt(BTN), interruptBtn, FALLING);
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
    if(intBtnPressed){
        runOption();
        menu->printMenu();
        updateScreen = false;
    }
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
    menu->clear();
    menu->printResistance(0);
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            intPart = encoderCounter;
            resistance = intPart;
            menu->printResistance(resistance, 1);
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    intBtnPressed = false;
    while(!intBtnPressed){
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
    menu->clear();
    menu->printMaterial(materials[0].name, sciNotation(materials[0].value));
    intBtnPressed = false;
    while(!intBtnPressed){
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
    intPart = 0;
    dotPart = 0;
    menu->clear();
    menu->printResistance(0, 0, "Wire Diameter");
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            intPart = encoderCounter;
            diameter = intPart;
            menu->printResistance(diameter, 1, "Wire Diameter");
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            dotPart = encoderCounter;
            diameter = double((double)intPart + (double)dotPart/100);
            menu->printResistance(diameter, 1, "Wire Diameter");
            updateScreen = false;
        }
    }
    intPart = 0;
    dotPart = 0;
    encoderCounter = 0;
    menu->clear();
    menu->printResistance(0, 0, "Coil Perimeter");
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            intPart = encoderCounter;
            perimeter = intPart;
            menu->printResistance(perimeter, 1, "Coil Perimeter");
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    intBtnPressed = false;
    while(intBtnPressed){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            dotPart = encoderCounter;
            perimeter = double((double)intPart + (double)dotPart/100);
            menu->printResistance(perimeter, 1, "Coil Perimeter");
            updateScreen = false;
        }
    }

    length = (resistance*1000*PI*(diameter/100*diameter/100))/(4*materials[materialIndex].value);
    coils = length / perimeter;
    while(digitalRead(BTN) == LOW){}
    menu->clear();
    menu->printCoils(coils, length/100);
    autoStop(coils, 1);
}

void Run::autoStop(int rounds, int multiplier){
    int maxRounds = rounds;
    encoderCounter = rounds;
    menu->printAuto(maxRounds);
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            if(encoderCounter < 0)
                encoderCounter = 0;
            maxRounds = encoderCounter * multiplier;
            menu->printAuto(maxRounds);
            updateScreen = false;
        }
    }
    windCoils(maxRounds);
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
    menu->clear();
    menu->printDirection(direction);
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            direction = !direction;
            menu->printDirection(direction);
            updateScreen = false;
        }
    }
    setDirection(direction);
    encoderCounter = 0;
    detachInterrupt(digitalPinToInterrupt(CLK));
    detachInterrupt(digitalPinToInterrupt(BTN));
    intBtnPressed = false;
    int prevOut = 0;
    int oldSpeed = 0;
    menu->printRun(NULL, NULL, direction);
    if(speed != 0) {
        int spd = map(speed, 100, 255, 0, 100);
        menu->printRun(&spd, NULL, direction);
    }

    bool exited = false;
    while((maxRounds == -1 || counter < maxRounds) && counter < MAX_ROUNDS)
        {
            if (digitalRead(DT) != prevOut)
            {
                if (digitalRead(CLK) != prevOut)
                {
                     if(speed < 255)
                        speed++;
                    if(speed > 255)
                        speed = 255;
                }
                else
                {
                    if(speed > 100)
                        speed--;
                }
            }
            prevOut = digitalRead(DT);
            hall = digitalRead(hallPin);

            if (speed > 100) 
                analogWrite(enA, speed);
            else
                analogWrite(enA, 0);
            int speedTemp = map(speed, 100, 255, 0, 100);

            if(hall != oldHall && hall == LOW){
                    counter++;
                }

            if((oldSpeed != speedTemp) && (hall != oldHall && hall == LOW)) {
                menu->printRun(&speedTemp, &counter, direction);
            } else if(oldSpeed != speedTemp) {
                menu->printRun(&speedTemp, NULL, direction);
            } else if(hall != oldHall && hall == LOW) {
                menu->printRun(NULL, &counter, direction);
            }
            oldHall = hall;
            oldSpeed = speedTemp;

            if(digitalRead(BTN) == LOW ){
                if(buttonPressed > 0){
                    if(millis() - buttonPressed > 1000) {
                        exited = true;
                        break;
                    }
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
        if(exited) {
            while (digitalRead(BTN) == LOW) {}
            delay(100);
        }
        attachInterrupt(digitalPinToInterrupt(CLK), interruptLaunch, LOW);
        attachInterrupt(digitalPinToInterrupt(BTN), interruptBtn, FALLING);
        while (digitalRead(BTN) != LOW) {}
        intBtnPressed = false;
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