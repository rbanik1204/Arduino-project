// const int buzzer = 8;
// const int trig_pin = 9;
// const int echo_pin = 10;
// float timing = 0.0;
// float distance = 0.0;

// void setup()
// {
//   pinMode(echo_pin, INPUT);
//   pinMode(trig_pin, OUTPUT);
//   pinMode(buzzer, OUTPUT);
  
//   digitalWrite(trig_pin, LOW);
//   digitalWrite(buzzer, LOW);
    
//   Serial.begin(9600);
// }

// void loop()
// {
//   digitalWrite(trig_pin, LOW);
//   delay(2);
  
//   digitalWrite(trig_pin, HIGH);
//   delay(10);
//   digitalWrite(trig_pin, LOW);
  
//   timing = pulseIn(echo_pin, HIGH);
//   distance = (timing * 0.034) / 2;
  
//   Serial.print("Distance: ");
//   Serial.print(distance);
//   Serial.print("cm | ");
//   Serial.print(distance / 2.54);
//   Serial.println("in");
  
    
//   if (distance <= 50) {
//   	tone(buzzer, 500);
//   } else {
//   	noTone(buzzer);
//   }
  
//   delay(100);
// }
const int pingPin = 12; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 13; // Echo Pin of Ultrasonic Sensor
void setup() {
   Serial.begin(9600); // Starting Serial Terminal
}
void loop() {
   long duration, inches, cm;
   pinMode(pingPin, OUTPUT);                              //Set which pin will be used for output
   digitalWrite(pingPin, LOW);                                //Ensure that the pin in low first
   delayMicroseconds(2);                                        //Introducing delay of 2 milliseconds
   digitalWrite(pingPin, HIGH);                               //Set which pin will be used for input
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);                  //Function for collecting the waves
   inches = microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   Serial.print(inches);
   Serial.print("in, ");
   Serial.print(cm);
   Serial.print("cm");
   Serial.println();
   delay(100);
}
long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}