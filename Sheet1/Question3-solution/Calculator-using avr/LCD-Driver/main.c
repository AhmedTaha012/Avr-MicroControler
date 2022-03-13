/*
 * LCD-Driver.c
 *
 * Created: 3/12/2022 12:49:27 AM
 * Author :		AhmedTaha
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
#include <stdlib.h>
#define LCD_Dir  DDRB			/* Define LCD data port direction */
#define LCD_Port PORTB			/* Define LCD data port */
#define RS PB0				/* Define Register Select pin */
#define EN PB1 				/* Define Enable signal pi*/

void lcd_clear(void);
void init_LCD(void);
void LCD_String (char *str)	;
void lcd_write(unsigned char data);
void LCD_Command(unsigned char cmd);
void LCD_String_xy (char row, char pos, char *str);
char* key_pressed();
int main(void)
{
	char arr[2][5];
	char arr2[5];
	char snum[5];
    DDRB=0xff;
	DDRC=0xFF;
	DDRD=0x0f;
	init_LCD();
	int i=0,j=0,num1,num2,result,num=0;
	int opera=0;
    while (1) 
    {   
		   
          if (key_pressed()!=0)
          {   
			   if(key_pressed()=="+"){ LCD_String_xy(j,i,"+"); num++;  opera=1; i++; }
			   if(key_pressed()=="X"){ LCD_String_xy(j,i,"X"); num++;  opera=2; i++; }
			   if(key_pressed()=="-"){ LCD_String_xy(j,i,"-"); num++;  opera=3; i++; }
			   if(key_pressed()=="/"){ LCD_String_xy(j,i,"/"); num++;  opera=4; i++; }
			   if(key_pressed()=="c"){ lcd_clear(); i=0; j=0; num=0; strcpy(arr[0],"");strcpy(arr[1],"");result=0;}
			   if (key_pressed()== "eq")
			   {   j++;
				   num1=atoi(arr[0]);
				   num2=atoi(arr[1]);
				   if(opera==1){ result=num1+num2; itoa(result, snum, 10); LCD_String_xy(1,9,snum);}
				   if(opera==2){result=num1*num2; itoa(result, snum, 10); LCD_String_xy(1,9,snum);}
				   if(opera==3){ result=num1-num2; itoa(result, snum, 10); LCD_String_xy(1,9,snum);}	   
				   if(opera==4){ result=num1/num2; itoa(result, snum, 10); LCD_String_xy(1,9,snum);}
			   }
			   else if(key_pressed()!= "eq" && key_pressed()!="+"&& key_pressed()!="-"&& key_pressed()!="X"&& key_pressed()!="/"){
			   if(key_pressed()=="1"||key_pressed()=="2"||key_pressed()=="3"||key_pressed()=="4"||key_pressed()=="5"||key_pressed()=="6"||key_pressed()=="7"||key_pressed()=="8"||key_pressed()=="9")
			   { LCD_String_xy(j,i,key_pressed());
			     i++;
			    strcat(arr[num],key_pressed());}
			   }
			    _delay_ms(300); //this delay for button bouncing 
          }
		  
		
		   
		  
    }
}

void init_LCD(void){
   LCD_Dir = 0xFF;		/* Make LCD port direction as o/p */
   _delay_ms(20);		/* LCD Power ON delay always >15ms */
   LCD_Command(0x33);
   LCD_Command(0x32);	/* Send for 4 bit initialization of LCD  */
   LCD_Command(0x28);	/* 2 line, 5*7 matrix in 4-bit mode */
   LCD_Command(0x0c);	/* Display on cursor off */
   LCD_Command(0x06);	/* Increment cursor (shift cursor to right) */
   LCD_Command(0x01);	/* Clear display screen */
}
void LCD_Command(unsigned char cmd){
	LCD_Port = (LCD_Port & 0x0F) | (cmd & 0xF0);/* Sending upper nibble */
	LCD_Port &= ~ (1<<RS);		/* RS=0, command reg. */
	LCD_Port |= (1<<EN);		/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (cmd << 4);/* Sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void LCD_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		lcd_write (str[i]);
	}
}

void lcd_write(unsigned char data){
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0);/* Sending upper nibble */
	LCD_Port |= (1<<RS);  /* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (data << 4);  /* Sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void lcd_clear(void){
		LCD_Command (0x01);		/* Clear display */
		_delay_ms(2);
		LCD_Command (0x80);		/* Cursor at home position */
}
void LCD_String_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	LCD_String(str);		/* Call LCD string function */
}
char * key_pressed(){
	
	    PORTD=0x01;
		if(PIND&0x10){ return "7";}
		if(PIND&0x20){ return "8"; }
		if(PIND&0x40){ return "9"; }
		if(PIND&0x80){ return "/"; }
		_delay_ms(1);
		PORTD=0x02;
		if(PIND&0x10){ return "4";}
		if(PIND&0x20){ return "5"; }
		if(PIND&0x40){ return "6"; }
		if(PIND&0x80){ return "X"; }
		_delay_ms(1);
		PORTD=0x04;
		if(PIND&0x10){ return "1";}
		if(PIND&0x20){ return "2"; }
		if(PIND&0x40){ return "3"; }
		if(PIND&0x80){ return "-"; }
		_delay_ms(1);
		PORTD=0x08;
		if(PIND&0x10){ return "c";}
		if(PIND&0x20){ return "0"; }
		if(PIND&0x40){ return "eq"; }
		if(PIND&0x80){ return "+"; }
		_delay_ms(1);
		
		 return 0 ;
		
}













/*
void second_line(void){
	lcd_cmd(0x0C);
	_delay_ms(100);
}
void lcd_start(void){
	lcd_cmd(0x0C);
	_delay_ms(100);
}
void make_display_on(void){
	lcd_cmd(0x0E); //make display on ,cursor on
	_delay_ms(1000);
}
void Cursor_pos(unsigned char x_pos,unsigned char y_pos){
	uint8_t add=0;
	if(x_pos==0) add=0x80;
	else if(x_pos==1) add=0xC0;
	if(y_pos<16) add+=y_pos;
	lcd_cmd(add);
}
/*
char keypad(void){
	PORTD=0b00001110;
	if((PIND & 0b00000000)) return '7';
	if((PIND & 0b00000010)) return '8';
	if((PIND & 0b00000100)) return '9';
	if((PIND & 0b00001000)) return '/';
	_delay_ms(50);
	/*PORTD=0x20;
	if((PIND & 0b00000001)) return '4';
	if((PIND & 0b00000010)) return '5';
	if((PIND & 0b00000100)) return '6';
	if((PIND & 0b00001000)) return 'x';
	_delay_ms(500);
	PORTD=0x40;
	if((PIND & 0b00000001)) return '1';
	if((PIND & 0b00000010)) return '2';
	if((PIND & 0b00000100)) return '3';
	if((PIND & 0b00001000)) return '-';
	_delay_ms(500);
	PORTD=0x80;
	if((PIND & 0b00000001)) return 'o';
	if((PIND & 0b00000010)) return '0';
	if((PIND & 0b00000100)) return '=';
	if((PIND & 0b00001000)) return '+';
	return 'N';
}
void lcd_display(char *arr){
	while(*arr>0){
		lcd_write(*arr++);
	}
}
*/
