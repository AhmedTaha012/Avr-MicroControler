/*
 * GccApplication1.c
 *
 * Created: 3/11/2022 8:42:34 AM
 * Author : Ahmed Taha Ahmed
 */ 

#include <avr/io.h>
#include <avr/delay.h>
int main(void)
{
	DDRB=0xff; // set all the port b to be output
	unsigned char arr[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; // arr to can make the loop of leds
	DDRC&=~(1<<0); //set the pin 0 in port c to be input 
	DDRC&=~(1<<3); // set the pin 3 in port c to be input 
	char button_Mode1,button_Mode2; // variable to contains the state of to buttons
	PORTB=0x00; // set all port b to zero at begin of code
    while (1) 
    {  
		PORTB^=0xff;
		_delay_ms(500);
		button_Mode1=PINC;
		button_Mode2=PINC;
		button_Mode1&=(1<<0);
		button_Mode2&=(1<<3);
		if (button_Mode1==1  && button_Mode2==0){
			_delay_ms(500);
			PORTB=0x00;
			for(int i=0; i<8;i++){
				if(button_Mode1==1  && button_Mode2==0){
				PORTB=arr[i];
				_delay_ms(200);
				}
				else {break;}
				
			}
			PORTB=0x00;
			for(int i=8;i>0;i--){
					if(button_Mode1==1  && button_Mode2==0){
						PORTB=arr[i];
						_delay_ms(200);
					}
					else {break;}
				
			}
			
		}
		if(button_Mode1==0 && button_Mode2==1 ){
			continue;
		}
	
	}
		
   
}

