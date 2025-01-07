#if 1
void setup() 
{
  Serial.begin(9600);
  SPI_Init();
}

void SPI_Init()
{
   DDRB |= (1<<5)|(1<<3)|(1<<2);
   SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, select Master spi mode, SCK Frequency to fosc/16
}

void SPI_transmit(unsigned int data)
{
  SPDR = data;
  while(!(SPSR & (1<<SPIF)));
}

void loop() {
  // put your main code here, to run repeatedly:
SPI_transmit(0x55);

}
#endif
