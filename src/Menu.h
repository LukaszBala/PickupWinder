#include <i2c/LiquidCrystal_I2C.h>
#include <Arduino.h>

class Menu
{
private:
    LiquidCrystal_I2C *lcd;
public:
    Menu();
    Menu(LiquidCrystal_I2C* lcd);
    ~Menu();
    void printMenu();
    int opt;
    void setup();
};

