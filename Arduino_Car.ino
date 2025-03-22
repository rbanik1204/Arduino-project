/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
int choice = 0;
void setup() {
   
   pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT);  
  pinMode(15, OUTPUT); 
  pinMode(14, OUTPUT); 
   Serial.begin(9600);
   
   // Initialize the LED_BUILTIN pin as an output
   // Initialize the LED_BUILTIN pin as an output
  // Initialize the LED_BUILTIN pin as an output
   // Initialize the LED_BUILTIN pin as an output
}

// the loop function runs over and over again forever
void loop() {
// Turn the LED on (Note that LOW is the voltage level
  // but actuaED_BUILTINlly the LED is on; this is because
  // it is active low on the ESP-01)
  

   if(Serial.available()>0)
  {
     choice = Serial.parseInt();
  //    choice = incomingByte - '0';
    Serial.println(choice);

  //   switch(choice)
  //  { 

  //  }

  }

  if(choice == 1){





  }
  if(choice == 2){





  }
  if(choice == 3){





  }if(choice == 4){





  }







                          // Wait for a second
 


  
                    // Wait for two seconds (to demonstrate the active low LED)
}