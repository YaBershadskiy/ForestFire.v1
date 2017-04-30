/*******************************************************************/

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_usart.h"
#include <stm32f4xx_adc.h>
#include "tm_stm32f4_adc.h"
#include <stdio.h>
#include "ADC.h"
#include "math.h"
#include "tm_stm32f4_adc.h"

GPIO_InitTypeDef gpio;
USART_InitTypeDef usart;
NVIC_InitTypeDef nvic; 
int time_send, time_counter = 0;
uint8_t data_usart;
char str[15];
int temperature=0;
int smoke=0;
int humidity=0;
void Init_Gpio_UART(){    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
   
    GPIO_StructInit(&gpio);
 
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Pin = GPIO_Pin_9;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &gpio);
 
    gpio.GPIO_Mode = GPIO_Mode_AF;
    gpio.GPIO_Pin = GPIO_Pin_10;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    gpio.GPIO_OType = GPIO_OType_PP;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &gpio);
 
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	}
		
void Init_USART(void){
		USART_StructInit(&usart);
		usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		usart.USART_BaudRate = 19200;	
		usart.USART_Parity = USART_Parity_No;
		usart.USART_StopBits = USART_StopBits_1;
		USART_Init(USART1, &usart);
	
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // enable the USART1 receive interrupt 
 
		USART_Cmd(USART1, ENABLE);	
}
	
void Init_Nvic_USART(void){
	
		nvic.NVIC_IRQChannel = USART1_IRQn;
		nvic.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&nvic);

		
}


void send_Uart(USART_TypeDef* USARTx, unsigned char c){
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)== RESET){}
	USART_SendData(USARTx, c);
}

void send_Uart_str(USART_TypeDef* USARTx, unsigned char *s){
while (*s != 0)
	send_Uart(USARTx, *s++);
}
void timer_delay(void){
	
	NVIC_InitTypeDef NVIC_InitStruct;;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
     
    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 45000 -1;
    TIM_TimeBaseStructure.TIM_Period = 1000;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);
     
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);   
    
}
float GetKTY81(float r){
    float const Pt100[] = { 515,567,624,684,747,815,886,961,
														1040,1122,1209,1299,1392,1490,1591,
														1696,1805,1915,2023,2124,2211,
													};
											
    int t = -50, i, dt = 10;
    if (r > Pt100[i = 0])
      while (150 > t) 
			{
        //dt = 10;
        if (r < Pt100[++i])
          return t + (r - Pt100[i-1]) * dt / (Pt100[i] - Pt100[i-1]);
        t += dt;
      }
    return t;
}

double convertAdcToResistant(int adcValue){
	double res_adc=0;
	double r = 0;
	double temp = 0;
	
	//нахождение температуры ЦО
	res_adc=((3.3*(adcValue))/4096);
	r=(1000/((3.3/res_adc)-1));
	return r;
}	
int Round(float x){
	float _temp,a;
	
	_temp = fmodf(x,a);
	//_temp = _x % 1;
	
	if (_temp<0.3)
	{
		return floor(x);
	}
	if (_temp>0.7)
	{
		return ceil(x);
	}

}
uint16_t Sort (uint16_t _a, uint16_t _b, uint16_t _c){
	uint16_t a, b, c, t;
	a = _a;
	b = _b;
	c = _c;

	for (int i = 0; i<2; i++)
	{
		if (a>b)
		{
			t = b;
			b = a;
			a = t;
		}
		if (b>c)
		{
			t = c;
			c = b;
			b = t;
		}
	}
	return b;
}



int main(){   
	Init_Gpio_UART();
	Init_USART();
	Init_Nvic_USART();
	timer_delay();
	TM_ADC_Init(ADC1, ADC_Channel_10);
		TM_ADC_Init(ADC1, ADC_Channel_11);
		while(1){
			
			temperature = Round(GetKTY81(convertAdcToResistant(TM_ADC_Read(ADC1, ADC_Channel_10))));
			smoke = TM_ADC_Read(ADC1, ADC_Channel_11);
			humidity = 10;
			sprintf(str, "ID:1 Temperature:%d, Smoke:%d, Humidity:%d",temperature, smoke, humidity);
			
			if((temperature>30)||(smoke>500)){
				time_send = 3;
			}else{
				time_send = 25;
			}
			
			
				if(time_counter >= time_send){
					send_Uart_str(USART1,"\n\r");
					send_Uart_str(USART1,str);
					send_Uart_str(USART1,"\n\r");
					time_counter = 0;
				}
				
			if(data_usart==49){				
				send_Uart_str(USART1,"\n\r");
				send_Uart_str(USART1,str);
				send_Uart_str(USART1,"\n\r");
				data_usart = 0;
			}
			
		}
}
 

/*******************************************************************/