#include <stm32f4xx.h>
#include "Lab3_Test.h"
uint32_t test = 0;
uint8_t var;
uint32_t i = 0;
uint8_t des[3];
uint8_t tst = 0;
uint8_t swt = 0;
uint8_t prev_state=0;
int main(void)
{
	

	GPIO_InitTypeDef GPIO_struct_LED;
	GPIO_InitTypeDef GPIO_struct_Button;
	//RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	//SystemInit ();
	// GPIOD->OTYPER = 0;
	//	GPIOD->OSPEEDR = 0;
	//RCC_AHB1Periph_GPIOD
	//SysTick_Config(SystemCoreClock /1000);//1ms
prev_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed;
	GPIO_struct_LED.GPIO_OType = GPIO_OType_PP;
	GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_struct_LED);
	GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
	GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN;
	GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed;
	GPIO_struct_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_struct_Button);
	var = Lab3_Test_ini("3fffff3");
	//GPIOD->ODR  = 0x0000;
	//GPIOD->MODER = 0x40000000 << 0; blue
	//GPIOD->MODER = 0x10000000 << 0; red
	//GPIOD->MODER = 0x04000000 << 0; yellow
	//GPIOD->MODER = 0x01000000 << 0; green
	//	GPIOD->ODR  = 0xF000;
	/*GPIOD->MODER = 0x01000000; //G
		for(i=0;i<3000000;i++) {}
		GPIOD->MODER = 0x04000000; //Y
		for(i=0;i<3000000;i++) {}
		GPIOD->MODER = 0x01000000; //G
		for(i=0;i<3000000;i++) {}
		GPIOD->MODER = 0x40000000; //B
		for(i=0;i<3000000;i++) {}
		GPIOD->MODER = 0x01000000; //G
		for(i=0;i<3000000;i++) {}
		GPIOD->MODER = 0x04000000; //Y
		for(i=0;i<3000000;i++) {}
		GPIOD->MODER = 0x01000000; //G
		for(i=0;i<3000000;i++) {}
		GPIOD->MODER = 0x40000000; //B
		for(i=0;i<3000000;i++) {}
		*/
	while (1)
	{
		GPIO_WriteBit(GPIOA, GPIO_Pin_0, GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2));
		tst = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
		if (prev_state != GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) && /*GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1 && */ GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 1)
		{
			switch (swt)
			{
			case 0:
			//{
				GPIO_SetBits(GPIOD, GPIO_Pin_12); //G
												  //for(i=0;i<3000000;i++) {}
												  //	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
		//	}
			break;
			case 1:
			//{
				GPIO_SetBits(GPIOD, GPIO_Pin_15); //B
												  //	for(i=0;i<3000000;i++) {}
												  //		GPIO_ResetBits(GPIOD,GPIO_Pin_15);
		//	}
			break;
			case 2:
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_14); //R
												  //	for(i=0;i<3000000;i++) {}
												  //GPIO_ResetBits(GPIOD,GPIO_Pin_14);
			}
			break;
			case 3:
		//	{
				GPIO_SetBits(GPIOD, GPIO_Pin_13); //Y
												  //	for(i=0;i<3000000;i++) {}
												  //GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		//	}
			break;
			case 4:
		//	{
				GPIO_SetBits(GPIOD, GPIO_Pin_15); //B
												  //	for(i=0;i<3000000;i++) {}
												  //	GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		//	}
			break;
			case 5:
			{
				GPIO_SetBits(GPIOD, GPIO_Pin_12); //G
												  //	for(i=0;i<3000000;i++) {}
												  //	GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			}
			break;
			case 6:
		//	{
				GPIO_SetBits(GPIOD, GPIO_Pin_14); //R
												  //	for(i=0;i<3000000;i++) {}
												  //GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		//	}
			break;
			case 7:
		//	{
				GPIO_SetBits(GPIOD, GPIO_Pin_13); //Y
												  //	for(i=0;i<3000000;i++) {}
												  //GPIO_ResetBits(GPIOD, GPIO_Pin_13);
	//		}
			break;
			}

		}
		else
		{
			swt++;
			if(swt == 8)swt = 0;
			GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		}
		for (i = 0; i < 20; i++)
			{}
		prev_state = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2);
		test = while_Test(des);

	}
}
void SysTick_Handler(void){
if(i>0){i--;if (i == 1){Flag=1;}}
}
