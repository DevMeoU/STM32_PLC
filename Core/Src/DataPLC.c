#include "DataPLC.h"
#include "mPrint.h"

volatile static uint8_t I[3][8] = {};
volatile uint16_t AI[8] = {};
volatile static uint8_t Q[3][8] = {};
volatile static uint8_t M[3][8] = {};
volatile static uint16_t u16VW[8] = {};
volatile static uint32_t u32VD[8] = {};
volatile static float f32VD[8] = {};
static uint8_t checksum(const uint8_t * data, size_t len);

QueueHandle_t xQueuePLC = NULL;

void PLC_ProcessTask(void *param)
{
    (void)param;
    while (1)
    {
		mPrint("PLC Task is running...\n");
        PLC_Read_Pin_Input();
        /*--------------NetWork 1 -----------*/

        volatile uint8_t I0_0sl0 = 0;
        volatile static uint8_t checkEU0 = 1;
        if (!(I0_0))
        {
            checkEU0 = 0;
        }
        if ((!checkEU0) && (I0_0))
        {
            checkEU0 = 1;
            I0_0sl0 = 1;
        }
        M0_0 = (((I0_0sl0 + M0_0)) * !I0_1);
        if (M0_0 > 0)
        {
            M0_0 = 1;
        }
        else
        {
            M0_0 = 0;
        }
        /*--------------NetWork 2 -----------*/

        if ((M0_0))
            u16VW1 = AIW0;
        M1_1 = (M0_0);
        if (M1_1 > 0)
        {
            M1_1 = 1;
        }
        else
        {
            M1_1 = 0;
        }
        /*--------------NetWork 3 -----------*/

        if ((M0_0))
            u32VD[0] = (uint32_t)u16VW1;
        /*--------------NetWork 4 -----------*/

        if ((M0_0))
            f32VD[0] = (float)u32VD[0];
        /*--------------NetWork 5 -----------*/

        if ((M0_0))
            f32VD[0] = f32VD[0] / 4096.0;
        /*--------------NetWork 6 -----------*/

        if ((M0_0))
            f32VD[0] = f32VD[0] * 100.0;
        /*--------------NetWork 7 -----------*/

        volatile uint8_t u8Compare0 = 0;
        u8Compare0 = 0;
        if (f32VD[0] >= 50.0)
        {
            u8Compare0 = 1;
        }
        Q0_0 = (M0_0 * u8Compare0);
        if (Q0_0 > 0)
        {
            Q0_0 = 1;
        }
        else
        {
            Q0_0 = 0;
        }
        PLC_Write_Pin_Output();

        /* Set data to queue */
        PLC_DataFrame_t sendFrame;
        if (xQueuePLC != NULL)
        {
            sendFrame.led_status = Q0_0; // Set LED status
            sendFrame.reserved[0] = 0; // Reserved bytes
            sendFrame.reserved[1] = 0;
            sendFrame.reserved[2] = 0;
            sendFrame.sensor_value.fsensor_v = f32VD[0];

            if (xQueueSend(xQueuePLC, &sendFrame, portMAX_DELAY) != pdPASS)
            {
                mPrint("Failed to send data to queue\n");
            }
        }
        else
        {
            mPrint("Queue is NULL\n");
        }

        mPrint("LED Status: %d, Sensor Value: %.2f\n", Q0_0, f32VD[0]);

        osDelay(100); // Delay to simulate PLC cycle time
    }
}

void PLC_SendDataTask(void * argument) {
    
    for (;;)
    {
        mPrint("Notify task running...\n");

        if (xQueuePLC != NULL)
        {
            PLC_DataFrame_t receivedData;
            if (xQueueReceive(xQueuePLC, &receivedData, portMAX_DELAY) == pdTRUE)
            {
                mSendCommand((uint8_t *)&receivedData, sizeof(PLC_DataFrame_t));
                mPrint("Received data: LED Status: %d, Sensor Value: %.2f\n", receivedData.led_status, receivedData.sensor_value.fsensor_v);
            }
            else
            {
                mPrint("Failed to receive data from queue\n");
            }

            const uint8_t LEN = sizeof(PLC_DataFrame_t);
            uint8_t cs = (LEN + checksum((uint8_t *)&receivedData, LEN)) & 0xFF;
            
            uint8_t frame[LEN + 3];
            memset(frame, 0, sizeof(frame));

            frame[0] = 0xAA; // Start byte
            frame[1] = LEN; // Length of the data
            memcpy(&frame[2], (uint8_t *)&receivedData, LEN);
            frame[LEN+2] = cs;
            mSendCommand(frame, sizeof(PLC_DataFrame_t)+3);
        }
        else
        {
            mPrint("Queue is NULL in Notify Task\n");
        }

        osDelay(250);
    }
    /* USER CODE END 5 */
}

void PLC_Read_Pin_Input(void)
{
    I0_0 = !HAL_GPIO_ReadPin(I0_0_PORT, I0_0_PIN);
    I0_1 = !HAL_GPIO_ReadPin(I0_1_PORT, I0_1_PIN);
}


void PLC_Write_Pin_Output(void)
{
    if (Q0_0 >= 1)
    {
        HAL_GPIO_WritePin(Q0_0_PORT, Q0_0_PIN, ENABLE); /* Set Q0_0 pin for LED */
    }
    else
    {
        HAL_GPIO_WritePin(Q0_0_PORT, Q0_0_PIN, DISABLE); /* Reset Q0_0 pin for LED */
    }
}

static uint8_t checksum(const uint8_t * data, size_t len)
{
    uint16_t sum = 0;
    for (size_t i = 0; i < len; i++) 
        sum += data[i];
    return sum & 0xFF;
}
