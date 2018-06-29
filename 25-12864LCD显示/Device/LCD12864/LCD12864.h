#ifndef __LCD12864_H_
#define __LCD12864_H_

#include "stm32f10x.h"


struct NumbCharType                 
{
	unsigned char  Index[1];           
	unsigned char  Msk[16];           
};

extern struct NumbCharType Numb_Char[];


/*************定义所使用的IO口**************/
//#define RCC_ST5767 	RCC_APB2Periph_GPIOA	
//#define GPIO_PORT 	GPIOB

///**************8位LED的IO口定义************/
//#define DATA_PORT 	(GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12\
//|GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)

/**********IO set**********/
//CS
#define LCD_CS(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_7, Bit_RESET);
//RSET
#define LCD_RST(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_6, Bit_RESET);
//RW
#define LCD_SCLK(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
//RS
#define LCD_DC(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_5, Bit_RESET);
//RD
#define LCD_SI(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);

//void InitST7567_IO(void);
//void Lcd12864_Init(void);
void Lcd12864_ClearScreen(void);
void LCD_ClearScreen_(unsigned char x);
//unsigned char Lcd12864_Write16CnCHAR(unsigned char x, unsigned char y, unsigned char *cn);
void InitLCD12864_IO(void);
void LCD12864_init(void);
void LCD_Init(void);
unsigned char Lcd_Write16CnChar(unsigned char x, unsigned char y,  char *cn);
unsigned char Lcd_WriteNumbChar(unsigned char x, unsigned char y,  char *Numb);
void GT20L16S1Y_LCD(unsigned char x, unsigned char y, char *cn);

#endif

