#ifndef INC_CSDL_H_
#define INC_CSDL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "main.h"
#include "cmsis_os.h"
#include "timers.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Define Input arrays */
#define IB0 	    I[0][0]
#define IDW0 	    I[0][0]
#define IW0 	    I[0][0]
#define I0_0 	    I[0][0]
#define I0_1 	    I[0][1]
#define I0_2 	    I[0][2]
#define I0_3 	    I[0][3]
#define I0_4 	    I[0][4]
#define I0_5 	    I[0][5]
#define I0_6 	    I[0][6]
#define I0_7 	    I[0][7]
#define IB1 	    I[1][0]
#define IDW1 	    I[1][0]
#define IW1 	    I[1][0]
#define I1_0        I[1][0]
#define I1_1        I[1][1]
#define I1_2        I[1][2]
#define I1_3        I[1][3]
#define I1_4        I[1][4]
#define I1_5        I[1][5]
#define I1_6        I[1][6]
#define I1_7        I[1][7]
#define IB2         I[2][0]
#define IDW2        I[2][0]
#define IW2         I[2][0]
#define I2_0        I[2][0]
#define I2_1        I[2][1]
#define I2_2        I[2][2]
#define I2_3        I[2][3]
#define I2_4        I[2][4]
#define I2_5        I[2][5]
#define I2_6        I[2][6]
#define I2_7        I[2][7]


/* Define Output arrays */
#define QB0         Q[0][0]
#define QDW0        Q[0][0]
#define QW0         Q[0][0]
#define Q0_0        Q[0][0]
#define Q0_1        Q[0][1]
#define Q0_2        Q[0][2]
#define Q0_3        Q[0][3]
#define Q0_4        Q[0][4]
#define Q0_5        Q[0][5]
#define Q0_6        Q[0][6]
#define Q0_7        Q[0][7]
#define QB1         Q[1][0]
#define QDW1        Q[1][0]
#define QW1         Q[1][0]
#define Q1_0        Q[1][0]
#define Q1_1        Q[1][1]
#define Q1_2        Q[1][2]
#define Q1_3        Q[1][3]
#define Q1_4        Q[1][4]
#define Q1_5        Q[1][5]
#define Q1_6        Q[1][6]
#define Q1_7        Q[1][7]
#define QB2         Q[2][0]
#define QDW2        Q[2][0]
#define QW2         Q[2][0]
#define Q2_0        Q[2][0]
#define Q2_1        Q[2][1]
#define Q2_2        Q[2][2]
#define Q2_3        Q[2][3]
#define Q2_4        Q[2][4]
#define Q2_5        Q[2][5]
#define Q2_6        Q[2][6]
#define Q2_7        Q[2][7]


/* Define Memory arrays */
#define MB0         M[0][0]
#define MDW0        M[0][0]
#define MW0         M[0][0]
#define M0_0        M[0][0]
#define M0_1        M[0][1]
#define M0_2        M[0][2]
#define M0_3        M[0][3]
#define M0_4        M[0][4]
#define M0_5        M[0][5]
#define M0_6        M[0][6]
#define M0_7        M[0][7]
#define MB1         M[1][0]
#define MDW1        M[1][0]
#define MW1         M[1][0]
#define M1_0        M[1][0]
#define M1_1        M[1][1]
#define M1_2        M[1][2]
#define M1_3        M[1][3]
#define M1_4        M[1][4]
#define M1_5        M[1][5]
#define M1_6        M[1][6]
#define M1_7        M[1][7]
#define MB2         M[2][0]
#define MDW2        M[2][0]
#define MW2         M[2][0]
#define M2_0        M[2][0]
#define M2_1        M[2][1]
#define M2_2        M[2][2]
#define M2_3        M[2][3]
#define M2_4        M[2][4]
#define M2_5        M[2][5]
#define M2_6        M[2][6]
#define M2_7        M[2][7]

/* Define AIW */
#define AIW0        AI[0]
#define AIW1        AI[1]
#define AIW2        AI[2]
#define AIW3        AI[3]
#define AIW4        AI[4]
#define AIW5        AI[5]
#define AIW6        AI[6]
#define AIW7        AI[7]

/* Define VW */
#define u16VW0      u16VW[0]
#define u16VW1      u16VW[1]
#define u16VW2      u16VW[2]
#define u16VW3      u16VW[3]
#define u16VW4      u16VW[4]
#define u16VW5      u16VW[5]
#define u16VW6      u16VW[6]
#define u16VW7      u16VW[7]

/* Define uint32_t VD */
#define u32VD0      u32VD[0]
#define u32VD1      u32VD[1]
#define u32VD2      u32VD[2]
#define u32VD3      u32VD[3]
#define u32VD4      u32VD[4]
#define u32VD5      u32VD[5]
#define u32VD6      u32VD[6]
#define u32VD7      u32VD[7]

/*  Define float VD */
#define f32VD0      f32VD[0]
#define f32VD1      f32VD[1]
#define f32VD2      f32VD[2]
#define f32VD3      f32VD[3]
#define f32VD4      f32VD[4]
#define f32VD5      f32VD[5]
#define f32VD6      f32VD[6]
#define f32VD7      f32VD[7]

// Define Input Pin
#define I0_0_PIN    GPIO_PIN_13
#define I0_1_PIN    GPIO_PIN_0


// Define Input Port
#define I0_0_PORT   GPIOC
#define I0_1_PORT   GPIOC


// Define Output pin
#define Q0_0_PIN    GPIO_PIN_5

/* Define Output Port */
#define Q0_0_PORT   GPIOA

/* Define Random values */
#define R			((float)rand()/(float)RAND_MAX)
#define MIN_RATE	(30.0) // Giá trị cảm biến tối thiểu của cảm biến LM35
#define MAX_RATE	(60.0) // Giá trị cảm biến tối đa của cảm biến LM35
/* Define Random sensor value */
#define RAND_SENSOR_VALUE (MIN_RATE + R * (MAX_RATE - MIN_RATE));


/* Define data frame */
typedef union {
    uint32_t u32sensor_v; /** Giá trị cảm biến 32 bit */
    float fsensor_v; /** Giá trị cảm biến 32 bit d?u dạng float */
} sensor_value; /** Giá trị cảm biến */

typedef struct {
    uint8_t led_status; /** Trạng thái led */
    uint8_t reserved[3];
    sensor_value temperature; /** Giá trị cảm biến nhiệt độ */
    sensor_value temperature_fake; /** Giá trị cảm biến nhiệt độ giả lập */
} PLC_DataFrame_t;

/* Define global variable */
extern volatile uint16_t AI[8];
extern QueueHandle_t xQueuePLC;

/* Define function prototype */
void PLC_ProcessTask(void *param);
void PLC_SendDataTask(void *param);
void PLC_Read_Pin_Input(void);
void PLC_Write_Pin_Output(void);

#endif /*INC_CSDL_H_*/