/*
 * GccApplication4.c
 *
 * Created: 3/13/2022 3:58:31 PM
 * Author : DELL
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>
int count=15;
unsigned char arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x6f}; // arr to can make the loop of leds
void display_Count(int x);
int main(void)
{
    /* Replace with your application code */
	
	DDRB=0xff;
	DDRC=0xff;
	DDRD|=(1<<7);
	DDRD|=(1<<6);
	
	MCUCR&=~(1<<ISC00);
	MCUCR|=(1<<ISC01);
	MCUCR&=~(1<<ISC10);
	MCUCR|=(1<<ISC11);
	GICR|=(1<<INT0);
	GICR|=(1<<INT1);
	sei();
	char arr2[2];
	int num1=0,num2=0;
    while (1) 
    {
		if(count>15){count==0;}
		else if (count<15)
		{
			PORTD=0x40;
		}
		else 
		{
			PORTD=0x80;
		}
		display_Count(count);
		
    }
}
ISR(INT0_vect){
	cli();
	count++;
	if(count>15){count=15;}
	sei();
}
ISR(INT1_vect){
	cli();
	count--;
	sei();
}
void display_Count(int x){
	  if(x==10){
		  PORTC=arr[1];
		  PORTB=arr[0];
	  }
	  else if(x-10>0){
	      PORTC=arr[1];
		  PORTB=arr[x-10];
		  
	  }
	  else
	  {
		  PORTC=arr[0];
		  PORTB=arr[x];
	  }
	  
	  
			
		  
	  
	  
}


