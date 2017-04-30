#include "ADC.h"

extern volatile uint16_t RegularConvData_Tab[];
extern volatile uint16_t temp_res_mass[];

void ADC1_CH6_DMA_Config(void)
{
	ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;
	NVIC_InitTypeDef 			nvic;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

//  DMA_DeInit(DMA2_Stream0);
  /* DMA2 Stream0 channe0 configuration **************************************/
  DMA_InitStructure.DMA_Channel = 							DMA_Channel_0;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = 		(uint32_t)&ADC1->DR;
  DMA_InitStructure.DMA_Memory0BaseAddr = 			(uint32_t)&ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = 									DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 						900;
  DMA_InitStructure.DMA_PeripheralInc = 				DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = 						DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = 		DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = 				DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = 									DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = 							DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = 							DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = 				DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = 					DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = 			DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);

  /* Configure ADC1 Channel6 pin as analog input ******************************/
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	

  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = 						ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = 			ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = 	ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay =ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC1 Init ****************************************************************/
  ADC_InitStructure.ADC_Resolution = 						ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = 					ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = 		DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv =			ADC_ExternalTrigConv_T3_TRGO;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = 	ADC_ExternalTrigConvEdge_Rising;
  ADC_InitStructure.ADC_DataAlign = 						ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 			3;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channe6 configuration *************************************/
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_3Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_3Cycles);

  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  /* Enable ADC3 DMA */
  ADC_DMACmd(ADC1, ENABLE);
	
  /* Enable ADC3 */
  ADC_Cmd(ADC1, ENABLE);
	
	//irq dma
		nvic.NVIC_IRQChannel = 											DMA2_Stream0_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 		1;
    nvic.NVIC_IRQChannelSubPriority = 					0;
    nvic.NVIC_IRQChannelCmd = 									ENABLE;
    NVIC_Init(&nvic);
		
    DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);
	
}
