#include "uart_platform.h"
#if defined(STM32G071xx)

#include "stm32g0xx_hal.h"
#include <stdint.h>

//HAL to UART Translation
static UARTStatus uart_status_from_hal(HAL_StatusTypeDef hal_status){
    switch(hal_status){
        case HAL_OK:
            return UART_STATUS_OK;
        case HAL_TIMEOUT:
            return UART_STATUS_TIMEOUT;
        case HAL_ERROR:
        case HAL_BUSY:
        default:
            return UART_STATUS_ERROR;
    }
}

// platform-specific transmitting of data
UARTStatus uart_platform_send(UART* uart, void* platform_handle, const uint8_t* data, size_t data_length, uint32_t timeout_ms){
    HAL_StatusTypeDef hal_status;

    if(uart == NULL ||
       platform_handle == NULL ||
       uart->platform_handle != platform_handle){
        return UART_STATUS_INVALID_ARGUMENT;
    }

    if(data_length == 0){
        return UART_STATUS_OK;
    }

    if(data == NULL || data_length > UINT16_MAX){
        return UART_STATUS_INVALID_ARGUMENT;
    }

    hal_status = HAL_UART_Transmit((UART_HandleTypeDef*)platform_handle, data, (uint16_t)data_length, timeout_ms);

    return uart_status_from_hal(hal_status);
}

// platform specific data receiving
UARTStatus uart_platform_receive(UART* uart, void* platform_handle, uint8_t* data, size_t data_length, uint32_t timeout_ms){
    HAL_StatusTypeDef hal_status;

    if(uart == NULL ||
       platform_handle == NULL ||
       uart->platform_handle != platform_handle){
        return UART_STATUS_INVALID_ARGUMENT;
    }

    if(data_length == 0){
        return UART_STATUS_OK;
    }

    if(data == NULL || data_length > UINT16_MAX){
        return UART_STATUS_INVALID_ARGUMENT;
    }

    hal_status = HAL_UART_Receive((UART_HandleTypeDef*)platform_handle, data, (uint16_t)data_length, timeout_ms);

    return uart_status_from_hal(hal_status);
}

#endif
