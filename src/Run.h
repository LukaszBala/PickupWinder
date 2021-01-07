#include <Arduino.h>
#include "Config.h"
#include "Menu.h"
#include "Material.h"


class Run {
    public:
        Run();
        void printMenu();
        void windCoils(int maxRounds = -1, int speed = 100);
        void autoStop(int rounds = 0, int multiplier = 10);
        void targetResistance();
        void interruptLaunch();
        void runOption();
    private: 
        void setDirection(int direction);
        String sciNotation(double num);
        Material *materials;
        int counter;
        int hall;
        int oldHall;
        unsigned long buttonPressed;
        Menu* menu;
        int btnPressed;
        int previousBtn;
};