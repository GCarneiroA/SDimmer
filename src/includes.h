
#ifndef INCLUDES_H
#define INCLUDES_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <inttypes.h>

#include "configuration.h"
//#include "simpleList.h"
#include "control.h"
#include "display.h"

// modules
#include "modules/singleLed.h"
#include "modules/singleButton.h"
#include "modules/encoder.h"
#include "modules/dimmer.h"
//#include "modules/lcd.h"
#include "modules/systemStatus.h"
#include "modules/controlButtons.h"
#include "modules/LEDs.h"

// menus
#include "menu/menu.h"
#include "menu/infomenu.h"
#include "menu/statusScreen.h"
#include "menu/ch1program.h"
#include "menu/ch2program.h"
#include "menu/ch3program.h"

#define CH1     0
#define CH2     1
#define CH3     2
#define MASTER  3

extern Encoder *encoder;

extern Dimmer *dimmer;
extern dimming dimmingInfo[DIMMERS];

extern LiquidCrystal_I2C *display;
extern ControlButtons *controlButtons;
extern PanelLeds *panelLeds;

extern display_t displayInfo;

extern bool appRunning;
extern bool programMode;
extern bool menuUpdates;

void basicHardwareInit();
void basicHardwareDeinit();

void basicDataInit();

#endif
