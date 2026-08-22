#include "uart.h"
#include "uart_platform.h"

UARTStatus uart_initialize(UART* uart, void* platform_handle){
    if(uart == NULL){
        return UART_STATUS_INVALID_ARGUMENT;
    }
    uart->platform_handle = platform_handle;
    return UART_STATUS_OK;
}

UARTStatus uart_send(UART* uart, const uint8_t* data, size_t data_length, uint32_t timeout_ms){
    if(uart == NULL || uart->platform_handle == NULL){
        return UART_STATUS_INVALID_ARGUMENT;
    }
    if(data_length == 0){
        return UART_STATUS_OK;
    }
    if(data == NULL){
        return UART_STATUS_INVALID_ARGUMENT;
    }
    return uart_platform_send(
        uart,
        uart->platform_handle,
        data,
        data_length, 
        timeout_ms
    );
}

UARTStatus uart_send_byte(UART* uart, uint8_t byte, uint32_t timeout_ms){
    return uart_send(uart, byte, 1, timeout_ms);
}

UARTStatus uart_receive_byte(UART* uart, uint8_t* byte, uint32_t timeout_ms){
    if(uart == NULL || uart->platform_handle == NULL || byte == NULL){
        return UART_STATUS_INVALID_ARGUMENT;
    }
    return uart_platform_receive(uart, uart->platform_handle, byte, 1, timeout_ms);

}