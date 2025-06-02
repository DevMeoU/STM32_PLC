#include "DataPLC.h"
#include "mPrint.h"

volatile static uint8_t I[3][8] = {};
volatile uint16_t AI[8] = {};
volatile static uint8_t Q[3][8] = {};
volatile static uint8_t M[3][8] = {};
volatile static uint16_t u16VW[8] = {};
volatile static uint32_t u32VD[8] = {};
volatile static float f32VD1[8] = {};
volatile static uint8_t T37 = 0;
volatile static uint32_t countT37 = 0;
volatile static uint32_t T37reset = 0;
volatile static uint8_t vaoT37 = 0;
volatile static const uint32_t datT37 = 10;
volatile static uint8_t checkT37 = 0;
volatile static uint8_t C1 = 0;
volatile static uint32_t countC1 = 0;
volatile static uint8_t vaoC1 = 0;
volatile static uint8_t resetC1 = 0;
volatile static const uint32_t datC1 = 50;
volatile static uint8_t startC1 = 0;
volatile static uint8_t checkC1 = 0;

static uint8_t checksum(const uint8_t * data, size_t len);

QueueHandle_t xQueuePLC = NULL;
TimerHandle_t handle_timerPLC[1];

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

		if (!T37reset)
		{
			vaoT37 = (M0_0);
			T37;
			if (vaoT37)
			{
				if (countT37 >= datT37)
					T37 = 1;

				if ((T37 == 0) && (checkT37 == 0))
				{
					if(xTimerStart(handle_timerPLC[0], 10) != pdPASS)
                    {
                    	Error_Handler();
					}
					checkT37 = 1;
				}
			}
			else
			{
				if (checkT37 == 1)
				{
					xTimerStop(handle_timerPLC[0], portMAX_DELAY);
					checkT37 = 0;
				}
				T37 = 0;
				countT37 = 0;
			}
		}
		else
		{
			xTimerStop(handle_timerPLC[0], portMAX_DELAY);
			countT37 = 0;
			T37 = 0;
			checkT37 = 0;
		}
		/*--------------NetWork 3 -----------*/

		volatile uint8_t T37sl1 = 0;
		volatile static uint8_t checkEU1 = 1;
		if (!(T37))
		{
			checkEU1 = 0;
		}
		if ((!checkEU1) && (T37))
		{
			checkEU1 = 1;
			T37sl1 = 1;
		}
		volatile uint8_t tempC1_0 = 0;
		if (countC1 >= 50)
		{
			tempC1_0 = 1;
		}
		vaoC1 = (T37sl1);
		resetC1 = (tempC1_0 + !M0_0);
		if (resetC1)
		{
			countC1 = 0;
			C1 = 0;
			startC1 = 1;
		}
		else
		{
			if (vaoC1)
			{
				if (((checkC1 == 1) || (startC1 == 1)) && (countC1 <= 4294967295))
				{
					countC1++;
					startC1 = 0;
				}
				if (countC1 >= datC1)
				{
					C1 = 1;
				}
			}
			else
			{
				checkC1 = 1;
			}
		}
		/*--------------NetWork 4 -----------*/

		volatile uint8_t tempC1_1 = 0;
		if (countC1 <= 20)
		{
			tempC1_1 = 1;
		}
		Q1_6 = (tempC1_1 * M0_0);
		if (Q1_6 > 0)
		{
			Q1_6 = 1;
		}
		else
		{
			Q1_6 = 0;
		}
		/*--------------NetWork 5 -----------*/

		volatile uint8_t tempC1_2 = 0;
		if (countC1 > 20)
		{
			tempC1_2 = 1;
		}
		volatile uint8_t tempC1_3 = 0;
		if (countC1 <= 25)
		{
			tempC1_3 = 1;
		}
		Q2_2 = (tempC1_2 * tempC1_3 * M0_0);
		if (Q2_2 > 0)
		{
			Q2_2 = 1;
		}
		else
		{
			Q2_2 = 0;
		}
		/*--------------NetWork 6 -----------*/

		volatile uint8_t tempC1_4 = 0;
		if (countC1 > 25)
		{
			tempC1_4 = 1;
		}
		Q2_0 = (tempC1_4 * M0_0);
		if (Q2_0 > 0)
		{
			Q2_0 = 1;
		}
		else
		{
			Q2_0 = 0;
		}
		/*--------------NetWork 7 -----------*/

		T37reset = (T37);
		if (T37reset > 0)
		{
			T37reset = 1;
		}
		else
		{
			T37reset = 0;
		}
		/*--------------NetWork 8 -----------*/

		if ((M0_0))
		{
			u16VW1 = AIW0;
			// memcpy((void*)&u16VW1, (const void*)&AIW0, sizeof(uint16_t));
		}
		M1_1 = ((M0_0));
		if (M1_1 > 0)
		{
			M1_1 = 1;
		}
		else
		{
			M1_1 = 0;
		}
		/*--------------NetWork 9 -----------*/

		if ((M0_0))
			u32VD0 = (uint32_t)u16VW1;
		/*--------------NetWork 10 -----------*/

		if ((M0_0))
			f32VD10 = (float)u32VD0;
		/*--------------NetWork 11 -----------*/

		if ((M0_0))
			f32VD10 = f32VD10 / 4096.0;
		/*--------------NetWork 12 -----------*/

		if ((M0_0))
			f32VD10 = f32VD10 * 100.0;
		PLC_Write_Pin_Output();

		PLC_DataFrame_t sendFrame;

        if (xQueuePLC != NULL)
        {
            sendFrame.led_green = Q1_6;
            sendFrame.led_red = Q2_0;
            sendFrame.led_yellow = Q2_2;
            sendFrame.reserved = 0;
            sendFrame.sensor_value.fsensor_v = f32VD10;

            if (xQueueSend(xQueuePLC, &sendFrame, portMAX_DELAY) != pdPASS)
            {
                mPrint("Failed to send data to queue\n");
            }
        }
        else
        {
            mPrint("Queue is NULL\n");
        }

        mPrint("I0_0: %d, I0_1: %d, M0_0: %d, T37: %d, countT37: %d, C1: %d, countC1: %d, Q1_6: %d, Q2_0: %d, Q2_2: %d\n",
               I0_0, I0_1, M0_0, T37, countT37, C1, countC1, Q1_6, Q2_0, Q2_2);

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
                mPrint("Received data: LED Green: %d, LED Red: %d, LED Yellow: %d, Sensor Value U32: %lu, Sensor Value F32: %.2f\n",
                       receivedData.led_green,
                       receivedData.led_red,
                       receivedData.led_yellow,
                       receivedData.sensor_value.u32sensor_v,
                       receivedData.sensor_value.fsensor_v);
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

void PLC_TimerCallBack(TimerHandle_t xTimer)
{
	int id;
	id = (uint32_t)pvTimerGetTimerID(xTimer);
	switch (id)
	{
	case 1:
		countT37++;
		break;
	}
}
void PLC_InitTimer(void)
{
	handle_timerPLC[0] = xTimerCreate("timerTONT37", pdMS_TO_TICKS(100), pdTRUE, (void *)1, PLC_TimerCallBack);
}

void PLC_Read_Pin_Input(void)
{
	I0_0 = !HAL_GPIO_ReadPin(I0_0_PORT, I0_0_PIN);
	I0_1 = !HAL_GPIO_ReadPin(I0_1_PORT, I0_1_PIN);
}
void PLC_Write_Pin_Output(void)
{
	if (Q1_6 >= 1)
	{
		HAL_GPIO_WritePin(Q1_6_PORT, Q1_6_PIN, ENABLE);
	}
	else
	{
		HAL_GPIO_WritePin(Q1_6_PORT, Q1_6_PIN, DISABLE);
	}
	if (Q2_0 >= 1)
	{
		HAL_GPIO_WritePin(Q2_0_PORT, Q2_0_PIN, ENABLE);
	}
	else
	{
		HAL_GPIO_WritePin(Q2_0_PORT, Q2_0_PIN, DISABLE);
	}
	if (Q2_2 >= 1)
	{
		HAL_GPIO_WritePin(Q2_2_PORT, Q2_2_PIN, ENABLE);
	}
	else
	{
		HAL_GPIO_WritePin(Q2_2_PORT, Q2_2_PIN, DISABLE);
	}
}

static uint8_t checksum(const uint8_t * data, size_t len)
{
    uint16_t sum = 0;
    for (size_t i = 0; i < len; i++) 
        sum += data[i];
    return sum & 0xFF;
}
