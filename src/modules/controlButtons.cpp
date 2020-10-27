
#include "controlButtons.h"

ControlButtons *controlButtons;

ControlButtons::ControlButtons(const SingleButton::ButtonParam buttonParams[], const int buttonCount)
    : m_buttonCount(buttonCount)
{
    m_buffer = new SingleButton[m_buttonCount]();
    m_events = new SingleButton::ButtonEvents[m_buttonCount]();

    for (int i = 0; i < m_buttonCount; i++) {
        m_buffer[i].setParam(buttonParams[i]);
        m_buffer[i].clickEvent(buttonParams[i].events.clickEvent);
        m_buffer[i].holdEvent(buttonParams[i].events.holdEvent);
        m_buffer[i].begin();
    }
}

ControlButtons::ControlButtons(const int pinOut[], unsigned long debounce[], unsigned long holdTime[], const int buttonCount)
    : m_buttonCount(buttonCount)
{
    m_buffer = new SingleButton[m_buttonCount]();
    m_events = new SingleButton::ButtonEvents[m_buttonCount]();

    for (int i = 0; i < m_buttonCount; i++) {
        m_buffer[i].setPin(pinOut[i]);
        m_buffer[i].setDebounce(debounce[i]);
        m_buffer[i].setHoldTime(holdTime[i]);
        m_buffer[i].begin();
    }
}

void ControlButtons::tick() 
{
    for (int i = 0; i < m_buttonCount; i++) {
        m_buffer[i].tick();
    }
}

SingleButton* ControlButtons::data() 
{
    return m_buffer;
}
