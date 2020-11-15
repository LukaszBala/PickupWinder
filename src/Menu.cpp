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

Menu::~Menu()
{
}

void Menu::setup() {
    opt = 0;
    lcd->begin();   // Inicjalizacja LCD 2x16
    lcd->backlight(); // zalaczenie podwietlenia 
    lcd->setCursor(0,0); // Ustawienie kursora w pozycji 0,0 (pierwszy wiersz, pierwsza kolumna)
    lcd->print("Pickup Winder");
    lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
    lcd->print("Choose Option");
}

void Menu::printMenu() {
    switch(opt) {
        case 1: 
            lcd->clear();
            lcd->print("Nawijanie");
            lcd->setCursor(0,1); //Ustawienie kursora w pozycji 0,0 (drugi wiersz, pierwsza kolumna)
            lcd->print(opt);
            break;
        case 2:
            lcd->clear();
            lcd->print("No druga");
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
