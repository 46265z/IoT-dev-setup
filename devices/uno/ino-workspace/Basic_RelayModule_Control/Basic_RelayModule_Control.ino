int RelayPin = 7;

void setup() {
  // Initialize serial connection at 9600 baudrate
  Serial.begin(9600);
  
  // Confirm that serial comm. is established
  Serial.println("Serial communication established.");
  
  // Set RelayPin as an output pin
  Serial.println("Setting RelayPin as output");
  pinMode(RelayPin, OUTPUT);
}

void loop() {
  
  // Turn on the relay...
  Serial.println("Turning the relay on (digitalWrite)");
  digitalWrite(RelayPin, LOW);delay(400);
  
  // Reading pin state with digitalRead and returning the current state.
  Serial.println("current state");delay(100);
  Serial.println(digitalRead(RelayPin));delay(2500);



  // Turn off the relay...
  Serial.println("Turning the relay off (digitalWrite)");
  digitalWrite(RelayPin, HIGH);delay(400);
  
  // Reading pin state with digitalRead and returning the current state.
  Serial.println("current state");delay(100);
  Serial.println(digitalRead(RelayPin));delay(2500);
}
