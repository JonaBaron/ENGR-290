const int sensorPin = A2; // Analog input pin connected to the sensor's output

void setup() {
  Serial.begin(9600);

  // Configure the ADC
  ADMUX = (1 << REFS0);  // Reference voltage set to AVcc (5V)
  ADCSRA = (1 << ADEN)   // Enable ADC
         | (1 << ADPS2)  // Set prescaler to 16 (for 16 MHz clock)
         | (1 << ADPS0); // This results in an ADC clock of 1 MHz
}

uint16_t readADC(uint8_t pin) {
  // Select the appropriate input pin (analog pin number)
  ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);  // Clear last 4 bits and set new pin
  ADCSRA |= (1 << ADSC);  // Start the conversion
  
  // Wait for the conversion to complete
  while (ADCSRA & (1 << ADSC));
  
  // Return the ADC value (10-bit resolution)
  return ADC;
}

void loop() {
  // Read the analog value from the sensor connected to sensorPin (A2)
  uint16_t sensorValue = readADC(sensorPin - A0);  // Subtract A0 to get the right pin number

  // Convert the analog value to voltage (0V to 5V)
  float voltage = sensorValue * (5.0 / 1023.0);

  // Convert the voltage to distance in cm (approximation)
  // The relationship between distance and voltage is non-linear.
  // For GP2Y0A21, it is approximately: distance (cm) = 27.86 / (voltage - 0.1)
  float distance = 27.86 / (voltage - 0.1);

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait for a short period before taking the next reading
  delay(100);
}
