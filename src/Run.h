#include <Arduino.h>
#include "Config.h"
#include "Menu.h"


class Run {
    public:
        Run();
        void printMenu();
        void windCoils(int maxRounds = -1, int speed = 100);
        void autoStop();
        void targetResistance();
        void interruptLaunch();
        void runOption();
    private: 
        void setDirection(int direction);
        String sciNotation(double num);
        int counter;
        int hall;
        int oldHall;
        unsigned long buttonPressed;
        Menu* menu;
        int btnPressed;
        int previousBtn;
};