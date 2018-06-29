#include "key.h"
#include "delay.h"

void KEY_Init(void)	   //�˿ڳ�ʼ��
{

/*********����һ��GPIO_InitTypeDef ���͵Ľṹ��**********/
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
/*********ѡ��Ҫ���Ƶ�GPIOx������**********/
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;

///*********������������Ϊ50MHZ**********/
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

///*********��������ģʽΪͨ���������**********/
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;

///*��ʼ����Ӧ��GPIO*/
//	GPIO_Init(GPIOA,&GPIO_InitStructure);

//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);		 //Changes the mapping of the specified pin.
   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;//GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //�������

	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7

	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;	//��������

	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}


//u8 keyscan()
//{
//	u16 value;
//	u8 h1,h2,h3,h4,key,key_value = 255;
//	GPIO_Write(GPIOA,(u16)(0x00fe));  //�жϵ�һ���Ǹ���������
//	value=GPIO_ReadInputData(GPIOA);
//	h1=(u8)(value);
//	if(h1!=0xfe)		 
//	{
//		delay_ms(200);	  //����
//		if(h1!=0xfe)
//		{
//			key=h1&0xf0;
//			switch(key)		
//			{
//				case 0xe0: key_value = 0;break;
//				case 0xd0: key_value = 1;break;
//				case 0xb0: key_value = 2;break;
//				case 0x70: key_value = 3;break;
//			}
//		}
//	//	while(h1!=0xfe);
//	}

//	GPIO_Write(GPIOA,(u16)(0xfd));  //�жϵ�2���Ǹ���������
//	value=GPIO_ReadInputData(GPIOA);
//	h2=(u8)(value);
//	if(h2!=0xfd)		 
//	{
//		delay_ms(200);
//		if(h2!=0xfd)
//		{
//			key=h2&0xf0;
//			switch(key)		
//			{
//				case 0xe0: key_value = 4;break;
//				case 0xd0: key_value = 5;break;
//				case 0xb0: key_value = 6;break;
//				case 0x70: key_value = 7;break;
//			}
//		}
//	//	while(h2!=0xfd);
//	}

//	GPIO_Write(GPIOA,(u16)(0xfb));  //�жϵ�3���Ǹ���������
//	value=GPIO_ReadInputData(GPIOA);
//	h3=(u8)(value);
//	if(h3!=0xfb)		 
//	{
//		delay_ms(200);
//		if(h3!=0xfb)
//		{
//			key=h3&0xf0;
//			switch(key)		
//			{
//				case 0xe0: key_value = 8;break;
//				case 0xd0: key_value = 9;break;
//				case 0xb0: key_value = 10;break;
//				case 0x70: key_value = 11;break;
//			}
//		}
//	//	while(h3!=0xfb);
//	}

//	GPIO_Write(GPIOA,(u16)(0xf7));  //�жϵ�4���Ǹ���������
//	value=GPIO_ReadInputData(GPIOA);
//	h4=(u8)(value);
//	if(h4!=0xf7)		 
//	{
//		delay_ms(200);
//		if(h4!=0xf7)
//		{
//			key=h4&0xf0;
//			switch(key)		
//			{
//				case 0xe0: key_value = 12;break;
//				case 0xd0: key_value = 13;break;
//				case 0xb0: key_value = 14;break;
//				case 0x70: key_value = 15;break;
//			}
//		}
//	//	while(h4!=0xf7);
//	}
//	return key_value;
//}
u8 keyscan()
{
	u16 value;
	u8 h1,h2,h3,h4,key,key_value = 255;
	
	value=GPIO_ReadInputData(GPIOB);
	GPIO_Write(GPIOB,(u16)(0xfe<<8)|(value&0x00FF));  //�жϵ�һ���Ǹ���������
	value=GPIO_ReadInputData(GPIOB);
	h1=(u8)(value>>8);
	if(h1!=0xfe)		 
	{
		delay_ms(20);	  //����
		if(h1!=0xfe)
		{
			key=h1&0xf0;
			switch(key)		
			{
				case 0xe0: key_value = 0;break;
				case 0xd0: key_value = 1;break;
				case 0xb0: key_value = 2;break;
				case 0x70: key_value = 3;break;
			}
		}
		
	}
	do
	{
		value=GPIO_ReadInputData(GPIOB);
		h1=(u8)(value>>8);		
	}
	while(h1!=0xfe);
	
	
	value=GPIO_ReadInputData(GPIOB);
	GPIO_Write(GPIOB,(u16)(0xfd<<8)|(value&0x00FF));  //�жϵ�2���Ǹ���������
	value=GPIO_ReadInputData(GPIOB);
	h2=(u8)(value>>8);
	if(h2!=0xfd)		 
	{
		delay_ms(20);
		if(h2!=0xfd)
		{
			key=h2&0xf0;
			switch(key)		
			{
				case 0xe0: key_value = 4;break;
				case 0xd0: key_value = 5;break;
				case 0xb0: key_value = 6;break;
				case 0x70: key_value = 7;break;
			}
		}
		//while(h2!=0xfd);
	}
	do
	{
		value=GPIO_ReadInputData(GPIOB);
		h2=(u8)(value>>8);		
	}
	while(h2!=0xfd);
	
	value=GPIO_ReadInputData(GPIOB);	
	GPIO_Write(GPIOB,(u16)(0xfb<<8)|(value&0x00FF));  //�жϵ�3���Ǹ���������
	value=GPIO_ReadInputData(GPIOB);
	h3=(u8)(value>>8);
	if(h3!=0xfb)		 
	{
		delay_ms(20);
		if(h3!=0xfb)
		{
			key=h3&0xf0;
			switch(key)		
			{
				case 0xe0: key_value = 8;break;
				case 0xd0: key_value = 9;break;
				case 0xb0: key_value = 10;break;
				case 0x70: key_value = 11;break;
			}
		}
		//while(h3!=0xfb);
	}
	do
	{
		value=GPIO_ReadInputData(GPIOB);
		h3=(u8)(value>>8);	
	}
	while(h3!=0xfb);
	
	value=GPIO_ReadInputData(GPIOB);	
	GPIO_Write(GPIOB,(u16)(0xf7<<8)|(value&0x00FF));  //�жϵ�4���Ǹ���������
	value=GPIO_ReadInputData(GPIOB);
	h4=(u8)(value>>8);
	if(h4!=0xf7)		 
	{
		delay_ms(20);
		if(h4!=0xf7)
		{
			key=h4&0xf0;
			switch(key)		
			{
				case 0xe0: key_value = 12;break;
				case 0xd0: key_value = 13;break;
				case 0xb0: key_value = 14;break;
				case 0x70: key_value = 15;break;
			}
		}
		//while(h4!=0xf7);
	}
	
		do
	{
		value=GPIO_ReadInputData(GPIOB);
		h4=(u8)(value>>8);	
	}
	while(h4!=0xf7);
	
	return key_value;
}









