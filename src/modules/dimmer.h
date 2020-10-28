
#ifndef DIMMER_H
#define DIMMER_H

#include <Arduino.h>
#include "configuration.h"

struct dimming
{
    uint8_t value;          // dimming value
    bool channelStatus;     // dimming channel status (on/off)
};

class Dimmer
{
public:
    /** Constructs requires pinOut array */
    Dimmer(const uint16_t pinOut[]);

    /** Destructor */
    ~Dimmer();

    /** Returns the current dimmer value in index */
    uint8_t dimmer(const int index) const;

    /** Returns all current dimmer values */
    uint8_t *dimmer() const;

    /** Set the dimmer value from channel */
    void setDimmer(const int index, const uint8_t value);

    /** Set all dimmer values in array */
    void setDimmer(const uint8_t values[]);

    dimming *data() const;
    dimming data(const int index);

    /** Set master on/off
     * If master is on(true), all channels is valued to channel value,
     * else if master is off(false), all channels is valued to 0 (off)
     */
    void master(bool value);

    bool master() const;

    /** Set the chanel on/off(true/false) */
    void setChannelStatus(const int channel, bool status);

    bool channelStatus(const int channel) const;

    void toggleChannelStatus(const int channel);

    void toggleMaster();

    void setDimming(const dimming *data);

    /** write dimmer data in outputs */
    void tick();

    bool *channelStatus() const;
    void channelStatus(const bool *status);

private:
    void clear();

    uint16_t m_pinOut[DIMMERS];

    dimming m_dimming[DIMMERS];

    bool m_master;
    bool m_changed;
};

#endif
