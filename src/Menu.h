#include <i2c/LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "Config.h"

class Menu
{
private:
    LiquidCrystal_I2C *lcd;
    int opt;
    int menuLvl;
    void zeroLvl();
    void firstLvl();
    bool btnPressed;
public:
    Menu();
    Menu(LiquidCrystal_I2C* lcd);
    ~Menu();

    void setOpt(int value);
    int getOpt();
    int checkBtn();

    void printMenu();
    void setup();
};

