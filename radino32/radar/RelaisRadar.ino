/*
  Relais for radino IP65-Radar
  (c) Claus Kuehnel 2017-10-12 info@ckuehnel.ch
*/

#define RXLED 17 // green LED
#define TXLED 18 // red LED


#define RELAIS_PIN   5            // defined radino32 Radar board

#define RELAIS_ON() digitalWrite(RELAIS_PIN, HIGH)
#define RELAIS_OFF() digitalWrite(RELAIS_PIN, LOW)
#define RELAIS_INIT() pinMode(RELAIS_PIN, OUTPUT)

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RXLED, OUTPUT);
  pinMode(TXLED, OUTPUT);
  RELAIS_INIT();
  Serial.begin(115200);
}


void loop() {
  digitalWrite(TXLED, HIGH);   
  digitalWrite(RXLED, LOW);
  RELAIS_ON();
  delay(1000);                       
  digitalWrite(TXLED, LOW);   
  digitalWrite(RXLED, HIGH);
  RELAIS_OFF();                      
  delay(1000); 
  Serial.println("Hi, there.");


}
