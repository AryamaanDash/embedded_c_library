#ifndef BUTTON_H
#define BUTTON_H

#include "gpio.h"
#include <stdint.h>

typedef enum {
    BUTTON_EVENT_NONE,
    BUTTON_EVENT_PRESSED,
    BUTTON_EVENT_RELEASED
} ButtonEvent;

typedef struct {
    GpioPin pin;
    GpioLevel active_level;
    GpioLevel raw_level;
    GpioLevel stable_level;
    uint32_t raw_change_time_ms;
    uint32_t debounce_time_ms;
    _Bool initialized;
} Button;

_Bool button_initialize(Button* button,
                        GpioPin pin,
                        GpioLevel active_level,
                        uint32_t debounce_time_ms,
                        uint32_t current_time_ms);
_Bool button_update(Button* button, uint32_t current_time_ms, ButtonEvent* event);
_Bool button_is_pressed(const Button* button);

#endif
