#ifndef _MPRINT_H
#define _MPRINT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include "stm32f4xx_hal.h"


#define PRINT_BUFFER_SIZE 250

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void mPrint(const char *format, ...);
void mSendCommand(const uint8_t *data, size_t len);

#endif // _MPRINT_H
