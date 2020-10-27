
#include "singleLed.h"
#include <Arduino.h>

SingleLED::SingleLED()
    : m_pin(-1)
    , m_ledState(false)
    , m_blink(false)
    , m_blinkTime(-1)
    , m_originalBlinkTime(-1)
    , m_taskBlink(0)
    , m_changed(false)
{
}

SingleLED::SingleLED(int pin, unsigned long blinkTime)
    : m_pin(pin)
    , m_ledState(false)
    , m_blink(false)
    , m_blinkTime(blinkTime)
    , m_originalBlinkTime(blinkTime)
    , m_taskBlink(0)
    , m_changed(false)
{}

SingleLED::SingleLED(LEDParam param)
    : m_pin(param.pin)
    , m_ledState(false)
    , m_blink(false)
    , m_blinkTime(param.blinkTime)
    , m_originalBlinkTime(param.blinkTime)
    , m_taskBlink(0)
    , m_changed(false)
{
}

void SingleLED::begin()
{
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW);
}

void SingleLED::tick()
{
    if (!m_changed) {
        return;
    }
    if (!m_blink) {
        digitalWrite(m_pin, m_ledState);
    } else {
        if ((millis() - m_taskBlink) < m_blinkTime) {
            digitalWrite(m_pin, HIGH);
        } else {
            digitalWrite(m_pin, LOW);
        }
        if ((millis() - m_taskBlink) > m_blinkTime * 2) {
            m_taskBlink = millis();
        }
    }
}

void SingleLED::setLedState(bool ledState)
{
    m_ledState = ledState;
    m_blink = false;
    m_changed = true;
}

bool SingleLED::ledState() const
{
    return m_ledState;
}

void SingleLED::toggle() 
{
    m_ledState = !m_ledState;
    m_changed = true;
}

void SingleLED::On()
{
    m_ledState = true;
    m_blink = false;
    m_changed = true;
}

void SingleLED::Off()
{
    m_ledState = false;
    m_blink = false;
    m_changed = true;
}

void SingleLED::blinkOn() 
{
    m_blink = true;
    m_blinkTime = m_originalBlinkTime;
    m_taskBlink = millis();
    m_changed = true;
}

void SingleLED::blinkOff() 
{
    m_blink = false;
    m_blinkTime = m_originalBlinkTime;
    m_taskBlink = millis();
    m_changed = true;
}

bool SingleLED::blinkState() const
{
    return m_blink;
}

void SingleLED::blink(long blinkTime)
{
    if (m_blink) {
        if (m_blinkTime != m_originalBlinkTime) {
            m_blinkTime = m_originalBlinkTime;
            if (blinkTime > 0) {
                m_blinkTime = blinkTime;
            }
            return;
        }
        m_blink = !m_blink;
        return;
    }
    m_blink = !m_blink;
    m_blinkTime = m_originalBlinkTime;
    if (blinkTime > 0) {
        m_blinkTime = blinkTime;
    }
    m_taskBlink = millis();
    m_changed = true;
}

void SingleLED::blinkState(const bool blinkState, unsigned long blinkTime)
{
    if (m_blink != blinkState) {
        m_blink = blinkState;
        m_blinkTime = m_originalBlinkTime;
        if (blinkTime > 0) {
            m_blinkTime = blinkTime;
        }
        m_taskBlink = millis();
        m_changed = true;
    }
}

void SingleLED::setParam(const LEDParam param) 
{
    m_pin = param.pin;
    m_blinkTime = param.blinkTime;
    m_originalBlinkTime = param.blinkTime;
}

void SingleLED::setPin(int pin) 
{
    m_pin = pin;
}

void SingleLED::setBlinkTime(unsigned long blinkTime) 
{
    m_blinkTime = blinkTime;
    m_originalBlinkTime = blinkTime;
    m_changed = true;
}

void SingleLED::sync(unsigned long time) 
{
    m_taskBlink = time;
}
