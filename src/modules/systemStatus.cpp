
#include "systemStatus.h"
#include "includes.h"

dimming dimmingInfo[DIMMERS];
dimming oldDimmingInfo[DIMMERS];

bool savedData = false;
bool savedMasterValue;
bool *savedChannelStatusValues;

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
        // running mode
        if (savedData) {
            dimmer->master(savedMasterValue);
            dimmer->channelStatus(savedChannelStatusValues);
            savedData = false;
        }

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
        // program mode
        panelLeds->allOff();
        int dimmerValue = dimmingInfo[channelToProgram].value;
        if (encoder->position() != dimmerValue) {
            encoder->setPosition(dimmerValue);
        }

        if (!savedData) {
            savedMasterValue = dimmer->master();
            savedChannelStatusValues = dimmer->channelStatus();
            if (channelToProgram < 0) {
                programMode = false;
                infoMenu.cur = MENU_STATUS;
                return;
            }
            savedData = true;
        }
        panelLeds->led(channelToProgram)->blink(1000);

        for (int index = 0; index < DIMMERS; index++) {

            dimmer->setChannelStatus(index, true);          // on all dimmer channels to program
            dimmingInfo[index] = dimmer->data(index);       // update dimming info with current values in dimmer module
            if (!menuUpdates) {
                menuUpdates = (dimmingInfo[index].value != oldDimmingInfo[index].value);
            }
        }
        dimmer->master(true);
        panelLeds->led(MASTER)->setLedState(true);
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
