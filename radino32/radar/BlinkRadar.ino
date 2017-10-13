/*
  Blink for radino IP65-Radar
  (c) Claus Kuehnel 2017-10-12 info@ckuehnel.ch
  
  Based on Blink.ino

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman
*/

#define RXLED 17 // green LED
#define TXLED 18 // red LED


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RXLED, OUTPUT);
  pinMode(TXLED, OUTPUT);
  Serial.begin(115200);
}


void loop() {
  digitalWrite(TXLED, HIGH);   
  digitalWrite(RXLED, LOW);
  delay(1000);                       
  digitalWrite(TXLED, LOW);   
  digitalWrite(RXLED, HIGH);
  delay(1000);                       
  Serial.println("Hi, there.");
}
