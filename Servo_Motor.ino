#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(0);
   
}
void loop() {
  for(int i=0;i<90; i++){
    servo.write(i);
     delay(15);
  }
  for(int i=90; i>0; i--){
    servo.write(i);
     delay(7);
  }
  
}