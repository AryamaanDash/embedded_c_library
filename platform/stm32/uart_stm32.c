#include "uart_platform.h"
#include <stddef.h>

UARTStatus uart_platform_send(UART* uart, void* platform_handle, const uint8_t* data, size_t data_length, uint32_t timeout_ms);

UARTStatus uart_platform_receive(UART* uart, void* platform_handle, uint8_t* data, size_t data_length);