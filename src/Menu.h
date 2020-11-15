#include <i2c/LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "Config.h"
#include "IOption.cpp"

class Menu
{
private:
    LiquidCrystal_I2C *lcd;
    int opt;
    int menuLvl;
    int choosenOpt;
    void chooseOption();
    void test(IOption option);
public:
    Menu();
    Menu(LiquidCrystal_I2C* lcd);
    ~Menu();

    void setOpt(int value);
    int getOpt();

    void onBtnClick();

    void printMenu();
    void setup();
};

