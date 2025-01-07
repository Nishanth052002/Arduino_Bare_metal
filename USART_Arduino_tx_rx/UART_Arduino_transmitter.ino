#define fclk 16000000UL
#define BAUD 9600
#define MYUBRR fclk/16/BAUD-1

void setup() 
{
  USART_Init(MYUBRR);
  sei();
}

void USART_Init(unsigned int ubrr)
{
   UBRR0H = (unsigned char)(ubrr>>8);
   UBRR0L = (unsigned char)ubrr;

   UCSR0A |= (1<<RXEN0) | (1<<TXEN0);

   UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);
   UCSR0C |= (1<<USBS0); 
}

void USART_Transmit(unsigned char data)
{
  while(!(UCSR0A & (1<<UDRE0)));
  UDR0 = data;
}

void USART_TransmitString(const char *str) 
{
    while (*str) {
        USART_Transmit(*str++);
 }
}
void loop() 
{
  while(1)
  {
    USART_TransmitString("Hello Nishanth\r\n");
  }
}
