/*
 * Interfacing 16x2 LCD with PIC18F4550
 * Author : Ali
 */

#include <pic18f4550.h>
#include "Configuration_Header_File.h"

#define RS LATD0                    /*PORTD 0 pin is used for Register Select*/
#define EN LATD1                    /*PORTD 1 pin is used for Enable*/
#define ldata LATB                  /*PORTB is used for transmitting data to LCD*/
#define LCD_Port TRISB              /*define macros for PORTB Direction Register*/             
#define LCD_Control TRISD           /*define macros for PORTD Direction Register*/


void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);
void MSdelay(unsigned int);
/*****************************Main Program*******************************/

void main(void)
{       
    OSCCON=0x72;                            /*Use Internal Oscillator with Frequency 8MHZ*/ 
    LCD_Init();                             /*Initialize 16x2 LCD*/
    LCD_String_xy(1,5,"OUSSAMA");             /*Display string at location(row,location).
                                             * This function passes string to display*/
    LCD_String_xy(2,0,"MARZOUKI");   /*Display string at location(row,location).
                                             * This function passes string to display*/    
    
    while(1);			
}

/****************************Functions********************************/
void LCD_Init()
{
    MSdelay(15);           /*15ms,16x2 LCD Power on delay*/
   	LCD_Port = 0x00;       /*Set PORTB as output PORT for LCD data(D0-D7) pins*/
    LCD_Control = 0x00;    /*Set PORTD as output PORT LCD Control(RS,EN) Pins*/
	LCD_Command(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
    LCD_Command(0x01);     /*clear display screen*/
    LCD_Command(0x0c);     /*display on cursor off*/
    LCD_Command(0x06);     /*increment cursor (shift cursor to right)*/
}

void LCD_Clear()
{
    LCD_Command(0x01);     /*clear display screen*/
}

void LCD_Command(char cmd )
{
	ldata= cmd;            /*Send data to PORT as a command for LCD*/   
	RS = 0;                /*Command Register is selected*/
	EN = 1;                /*High-to-Low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	MSdelay(3);	
}

void LCD_Char(char dat)
{
	ldata= dat;            /*Send data to LCD*/  
	RS = 1;                /*Data Register is selected*/
	EN=1;                  /*High-to-Low pulse on Enable pin to latch data*/   
	NOP();
	EN=0;
    MSdelay(1);
}


void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }		
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f); /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f); /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    LCD_String(msg);
}

/*********************************Delay Function********************************/
void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }


