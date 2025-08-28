const int buzzerPin = 4; // Example: Use GPIO4 for the buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  digitalWrite(buzzerPin, HIGH); // Turn buzzer on
  delay(1000); // Beep for 1 second
  digitalWrite(buzzerPin, LOW); // Turn buzzer off
  delay(1000); // Pause for 1 second
}






















