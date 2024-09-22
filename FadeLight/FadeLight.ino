// Jonathan Mehmannavaz ©
// How to dim the light

void setup() {
  // Set pin 11 (PB3) as output
  DDRB |= (1 << DDB3);

  // Configure Timer2 for Fast PWM
  TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2A1); // Fast PWM, non-inverting mode
  TCCR2B = (1 << CS20); // No prescaler
}

void loop() {
  // Fade in
  for (int brightness = 0; brightness <= 255; brightness++) {
    OCR2A = brightness; // Set PWM duty cycle
    _delay_ms(10); // Adjust delay for fade speed
  }

  // Fade out
  for (int brightness = 255; brightness >= 0; brightness--) {
    OCR2A = brightness; // Set PWM duty cycle
    _delay_ms(10); // Adjust delay for fade speed
  }
}
