#include <Arduino.h>
#include "Config.h"
#include "Menu.h"


class Run {
    public:
        Run();
        void printMenu();
        void windCoils(int maxRounds = -1, int speed = 100);
        void autoStop();
        void interruptLaunch();
        void runOption();
    private: 
        int counter;
        int hall;
        int oldHall;
        unsigned long buttonPressed;
        Menu* menu;
        int btnPressed;
        int previousBtn;
};