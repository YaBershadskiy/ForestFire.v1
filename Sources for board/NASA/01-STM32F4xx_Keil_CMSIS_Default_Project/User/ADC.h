#ifndef _ADC_CONFIG_H
#define _ADC_CONFIG_H
#include "stm32f4xx.h"

extern uint16_t ADC_ConvertedValue[900];

void ADC1_CH6_DMA_Config(void);

#endif 
