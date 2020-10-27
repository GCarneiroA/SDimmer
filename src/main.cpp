
#include "includes.h"

bool appRunning;

int main()
{
    basicHardwareInit();    // init hardware basics
    basicDataInit();        // init variables basics
    loadDimmerInfo();       // load saved dimmer info
    
    infoMenuSelect();       // Enter in info menu (welcome message)

    // main application loop
    while (appRunning) {
        (*infoMenu.menu[infoMenu.cur])();
        if (serialEventRun) serialEventRun();
    }
    //theEndMenuInfo();
    
    basicHardwareDeinit();
}
