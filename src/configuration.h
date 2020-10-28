
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define SHOW_WELCOME_MESSAGE

// I2C LCD Address
#define LCDI2C_ADDR 0x3F

// Count of dimmer modules
#define DIMMERS 3

// Dimmer module pins
#define DIMMER_PINS {3, 5, 6/*, 9*/}

// Encoder pins, {Clock, Data, Switch}
#define ENCODER_PINS {14, 15, 16}

// Count of leds
#define LEDS 4

// SingleLED pins, {ch1, ch2, ch3, master}
#define LED_PINS {9, 10, 11, 12}

// Count of channel buttons, including master button
#define BUTTONS 4

// Control button pins, (ch1, ch2, ch3, [ch...], Master)
#define BUTTON_PINS {2, 4, 7, 8}

// debounce delay for encoder button
#define DEBOUNCE_DELAY 70

//#define DEBUG

#endif
