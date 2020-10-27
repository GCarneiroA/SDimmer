
#include "systemStatus.h"
#include "includes.h"

dimming dimmingInfo[DIMMERS];
dimming oldDimmingInfo[DIMMERS];

const SingleLED::LEDParam leds[LEDS] =
{
    // pin, blinkTime
    {  9,   500 },      // LED ch1
    { 10,   500 },      // LED ch2
    { 11,   500 },      // LED ch3
    { 12,   500 }       // LED master
};

void initializeLeds()
{
    panelLeds = new PanelLeds(leds, LEDS);
}

void systemStatusUpdate()
{
    if (!programMode) {
        bool master = dimmer->master();
        for (int index = 0; index < DIMMERS; index++) {

            bool status = dimmingInfo[index].channelStatus;

            if (!master && status) {
                panelLeds->led(index)->blink(200);
            } else {
                panelLeds->led(index)->setLedState(status);
            }
            dimmingInfo[index] = dimmer->data(index);
            
            if (!menuUpdates) {
                menuUpdates = (dimmingInfo[index].value != oldDimmingInfo[index].value);
            }
        }
        panelLeds->led(MASTER)->setLedState(master);
    } else {

    }
}

void loadDimmerInfo()
{
    unsigned int address = 0;
    for (int index = 0; index < DIMMERS; index++) {
        eeprom_read_block((void *)&dimmingInfo[index], (void*)address, sizeof(dimming));
        oldDimmingInfo[index] = dimmingInfo[index];
        address += sizeof(dimming);
    }
    dimmer->setDimming(dimmingInfo);

    menuUpdates = true;
}

void saveDimmerInfo()
{
    unsigned int address = 0;
    for (int index = 0; index < DIMMERS; index++) {
        eeprom_update_block((const void*)&dimmingInfo[index], (void*)address, sizeof(dimming));
        address += sizeof(dimming);
    }
}

void systemUpdated() 
{
    for (int index = 0; index < DIMMERS; index++) {
        oldDimmingInfo[index] = dimmingInfo[index];
    }
}
