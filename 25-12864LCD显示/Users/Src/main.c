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
void RCCINIT()	 //系统时钟配置
{	
	//SystemInit();					//系统时钟初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);		  //打开GPIOB的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	      //打开GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//管脚复用功能时钟打开
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//把调试设置普通IO口
}


void RCC_Configuration(void)
{   
	ErrorStatus HSEStartUpStatus;
 //复位RCC外部设备寄存器到默认值
  RCC_DeInit();

  //打开外部高速晶振
  RCC_HSEConfig(RCC_HSE_ON);

   //等待外部高速时钟准备好
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //外部高速时钟已经准别好
  {								    
    //开启FLASH的预取功能
//    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH延迟2个周期
//    FLASH_SetLatency(FLASH_Latency_2);
 	
  //配置AHB(HCLK)时钟=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //配置APB2(PCLK2)钟=AHB时钟
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //配置APB1(PCLK1)钟=AHB 1/2时钟
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //配置PLL时钟 == 外部高速晶体时钟*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    //使能PLL时钟
    RCC_PLLCmd(ENABLE);

   //等待PLL时钟就绪
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

  //配置系统时钟 = PLL时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

   //检查PLL时钟是否作为系统时钟
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
  Locate(manyou); //进入菜单
	while (1)
	{
		key = keyscan();
		if(key != 255)
		{
			MENU(key);
		}
	}
}

