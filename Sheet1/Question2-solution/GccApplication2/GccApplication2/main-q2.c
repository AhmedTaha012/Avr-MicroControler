/*
 * GccApplication2.c
 *
 * Created: 3/11/2022 11:38:39 AM
 * Author : DELL
 */ 

#include <avr/io.h>

#include <avr/delay.h>
int main(void)
{
	DDRB=0xff; // set all the port b to be output
	DDRD=0xff; // set all the port c to be output
	unsigned char arr[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7c,0x07,0x7f,0x6f}; // arr to can make the loop of leds
	DDRC&=~(1<<0); //set the pin 0 in port c to be input
	char button1;
	int counter1=0,counter2=0;
	while (1)
	{
		
	    button1=PINC;
		button1&=(1<<0);
		if(button1==0){
			_delay_ms(500);
			PORTB=arr[counter1];
			PORTD=arr[counter2];
			counter1++;
			if(counter1==10){
				counter2++;
				 if(counter2==10){counter2=0;}
				 counter1=0;}
			
		}
		
	}
	
	
}

