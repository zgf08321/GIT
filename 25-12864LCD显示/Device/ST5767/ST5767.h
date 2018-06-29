#ifndef __ST5767_H_
#define __ST5767_H_

#include "stm32f10x.h"

// ------------------  ??????????? ------------------------ //
struct Cn16CharTypeDef                  // ???????? 
{
	char  Index[2];            // ??????,?????????	
	unsigned char  Msk[32];             // ?????(16*16?32???) 
};

extern struct Cn16CharTypeDef CN16CHAR[];

/*************定义所使用的IO口**************/
#define RCC_ST5767 	RCC_APB2Periph_GPIOA	
#define GPIO_PORT 	GPIOB

/**************8位LED的IO口定义************/
#define DATA_PORT 	(GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12\
|GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15)

/**********IO set**********/
//CS
#define CS(a) if(a)\
GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_SET);\
else GPIO_WriteBit(GPIOA, GPIO_Pin_8, Bit_RESET);
//RSET
#define RSET(a) if(a)\
GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_SET);\
else GPIO_WriteBit(GPIOA, GPIO_Pin_11, Bit_RESET);
//RW
#define RW(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_0, Bit_RESET);
//RS
#define RS(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_1, Bit_RESET);
//RD
#define RD(a) if(a)\
GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_SET);\
else GPIO_WriteBit(GPIOB, GPIO_Pin_2, Bit_RESET);

void InitST7567_IO(void);
void Lcd12864_Init(void);
void Lcd12864_ClearScreen(void);
void LCD12864_ClearScreen_(unsigned char x);
unsigned char Lcd12864_Write16CnCHAR(unsigned char x, unsigned char y, char *cn);

#endif

