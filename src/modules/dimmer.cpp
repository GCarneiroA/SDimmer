
#include "dimmer.h"

Dimmer *dimmer;

Dimmer::Dimmer(const uint16_t pinOut[])
    : m_master(false)
    , m_changed(false)
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
    }
    m_changed = true;
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
    m_master = value;
    m_changed = true;
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
    m_dimming[channel].channelStatus = status;
    m_changed = true;
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

    #ifdef DEBUG
        Serial.print("CH: ");
        Serial.print(channel + 1);
        Serial.print(" = ");
        Serial.print(m_dimming[channel].channelStatus);
        Serial.println();
    #endif
}

void Dimmer::toggleMaster() 
{
    m_master = !m_master;
    m_changed = true;
}

void Dimmer::setDimming(const dimming *data) 
{
    if (!data) return;
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
    for (uint8_t i = 0; i < DIMMERS; i++) {
        temp[i] = m_dimming[i].value;
        if (!m_master) {
            temp[i] = 0;
        }
        if (m_dimming[i].channelStatus == true) {
            analogWrite(m_pinOut[i], temp[i]);
        } else {
            analogWrite(m_pinOut[i], 0);
        }
    }
    m_changed = false;
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
