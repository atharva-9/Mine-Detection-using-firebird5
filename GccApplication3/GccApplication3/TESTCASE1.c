/*
 * GccApplication3.c
 *
 * Created: 12-03-2020 8.33.03 AM
 * Author : Dark Warrior
 */ 
//PJ2 PJ3 PJ5 Radar sensor 
//PJ1 PJ2 gps TX RX port 
//Zigbee is premounted on TX0 RX0



#define F_CPU 14745600
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "motion.h"

#define RS 0
#define RW 1
#define EN 2
#define lcd_port PORTC
unsigned char data; //to store received data from UDR1
#define sbit(reg,bit)	reg |= (1<<bit)			// Macro defined for Setting a bit of any register.
#define cbit(reg,bit)	reg &= ~(1<<bit)		// Macro defined for Clearing a bit of any register.

void init_ports();
void lcd_reset();
void lcd_init();
void lcd_wr_command(unsigned char);
void lcd_wr_char(char);
void lcd_line1();
void lcd_line2();
void lcd_string(char*);
//Function to configure LCD port
void lcd_port_config (void)
{
	DDRC = DDRC | 0xF7; //all the LCD pin's direction set as output
	PORTC = PORTC & 0x80; // all the LCD pins are set to logic 0 except PORTC 7
}
void lcd_wr_command(unsigned char cmd)
{
	unsigned char temp;
	temp = cmd;
	temp = temp & 0xF0;
	lcd_port &= 0x0F;
	lcd_port |= temp;
	cbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);
	
	cmd = cmd & 0x0F;
	cmd = cmd<<4;
	lcd_port &= 0x0F;
	lcd_port |= cmd;
	cbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);
}

//Function to Write Data on LCD
void lcd_wr_char(char letter)
{
	char temp;
	temp = letter;
	temp = (temp & 0xF0);
	lcd_port &= 0x0F;
	lcd_port |= temp;
	sbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);

	letter = letter & 0x0F;
	letter = letter<<4;
	lcd_port &= 0x0F;
	lcd_port |= letter;
	sbit(lcd_port,RS);
	cbit(lcd_port,RW);
	sbit(lcd_port,EN);
	_delay_ms(5);
	cbit(lcd_port,EN);
}

//Function to Print String on LCD
void lcd_string(char *str)
{
	while(*str != '\0')
	{
		lcd_wr_char(*str);
		str++;
	}
}


//Function to Initialize LCD
void lcd_init()
{
	_delay_ms(1);

	lcd_wr_command(0x28);			//LCD 4-bit mode and 2 lines.
	lcd_wr_command(0x01);
	lcd_wr_command(0x06);
	lcd_wr_command(0x0E);
	lcd_wr_command(0x80);
	
}

//Function to initialize ports
void port_init()
{
	DDRB = 0x40;
	lcd_port_config();
PORTJ=0x00;
DDRA = DDRA | 0x0F; //set direction of the PORTA 3 to PORTA 0 pins as output
PORTA = PORTA & 0xF0; // set initial value of the PORTA 3 to PORTA 0 pins to logic 0
DDRL = DDRL | 0x18;   //Setting PL3 and PL4 pins as output for PWM generation
PORTL = PORTL | 0x18; //PL3 and PL4 pins are for velocity control using PWM
}


//Function To Initialize UART0
// desired baud rate:9600
// actual baud rate:9600 (error 0.0%)
// char size: 8 bit
// parity: Disabled
void uart0_init(void)
{
	UCSR0B = 0x00; //disable while setting baud rate
	UCSR0A = 0x00;
	UCSR0C = 0x06;
	// UBRR0L = 0x47; //11059200 Hz
	UBRR0L = 0x5F; // 14745600 Hzset baud rate lo
	UBRR0H = 0x00; //set baud rate hi
	UCSR0B = 0x98;
}


ISR(_VECTOR(26))        // ISR for receive complete interrupt
{
	data = UDR0;                //making copy of data from UDR0 in 'data'  variable

	UDR0 = data;                //echo data back to PC

	if(data == 0x37)
	PORTB = 0x00;
	if(data == 0x39)
	PORTB = 0x40;

}


//Function To Initialize all The Devices
void init_devices()
{
	cli(); //Clears the global interrupts
	port_init();  //Initializes all the ports
	lcd_init();
	uart0_init(); //Initialize UART0 for serial communication
	sei();   //Enables the global interrupts
}

void motions(void)
{
	
forward(); //both wheels forward
_delay_ms(40000);

stop();
_delay_ms(5000);
left(); //Left wheel backward, Right wheel forward
_delay_ms(12000);

stop();
_delay_ms(5000);
forward(); //both wheels forward
_delay_ms(5000);

stop();
_delay_ms(5000);
left(); //Left wheel backward, Right wheel forward
_delay_ms(12000);

stop();
_delay_ms(5000);
forward(); //both wheels forward
_delay_ms(40000);

stop();
_delay_ms(5000);
stop();
right(); //Left wheel backward, Right wheel forward
_delay_ms(9000);
forward(); //both wheels forward
_delay_ms(5000);

stop();
_delay_ms(5000);

stop();
_delay_ms(5000);
right(); //Left wheel backward, Right wheel forward
_delay_ms(12000);

}

//Main Function
int main(void)
{
	
	init_devices();
	//lcd_string(data);
	lcd_string("GPS DATA:");
	lcd_wr_command(0xc0);
	lcd_string("LAT:");
	_delay_ms(1000);
	while(1)
	{
		

	
	if ((PINJ2 == 1 && PINJ2 ==1 && PINJ5 == 1)||(PINJ2 == 0 && PINJ2 == 1 && PINJ5 == 1) ||(PINJ2 == 1 && PINJ2 ==0 && PINJ5 == 1) ||(PINJ2 == 1 && PINJ2 ==1 && PINJ5 == 0 ) )
	{
		lcd_string("Threat  detected");
		stop();
		_delay_ms(100);
		lcd_wr_command(0x01);
		//gpstx();
		
		
		
	}
	else
	{
		lcd_string("NO threat");
		motions();
		_delay_ms(100);
		lcd_wr_command(0x01);
	}
	}
	}
