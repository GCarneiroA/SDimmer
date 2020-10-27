
#ifndef SINGLELED_H
#define SINGLELED_H

class SingleLED
{
public:
    struct LEDParam
    {
        int pin;
        unsigned long blinkTime;
    };

    SingleLED();
    SingleLED(int pin, unsigned long blinkTime);
    SingleLED(LEDParam param);

    void begin();
    void tick();
    
    void setLedState(bool ledState);
    bool ledState() const;

    void toggle();

    void On();
    void Off();
    
    void blinkOn();
    void blinkOff();

    bool blinkState() const;
    void blinkState(const bool blinkState, unsigned long blinkTime = -1);
    void blink(long blinkTime = -1);

    void setParam(const LEDParam param);
    void setPin(int pin);
    void setBlinkTime(unsigned long blinkTime);

    void sync(unsigned long time);

private:
    unsigned long m_pin;
    bool m_ledState;

    bool m_blink;
    unsigned long m_blinkTime;
    unsigned long m_originalBlinkTime;

    unsigned long m_taskBlink;

    bool m_changed;

};

#endif
