#include <i2c/LiquidCrystal_I2C.h>
#include <Arduino.h>
#include <vector.h>

class Menu
{
private:
    LiquidCrystal_I2C *lcd;
    int opt;
    int menuLvl;
    int choosenOpt;
    Vector <int> choosen;
    void chooseOption();
public:
    Menu();
    Menu(LiquidCrystal_I2C* lcd);
    ~Menu();

    void setOpt(int value);
    int getOpt();
    int getLvl();

    void onBtnClick();

    void printMenu();
    void setup();
    void printRun(int speed, int counter, int direction);
    void printDirection(int direction);
    void printAuto(int rounds);
};

