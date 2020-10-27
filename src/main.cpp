
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



/*
void clear();

unsigned int address = 0;

void setup()
{
    init();

    Serial.begin(9600);
    Serial.println("OK");

    //clear();
    writedimming();

    Serial.println("OK 2");

    address = 0;
    for (int i = 0; i < DIMMERS; i++) {

        //dimming dInfo;
        eeprom_read_block((void *)&dimmingInfo[i], (void*)address, sizeof(dimming));

        //dimmingInfo[i] = dInfo;

        Serial.print("dim: ");
        Serial.print(i);
        Serial.print(" - value: ");
        Serial.print(dimmingInfo[i].value);
        Serial.print(" - status: ");
        Serial.print(dimmingInfo[i].channelStatus);
        Serial.println();

        address += sizeof(dimming);

    }

    //eeprom_read_block((void*)&dimmingInfo, (void*)0, sizeof(dimming));
}

void loop()
{

}

void clear()
{
    Serial.println( EEPROM.length() );

    for (unsigned int addr = 0; addr < EEPROM.length(); addr++) {

        EEPROM.write(addr, 0);

    }
}

void writedimming()
{
    dimmingInfo[0].channelStatus = false;
    dimmingInfo[0].value = 12;

    dimmingInfo[1].channelStatus = true;
    dimmingInfo[1].value = 80;

    dimmingInfo[2].channelStatus = false;
    dimmingInfo[2].value = 99;

    address = 0;

    for (int i = 0; i < DIMMERS; i++) {

        Serial.println("writing...");

        eeprom_write_block ((const void*)&dimmingInfo[i], (void*)address, sizeof(dimming));
        //eeprom_update_block((const void*)&dimmingInfo[i], (void*)address, sizeof(dimming));

        address += sizeof(dimming);

    }

}
*/
