
#ifndef SINGLEBUTTON_H
#define SINGLEBUTTON_H

class SingleButton
{
public:
    typedef void (*pClickEvent)();
    typedef void (*pHoldEvent)();

    struct ButtonEvents
    {
        pClickEvent clickEvent;
        pHoldEvent holdEvent;
        //ButtonEvents() : clickEvent(nullptr) , holdEvent(nullptr) {}
    };

    struct ButtonParam
    {
        int pin;
        unsigned long debounce;
        unsigned long holdTime;
        ButtonEvents events;
    };
    
public:
    SingleButton();
    SingleButton(ButtonParam param);
    SingleButton(int pin, unsigned long debounce, unsigned long holdTime);
    ~SingleButton();

    void begin();

    void tick();

    void clickEvent(pClickEvent clickEvent);
    void holdEvent(pHoldEvent holdEvent);

    void setParam(const ButtonParam param);
    void setPin(int pin);
    void setDebounce(unsigned long debounce);
    void setHoldTime(unsigned long holdTime);

private:
    int m_pin;
    unsigned long m_debounce;
    unsigned long m_holdTime;

    int m_current;
    int m_previous;
    
    bool m_ignoreUp;

    pClickEvent m_clickEvent;
    pHoldEvent m_holdEvent;
};

#endif
