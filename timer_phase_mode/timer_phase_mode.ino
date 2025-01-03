void setup() {
  // Initialize Serial Communication at 9600 baud
  Serial.begin(9600);

  // Set pin 6 (OC0A) as output for PWM
  pinMode(6, OUTPUT);

  // Configure Timer0 for Phase Correct PWM
  // Phase Correct PWM Mode: WGM00 = 1, WGM01 = 0 (Phase Correct PWM), COM0A1 = 1, COM0A0 = 0 (Non-inverting mode)
  TCCR0A = (1 << WGM00) | (1 << COM0A1);   // Phase Correct PWM, non-inverting mode
  TCCR0B = (1 << CS00);  // No prescaler, clock is directly from system clock

  // Start with 50% duty cycle
  OCR0A = 50;  // (255 / 1) for 50% duty cycle (since Timer0 is 8-bit)
}

void loop() {
  // Sweep duty cycle from 0 to 100%
  for (int duty = 0; duty <= 100; duty += 10) {
    // Set duty cycle (0-255 range for Timer0)
    OCR0A = (255 * duty) / 100;

    // Print the duty cycle to Serial Monitor
    Serial.print("Duty Cycle: ");
    Serial.print(duty);
    Serial.println("%");

    delay(500); // Wait for 500 ms
  }
}
