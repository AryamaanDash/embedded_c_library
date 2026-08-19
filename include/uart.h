#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <stddef.h>

// Tells caller what happened instead of only returning true of false.
typedef enum{
    UART_STATUS_OK,
    UART_STATUS_TIMEOUT,
    UART_STATUS_INVALID_ARGUMENT,
    UART_STATUS_ERROR,
} UARTStatus;

// Just the UART object.
typedef struct{
    void* platform_handle;
} UART;

// Initialization of UART process
UARTStatus uart_initialize(UART* uart, void* platform_handle);

// Sending byte
UARTStatus uart_send_byte(UART* uart, uint8_t byte, uint32_t timeout_ms);

// Sends several bytes
UARTStatus uart_send(UART* uart, const uint8_t* data, size_t data_length, uint32_t timeout_ms);

// Receives a byte
UARTStatus uart_receive_byte(UART* uart, uint8_t* byte, uint32_t timeout_ms);



#endif