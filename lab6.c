#include <stm32f4xx.h>
#include "Lab6_Test.h"
uint32_t test = 0;
uint8_t var;
uint32_t i = 0;
uint16_t des[1000];
uint8_t tst = 0;
uint8_t swt = 0;
uint8_t prev_state = 0;
uint32_t delay_count = 0, mode_count = 5400;
void SysTick_Handler(void)
{
	if (mode_count > 0)
	{
		mode_count--;
	}
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,
							  TIM_IT_Update);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, 1);
	}else{
		
	}
}

int main(void)
{

	TIM_TimeBaseInitTypeDef timer_struct;
	GPIO_InitTypeDef GPIO_struct_Button;
	NVIC_InitTypeDef NVIC_struct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_struct_Button.GPIO_Pin = GPIO_Pin_2;
	GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN;
	GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed;
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_struct_Button);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	timer_struct.TIM_Prescaler = 19;
	timer_struct.TIM_Period  = 1000;
	timer_struct.TIM_CounterMode = TIM_CounterMode_Up;
	timer_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	timer_struct.TIM_RepetitionCounter = 0;
	NVIC_struct.NVIC_IRQChannel =TIM3_IRQn;
	NVIC_struct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_struct.NVIC_IRQChannelCmd = ENABLE;
	TIM_TimeBaseInit(TIM3, &timer_struct);
	NVIC_EnableIRQ(TIM3_IRQn);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	NVIC_Init(&NVIC_struct);
	TIM_Cmd(TIM3, ENABLE);
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 5400); //1ms
	var = Lab6_Test_ini("3fffff3");
	while(1){
		
	test = while_Test(des);
		GPIO_WriteBit(GPIOA, GPIO_Pin_2, 0);
	}
}
