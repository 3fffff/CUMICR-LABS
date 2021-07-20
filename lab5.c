#include <stm32f4xx.h>
#include "Lab1_Test.h"
#include "main.h"
uint32_t test = 0;
uint8_t var;
uint32_t i = 0;
uint8_t des[3];
uint32_t tst = 0;
uint8_t swt = 0;
uint8_t SPI_data = 0;
uint8_t prev_state = 0;
uint8_t button_state = 0,ret=0;
uint32_t button_count = 0;
uint16_t mode_count = 0, mode_new = 0;
void delay_ms(uint16_t delay_time)
{
  int i = 0;
  for (i = 0; i < delay_time; i++)
  {
    continue;
  }
}
uint8_t Button(void)
{
  if (BUTTON_READ() == 1)
  {
    if (button_count < 50)
    {
      button_count++;
    }
    else
    {
      if (button_state == 0)
      {
        button_state = 1;
        return 1;
      }
			else if(des[1]== 0x18 && button_count == 15000  && button_state ==1){
				button_state =0;
				button_count=0;
			}
    }
  }
  else
  {
    if (button_count > 0)
    {
      button_count--;
    }
    else
    {
      if (button_state == 1)
      {
        button_state = 0;
      }
    }
  }
  return 0;
}
void SysTick_Handler(void)
{
	    ret = Button();
    if (ret == 1)
    {
			GPIO_ResetBits(GPIOD, GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
      switch (swt)
      {
      case 0:
        GPIO_SetBits(GPIOD, GPIO_Pin_12); //G
        break;
      case 1:
        GPIO_SetBits(GPIOD, GPIO_Pin_15); //B
        break;
      case 2:
        GPIO_SetBits(GPIOD, GPIO_Pin_14); //R
        break;
      case 3:
        GPIO_SetBits(GPIOD, GPIO_Pin_13); //Y
        break;
      case 4:
        GPIO_SetBits(GPIOD, GPIO_Pin_15); //B
        break;
      case 5:
        GPIO_SetBits(GPIOD, GPIO_Pin_12); //G
        break;
      case 6:
        GPIO_SetBits(GPIOD, GPIO_Pin_14); //R
        break;
      case 7:
        GPIO_SetBits(GPIOD, GPIO_Pin_13); //Y
        break;
      }
      swt++;
      if (swt > 7)
        swt = 0;
      
    }
}

void button_init()
{
  GPIO_InitTypeDef GPIO_struct_Button;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  GPIO_struct_Button.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
  GPIO_struct_Button.GPIO_Mode = GPIO_Mode_IN;
  GPIO_struct_Button.GPIO_Speed = GPIO_Low_Speed;
  GPIO_struct_Button.GPIO_OType = GPIO_OType_PP;
  GPIO_struct_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_struct_Button);
}
void led_init()
{
  GPIO_InitTypeDef GPIO_struct_LED;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_struct_LED.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_struct_LED.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_struct_LED.GPIO_Speed = GPIO_Low_Speed;
  GPIO_struct_LED.GPIO_OType = GPIO_OType_PP;
  GPIO_struct_LED.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_struct_LED);
}

/*int main(void)
{
  SysTick_Config(SystemCoreClock / 1000);
  SystemCoreClockUpdate();
  var = Lab5_Test_ini("3fffff3");
  button_init();

  led_init();
  while (1)
  {

	tst = while_Test(des);
	}
  return 0;
}*/
