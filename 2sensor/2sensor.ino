// Define pin for the GP2Y0A21 sensor
const int sensorPin = A2; // Analog input pin connected to the sensor's output

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the sensor (0 to 1023)
  int sensorValue = analogRead(sensorPin);

  // Convert the analog value to voltage (0V to 5V)
  float voltage = sensorValue * (5.0 / 1023.0);

  // Convert the voltage to distance in cm (approximation)
  // The relationship between distance and voltage is non-linear.
  // For GP2Y0A21, it is approximately: distance (cm) = 27.86 / (voltage - 0.1)
  // The factor 27.86 and offset 0.1 can vary depending on calibration.
  float distance = 27.86 / (voltage - 0.1); 

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Wait for a short period before taking the next reading
  delay(100);
}
