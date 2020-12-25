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

int Menu::getLvl(){
    return menuLvl;
}

void Menu::onBtnClick(){
    choosen.push_back(opt);
    menuLvl = choosen.size();
}

void Menu::setup() {
    opt = 0;
    menuLvl = 0;
    lcd->begin();  
    lcd->backlight();
    lcd->setCursor(0,0);
    lcd->print("Pickup Winder");
    lcd->setCursor(0,1);
    lcd->print("Choose Option");
}

void Menu::printResistance(double res){
    lcd->clear();
    lcd->print("Resistance: " + String(res));
}

void Menu::printMaterial(String mat, String res){
    lcd->clear();
    lcd->print("Mat: " + mat);
    lcd->setCursor(0,1);
    lcd->print("Res: " + res);
}

void Menu::printDirection(int direction){
    lcd->clear();
    if(direction == 1) {
        lcd->print("Direction: ->");
    } else
    {
        lcd->print("Direction: <-");
    }
    
}

void Menu::printAuto(int rounds){
    lcd->clear();
    String roundsStr = String(rounds);
    lcd->print("Rounds: " + roundsStr);
}

void Menu::printRun(int speed, int counter, int direction){
    lcd->clear();
    String strSpeed = String(speed);
    String strCount = String(counter);
    lcd->print("Speed: " + strSpeed +"%");
    lcd->setCursor(13,0);
    if(direction)
        lcd->print("->");
    else
        lcd->print("<-");
    lcd->setCursor(0,1);
    lcd->print("Winds: " + strCount);
}

void Menu::printMenu() {
    switch (menuLvl){
        case 0:
            chooseOption();
            break;
        case 1:
            chooseOption();
            break;
        default:
            chooseOption();
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