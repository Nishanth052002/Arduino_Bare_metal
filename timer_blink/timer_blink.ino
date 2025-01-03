#include <avr/io.h>

void setup() {
    // Configure LED pin (PB5 = D13 on Arduino)
    DDRB |= (1 << PORTB5);   // Set PB5 as output
    PORTB &= ~(1 << PORTB5); // Turn off LED initially

    // Configure Timer1 in CTC mode(clear time on compare match}
    TCCR1A = 0;                      // Normal mode (no PWM)
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode(WGM12), Prescaler = 1024(CS12,CS10)
    OCR1A = 31249;                   // Set compare value for 1-second delay (16 MHz clock)
}

void loop() {
    // Polling Timer1 Compare Match Flag
    while (1) {
        if (TIFR1 & (1 << OCF1A)) { // Check if Compare Match A flag is set and will be automatically cleared when the output compare match A
            TIFR1 |= (1 << OCF1A);  // Clear the flag by writing 1 to it 
            PORTB ^= (1 << PORTB5); // Toggle LED on PB5
        }
    }
}
