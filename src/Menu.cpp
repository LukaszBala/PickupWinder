#include "Menu.h"

Menu::Menu(LiquidCrystal_I2C* lcdIn)
{
    lcd = lcdIn;
    setup();
}

Menu::Menu(){
    this->lcd = new LiquidCrystal_I2C(0x27, 16, 2);
    setup();
}

Menu::~Menu()
{
}

void Menu::setOpt(int value)
{
    if(value > 3)
        opt = 0;
    else if(value < 0)
        opt = 3;
    else
        opt = value;
}

int Menu::getOpt()
{
    return opt;
}

void Menu::onBtnClick(){
    choosenOpt = opt;

}

void Menu::setup() {
    opt = 0;
    menuLvl = 0;
    choosenOpt = 0;
    lcd->begin();  
    lcd->backlight();
    lcd->setCursor(0,0);
    lcd->print("Pickup Winder");
    lcd->setCursor(0,1);
    lcd->print("Choose Option");
}

void Menu::printRun(int counter){
    lcd->clear();
    lcd->setCursor(0,1);
    lcd->print(counter);
}

void Menu::printMenu() {
    switch (menuLvl){
        case 0:
            chooseOption();
            break;
        case 1:
            // Run run = new Run(this);
            // run->run();
            break;
        default:
            break;
    }
}

void Menu::chooseOption() {
    switch(opt) {
        case 1: 
            lcd->clear();
            lcd->print("Free Roam");
            lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
            lcd->print(opt);
            break;
        case 2:
            lcd->clear();
            lcd->print("Automatic Wind");
            lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
            lcd->print(opt);
            break;
        case 3:
            lcd->clear();
            lcd->print("Calculate");
            lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
            lcd->print(opt);
            break;
        default:
            lcd->clear();
            lcd->print("Choose Option");
            lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
            lcd->print(opt);
            break;
    }
}