/*
  Speed measurement by radino IP65-Radar
  (c) Claus Kuehnel 2017-10-12 info@ckuehnel.ch
*/

// DEFINE PINOUT
#define RELAY       5           // output for relay
#define TXLED      18           // red LED
#define RXLED      17           // green LED
#define RADAR      A0           // input for IPM-165 Radar Module
#define TXEN       A5           // RS485 DE

// DEFINE RS485
#define RS485      Serial1      // Serial for USB-UART, Serial1 and Serial2 for HW-UART
#define RS485Speed 9600         // Baudrate

#define TXEN_ON()  digitalWrite(TXEN, HIGH)
#define TXEN_OFF() digitalWrite(TXEN, LOW)

// DEFINE VALUEs
#define SERIAL                    Serial        // USB-UART
#define SERIAL_SPEED              115200        // Serial Speed to PC
#define THRESHOLD                 512           // Switching threshold
#define HYSTERESIS_VAL            5
#define LED_ON_TIME               50            // Time for led on in ms

#define F_TO_V                    (0.02272727272727272727272727272727)  // 1/44 Hz
#define MIN_VALID_MEASURES        8             // Minimal correct values for output
#define MIN_SPEED                 10            // Minimal detected speed

int series = 0;                                 // series of compared values
int v_filter = MIN_SPEED;                       // Minimal speed for compare

unsigned long T = 0;                            // Period in us
float f = 0.0;                                  // Frequency in Hz
float v = 0.0;                                  // Speed

void tx_led_out()
{
  digitalWrite(TXLED, HIGH);
  delay(LED_ON_TIME);
  digitalWrite(TXLED, LOW);
}

void relay_out()
{
  digitalWrite(RELAY, HIGH);
  delay(500);
  digitalWrite(RELAY, LOW);
}

void serial_out()
{
  // Period output
  SERIAL.print("T in us:   " );
  SERIAL.println(T);
  // Frequency output
  SERIAL.print("f in Hz:   " );
  SERIAL.println(f);
  // Speed output
  SERIAL.print("v in km/h: " );
  SERIAL.println(v);
  SERIAL.println();
}

void setup() 
{
  SERIAL.begin(SERIAL_SPEED);
  pinMode(RXLED, OUTPUT);
  digitalWrite(RXLED, LOW);
  pinMode(TXLED, OUTPUT);
  digitalWrite(TXLED, LOW);
  pinMode(RADAR, INPUT);
  pinMode(RELAY, OUTPUT);
  delay(5000);
  pinMode(TXEN, OUTPUT);
  RS485.begin(RS485Speed);
}

void loop()
{
  int32_t th = 0;                               // Time for rising edge
  int32_t tl = 0;                               // Time for falling edge
  // wait for high flank
  while (analogRead(RADAR) < (THRESHOLD + HYSTERESIS_VAL));
  th = micros();                                // Set time rising edge in micros

  // wait for low flank
  while (analogRead(RADAR) > (THRESHOLD - HYSTERESIS_VAL));
  tl = micros();                                // Set time falling edge in micros

  T = (tl - th + 0xFFFF) % 0xFFFF;              // Period in micros
  
  f = 1 / (float)T;                             // Frequency in MHz f=1/T
  f *= 1000000;                                 // Frequency in Hz
  v = f * F_TO_V;                               // Speed in km/h
  
  if (v >= v_filter)
  {
    series++;
    SERIAL.print(series);
    SERIAL.print("\t");
    SERIAL.println(v);

    if (series >= MIN_VALID_MEASURES)  
    {                     
      serial_out();                               
      tx_led_out();  
      relay_out();
      TXEN_ON();
      RS485.println(v);
      delay(20);    // switch off TXEN not before RS485 output is finished ( 1 ms/character @ 9600 Baud)
      TXEN_OFF();
      series = 0;
    }
  }
  else
  {
    series = 0;
  }
}

