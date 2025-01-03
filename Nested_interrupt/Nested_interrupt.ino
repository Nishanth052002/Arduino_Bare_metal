#include <avr/io.h>
#include <avr/interrupt.h>

volatile bool buttonPressed = false;

// Timer0 ISR (called every 1 second)
ISR(TIMER0_COMPA_vect) {
  // Toggle LED on Pin 13 (built-in LED)
  PORTB ^= (1 << PORTB5);
  
  // Check if button was pressed
  if (buttonPressed) {
    // Toggle LED on Pin 12 (another LED)
    PORTB ^= (1 << PORTB4);
    buttonPressed = false;  // Reset the flag
  }
}

// External interrupt ISR (INT0)
ISR(INT0_vect) {
  // Set the flag to indicate that the button was pressed
  buttonPressed = true;
}

void setup() {
  // Configure Pin 13 (PB5) as output for the built-in LED
  DDRB |= (1 << DDB5);
  // Configure Pin 12 (PB4) as output for the second LED
  DDRB |= (1 << DDB4);
  
  // Set up external interrupt INT0 (pin 2)
  // Enable INT0 and set the interrupt to trigger on the falling edge (button press)
  EICRA |= (1 << ISC01);  // Falling edge trigger
  EIMSK |= (1 << INT0);   // Enable INT0 interrupt
  
  // Set up Timer0 in CTC mode to trigger every 1 second
  TCCR0A = 0;  // Normal mode
  TCCR0B = (1 << WGM12) | (1 << CS02) | (1 << CS00);  // CTC mode, prescaler 1024
  OCR0A = 3036 ;  // Correct compare value for 1-second interrupt (16 MHz clock)
  TIMSK0 |= (1 << OCIE0A);  // Enable Timer0 compare interrupt
  
  // Enable global interrupts
  sei();
}

void loop() {
  // Main loop does nothing, interrupt handling takes care of the rest
}
