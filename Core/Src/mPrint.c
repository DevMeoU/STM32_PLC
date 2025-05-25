#include "mPrint.h"

char mPrintBuffer[PRINT_BUFFER_SIZE];

void mPrint (const char * format, ...)
{
    memset(mPrintBuffer, 0, sizeof(mPrintBuffer));
    va_list args;
    va_start(args, format);
    int len = vsnprintf(mPrintBuffer, sizeof(mPrintBuffer), format, args);
    va_end(args);
    if (len < 0) len = 0;
    if (len >= sizeof(mPrintBuffer)) len = sizeof(mPrintBuffer) - 1;
    HAL_UART_Transmit(&huart2, (uint8_t*)mPrintBuffer, (uint16_t)len, 100);
}

void mSendCommand(const uint8_t *data, size_t len) {
    if (data == NULL || len == 0) return;
    HAL_UART_Transmit(&huart1, data, len, 100); // Gửi toàn bộ dữ liệu nhị phân
}