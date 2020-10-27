
#include "ch1program.h"
#include "includes.h"

void ch1program() 
{
    checkControls();

    if (menuUpdates) {

        display->setCursor(0, 0);
        display->print(F("program ch1     "));
        if (infoMenu.cur == 1) {
            menuUpdates = false;
        }
    }
}
