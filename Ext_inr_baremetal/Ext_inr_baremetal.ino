#include <avr/io.h>
#include <avr/interrupt.h>

// ISR for External Interrupt 1 (INT1)
ISR(INT1_vect) {
    PORTB ^= (1 << PORTB5); // Toggle LED on Pin D13 (PB5)
}

void setup() {
    // Configure LED pin
    DDRB |= (1 << DDB5);  // Set PB5 (D13) as output
    PORTB &= ~(1 << PORTB5); // Ensure LED is off initially

    // Configure INT1 (Pin D3) as input with pull-up
    DDRD &= ~(1 << DDD3);  // Set PD3 (D3) as input
    PORTD |= (1 << PORTD3); // Enable pull-up resistor on PD3

    // Configure External Interrupt 1 (INT1)
    EICRA |= (1 << ISC11) | (1 << ISC10); // Rising edge trigger
    EIMSK |= (1 << INT1);   // Enable INT1 interrupt

}

void loop() {
    // Main loop does nothing; ISR handles the interrupt
}
