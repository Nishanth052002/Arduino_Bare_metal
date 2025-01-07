#if 1
void setup() 
{
  Serial.begin(9600);
  SPI_Init();
}

void SPI_Init()
{
   DDRB |= (1<<4);
   SPCR |= (1<<SPE); //Enable SPI, select Master spi mode, SCK Frequency to fosc/16
}


char SPI_Receive(void)
{
   while(!(SPSR & (1<<SPIF)));
   return SPDR;
}

void loop() 
{
  unsigned int received_data = SPI_Receive();
    Serial.println(received_data,HEX);

}
#endif
