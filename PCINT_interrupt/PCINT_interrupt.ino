#include<avr/io.h>

ISR(PCINT0_vect) {
    PORTB ^= (1 << 5); // Toggle LED on Pin D13 (PB5)
}
void setup() 
{
  // put your setup code here, to run once:
  DDRB |= (1<<5);
  PORTB &= ~(1<<5);
  
  PCICR |= (1<<0);
  PCMSK0 |= (1 << 0);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
