
#ifndef LED_S_H
#define LED_S_H

#include "singleLed.h"

class PanelLeds
{
public:
    PanelLeds(const SingleLED::LEDParam ledParams[], const int ledCount);
    PanelLeds(const int pinOut[], unsigned long blinkTime[], const int ledCount);

    void tick();
    SingleLED *data();

    SingleLED *led(const int index);

    void sync();
private:

    int m_ledCount;
    SingleLED *m_buffer;
};

#endif
