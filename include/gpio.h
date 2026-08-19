#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

typedef enum {
    GPIO_DRIVER_MODE_INPUT,
    GPIO_DRIVER_MODE_OUTPUT_PUSH_PULL,
    GPIO_DRIVER_MODE_OUTPUT_OPEN_DRAIN
} GpioMode;

typedef enum {
    GPIO_DRIVER_PULL_NONE,
    GPIO_DRIVER_PULL_UP,
    GPIO_DRIVER_PULL_DOWN
} GpioPull;

typedef enum {
    GPIO_DRIVER_LEVEL_LOW,
    GPIO_DRIVER_LEVEL_HIGH
} GpioLevel;

typedef struct {
    void* port;
    uint16_t pin;
} GpioPin;

_Bool gpio_configure(GpioPin pin, GpioMode mode, GpioPull pull);
_Bool gpio_read(GpioPin pin, GpioLevel* level);
_Bool gpio_write(GpioPin pin, GpioLevel level);
_Bool gpio_toggle(GpioPin pin);

#endif
