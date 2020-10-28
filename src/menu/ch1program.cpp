
#include "ch1program.h"
#include "includes.h"

// Menu 1

void updateCh1Menu();

void ch1program() 
{
    checkControls();
    systemStatusUpdate();

    if (menuUpdates) {
        updateCh1Menu();
        if (infoMenu.cur == 1) {
            systemUpdated();
        }
        refreshDisplay();
    }
}

static unsigned long task = millis();

void updateCh1Menu()
{
    displayInfo.line1 = F("CH1.CH2.CH3.MST.");

    String info;
    info.reserve(16);
    
    for (int index = 0; index < DIMMERS; index++) {
        char *strValue = new char[4];
        {
            if (index == CH1) {
                //if ((millis() - task) < 500) {
                    sprintf(strValue, "%3d.", dimmingInfo[index].value);
                    info.concat(strValue);
                /*} else {
                    memcpy(strValue, "    ", 4);
                    info.concat(strValue);
                }
                if ((millis() - task) > 1000) {
                    task = millis();
                }*/
            } else {
                sprintf(strValue, "%3d.", dimmingInfo[index].value);
                info.concat(strValue);
            }
        }
        delete[] strValue;
    }
    
    displayInfo.line2 = info;
   
    menuUpdates = false;
}
