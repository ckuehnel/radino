/*
  RS485 for radino IP65-Radar
  (c) Claus Kuehnel 2017-10-12 info@ckuehnel.ch
*/

#define RXLED 17 // green LED
#define TXLED 18 // red LED

#define RS485      Serial2      // Serial for USB-UART, Serial1 and Serial2 for HW-UART
#define RS485Speed 9600         // Baudrate
#define TXEN_PIN   2            //Which pin to use for RS485 functionality - comment to disable

#define TXEN_ON() digitalWrite(TXEN_PIN, HIGH)
#define TXEN_OFF() digitalWrite(TXEN_PIN, LOW)
#define TXEN_INIT() pinMode(TXEN_PIN, OUTPUT)

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RXLED, OUTPUT);
  pinMode(TXLED, OUTPUT);
  TXEN_INIT();
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
  TXEN_ON();
  RS485.println("RS485 out");
  TXEN_OFF();
}
