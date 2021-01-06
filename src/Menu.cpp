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

void Menu::setup() {
    opt = 0;
    lcd->begin();  
    lcd->backlight();
    lcd->setCursor(0,0);
    lcd->print("Pickup Winder");
    lcd->setCursor(0,1);
    lcd->print("Choose Option");
}

void Menu::printResistance(double res, int reset, String text){
    if(!reset) {
        lcd->setCursor(0,0);
        lcd->print(text + ":          ");
    }
    lcd->setCursor(0,1);
    if(res < 10)
        lcd->print("       " + String(res) + " ");
    else
        lcd->print("      " + String(res) + " ");
}

void Menu::clear(){
    lcd->clear();
}

void Menu::printCoils(int coils, double length){
    lcd->setCursor(0,0);
    lcd->print("Length: " + String(length) + "m         ");
    lcd->setCursor(0,1);
    lcd->print("Coils: " + String(coils) + "      ");
}

void Menu::printMaterial(String mat, String res){
    lcd->setCursor(0,0);
    lcd->print("Mat: " + mat + "        ");
    lcd->setCursor(0,1);
    lcd->print("Res: " + res + "        ");
}

void Menu::printDirection(int direction){
    lcd->setCursor(0,0);
    if(direction == 1) {
        lcd->print("Direction: ->");
    } else
    {
        lcd->print("Direction: <-");
    }
    
}

void Menu::printAuto(int rounds){
    lcd->setCursor(0,0);
    String roundsStr = String(rounds);
    lcd->print("Rounds: " + roundsStr + "        ");
}

void Menu::printRun(int* speed, int* counter, int direction){
    if (speed == NULL && counter == NULL){
        lcd->clear();
        lcd->print("Power: 0%");
        lcd->setCursor(13,0);
        if(direction)
            lcd->print("->");
        else
            lcd->print("<-");
        lcd->setCursor(0,1);
        lcd->print("Winds: 0");
    } else {
        if( speed != NULL) {
            String strSpeed = String(*speed);
            lcd->setCursor(7,0);
            lcd->print(strSpeed + "% ");
        }
        if( counter != NULL){
            String strCount = String(*counter);
            lcd->setCursor(7,1);
            lcd->print(strCount + "      ");
        }
    }
}

void Menu::printMenu() {
    chooseOption();
}

void Menu::chooseOption() {
    switch(opt) {
        case 1: 
            lcd->setCursor(0,0);
            lcd->print("Free Roam       ");
            lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
            lcd->println(String(opt) + "               ");
            break;
        case 2:
            lcd->setCursor(0,0);
            lcd->print("Automatic Wind  ");
            lcd->setCursor(0,1);
            lcd->println(String(opt) + "               ");
            break;
        case 3:
            lcd->setCursor(0,0);
            lcd->print("Calculate       ");
            lcd->setCursor(0,1);
            lcd->println(String(opt) + "               ");
            break;
        default:
            lcd->setCursor(0,0);
            lcd->print("Choose Option   ");
            lcd->setCursor(0,1);
            lcd->println(String(opt) + "               ");
            break;
    }
}