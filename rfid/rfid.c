//8MHZ fre. of MCU and 9600 baud rate value of UBRR is 51
#include <avr/io.h>
#include<avr/delay.h>
#include <compat/deprecated.h>
#define rs PB0
#define rw PB1
#define en PB2
#define dataport PORTA 

void LCD_DisplayString (const unsigned char *string)
{
	//LCD_Cursor (row, column);
	while (*string)
	wrdata(*string++);
}
void LCD_init(void)
{
	wrcomm(0x38); //initialize LCD 2 lines, 5x7 matrix
	wrcomm(0x06);//Clear LCD
	wrcomm(0x0E); //Display on Cursor Blinking
	wrcomm(0x01);//Cursor at line 1, position 1
	wrcomm(0x80); //Shift Entire Display To Right
}
void wrcomm(unsigned char Command)
{
	cbi(PORTB,rs);
	dataport = Command;
	sbi(PORTB,en);
	_delay_ms(1);
	cbi(PORTB,en);
	_delay_ms(1); 
}
void wrdata(unsigned char Data)
{
	sbi(PORTB,rs);
	dataport = Data;
	sbi(PORTB,en);
	_delay_ms(1) ; 
	cbi(PORTB,en); 
	_delay_ms(1) ; 
}


void USART_Init( unsigned char ubrr)
{
	/* Set baud rate */
	UBRRH = 0;
	UBRRL = ubrr;

	/* Enable receiver and transmitter */
	UCSRB|= (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8data---ucsz0=1,ucsz1=1, 1stop bit ---usbs=0*/
	UCSRC |= (1 << URSEL)|(3<<UCSZ0);
}







//RX
unsigned char USART_Receive( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)))
	;
	/* Get and return received data from buffer */
	return UDR;
}


void DOOR()
{	 
//DOOR OPEN
PORTC=0B00001111;_delay_ms(50000);_delay_ms(20000);
//STOP
PORTC=0B11111111;_delay_ms(50000);_delay_ms(50000);_delay_ms(50000);
//DOWN
PORTC=0B11110000;_delay_ms(50000);_delay_ms(50000);
//STOP
PORTC=0B11111111;_delay_ms(50000);_delay_ms(50000);_delay_ms(50000);
}

void main (void)
{
	DDRA=0xFF;
	DDRB=0xFF;
	DDRC=0xFF;
	DDRD=0xFF;
	LCD_init();


   USART_Init(51);
  _delay_ms(10);
	unsigned char arr[15];
	unsigned char ReceivedByte=0,s=0,i=0;
	//memset(0,&arr,sizeof(arr));


while(1) // Loop forever
{	 
	wrcomm(0x80);
	LCD_DisplayString (" SWIPE UR CARD. ");
   	
	for (s=0;s<12;s++)
	{
	arr[s]=USART_Receive();	
	
	}
	LCD_init();
	_delay_ms(40000);
		
		wrcomm(0xc0);	
		for (s=0;s<12;s++)
   		wrdata(arr[s]);	

if(arr[10]=='F' && arr[11]=='E')		
{	wrcomm(0x80);
	LCD_DisplayString (" CARD 1");
	DOOR();
}
else if(arr[10]=='E' && arr[11]=='4')		
{	wrcomm(0x80);
	LCD_DisplayString (" CARD 2");
	DOOR();
}
else if(arr[10]=='4' && arr[11]=='5')		
{	wrcomm(0x80);
	LCD_DisplayString (" CARD 3");
	DOOR();
}
else
{	wrcomm(0x80);
	LCD_DisplayString ("  ACCESS DENIED ");
}
	_delay_ms(60000);LCD_init();_delay_ms(10000);
}
      
}
