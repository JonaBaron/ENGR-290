// Constants for pin connections
const int triggerPin = 11; // OC2A, pin D11
const int echoPin = 2;     // INT0, pin D2

volatile long duration = 0; // To store pulse width from Echo
volatile bool echoReceived = false;

// Interrupt service routine to capture the echo pulse width
ISR(INT0_vect) {
  if (PIND & (1 << PD2)) { // Check if Echo pin (D2) is HIGH
    TCNT1 = 0;             // Reset Timer1
    TCCR1B |= (1 << CS11);  // Start Timer1 with prescaler 8
  } else {
    TCCR1B &= ~(1 << CS11); // Stop Timer1
    duration = TCNT1;       // Capture the pulse width
    echoReceived = true;
  }
}

// Set up Timer2 for PWM generation on OC2A (D11)
void setupPWM() {
  DDRB |= (1 << DDB3);   // Set OC2A (D11) as output

  // Set Timer2 for Fast PWM, non-inverted on OC2A
  TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2A1);
  TCCR2B = (1 << CS21);  // Prescaler of 8
  OCR2A = 100;           // Set the duty cycle (adjust as needed)
}

// Set up Timer1 to capture echo pulse width
void setupTimer1() {
  TCCR1A = 0;  // Normal operation (no PWM)
  TCCR1B = 0;  // Timer stopped initially
  TCNT1 = 0;   // Clear the counter
}

// Set up external interrupt on INT0 (D2)
void setupInterrupt() {
  EIMSK |= (1 << INT0);   // Enable external interrupt INT0
  EICRA |= (1 << ISC00);  // Trigger on any edge (rising/falling)
}

// Initialize the system
void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set up the PWM signal on trigger pin (D11) using Timer2
  setupPWM();

  // Set up Timer1 for capturing echo pulse width
  setupTimer1();

  // Set up external interrupt on echo pin (D2)
  setupInterrupt();
  
  // Enable global interrupts
  sei();
}

void loop() {
  if (echoReceived) {
    // Convert pulse width to distance in cm
    long distance = (duration * 1000) / 58200; // Convert to distance in cm
 // Convert pulse width to cm

    // Output distance value over Serial
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Reset echo flag
    echoReceived = false;

    // Add a short delay between measurements
    _delay_ms(50);
  }

}
