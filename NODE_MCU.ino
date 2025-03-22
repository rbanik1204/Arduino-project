int choice = 0;

int in1 = 14;
int in2 = 12;
// connections for drive Motor FL & BL
int in3 = 13;
int in4 = 15;

void setup() {
  Serial.begin(9600);

  // Define motor pins
  pinMode(in1, OUTPUT); // Left Motor Reverse
  pinMode(in2, OUTPUT); // Right Motor Reverse
  pinMode(in3, OUTPUT); // Right Motor Forward
  pinMode(in4, OUTPUT); // Left Motor Forward

  // Ensure all motors are OFF at startup
  digitalWrite(in, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  digitalWrite(15, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Read input until newline
    choice = input.toInt();  // Convert to integer
    Serial.print("Received Choice: ");
    Serial.println(choice);
  }

  // Stop all motors first to ensure no unintended movement
  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(15, LOW);
  digitalWrite(14, LOW);

  switch (choice) {
    case 1:  // Move Forward
      Serial.println("Moving Forward");
      digitalWrite(13, HIGH);  // Right Motor Forward
      digitalWrite(12, LOW);
      digitalWrite(15, HIGH);  // Left Motor Forward
      digitalWrite(14, LOW);
      break;

    case 2:  // Move Backward
      Serial.println("Moving Backward");
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(15, LOW);
      digitalWrite(14, HIGH);
      break;

    case 3:  // Turn Left
      Serial.println("Turning Left");
      digitalWrite(13, HIGH);  // Right Motor Forward
      digitalWrite(12, LOW);
      digitalWrite(15, LOW);   // Left Motor Off
      digitalWrite(14, HIGH);  // Left Motor Reverse
      break;

    case 4:  // Turn Right
      Serial.println("Turning Right");
      digitalWrite(13, LOW);   // Right Motor Off
      digitalWrite(12, HIGH);  // Right Motor Reverse
      digitalWrite(15, HIGH);  // Left Motor Forward
      digitalWrite(14, LOW);
      break;

    default:  // Stop Motors
      Serial.println("Stopping Motors");
      digitalWrite(13, LOW);
      digitalWrite(12, LOW);
      digitalWrite(15, LOW);
      digitalWrite(14, LOW);
      break;
  }

  delay(100);  // Small delay for stability
}
