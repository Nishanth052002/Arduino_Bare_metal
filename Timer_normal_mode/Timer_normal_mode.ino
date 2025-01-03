#if 0
//Normal mode timer1.
void setup() {
  // Configure Timer1 in Normal Mode
  TCCR1A = 0;           // Normal mode 
  TCCR1B = (1 << CS12); // Prescaler = 256

  // Enable Timer1 Overflow Interrupt
  TIMSK1 = (1 << TOIE1);

  // Initialize Timer1 Counter
  TCNT1 = 0;

  // Enable global interrupts
  sei();
}

ISR(TIMER1_OVF_vect) {
  // Overflow interrupt code
  PORTB ^= (1 << PORTB5); // Toggle LED on Pin D13
}
void loop(){
  
}
#endif
