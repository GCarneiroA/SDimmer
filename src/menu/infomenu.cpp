
#include "infomenu.h"
#include "includes.h"

void infoMenuSelect() 
{
    infoMenu.cur = MENU_STATUS;
    #ifdef SHOW_WELCOME_MESSAGE
        const unsigned long welcome_task = millis();
        // show welcome message
        displayInfo.line1 = F("    WELCOME!    ");
        displayInfo.line2 = F("   SQUINA  73   ");
        refreshDisplay();
        while ((millis() - welcome_task) < 3000) ;
    #endif
}
