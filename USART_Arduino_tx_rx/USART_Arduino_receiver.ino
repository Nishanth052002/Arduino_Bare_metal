#define FCLK 16000000UL
#define BAUD 9600
#define MYUBRR FCLK/16/BAUD-1

void setup() {
    USART_Init(MYUBRR);
    sei();
}

void USART_Init(unsigned int ubrr) {
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00) | (1 << USBS0);
}

void USART_Transmit(unsigned char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_TransmitString(const char *str) {
    while (*str) {
        USART_Transmit(*str++);
    }
}

unsigned char USART_Receive(void) {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void loop() {
    while (1) {
        char received = USART_Receive();
        USART_Transmit(received);
    }
}
