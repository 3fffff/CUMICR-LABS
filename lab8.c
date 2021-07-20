#include <stm32f4xx.h>
#include "Lab8_Test.h"
#define GREEN_ON() GPIO_SetBits(GPIOD, GPIO_Pin_12)
#define RED_ON() GPIO_SetBits(GPIOD, GPIO_Pin_14)
#define YELLOW_ON() GPIO_SetBits(GPIOD, GPIO_Pin_13)
#define BLUE_ON() GPIO_SetBits(GPIOD, GPIO_Pin_15)
#define RESET_LED() GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)
#define GET_X 0
#define GET_Y 1
#define GET_Z 2
#define CS_ON() GPIO_ResetBits(GPIOE, GPIO_Pin_3)
#define CS_OFF() GPIO_SetBits(GPIOE, GPIO_Pin_3)
uint8_t SPI_in[7];
uint8_t SPI_out[7];
uint8_t SPI_work = 0;
uint8_t res_test[4];
uint8_t type_acc = 0;
uint8_t ret_test[4];
uint8_t SPI_counter = 0, counter = 0;
int16_t data_x, data_y, data_z;
void LED_init()
{
	GPIO_InitTypeDef GPIO_USART_ini;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_USART_ini.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_USART_ini.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_USART_ini.GPIO_Speed = GPIO_Low_Speed;
	GPIO_USART_ini.GPIO_OType = GPIO_OType_PP;
	GPIO_USART_ini.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_USART_ini);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_USART_ini.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_USART_ini.GPIO_Mode = GPIO_Mode_AF;
	GPIO_USART_ini.GPIO_Speed = GPIO_Low_Speed;
	GPIO_USART_ini.GPIO_OType = GPIO_OType_PP;
	GPIO_USART_ini.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_USART_ini);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	GPIO_USART_ini.GPIO_Pin = GPIO_Pin_3;
	GPIO_USART_ini.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_USART_ini.GPIO_Speed = GPIO_Low_Speed;
	GPIO_USART_ini.GPIO_OType = GPIO_OType_PP;
	GPIO_USART_ini.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_USART_ini);
	CS_OFF();
}
void SPI_DMA_init()
{
	DMA_InitTypeDef DMA_init_SPI;
	SPI_InitTypeDef SPI_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Cmd(SPI1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	DMA_init_SPI.DMA_Channel = DMA_Channel_3;
	DMA_init_SPI.DMA_PeripheralBaseAddr = (uint32_t) & (SPI1->DR);
	DMA_init_SPI.DMA_Memory0BaseAddr = (uint32_t)SPI_out;
	DMA_init_SPI.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_init_SPI.DMA_BufferSize = 2;
	DMA_init_SPI.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_init_SPI.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_init_SPI.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_init_SPI.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_init_SPI.DMA_Mode = DMA_Mode_Normal;
	DMA_init_SPI.DMA_Priority = DMA_Priority_Medium;
	DMA_init_SPI.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_init_SPI.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_init_SPI.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_init_SPI.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream3, &DMA_init_SPI);
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
	DMA_ITConfig(DMA2_Stream3, DMA_IT_TC, ENABLE);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);

	DMA_init_SPI.DMA_Channel = DMA_Channel_3;
	DMA_init_SPI.DMA_PeripheralBaseAddr = (uint32_t) & (SPI1->DR);
	DMA_init_SPI.DMA_Memory0BaseAddr = (uint32_t)SPI_in;
	DMA_init_SPI.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_init_SPI.DMA_BufferSize = 2;
	DMA_init_SPI.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_init_SPI.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_init_SPI.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_init_SPI.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_init_SPI.DMA_Mode = DMA_Mode_Normal;
	DMA_init_SPI.DMA_Priority = DMA_Priority_Medium;
	DMA_init_SPI.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_init_SPI.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
	DMA_init_SPI.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_init_SPI.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_init_SPI);
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);
	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
}

uint8_t getSPI_in(uint8_t adr)
{
	return SPI_in[adr];
}
void SetSPI_out(uint8_t adr, uint8_t data)
{
	if (adr < 7)
		SPI_out[adr] = data;
}
void startSPI(uint8_t number)
{
	DMA_SetCurrDataCounter(DMA2_Stream0, number);
	DMA_SetCurrDataCounter(DMA2_Stream3, number);

	SPI_work = 1;
	CS_ON();
	DMA_Cmd(DMA2_Stream0, ENABLE);
	DMA_Cmd(DMA2_Stream3, ENABLE);
}

void SPI_systick()
{
	if (SPI_counter == 7)
	{
		if (type_acc == 0)
		{
			counter = (counter + 1) % 3;
			if (counter == GET_X)
			{
				SetSPI_out(0, 0xA9);
				SetSPI_out(1, 0x00);
			}
			else if (counter == GET_Y)
			{
				SetSPI_out(0, 0xAB);
				SetSPI_out(1, 0x00);
			}
			else if (counter == GET_Z)
			{
				SetSPI_out(0, 0xAD);
				SetSPI_out(1, 0x00);
			}
			Lab8_data_out(SPI_out[0]);
			startSPI(2);
		}
		else if (type_acc == 1)
			startSPI(7);
		SPI_counter = 0;
	}
	else
		SPI_counter++;
}
void DMA2_Stream3_IRQHandler()
{
	if (DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3) == SET)
		DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);
}
void DMA2_Stream0_IRQHandler()
{
	uint16_t i = 0;
	if (DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0) == SET)
	{
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
		CS_OFF();

		RESET_LED();
		if (type_acc == 1)
		{

			data_x = ((uint16_t)SPI_in[2] << 8) | ((uint16_t)SPI_in[1]);
			data_x /= 16.384;
			data_y = ((uint16_t)SPI_in[4] << 8) | ((uint16_t)SPI_in[3]);
			data_y /= 16.384;
			data_z = ((uint16_t)SPI_in[6] << 8) | ((uint16_t)SPI_in[5]);
			data_z /= 16.384;
			if (data_x > 700)
			{
				RED_ON();
			}
			else if (data_x < -700)
			{
				GREEN_ON();
			}
			else if (data_y > 1200)
			{
				YELLOW_ON();
			}
			else if (data_y < -1200)
			{
				BLUE_ON();
			}
		}
		else if (type_acc == 0)
		{
			if (counter == GET_X)
			{
				data_x = (int8_t)SPI_in[1] * 1000 / 55;
				if (data_x > 700)
				{
					RED_ON();
				}
				else if (data_x < -700)
				{
					GREEN_ON();
				}
			}
			if (counter == GET_Y)
			{
				data_y = (int8_t)SPI_in[1] * 1000 / 55;
				if (data_y > 700)
				{
					YELLOW_ON();
				}
				else if (data_y < -700)
				{
					BLUE_ON();
				}
			}
			if (counter == GET_Z)
			{
				data_z = (int8_t)SPI_in[1] * 1000 / 55;
			}
		}

		SPI_work = 0;
		Lab8_data_in(SPI_in[1]);
		Lab8_data_in(SPI_in[2]);
		Lab8_data_in(SPI_in[3]);
		Lab8_data_in(SPI_in[4]);
		Lab8_data_in(SPI_in[5]);
		Lab8_data_in(SPI_in[6]);
		get_decision(ret_test);
	}
}
void SysTick_Handler()
{
	SPI_systick();
}
void SPIWait()
{
	while (SPI_work)
	{
	}
}
uint32_t result;
int main()
{
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000);
	LED_init();
	SPI_DMA_init();
	SetSPI_out(0, 0x8F);
	SetSPI_out(1, 0x00);
	startSPI(2);
	SPIWait();
	if ((uint8_t)getSPI_in(1) == 0x3B)
	{
		type_acc = 1;
	}
	else if (getSPI_in(1) == 0x3F)
	{
		type_acc = 0;
		SetSPI_out(0, 0x20);
		SetSPI_out(1, 0x97);
		startSPI(2);
		SPIWait();
	}
	Lab8_ini(type_acc);
	while (1)
	{
		result = Lab8_while();
	}
}