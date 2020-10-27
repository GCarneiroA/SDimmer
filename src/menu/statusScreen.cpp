
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

void updateStatusMenu()
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

    #ifdef DEBUG
        Serial.println(info.c_str());
        Serial.println(info.length());

    #endif

    menuUpdates = false;
}
