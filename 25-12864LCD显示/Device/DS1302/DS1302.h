#ifndef __DS1302_H
#define __DS1302_H  

#include "stm32f10x.h"

#define DATA (GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15)
#define rs (GPIO_Pin_1)
#define rw (GPIO_Pin_2)
#define e (GPIO_Pin_0)

#define io (GPIO_Pin_12)
#define ce (GPIO_Pin_13)
#define sck (GPIO_Pin_14)


extern u8 miao,fen,shi,zhou,ri,yue,nian;


void DS1302_GPIOINIT(void);
void settime(void);
void readtime(void);


#endif

