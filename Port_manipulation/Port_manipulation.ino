#define SET_PIN(port, pin) (DDR ## port |= (0 << pin)) // Sets the pin as an output
#define PIN_READ(port, pin) (PIN ## port & (1 << pin)) // Reads the state of the pin
#define LED_ON(port,pin) (PORT ## port |= (1<<pin))

void setup() 
{
  SET_PIN(D, 7); // Set pin D7 as output
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  int res = PIN_READ(D, 7); // Attempt to read an output pin (issue explained below)
  Serial.println(res); 
  if(res > 0)
    LED_ON(B, 5);
   else
   digitalWrite(13, LOW);
  delay(500);
}
