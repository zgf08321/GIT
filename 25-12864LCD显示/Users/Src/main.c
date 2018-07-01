#include "stm32f10x.h"
#include "usart.h"
#include "ST5767.h"
#include "delay.h"
#include "LCD12864.h"
#include "ds18b20.h"
#include "DS1302.h"
#include "key.h"
#include "MENU.h"

/****************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void RCCINIT()	 //ϵͳʱ������
{	
	//SystemInit();					//ϵͳʱ�ӳ�ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		  //��GPIOB��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	      //��GPIOA��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//�ܽŸ��ù���ʱ�Ӵ�
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//�ѵ���������ͨIO��
}


void RCC_Configuration(void)
{   
	ErrorStatus HSEStartUpStatus;
 //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_DeInit();

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON);

   //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
  {								    
    //����FLASH��Ԥȡ����
//    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH�ӳ�2������
//    FLASH_SetLatency(FLASH_Latency_2);
 	
  //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    //ʹ��PLLʱ��
    RCC_PLLCmd(ENABLE);

   //�ȴ�PLLʱ�Ӿ���
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

  //����ϵͳʱ�� = PLLʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

   //���PLLʱ���Ƿ���Ϊϵͳʱ��
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}


float f;
u8 In;
int main(void)
{
	u8 key;
	RCC_Configuration();
	RCCINIT();
	delay_init();
	uart_init(9600);
	printf("uart_init!");
	
	DS1302_GPIOINIT();
	settime();
	readtime();
	delay_ms(10);
	
	KEY_Init();
	delay_ms(1000);
	delay_us(1000);
  LCD_Init();
//	In = DS18B20_Init();
	manyou=&m0_main[0]; //?????  
  Locate(manyou); //����˵�
	while (1)
	{
		key = keyscan();
		if(key != 255)
		{
			MENU(key);
		}
	}
}

