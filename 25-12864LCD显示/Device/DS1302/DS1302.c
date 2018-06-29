#include "DS1302.h"
#include "delay.h"
#include "usart.h"

u8 num[]="0123456789"; 
u8 time[7]={0x18, 0x19, 0x13, 0x01, 0x10, 0x06, 0x16};//秒分时日月周年
u8 w[7]={0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c};  //写地址
u8 r[7]={0x81, 0x83, 0x85, 0x87, 0x89, 0x8b, 0x8d};  //读地址
u8 miao,fen,shi,zhou,ri,yue,nian;


void DS1302_GPIOINIT(void)	  //端口初始化
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=DATA|rs|rw|e;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);//把调试设置普通IO口
	
	GPIO_InitStructure.GPIO_Pin=ce|sck;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
/*
	GPIO_InitStructure.GPIO_Pin=io;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;	//经过测试并不是双向IO口
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
*/
}

void IOOUTINIT()   //io输出配置
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=io;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
}
void IOININT()	 //io输入配置
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=io;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
}



u8 readbusy()	//忙信号检测
{		
	u8 f;	
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_SetBits(GPIOB,rw);
	GPIO_SetBits(GPIOB,e);	
	f=((GPIO_ReadInputData(GPIOB)&0X8000));
	delay_ms(10);
	GPIO_ResetBits(GPIOB,e);
	return f;		
}
void lcdwrc(u8 c)
{	
	while(readbusy());
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);
	GPIOB->BSRR = c<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<8) & 0xf000;

	delay_ms(1);
	GPIO_SetBits(GPIOB,e);
	delay_ms(1);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);
}

void lcdwrc4bit(long c)
{	
	while(readbusy());
	GPIO_ResetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);
	GPIOB->BSRR = c<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<8) & 0xf000;
	delay_ms(1);
	GPIO_SetBits(GPIOB,e);
	delay_ms(1);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);

	GPIOB->BSRR = c<<12 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~c)<<12) & 0xf000;
	delay_ms(1);
	GPIO_SetBits(GPIOB,e);
	delay_ms(1);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);
}

void lcdwrd(long dat)
{
	while(readbusy());		
	GPIO_SetBits(GPIOB,rs);		
	GPIO_ResetBits(GPIOB,rw);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);
	GPIOB->BSRR = dat<<8 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~dat)<<8) & 0xf000;
	delay_ms(1);
	GPIO_SetBits(GPIOB,e);
	delay_ms(1);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);
	GPIOB->BSRR = dat<<12 & 0xf000;  //将数据送到P0口 
    GPIOB->BRR = ((~dat)<<12) & 0xf000;
	delay_ms(1);
	GPIO_SetBits(GPIOB,e);
	delay_ms(1);
	GPIO_ResetBits(GPIOB,e);
	delay_ms(1);
	GPIO_ResetBits(GPIOB,rs);
}
void lcdinit()
{
	delay_ms(15);
	lcdwrc4bit(0x32);
	delay_ms(5);	
	lcdwrc4bit(0x28);
	delay_ms(5);
	lcdwrc4bit(0x08);
	delay_ms(5);
	lcdwrc4bit(0x01);
	delay_ms(5);
	lcdwrc4bit(0x06);
	delay_ms(5);
	lcdwrc4bit(0x0c);
	delay_ms(5);
}

void ds1302writebyte(u8 dat)   //单字节写
{
	u8 i,value;
	GPIO_ResetBits(GPIOA,sck);
	delay_us(20);
	IOOUTINIT();		
	for(i=0;i<8;i++)
	{
		value=dat&0x01;	
		if(value)
			GPIO_WriteBit(GPIOA,io,Bit_SET);
		else
			GPIO_WriteBit(GPIOA,io,Bit_RESET);
		dat>>=1;
		GPIO_SetBits(GPIOA,sck);
		delay_us(20);
		GPIO_ResetBits(GPIOA,sck);
		delay_us(20);	
	}
}
void ds1302writebytes(u8 add,u8 dat) //多字节写
{
	GPIO_ResetBits(GPIOA,ce);
	delay_us(20);
	GPIO_SetBits(GPIOA,ce);
	delay_us(20);
	ds1302writebyte(add);
	ds1302writebyte(dat);
	GPIO_ResetBits(GPIOA,ce);
	delay_us(20);			
}
u8 ds1302readbyte()	 //单字节读
{
	u8 i,value;
	GPIO_ResetBits(GPIOA,sck);
	delay_us(20);
	IOININT();		
	for(i=0;i<8;i++)
	{
		value>>=1;
		if(GPIO_ReadInputDataBit(GPIOA,io)==1)
		{
			value|=0x80;
		}	
		GPIO_SetBits(GPIOA,sck);
		delay_us(20);
		GPIO_ResetBits(GPIOA,sck);
		delay_us(20);	
	}
	return value;					
}
u8 ds1302readbytes(u8 add)	 //多字节读
{
	u8 temp;
	GPIO_ResetBits(GPIOA,ce);
	delay_us(20);
	GPIO_SetBits(GPIOA,ce);
	delay_us(20);
	ds1302writebyte(add);
	temp=ds1302readbyte();
	GPIO_ResetBits(GPIOA,ce);
	delay_us(20);
	GPIO_ResetBits(GPIOA,io);
	delay_us(20);	
	GPIO_SetBits(GPIOA,io);	 //释放IO
	delay_us(20);	
	return temp;		
}
void settime()
{
	u8 i;
	ds1302writebytes(0x8e,0x00);
	for(i=0;i<7;i++)
	{
		ds1302writebytes(w[i],time[i]);	
	}
	ds1302writebytes(0x8e,0x80);
}
void readtime()
{
	miao=ds1302readbytes(r[0]);
	fen=ds1302readbytes(r[1]);
	shi=ds1302readbytes(r[2]); 
	zhou=ds1302readbytes(r[5]);
	ri=ds1302readbytes(r[3]);
	yue=ds1302readbytes(r[4]);	
	nian=ds1302readbytes(r[6]);	
	printf("%x 年 %x月%x日 %x时%x分%x秒",nian,yue,ri,shi,fen,miao);
}
void display()
{
	lcdwrc4bit(0x00+0x80);	
	lcdwrd(num[shi/16]);
	lcdwrd(num[shi%16]);
	lcdwrd(':');
	lcdwrd(num[fen/16]);
	lcdwrd(num[fen%16]);
	lcdwrd(':');
	lcdwrd(num[miao/16]);
	lcdwrd(num[miao%16]);
	lcdwrc4bit(0x40+0x80);
	lcdwrd(num[nian/16]);
	lcdwrd(num[nian%16]);
	lcdwrd('-');
	lcdwrd(num[yue/16]);
	lcdwrd(num[yue%16]);
	lcdwrd('-');
	lcdwrd(num[ri/16]);
	lcdwrd(num[ri%16]); 
	lcdwrd('-');
	lcdwrd(num[zhou%16]);
}
