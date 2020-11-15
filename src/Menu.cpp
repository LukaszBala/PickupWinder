#include "Menu.h"


Menu::Menu(LiquidCrystal_I2C* lcdIn)
{
    lcd = lcdIn;
    setup();
    // lcd->begin();   // Inicjalizacja LCD 2x16
    // lcd->backlight(); // zalaczenie podwietlenia 
    // lcd->setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
    // lcd->print("Pickup Winder");
    // lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
    // lcd->print("Choose Option");
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

Menu::~Menu()
{
}

void Menu::setup() {
    opt = 0;
    menuLvl = 0;
    lcd->begin();   // Inicjalizacja LCD 2x16
    lcd->backlight(); // zalaczenie podwietlenia 
    lcd->setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
    lcd->print("Pickup Winder");
    lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
    lcd->print("Choose Option");
}

int Menu::checkBtn(){
btnPressed = digitalRead(BTN);

  if (btnPressed == 0)
  {
    menuLvl++;
    opt = 0;
    return 1;
  }
  return 0;
}

void Menu::printMenu() {
    switch (menuLvl){
        case 0:
            zeroLvl();
            break;
        case 1:
            firstLvl();
            break;
        default:
            break;
    }
}

void Menu::firstLvl(){
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

void Menu::zeroLvl() {
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