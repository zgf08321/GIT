#include "MENU.h"
#include "ST5767.h"
#include "LCD12864.h"
#include "stdio.h"
//#include "Usart.h"
#include "delay.h"
#include "key.h"
#include "stdlib.h"
#include "string.h"		
#include "ds18b20.h"
#include "DS1302.h"



struct MenuItem *manyou; //??,?????? 

char menuid[3]={0,0,0};
//char code menuid[3]={0,0,0};
//====================================   
//?????   
struct  MenuItem  DisPlay[3]; 

struct  MenuItem  m0_main[4];   
struct  MenuItem  m1_file[5];   
//struct MenuItem m1_edit[4];   
//struct MenuItem m1_view[2];   
//struct MenuItem m2_font[3];   
//struct MenuItem m1_help[3];  
//====================================   


struct MenuItem *manyou; 

//?????
//====================================      
struct MenuItem  m0_main[4]=   
{   
    {0,4,"file","普中科技菜单",Nop,m1_file,Null},   
    {0,4,"edit","计算器",Calculator,Null,Null},   
    {0,4,"view","温度",Temperature,Null,Null},   
    {0,4,"help","时钟",DS1302,Null,Null},   
};  

  
struct MenuItem  m1_file[5]=   
{   
    {0,5,"open","打开",Null,Null,m0_main},   
    {0,5,"save","保存",Null,Null,m0_main},   
    {0,5,"save as","另存",Null,Null,m0_main},   
    {0,5,"print","打印",Null,Null,m0_main},   
    {0,5,"exit","退出",Null,Null,m0_main},   
};  
  
//struct MenuItem m1_edit[4]=   
//{   
//    {0,4,"undo","??",DoSomething,Null,m0_main},   
//    {0,4,"redo","??",DoSomething,Null,m0_main},   
//    {0,4,"copy","??",DoSomething,Null,m0_main},   
//    {0,4,"paste","??",DoSomething,Null,m0_main},   
//};  
//  
//struct MenuItem m1_view[2]=   
//{   
//    {0,2,"font","??",Nop,m2_font,m0_main},   
//    {0,2,"color","??",DoSomething,Null,m0_main},   
//};  
//  
//
//struct MenuItem m2_font[3]=   
//{   
//    {0,3,"songti","??",DoSomething,Null,m1_view},   
//    {0,3,"heiti","??",DoSomething,Null,m1_view},   
//    {0,3,"youyuan","??",DoSomething,Null,m1_view},   
//};  
//  
//struct MenuItem m1_help[3]=   
//{   
//    {0,3,"index","??",DoSomething,Null,m0_main},   
//    {0,3,"online","??",DoSomething,Null,m0_main},   
//    {0,3,"about","??",DoSomething,Null,m0_main},   
//};  
char str[32] = "";


unsigned char language='c';

unsigned char i = 0;

void MENU(unsigned char key)
{
	      switch (key) //??????   
	        {   
	        case 9: //?????????   
	            { 	
			    menuid[i]++;
                if (menuid[i] > manyou->MenuCount-1) 
					menuid[i]=0;//????MenuCount?????   

                Locate(manyou+menuid[i]);   
                break; 
	            }   
	        case 1: //?????????   
	            { 
                if (menuid[i]==0) 
						menuid[i]=manyou->MenuCount-1;//????MenuCount?????   
                else 
					menuid[i]--; 

                Locate(manyou+menuid[i]);   
                break;   
	            }   
	        case 6: //??????,?????????   
	            {   
	                if ((manyou+menuid[i])->Childrenms != Null)   
	                {  
	                    manyou=(manyou+menuid[i])->Childrenms;   
	                    i++;   
	                    menuid[i]=0;   
	                    Locate(manyou+menuid[i]);   
	                }   
	                else   
	                {  
	                    Run(manyou+menuid[i]);
						Locate(manyou+menuid[i]);   
	                }   
	                break;   
	            }   
	        case 4: //??????,?????????   
	            {   
	                if ((manyou+menuid[i])->Parentms !=Null)   
	                {  
	                  manyou=(manyou+menuid[i])->Parentms;   
	                  i--; 
	                  Locate(manyou+menuid[i]);
	                }   
	                else   
	                {   
	                    //printf("You are at the top of menu");   
	                }   
	                break;   
	            }   
	        default:  break;   
	        } 


}
//void DidPlay(struct MenuItem *manyou)
//{
//	unsigned char i;
//   for(i = 1;i <= manyou->MenuCount;i++)
//	{
//		if(manyou->Menu == 1)
//		{
//		   LCD12864_FClearScreen(2*i);
//	   	   if(manyou->DisplayChinese != NULL )
//		   		Lcd12864_Write16CnCHAR_F(1,2*i,manyou->DisplayChinese); manyou++ ;
//		}else
//		{
//			if(manyou->DisplayChinese != NULL )
//				Lcd12864_Write16CnCHAR(1,2*i,manyou->DisplayChinese); manyou++ ;		
//		}
//	}
//}


void Locate(struct MenuItem *manyou)   
{ 
//	LCD12864_ClearScreen_(4);
	LCD_ClearScreen_(4);
    switch(language)
    {
      case 'c':
			  Lcd_Write16CnChar(0,4,manyou->DisplayChinese);
			  //NEW 12864  

//			  GT20L16S1Y_LCD(1,4,manyou->DisplayChinese);
			  manyou++ ;
	  break;
      case 'y':
//	  LCD_showch_ASCII(1,1,manyou++->DisplayString);
	  break;
      default:break;
    }
} 


void Run(struct MenuItem *manyou)   
{ 
//	LCD12864_ClearScreen_(4);
	LCD_ClearScreen_(4);
   (*(manyou->Subs))();  
}  

void Nop(void)   
{
} 

 
void DS1302(void)
{
	int Dis = 0;	
	while(1)
	{
		if(keyscan() == 14)	 
		{
		   break;
		}
		readtime();
		memset(str,0,32);
		str[0] = (shi>>4) + 0x30;
		str[1] = (0x0f & shi) + 0x30;
	    str[2] = ':';
		str[3] = (fen>>4) + 0x30;
		str[4] = (0x0f & fen) + 0x30;
		str[5] = ':';
		str[6] = (miao>>4) + 0x30;
		str[7] = (0x0f & miao) + 0x30;
		Lcd_WriteNumbChar(4, 4, str);

		memset(str,0,32);
		str[0] = '2';
		str[1] = '0';
		str[2] = (nian>>4) + 0x30;
		str[3] = (0x0f & nian) + 0x30;
	    str[4] = '.';
		str[5] = (yue>>4) + 0x30;
		str[6] = (0x0f & yue) + 0x30;
		str[7] = '.';
		str[8] = (ri>>4) + 0x30;
		str[9] = (0x0f & ri) + 0x30;
		Lcd_WriteNumbChar(3, 2, str);

	}
//	LCD12864_ClearScreen_(2);
	LCD_ClearScreen_(2);
//	LCD12864_ClearScreen_(4);
	LCD_ClearScreen_(4);
}

  
void Temperature()
{
	float f = 25; 
	sprintf(str, "%f", f);
	Lcd_Write16CnChar(3, 2, "温度");
	Lcd_WriteNumbChar(4, 4, str);	
	
 	while(DS18B20_Init())	//DS18B20初始化	
	{
		delay_ms(200);
		Lcd_Write16CnChar(3, 4, "温度");
 		delay_ms(200);
		LCD12864_ClearScreen_(4);
	}
	
	while(1)
	{
		if(keyscan() == 14)	 
		{
		   break;
		}
		f = (float)DS18B20_Get_Temp()/10;
		sprintf(str, "%f", f);
		Lcd_WriteNumbChar(4, 4, str);
	}
	LCD_ClearScreen_(2);
	LCD_ClearScreen_(4);
}


void Calculator()
{
	unsigned char key = 0,sign = '\0';
	long x = 0,y = 0,z = 0,display = 0;
//	Lcd12864_Write16CnCHAR(2, 2, "计算器");
	Lcd_Write16CnChar(2, 2, "计算器");
//	GT20L16S1Y_LCD(2, 2, "???");
//	Lcd12864_WriteNumbChar(15, 4, "0");
	Lcd_WriteNumbChar(15, 4, "0");
	while(1)
	{
		key = keyscan();
		if(key != 255)
		{
	      switch (key) //??????   
	        {   
						case 13: //????   0
									x = 10*x + 0;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;   
						case 0: //????   1 
									x = 10*x + 1;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;  
						case 1: //????   2
									x = 10*x + 2;
									if(x > 32767)
									x =  display;
									else
									display = x;
						break;
						case 2: //????   3
									x = 10*x + 3;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;
						case 4: //????   4
									x = 10*x + 4;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;
						case 5: //????   5
									x = 10*x + 5;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;  
						case 6: //????   6
									x = 10*x + 6;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;  
						case 8: //????   7
									x = 10*x + 7;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;
						case 9: //????   8
									x = 10*x + 8;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;
						case 10: //????  9
									x = 10*x + 9;
									if(x > 32767)
									x =  display;
									else
									display = x;
									break;



						case 3:  //????  +
									y = x; x = 0; sign = '+';
									break;
						case 7:  //????  -
									y = x; x = 0; sign = '-';
									break;
						case 11: //????  *
									y = x; x = 0; sign = '*';
									break;
						case 15: //????  /
									y = x; x = 0; sign = '/';
									break;

						case 12:  //????  =
						switch(sign)
						{
								case '+':
											z = x + y;
											x = 0;y = 0;
											display = z;
											break;
								case '-':
											z = y - x;
											x = 0;y = 0;
											display = z	;
											break;
								case '*':
										z = x * y;
										x = 0;y = 0;
										display = z	;
										break;
								case '/':
										z = x / y;
										x = 0;y = 0;
										display = z;
										break;					
								default:  break;				
						}

						break;				
								case 14:  //????  ??
								goto return_;

						//break;

						default:  break;   
	        }
			sprintf(str, "%d", (int)display);
//			LCD12864_ClearScreen_(4);
			LCD_ClearScreen_(4);
//			Lcd12864_WriteNumbChar(16-strlen(str), 4,str);	
			Lcd_WriteNumbChar(16-strlen(str), 4,str);	
		}

	} 
	return_:
//		LCD12864_ClearScreen_(2);
		LCD_ClearScreen_(2);	
}


void DoSomething()   
{   
//    LCD_showch_ASCII(1,0,manyou->DisplayString);  
}  


void save()   
{   
//    LCD_showch_ASCII(1,2,manyou->DisplayString);  
}

    
void GameOver(void)   
{   
   
}  

