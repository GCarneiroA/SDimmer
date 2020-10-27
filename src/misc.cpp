
#include "includes.h"

void basicHardwareInit()
{
    init();     // init avr basics

    #ifdef DEBUG
        Serial.begin(9600);
        Serial.println(F("Initialized..."));
    #endif
    
    initializeLeds();
    initalizeControlButtons();
    initializeDisplay();

    // encoder initialization
    const uint16_t encPin[] = ENCODER_PINS;
    encoder = new Encoder(encPin[0], encPin[1], -1, -1);
    encoder->enconderChanged(encoderChanged);
    encoder->begin();

    // dimmer module initialization
    const uint16_t dimmerPins[] = DIMMER_PINS;
    dimmer = new Dimmer(dimmerPins);
}

void basicHardwareDeinit()
{
    delete[] controlButtons;
    delete[] display;
    delete[] encoder;
    delete[] dimmer;
}

void basicDataInit()
{
    appRunning = true;
    programMode = false;
    menuUpdates = false;
}
