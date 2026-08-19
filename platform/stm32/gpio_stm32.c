#include "gpio.h"
#if defined(STM32G071xx)

#include "stm32g0xx_hal.h"
#include <stddef.h>

static _Bool gpio_mode_to_hal(GpioMode mode, uint32_t* hal_mode){
    if(hal_mode == NULL){
        return 0;
    }

    switch(mode){
        case GPIO_DRIVER_MODE_INPUT:
            *hal_mode = GPIO_MODE_INPUT;
            return 1;
        case GPIO_DRIVER_MODE_OUTPUT_PUSH_PULL:
            *hal_mode = GPIO_MODE_OUTPUT_PP;
            return 1;
        case GPIO_DRIVER_MODE_OUTPUT_OPEN_DRAIN:
            *hal_mode = GPIO_MODE_OUTPUT_OD;
            return 1;
        default:
            return 0;
    }
}

static _Bool gpio_pull_to_hal(GpioPull pull, uint32_t* hal_pull){
    if(hal_pull == NULL){
        return 0;
    }

    switch(pull){
        case GPIO_DRIVER_PULL_NONE:
            *hal_pull = GPIO_NOPULL;
            return 1;
        case GPIO_DRIVER_PULL_UP:
            *hal_pull = GPIO_PULLUP;
            return 1;
        case GPIO_DRIVER_PULL_DOWN:
            *hal_pull = GPIO_PULLDOWN;
            return 1;
        default:
            return 0;
    }
}

static _Bool gpio_pin_is_valid(GpioPin pin){
    return pin.port != NULL && pin.pin != 0;
}

_Bool gpio_configure(GpioPin pin, GpioMode mode, GpioPull pull){
    GPIO_InitTypeDef configuration = {0};

    if(!gpio_pin_is_valid(pin) ||
       !gpio_mode_to_hal(mode, &configuration.Mode) ||
       !gpio_pull_to_hal(pull, &configuration.Pull)){
        return 0;
    }

    configuration.Pin = pin.pin;
    configuration.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init((GPIO_TypeDef*)pin.port, &configuration);
    return 1;
}

_Bool gpio_read(GpioPin pin, GpioLevel* level){
    if(!gpio_pin_is_valid(pin) || level == NULL){
        return 0;
    }

    *level = HAL_GPIO_ReadPin((GPIO_TypeDef*)pin.port, pin.pin) == GPIO_PIN_SET
                 ? GPIO_DRIVER_LEVEL_HIGH
                 : GPIO_DRIVER_LEVEL_LOW;
    return 1;
}

_Bool gpio_write(GpioPin pin, GpioLevel level){
    GPIO_PinState hal_level;

    if(!gpio_pin_is_valid(pin)){
        return 0;
    }

    if(level == GPIO_DRIVER_LEVEL_LOW){
        hal_level = GPIO_PIN_RESET;
    }else if(level == GPIO_DRIVER_LEVEL_HIGH){
        hal_level = GPIO_PIN_SET;
    }else{
        return 0;
    }

    HAL_GPIO_WritePin((GPIO_TypeDef*)pin.port, pin.pin, hal_level);
    return 1;
}

_Bool gpio_toggle(GpioPin pin){
    if(!gpio_pin_is_valid(pin)){
        return 0;
    }

    HAL_GPIO_TogglePin((GPIO_TypeDef*)pin.port, pin.pin);
    return 1;
}

#endif
