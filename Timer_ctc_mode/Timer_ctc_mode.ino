
#if 0
//CTC Mode
void setup() {
  // Configure Timer1 in CTC Mode
  TCCR1A = 0;                      // CTC mode (WGM12 = 1, others = 0)
  TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode, prescaler = 1024

  // Set Compare Match value for 1-second interval (16 MHz clock)
  OCR1A = 15624;

  // Enable Timer1 Compare Match Interrupt
  TIMSK1 = (1 << OCIE1A);

  // Configure Pin D13 (PB5) as output
  DDRB |= (1 << DDB5);
}

ISR(TIMER1_COMPA_vect) {
  // Toggle LED on Pin D13 (PB5)
  PORTB ^= (1 << PORTB5);
}

void loop() {
  // Main code can run here independently
}
#endif
