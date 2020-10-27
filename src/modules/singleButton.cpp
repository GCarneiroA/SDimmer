
#include "singleButton.h"
#include <Arduino.h>

static long m_upTime;
static long m_downTime;

SingleButton::SingleButton()
    : m_pin(-1)
    , m_debounce(70)
    , m_holdTime(2000)
    , m_current(1)
    , m_previous(1)
    , m_ignoreUp(false)
    , m_clickEvent(nullptr)
    , m_holdEvent(nullptr)
{
}

SingleButton::SingleButton(ButtonParam param)
    : m_pin(param.pin)
    , m_debounce(param.debounce)
    , m_holdTime(param.holdTime)
    , m_current(1)
    , m_previous(1)
    , m_ignoreUp(false)
    , m_clickEvent(nullptr)
    , m_holdEvent(nullptr)
{
}

SingleButton::SingleButton(int pin, unsigned long debounce, unsigned long holdTime)
    : m_pin(pin)
    , m_debounce(debounce)
    , m_holdTime(holdTime)
    , m_current(1)
    , m_previous(1)
    , m_ignoreUp(false)
    , m_clickEvent(nullptr)
    , m_holdEvent(nullptr)
{
}

SingleButton::~SingleButton() {}

void SingleButton::begin() 
{
    pinMode(m_pin, INPUT_PULLUP);
    delay(50);
}

void SingleButton::tick() 
{
    // read the state of the button
    m_current = digitalRead(m_pin);

    // test for button pressed and store the down time
    if (m_current == LOW && m_previous == HIGH && (millis() - m_upTime) > m_debounce) {
        m_downTime = millis();
    }

    // test for button release and store the up time
    if (m_current == HIGH && m_previous == LOW && (millis() - m_downTime) > m_debounce) {
        if (!m_ignoreUp) {
            if (m_clickEvent) { m_clickEvent(); }
        } else {
            m_ignoreUp = false;
        }
        m_upTime = millis();
    }

    // test for button hold down for longer than the hold time
    if (m_current == LOW && (millis() - m_downTime) > m_holdTime) {
        if (m_holdEvent) { m_holdEvent(); }
        m_ignoreUp = true;
        m_downTime = millis();
    }
    m_previous = m_current;
}

void SingleButton::clickEvent(pClickEvent clickEvent) 
{
    m_clickEvent = clickEvent;
}

void SingleButton::holdEvent(pHoldEvent holdEvent) 
{
    m_holdEvent = holdEvent;
}

void SingleButton::setParam(const ButtonParam param) 
{
    m_pin = param.pin;
    m_debounce = param.debounce;
    m_holdTime = param.holdTime;
}

void SingleButton::setPin(int pin) 
{
    m_pin = pin;
}

void SingleButton::setDebounce(unsigned long debounce) 
{
    m_debounce = debounce;
}

void SingleButton::setHoldTime(unsigned long holdTime) 
{
    m_holdTime = holdTime;
}
