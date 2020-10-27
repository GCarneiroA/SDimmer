
#include "encoder.h"

#define LATCHSTATE 3
#define DEBOUNCE_BUTTON 70

Encoder *encoder;

const int8_t KNOBDIR[] = { 0, -1,  1,  0, 1,  0,  0, -1, -1,  0,  0,  1, 0,  1, -1,  0 };

Encoder::Encoder(int pinA, int pinB, int pinSw, unsigned long holdTime)
    : m_pinA(pinA)
    , m_pinB(pinB)
    , m_oldState(3)
    , m_position(0)
    , m_positionExt(0)
    , m_positionExtPrev(0)
    , m_encoderChange(nullptr)
    , m_button(nullptr)
{
    pinMode(pinA, INPUT_PULLUP);
    pinMode(pinB, INPUT_PULLUP);

    if (pinSw >= 0) {
        m_button = new SingleButton(pinSw, DEBOUNCE_BUTTON, holdTime);
    }
}

Encoder::~Encoder() 
{
    if (m_button) {
        delete m_button;
    }
}

void Encoder::begin() 
{
    if (m_button) {
        m_button->begin();
        delay(50);
    }
}

long Encoder::position()
{
    return m_positionExt;
}

Encoder::Direction Encoder::direction()
{
    Encoder::Direction ret = Direction::NOROTATION;

    if (m_positionExtPrev > m_positionExt) {
        ret = Direction::RIGHT;
        m_positionExtPrev = m_positionExt;
    } else if (m_positionExtPrev < m_positionExt) {
        ret = Direction::LEFT;
        m_positionExtPrev = m_positionExt;
    } else {
        ret = Direction::NOROTATION;
        m_positionExtPrev = m_positionExt;
    }

    return ret;
}

void Encoder::setPosition(long newPosition)
{
    m_position = ((newPosition << 2) | (m_position & 0x03L));
    m_positionExt = newPosition;
    m_positionExtPrev = newPosition;
}

void Encoder::tick()
{
    // read encoder
    int sig1 = digitalRead(m_pinA);
    int sig2 = digitalRead(m_pinB);
    int8_t thisState = sig1 | (sig2 << 1);

    if (m_oldState != thisState) {
        m_position += KNOBDIR[thisState | (m_oldState << 2)];

        if (thisState == LATCHSTATE) {
            m_positionExt = m_position >> 2;
            m_positionExtTimePrev = m_positionExtTime;
            m_positionExtTime = millis();
            
            if (m_encoderChange) {
                
                static int staticPos = 0;
                int _position = position();

                if (staticPos != _position) {
                    m_encoderChange(_position, direction());
                    staticPos = _position;
                }
            }
        }
        m_oldState = thisState;
    }

    if (m_button) {
        m_button->tick();
    }
}

unsigned long Encoder::getMillisBetweenRotations() const
{
    return m_positionExtTime - m_positionExtTimePrev;
}

void Encoder::buttonClick(SingleButton::pClickEvent clickEvent) 
{
    if (m_button) {
        m_button->clickEvent(clickEvent);
    }
}

void Encoder::buttonHold(SingleButton::pHoldEvent holdEvent) 
{
    if (m_button) {
        m_button->holdEvent(holdEvent);
    }
}

void Encoder::enconderChanged(pEncoderChange encChange) 
{
    m_encoderChange = encChange;
}
