#if 1
#include <avr/interrupt.h>

volatile uint8_t overflowCount = 0; // Counter for timer overflows

ISR(TIMER1_OVF_vect) {
  TCNT1 = 0; // No preload needed for full overflow period
  overflowCount++;

  if (overflowCount >= 38) { // Toggle LED after 19 overflows (5 seconds)
    PORTB ^= (1<<5);
    overflowCount = 0; // Reset the counter
  }
}

void setup() {
  // Configure Timer1
  TCCR1A = 0;           // Normal mode
  TCCR1B = 0;           // Clear control register
  TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler = 64
  TCNT1 = 0;            // Start Timer1 from 0
  TIMSK1 |= (1 << TOIE1); // Enable Timer1 overflow interrupt
  
  // Configure LED pin
  DDRB |= (1<<5);
}

void loop() {
  // Main loop does nothing; ISR handles the timer
}
#endif
