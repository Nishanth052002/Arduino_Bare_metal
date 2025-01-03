#if 0
#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1
void setup(void)
{
    USART_Init(MYUBRR);

}

void USART_Init(unsigned int ubrr)
{
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /*Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 8data, 2 stop bit */
    UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)));
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char USART_Receive(void)
{
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    return UDR0;
}

void USART_TransmitString(const char *str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}
void loop()
{

    while (1) {
       USART_TransmitString("Hello, USART!\r\n");
        char received = USART_Receive();  // Echo received character
        USART_Transmit(received);
    }
  
}
#endif

#if 1
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOSC 16000000  // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

volatile char received_data;  // Variable to store received data
volatile const char *transmit_buffer = NULL;  // Pointer to data being transmitted

void USART_Init(unsigned int ubrr);
void USART_TransmitString(const char *str);

void setup(void) 
{
    USART_Init(MYUBRR);
    sei();  // Enable global interrupts
}

void USART_Init(unsigned int ubrr) {
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    /* Enable receiver, transmitter, and RX Complete Interrupt */
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0) | (1 << UDRIE0);

    /* Set frame format: 8 data bits, 2 stop bits */
    UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_TransmitString(const char *str) 
{
    transmit_buffer = str;  // Point to the string to transmit
    UCSR0B |= (1 << UDRIE0);  // Enable Data Register Empty Interrupt
}

void USART_TransmitChar(char c) {
    while (!(UCSR0A & (1 << UDRE0)));  // Wait for the data register to be empty
    UDR0 = c;  // Load the character into the data register
}

/* ISR for Receive Complete Interrupt */
ISR(USART_RX_vect) {
    received_data = UDR0;  // Read received data
    USART_TransmitChar(received_data);  // Echo back the received character
}

/* ISR for Data Register Empty Interrupt */
ISR(USART_UDRE_vect) {
    if (*transmit_buffer) {
        UDR0 = *transmit_buffer++;  // Send next character
    } else {
        UCSR0B &= ~(1 << UDRIE0);  // Disable interrupt when done
        transmit_buffer = NULL;
    }
}

ISR(USART_TX_vect) 
{
    PORTB ^= (1 << PB0); 
}
void loop() {

}

#endif
