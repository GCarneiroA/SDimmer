
#include "LEDs.h"
#include "includes.h"

PanelLeds *panelLeds;

PanelLeds::PanelLeds(const SingleLED::LEDParam ledParams[], const int ledCount)
    : m_ledCount(ledCount)
{
    m_buffer = new SingleLED[m_ledCount];
    
    for (int i = 0; i < m_ledCount; i++) {
        m_buffer[i].setParam(ledParams[i]);
        m_buffer[i].begin();
    }
}

PanelLeds::PanelLeds(const int pinOut[], unsigned long blinkTime[], const int ledCount)
    : m_ledCount(ledCount)
{
    m_buffer = new SingleLED[m_ledCount]();
    for (int i = 0; i < m_ledCount; i++) {
        m_buffer[i].setPin(pinOut[i]);
        m_buffer[i].setBlinkTime(blinkTime[i]);
        m_buffer[i].begin();
    }
}

void PanelLeds::tick()
{
    for (int i = 0; i < m_ledCount; i++) {
        m_buffer[i].tick();
    }
}

SingleLED* PanelLeds::data()
{
    return m_buffer;
}

SingleLED *PanelLeds::led(const int index) 
{
    if (index >= m_ledCount) {
        return nullptr;
    }
    return &m_buffer[index];
}

void PanelLeds::allOn() 
{
    for (int index = 0; index < m_ledCount; index++) {
        m_buffer[index].On();
    }
}

void PanelLeds::allOff() 
{
    for (int index = 0; index < m_ledCount; index++) {
        m_buffer[index].Off();
    }
}

void PanelLeds::sync() 
{
    unsigned long time = millis();
    for (int index = 0; index < m_ledCount; index++) {
        m_buffer[index].sync(time);
    }
}
