int IRsensor = 

void setup() {
  put your setup code here, to run once:
  pinMode(2, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(14, OUTPUT);
  Serial.begin(115200);
  Serial.println("Serial is working!");
  pinMode(13,INPUT);
  pinMode()

}

void loop() {
  put your main code here, to run repeatedly:
  digitalWrite(2,HIGH);
  delay(1000);
  digitalWrite(2,LOW);
  delay(1000);

  digitalWrite(0,HIGH);
  delay(1000);
  digitalWrite(0,LOW);
  delay(1000);

  digitalWrite(14,HIGH);
  delay(1000);
  digitalWrite(14,LOW);
  delay(1000);

}
