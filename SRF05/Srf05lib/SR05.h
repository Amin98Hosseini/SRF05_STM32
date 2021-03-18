#ifndef __SR04
#define __SR04

#include "stm32f1xx_hal.h"


#define    TRIG_PIN             GPIO_PIN_9
#define    TRIG_PORT           GPIOA



void delay(uint16_t time);
uint8_t SR05_Read (void);
void input_capture(void);
uint8_t srf05_data(void);

#endif
