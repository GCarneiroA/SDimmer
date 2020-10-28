
#include "includes.h"

bool appRunning;

int main()
{
    basicHardwareInit();    // init hardware basics
    basicDataInit();        // init variables basics
    loadDimmerInfo();       // load saved dimmer info
    loadMenuInfo();         // load menuInfo structure
    
    infoMenu.cur = MENU_WELCOME;

    // main application loop
    while (appRunning) {
        (*infoMenu.menu[infoMenu.cur])();
        if (serialEventRun) serialEventRun();
    }
    //theEndMenuInfo();
    
    basicHardwareDeinit();
}
