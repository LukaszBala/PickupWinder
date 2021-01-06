#include "LiquidCrystal_I2C.h"
#include <Arduino.h>

class Menu
{
private:
    LiquidCrystal_I2C *lcd;
    int opt;
    int choosenOpt;
    void chooseOption();
public:
    Menu();
    Menu(LiquidCrystal_I2C* lcd);
    ~Menu();

    void setOpt(int value);
    int getOpt();

    void printMenu();
    void setup();
    void clear();
    void printRun(int* speed, int* counter, int direction);
    void printDirection(int direction);
    void printAuto(int rounds);
    void printResistance(double res, int reset = 0, String text="Resistance");
    void printMaterial(String mat, String res);
    void printCoils(int coils, double length);
};

