
#include "control.h"
#include "includes.h"

bool programMode;

void ch1click();
void ch2click();
void ch3click();
void masterclick();

const SingleButton::ButtonParam panelButtons[BUTTONS + 1] =
{
  // pin, debounce, holdTime, events(click, hold)
    { 2,  70,       2000,       { ch1click,             nullptr             }},     // channel 1
    { 4,  70,       2000,       { ch2click,             nullptr             }},     // channel 2
    { 7,  70,       2000,       { ch3click,             nullptr             }},     // channel 3
    { 8,  70,       2000,       { masterclick,          nullptr             }},     // master
    {16,  70,       2000,       { pressEncoderButton,   enterProgramMode    }},     // encoder
};

void initalizeControlButtons()
{
    controlButtons = new ControlButtons(panelButtons, BUTTONS + 1);
}

void encoderChanged(const long position, const Encoder::Direction direction)
{
    #ifdef DEBUG
        Serial.println(position);
    #endif
}

void ch1click()
{
    if (!programMode) {
        dimmer->toggleChannelStatus(CH1);
        panelLeds->sync();
    }
    #ifdef DEBUG
        Serial.println("CH1 click");
    #endif
}

void ch2click()
{
    if (!programMode) {
        dimmer->toggleChannelStatus(CH2);
        panelLeds->sync();
    }
    #ifdef DEBUG
        Serial.println("CH2 click");
    #endif
}

void ch3click()
{
    if (!programMode) {
        dimmer->toggleChannelStatus(CH3);
        panelLeds->sync();
    }
    #ifdef DEBUG
        Serial.println("CH3 click");
    #endif
}

void masterclick() 
{
    dimmer->toggleMaster();
    panelLeds->sync();
    #ifdef DEBUG
        Serial.println("Master click");
    #endif
}







int lastDebounceTime = 0;

// const FP_MENU programMenus[DIMMERS] = { ch1program, ch2program, ch3program };

void checkControls() 
{
    panelLeds->tick();
    
    encoder->tick();
    controlButtons->tick();
    
    dimmer->tick();
}

void pressEncoderButton() 
{
    if (programMode) {
        #ifdef DEBUG
            Serial.println(F("program mode leave..."));
        #endif
        programMode = false;
        menuUpdates = true;
        // save configurations in eeprom

        // return to menu status
        infoMenu.cur = 0;
        //infoMenu.menu[infoMenu.cur] = menuStatus;
    }
}

void enterProgramMode() 
{
    if (programMode) {
        return;
    }
    display->clear();

    menuUpdates = true;
    programMode = true;

    #ifdef DEBUG
        Serial.println(F("program mode enter..."));
    #endif

    infoMenu.cur = 1;
    infoMenu.menu[infoMenu.cur] = ch1program;
}
