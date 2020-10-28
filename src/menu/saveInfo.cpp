
#include "saveInfo.h"
#include "includes.h"

void saveInfoMenu()
{
    infoMenu.cur = 0;
    infoMenu.menu[infoMenu.cur] = menuStatus;

    unsigned long saving_task = millis();
    displayInfo.line1 = F("    SAVING..    ");
    displayInfo.line2 = F("                ");
    refreshDisplay();
    while ((millis() - saving_task) < 3000) ;

    saveDimmerInfo();   // Save data in eeprom
    
    saving_task = millis();
    displayInfo.line2 = F("    SAVED..     ");
    refreshDisplay();
    while ((millis() - saving_task) < 3000) ;

    menuUpdates = true;
}
