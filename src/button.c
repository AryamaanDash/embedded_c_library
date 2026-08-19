#include "button.h"
#include <stddef.h>

static _Bool button_level_is_valid(GpioLevel level){
    return level == GPIO_DRIVER_LEVEL_LOW ||
           level == GPIO_DRIVER_LEVEL_HIGH;
}

_Bool button_initialize(Button* button,
                        GpioPin pin,
                        GpioLevel active_level,
                        uint32_t debounce_time_ms,
                        uint32_t current_time_ms){
    GpioLevel initial_level;

    if(button == NULL){
        return 0;
    }

    button->initialized = 0;

    if(!button_level_is_valid(active_level) ||
       debounce_time_ms == 0 ||
       !gpio_read(pin, &initial_level)){
        return 0;
    }

    button->pin = pin;
    button->active_level = active_level;
    button->raw_level = initial_level;
    button->stable_level = initial_level;
    button->raw_change_time_ms = current_time_ms;
    button->debounce_time_ms = debounce_time_ms;
    button->initialized = 1;

    return 1;
}

_Bool button_update(Button* button,
                    uint32_t current_time_ms,
                    ButtonEvent* event){
    GpioLevel current_level;

    if(button == NULL || event == NULL || !button->initialized){
        return 0;
    }

    *event = BUTTON_EVENT_NONE;

    if(!gpio_read(button->pin, &current_level)){
        return 0;
    }

    if(current_level != button->raw_level){
        button->raw_level = current_level;
        button->raw_change_time_ms = current_time_ms;
        return 1;
    }

    if(button->raw_level != button->stable_level &&
       (uint32_t)(current_time_ms - button->raw_change_time_ms) >=
           button->debounce_time_ms){
        button->stable_level = button->raw_level;
        *event = button->stable_level == button->active_level
                     ? BUTTON_EVENT_PRESSED
                     : BUTTON_EVENT_RELEASED;
    }

    return 1;
}

_Bool button_is_pressed(const Button* button){
    if(button == NULL || !button->initialized){
        return 0;
    }

    return button->stable_level == button->active_level;
}
