
#include "display.h"
#include "includes.h"

display_t displayInfo;

// Links uteis com informações para o LCD
// https://www.baldengineer.com/arduino-lcd-display-tips.html
// https://www.baldengineer.com/arduino-f-macro.html
// https://stackoverflow.com/questions/276827/string-padding-in-c

// Código útil para LCD, testar funcionamento
//
// printf("%-10s", "Hello");

LiquidCrystal_I2C *display;

String make_str(String str);

void initializeDisplay()
{
    display = new LiquidCrystal_I2C(LCDI2C_ADDR, 16, 2);
    display->init();
    display->backlight();

    displayInfo.line1.reserve(16);
    displayInfo.line2.reserve(16);
}

void refreshDisplay() 
{
    display->setCursor(0, 0);
    display->print(make_str(displayInfo.line1).c_str());
    display->setCursor(0, 1);
    display->print(make_str(displayInfo.line2).c_str());
}

String make_str(String str)
{
    for (unsigned int index = 0; index < (16 - str.length()); index++) {
        str += ' '; 
    }
    return str;
}
