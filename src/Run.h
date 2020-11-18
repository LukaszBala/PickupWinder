#include <Arduino.h>
#include "Config.h"
#include "Menu.h"


class Run {
    public:
        Run();
        void printMenu();
        void windCoils();
        void interruptLaunch();
    private: 
        int prevOut;
        int maxRounds;
        int counter;
        int speed;
        int hall;
        int oldHall;
        int oldSpeed;
        unsigned long buttonPressed;
        Menu* menu;
        int btnPressed;
        int previousBtn;
};