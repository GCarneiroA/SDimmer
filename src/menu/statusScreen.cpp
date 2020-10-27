
#include "statusScreen.h"
#include "includes.h"

// MENU 0

void updateStatusMenu();

void menuStatus()
{
    checkControls();
    systemStatusUpdate();

    if (menuUpdates) {
        updateStatusMenu();
        if (infoMenu.cur == 0) {
            systemUpdated();
        }
        refreshDisplay();
    }
}

/*
    0 1 2 3 4 5 6 7 8 9 101112131415
    | | | | | | | | | | | | | | | | 
    C H 1 . C H 2 . C H 3 . C H 4 .
    1 0 0 . 1 0 0 . 1 0 0 . 1 0 0 .
    | | | | | | | | | | | | | | | |
    0       4       8       12
*/

void updateStatusMenu()
{
    displayInfo.line1 = F("CH1.CH2.CH3.MST.");

    String info;
    info.reserve(16);

    for (int index = 0; index < 3; index++) {
        
        char *strValue = new char[4];
        sprintf(strValue, "%3d.", dimmingInfo[index].value);
        info.concat(strValue);
        
        delete[] strValue;
    }

    displayInfo.line2 = info;

    #ifdef DEBUG
        Serial.println(info.c_str());
        Serial.println(info.length());

    #endif

    menuUpdates = false;
}
