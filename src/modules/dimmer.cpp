
#include "dimmer.h"

Dimmer *dimmer;

Dimmer::Dimmer(const uint16_t pinOut[])
    : m_master(false)
    , m_changed(false)
    , m_percentageMode(false)
{
    clear();
    for (uint8_t i = 0; i < DIMMERS; i++) {
        m_pinOut[i] = pinOut[i];                        // initialize pinOut's
        m_dimming[i].value = 0;                         // initialize all values to 0 (off)
        m_dimming[i].channelStatus = false;             // initialize all channels in off mode
        pinMode(m_pinOut[i], OUTPUT);                   // set all pinOut's to OUTPUT mode
        analogWrite(m_pinOut[i], m_dimming[i].value);   // write all OUTPUT's to 0 (off)
        delay(50);
    }
    delay(50);
}

Dimmer::~Dimmer() 
{
    clear();
}

void Dimmer::setPercentageMode(const bool percentageMode)
{
    if (m_percentageMode != percentageMode) {
        m_percentageMode = percentageMode;
        m_changed = true;
    }
}

uint8_t Dimmer::dimmer(const int index) const
{
    if (index > DIMMERS -1) {
        return -1;
    }
    return m_dimming[index].value;
}

uint8_t *Dimmer::dimmer() const
{
    static uint8_t dimm[DIMMERS];
    for (uint8_t i = 0; i < DIMMERS; i++) {
        dimm[i] = m_dimming[i].value;
    }
    return dimm;
}

void Dimmer::setDimmer(const int index, const uint8_t value) 
{
    if (index > DIMMERS -1) {
        return;
    }
    if (m_dimming[index].value != value) {
        m_dimming[index].value = value;
        m_changed = true;
    }
}

void Dimmer::setDimmer(const uint8_t values[]) 
{
    const size_t size = sizeof(*values) / sizeof(dimming);
    if (size < DIMMERS) {
        return;
    }
    for (uint8_t i = 0; i < DIMMERS; i++) {
        m_dimming[i].value = values[i];
    }
    m_changed = true;
}

dimming *Dimmer::data() const
{
    dimming *buffer = new dimming[DIMMERS];
    for (int index = 0; index < DIMMERS; index++) {
        buffer[index] = m_dimming[index];
    }
    return buffer;
}

dimming Dimmer::data(const int index) 
{
    return m_dimming[index];
}

void Dimmer::master(bool value) 
{
    if (m_master != value) {
        m_master = value;
        m_changed = true;
    }
}

bool Dimmer::master() const
{
    return m_master;
}

void Dimmer::setChannelStatus(const int channel, bool status) 
{
    if (channel > DIMMERS -1) {
        return;
    }
    if (m_dimming[channel].channelStatus != status) {
        m_dimming[channel].channelStatus = status;
        m_changed = true;
    }
}

bool Dimmer::channelStatus(const int channel) const
{
    if (channel > DIMMERS -1) {
        return false;
    }
    return m_dimming[channel].channelStatus;
}

void Dimmer::toggleChannelStatus(const int channel) 
{
    if (channel > DIMMERS -1) {
        return;
    }
    m_dimming[channel].channelStatus = !m_dimming[channel].channelStatus;
    m_changed = true;
}

void Dimmer::toggleMaster() 
{
    m_master = !m_master;
    m_changed = true;
}

void Dimmer::setDimming(const dimming *data) 
{
    if (!data) {
        return;
    }
    for (int index = 0; index < DIMMERS; index++) {
        m_dimming[index] = data[index];
    }
    m_changed = true;
}

void Dimmer::tick() 
{
    if (!m_changed) {
        return;
    }
    uint8_t temp[DIMMERS];
    for (uint8_t index = 0; index < DIMMERS; index++) {
        temp[index] = m_dimming[index].value;
        if (!m_master) {
            temp[index] = 0;
        }
        if (m_dimming[index].channelStatus == true) {
            byte value = temp[index];
            if (m_percentageMode) {
                value = ((255 * temp[index]) / 100);
                if (value > 255) {
                    value = 255;
                }
            }
            #ifdef DEBUG
                Serial.print("Real value in output channel[");
                Serial.print(index);
                Serial.print("] is -> ");
                Serial.println(value);
            #endif
            analogWrite(m_pinOut[index], value);
        } else {
            analogWrite(m_pinOut[index], 0);
        }
    }
    m_changed = false;
}

bool* Dimmer::channelStatus() const
{
    bool *buffer = new bool[DIMMERS];
    for (int index = 0; index < DIMMERS; index++) {
        buffer[index] = m_dimming[index].channelStatus;
    }
    return buffer;
}

void Dimmer::channelStatus(const bool *status) 
{
    if (!status) {
        return;
    }
    for (int index = 0; index < DIMMERS; index++) {
        m_dimming[index].channelStatus = status[index];
    }
    m_changed = true;
}

void Dimmer::clear() 
{
    for (uint8_t i = 0; i < DIMMERS; i++) {
        m_dimming[i].value = 0;
        analogWrite(m_pinOut[i], m_dimming[i].value);
        m_pinOut[i] = 0;
        m_dimming[i].channelStatus = false;
    }
}
