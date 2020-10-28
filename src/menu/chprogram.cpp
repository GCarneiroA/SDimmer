
#include "chprogram.h"
#include "includes.h"

// Menu 1

void updateChMenu();

void chprogram() 
{
    checkControls();
    systemStatusUpdate();

    if (menuUpdates) {
        updateChMenu();
        if (infoMenu.cur == MENU_PRGCHS) {
            systemUpdated();
        }
        refreshDisplay();
    }
}

void updateChMenu()
{
    displayInfo.line1 = F("CH1.CH2.CH3.MST.");

    String info;
    info.reserve(16);
    
    for (int index = 0; index < DIMMERS; index++) {
        char *strValue = new char[4];
        {
            sprintf(strValue, "%3d.", dimmingInfo[index].value);
            info.concat(strValue);
        }
        delete[] strValue;
    }
    
    displayInfo.line2 = info;
   
    menuUpdates = false;
}
