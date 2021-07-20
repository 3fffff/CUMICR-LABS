#include "stm32f4xx.h"
//#include "stdio.h"
#include "Lab10_test.h"
uint16_t delay_count = 0;
uint16_t ADC_result = 0;
/*void TIM2_IRQHandler(void)
{
	//period[1]=1;
		if(i<7){
			DAC_SetChannel1Data(DAC_Align_12b_R, 1120*1.365+140*i);
	i++;
	}
	else i=0;

//	ADC_SoftwareStartConv(ADC1);

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,
							  TIM_IT_Update);
	}
}*/
void SysTick_Handler(void) //1ms
{
	lab10_systick();
	//ADC_SoftwareStartConv(ADC1);
	//lab9_systick();
	//delay_ms(10);
}

//----------------------------------------------
//
//----------------------------------------------
void ADC_IRQHandler(void)
{
	if(ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET)
	{
	ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
	
	ADC_result = ADC_GetConversionValue(ADC1);
	//if(min>ADC_result)min= ADC_result;
	//if(max<ADC_result)max=ADC_result;
	}
	//sprintf(str, "V=%d mv", ADC_result);
}
//----------------------------------------------
//
//----------------------------------------------
/*void DAC_init()
{
		GPIO_InitTypeDef GPIO_Init_DAC;
	DAC_InitTypeDef DAC_InitDAC;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_Init_DAC.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init_DAC.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_DAC.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_DAC.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_DAC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Init_DAC);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	DAC_InitDAC.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitDAC.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	//DAC_InitDAC.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;
	DAC_InitDAC.DAC_Trigger = DAC_Trigger_T2_TRGO;//DAC_Trigger_T4_TRGO;
	DAC_InitDAC.DAC_WaveGeneration = DAC_WaveGeneration_None; //DAC_WaveGeneration_None;
	DAC_Init(DAC_Channel_1, &DAC_InitDAC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_InitTypeDef dac_triangle;
	TIM_TimeBaseInitTypeDef timer;
	GPIO_InitTypeDef gpio_dacchannel1;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_DAC, ENABLE);
	//---????????????? 4 ?????? GPIO---//
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM2);
	GPIO_StructInit(&gpio_dacchannel1);
	gpio_dacchannel1.GPIO_Mode = GPIO_Mode_AF;
	gpio_dacchannel1.GPIO_OType = GPIO_OType_PP;
	gpio_dacchannel1.GPIO_Pin = GPIO_Pin_2;
	gpio_dacchannel1.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_dacchannel1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_dacchannel1);
	//---????????????? ??????? TIM4 ? ???????? ????????---//

	TIM_TimeBaseStructInit(&timer);
	timer.TIM_ClockDivision = TIM_CKD_DIV1;
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_Period = 20 - 1;
	timer.TIM_Prescaler = 10;
	TIM_TimeBaseInit(TIM2, &timer);
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
	//---????????????? ?????????????? ???????---//
	//---????????????? ???, ????? 1---//

	DAC_StructInit(&dac_triangle);
	dac_triangle.DAC_Trigger = DAC_Trigger_T2_TRGO;
	dac_triangle.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
	dac_triangle.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_2047;
	dac_triangle.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &dac_triangle);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	TIM_Cmd(TIM2, ENABLE);
}*/
void ADC_timer()
{
	TIM_TimeBaseInitTypeDef timer_struct;
	//NVIC_InitTypeDef NVIC_struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	timer_struct.TIM_Prescaler = 20 - 1;
	timer_struct.TIM_Period = 10;
	timer_struct.TIM_CounterMode = TIM_CounterMode_Up;
	timer_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	timer_struct.TIM_RepetitionCounter = 0;
//	NVIC_struct.NVIC_IRQChannel = TIM3_IRQn;
//	NVIC_struct.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_struct.NVIC_IRQChannelSubPriority = 0;
//	NVIC_struct.NVIC_IRQChannelCmd = ENABLE;
	TIM_TimeBaseInit(TIM3, &timer_struct);
	//NVIC_EnableIRQ(TIM2_IRQn);
	//TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	///NVIC_Init(&NVIC_struct);
	TIM_SelectOutputTrigger(TIM3,TIM_TRGOSource_Update);
	TIM_Cmd(TIM3, ENABLE);
}
void ADC_init(void)
{
	ADC_InitTypeDef ADC_InitType;
	GPIO_InitTypeDef GPIO_Init_user;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_Init_user.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init_user.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init_user.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_user.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_user.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_Init_user);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitType.ADC_ContinuousConvMode = DISABLE;
	ADC_InitType.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitType.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_InitType.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//ADC_ExternalTrigConvEdge_Rising;
	ADC_InitType.ADC_NbrOfConversion = 1;
	ADC_InitType.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitType.ADC_ScanConvMode = DISABLE;

	ADC_Init(ADC1, &ADC_InitType);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 1, ADC_SampleTime_56Cycles);

	NVIC_EnableIRQ(ADC_IRQn);
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
	//ADC_timer();
	ADC_Cmd(ADC1, ENABLE);
}

/*void dac_saw(void)
{
	//---??????? ???????? ?????????---//
	uint16_t sin[74] = {2225, 2402, 2577, 2747, 2912, 3070, 3221, 3363, 3494, 3615, 3724, 3820, 3902, 3971, 4024, 4063, 4085, 4095, 4063, 4024, 3971, 3902, 3820, 3724, 3615, 3495, 3363, 3221, 3071, 2912, 2747, 2577, 2403, 2226, 2047, 1869, 1692, 1517, 1347, 1182, 1024, 873, 731, 600, 479, 370, 274, 192, 274, 124, 70, 31, 31, 10, 0, 10, 31, 70, 123, 192, 274, 370, 479, 599, 599, 731, 873, 1023, 1182, 1347, 1517, 1691, 1868, 2047};
	DMA_InitTypeDef DMA_dac;
	GPIO_InitTypeDef gpio_dacchannel1;
	GPIO_InitTypeDef gpio_dacchannel2;
	TIM_TimeBaseInitTypeDef timer;
	DAC_InitTypeDef dac_sin;
	DAC_InitTypeDef dac_triangle;
	//---???????????? ???????????? ?????????---//
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	//---????????????? 4 ?????? GPIO---//

	GPIO_StructInit(&gpio_dacchannel1);
	gpio_dacchannel1.GPIO_Mode = GPIO_Mode_AF;
	gpio_dacchannel1.GPIO_OType = GPIO_OType_PP;
	gpio_dacchannel1.GPIO_Pin = GPIO_Pin_2;
	gpio_dacchannel1.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_dacchannel1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio_dacchannel1);

	DAC_StructInit(&dac_triangle);
	dac_triangle.DAC_Trigger = DAC_Trigger_None;
	dac_triangle.DAC_WaveGeneration = DAC_WaveGeneration_None;
	dac_triangle.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	dac_triangle.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &dac_triangle);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}*/

//----------------------------------------------
//
//----------------------------------------------
uint16_t i=0;
int main(void)
{
	SysTick_Config(SystemCoreClock / 1000); //1 ms
	//ADC_init();
	lab10_Test_ini(0);
	//DAC_SetChannel1Data(DAC_Align_12b_R, 4095);
	
	while (1)
	{
		
		//	for(i=0;i<100;i++){}
		//	ADC_SoftwareStartConv(ADC1);
		//		
				val=check_result(min,max,200);
		//val=0;
		//check_result();
		//val = lab10_while(period);
	}
}
