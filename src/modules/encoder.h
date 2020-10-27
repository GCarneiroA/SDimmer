
#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>
#include "singleButton.h"

class Encoder
{
public:
    enum Direction { NOROTATION = 0, LEFT = -1, RIGHT = 1 };

    typedef void (*pEncoderChange)(const long position, const Direction direction);

    Encoder(int pinA, int pinB, int pinSw, unsigned long holdTime);
    ~Encoder();

    void begin();

    long position();
    Direction direction();
    void setPosition(long newPosition);
    void tick();
    unsigned long getMillisBetweenRotations() const;

    void enconderChanged(pEncoderChange encChange);

    void buttonClick(SingleButton::pClickEvent clickEvent);
    void buttonHold(SingleButton::pHoldEvent holdEvent);

private:
    int m_pinA;
    int m_pinB;

    volatile int8_t m_oldState;
    volatile long m_position;
    volatile long m_positionExt;
    volatile long m_positionExtPrev;

    unsigned long m_positionExtTime;
    unsigned long m_positionExtTimePrev;

    pEncoderChange m_encoderChange;

    SingleButton *m_button;
};

#endif
