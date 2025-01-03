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

#if 1
//Fast pwm mode
void setup() {
  Serial.begin(9600);
  // Configure Pin 9 (OC1A) as output
  DDRB |= (1 << PB1);

  // Set Timer1 to Fast PWM mode, ICR1 as TOP
  TCCR1A = (1 << WGM11) | (1 << COM1A1); // Fast PWM, Clear OC1A on Compare Match
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11); // Fast PWM, Prescaler = 8

  ICR1 = 3999; // 16 MHz / (8 * (1 + TOP)) = ~490 Hz

  // Set duty cycle to 50%
  OCR1A = ICR1 / 2; // 50% of TOP
}

void loop() {
 
  for (uint16_t duty = 0; duty <= ICR1; duty += 200) { 
    OCR1A = duty; // Adjust duty cycle
    _delay_ms(5); 

  // Gradually decrease duty cycle from 100% to 0%
  for (uint16_t duty = ICR1; duty > 0; duty -= 200) {  
    OCR1A = duty; // Adjust duty cycle
    _delay_ms(5); 
  }
}
#endif

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
