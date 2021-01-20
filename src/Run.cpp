#include "Run.h"

volatile bool updateScreen = false;
volatile int encoderCounter = 0;
volatile bool intBtnPressed = false;

static void interruptLaunch(){
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if(interruptTime - lastInterruptTime > 10){
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

static void interruptBtn() {
    static unsigned long lastInterruptTimeBtn = 0;
    unsigned long interruptTimeBtn = millis();

    if ((interruptTimeBtn - lastInterruptTimeBtn) > 300) {
        intBtnPressed = true;
    }
    lastInterruptTimeBtn = interruptTimeBtn;
}

Run::Run(){
    menu = new Menu();
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
        cli();
        menu->setOpt(encoderCounter);
        encoderCounter = menu->getOpt();
        sei();
        menu->printMenu();
        cli();
        encoderCounter = menu->getOpt();
        updateScreen = false;
        sei();
    }
    if(intBtnPressed){
        runOption();
        menu->printMenu();
        cli();
        updateScreen = true;
        intBtnPressed = false;
        encoderCounter = 0;
        menu->setOpt(encoderCounter);
        sei();
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
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            intPart = encoderCounter;
            sei();
            resistance = intPart;
            menu->printResistance(resistance, 1);
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            dotPart = encoderCounter;
            sei();
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
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > materialSize)
                encoderCounter = 0;
            materialIndex = encoderCounter;
            sei();
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
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            intPart = encoderCounter;
            sei();
            diameter = intPart;
            menu->printResistance(diameter, 1, "Wire Diameter");
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            dotPart = encoderCounter;
            sei();
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
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            intPart = encoderCounter;
            sei();
            perimeter = intPart;
            menu->printResistance(perimeter, 1, "Coil Perimeter");
            updateScreen = false;
        }
    }
    encoderCounter = 0;
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > 99)
                encoderCounter = 99;
            dotPart = encoderCounter;
            sei();
            perimeter = double((double)intPart + (double)dotPart/100);
            menu->printResistance(perimeter, 1, "Coil Perimeter");
            updateScreen = false;
        }
    }
    intBtnPressed = false;
    length = (resistance*1000*PI*(diameter/100*diameter/100))/(4*materials[materialIndex].value);
    coils = (length / perimeter > MAX_ROUNDS || length / perimeter < 0) ? -1 : length / perimeter;
    menu->clear();
    menu->printCoils(coils, length/100);
    if ( coils <= MAX_ROUNDS && length/100 < 10000000 && coils >= 0 && length/100 >= 0)
        autoStop(coils, 1);
    else 
        while(!intBtnPressed) {}
}

void Run::autoStop(int rounds, int multiplier){
    int maxRounds = rounds;
    encoderCounter = rounds;
    menu->printAuto(maxRounds);
    intBtnPressed = false;
    while(!intBtnPressed){
        if( updateScreen) {
            cli();
            if(encoderCounter < 0)
                encoderCounter = 0;
            if(encoderCounter > MAX_ROUNDS/10)
            encoderCounter = MAX_ROUNDS/10;
            maxRounds = encoderCounter * multiplier;
            sei();
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

    int counter = 0;
    int hall;
    int oldHall = -1;
    unsigned long buttonPressed = 0;
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
        digitalWrite(in1, LOW);
        digitalWrite(in2, LOW);
        analogWrite(enA, 255);
        delay(300);
        analogWrite(enA, 0);
        buttonPressed = 0;
        counter = 0;
        speed = 0;
        maxRounds = 0; 
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