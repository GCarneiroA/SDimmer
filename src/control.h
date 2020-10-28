
#ifndef MODE_H
#define MODE_H

#include "modules/encoder.h"

extern int channelToProgram;

void checkControls();

void pressEncoderButton();

// program mode
void enterProgramMode();

void initalizeControlButtons();

void encoderChanged(const long position, const Encoder::Direction direction);

#endif
