#include <i2c/LiquidCrystal_I2C.h>
#include <Arduino.h>

class Menu
{
private:
    LiquidCrystal_I2C *lcd;
    int opt;
    int menuLvl;
    int choosenOpt;
    void chooseOption();
public:
    Menu();
    Menu(LiquidCrystal_I2C* lcd);
    ~Menu();

    void setOpt(int value);
    int getOpt();

    void onBtnClick();

    void printMenu();
    void setup();
    void printRun(int counter);
};

