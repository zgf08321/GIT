#ifndef __MENU_H
#define __MENU_H

#define Null 0

//typedef unsigned int u16;	  //???????????
//typedef unsigned char u8;
 

//???????   
struct MenuItem       
{ 
    char Menu;                      //????
    char MenuCount;                 //??????????   
    char *DisplayString;            //??LCD???????  
    char *DisplayChinese;            //??LCD??????? 
    void (*Subs)();                 //????????.   
    struct MenuItem *Childrenms;    //????????   
    struct MenuItem *Parentms;      //????????   
};

extern struct MenuItem *manyou; 
extern struct  MenuItem  m0_main[4]; 

void MENU(unsigned char key);

void Calculator(void);
void Temperature(void);
void DS1302(void);


void Nop(void);   
void DoSomething(void); 
void save(void);
void GameOver(void);   
void Locate(struct MenuItem *manyou);   
void Run(struct MenuItem *manyou); 

//void Nop(void);   
//void DoSomething(struct MenuItem *manyou); 
//void save(struct MenuItem *manyou);
//void GameOver(void);   
//void Locate(struct MenuItem *manyou);   
//void Run(struct MenuItem *manyou); 

#endif

