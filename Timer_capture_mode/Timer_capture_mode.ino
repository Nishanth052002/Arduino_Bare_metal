#if 0
//CAPTURE Mode
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t startTime = 0;
volatile uint16_t endTime = 0;
volatile uint16_t pulseWidth = 0;

ISR(TIMER1_CAPT_vect) {
  // Read the captured value from ICR1
  if (startTime == 0) {
    startTime = ICR1; // Store the first capture
  } else {
    endTime = ICR1;   // Store the second capture
    pulseWidth = endTime - startTime; // Calculate the pulse width
    startTime = 0;    // Reset for the next measurement
  }
}

void setup() {
  Serial.begin(9600);

  // Configure ICP1 pin (Pin 8 on Arduino Uno) as input
  DDRB &= ~(1 << DDB0);

  // Configure Pin 6 (PD6) as output
  DDRD |= (1 << DDD6);

  // Configure Timer1
  TCCR1A = 0;                  // Normal mode
  TCCR1B = (1 << ICES1) | (1 << CS11); // Capture on rising edge, Prescaler = 8
  TIMSK1 = (1 << ICIE1);       // Enable Input Capture Interrupt
  
  sei(); // Enable global interrupts
}

void loop() {
  // Print pulse width if available
  if (pulseWidth > 0) {
    Serial.println(pulseWidth);
    pulseWidth = 0;             // Reset for the next measurement
  }
}

#endif
