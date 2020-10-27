
#ifndef CONTROLBUTTONS_H
#define CONTROLBUTTONS_H

#include "singleButton.h"

class ControlButtons
{
public:
    ControlButtons(const SingleButton::ButtonParam buttonParams[], const int buttonCount);
    ControlButtons(const int pinOut[], unsigned long debounce[], unsigned long holdTime[], const int buttonCount);

    void tick();

    SingleButton *data();

private:
    int m_buttonCount;
    SingleButton *m_buffer;
    SingleButton::ButtonEvents *m_events;

};

#endif
