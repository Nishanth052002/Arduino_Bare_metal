#if 0
#define SET_PIN(port,pin) (DDR ## port |= (1<<pin))
void setup() 
{  
    SET_PIN(C, 5);
}

void loop() 
{
  for(int i=0;i<255;i++)
  {
  analogWrite(5,i);
  delay(5);
  }
  for(int i=255;i>=0;i--)
  {
    analogWrite(5,i);
    delay(5);
  }
}
#endif

#if 0
unsigned long T1 = 0, T2 = 0,T3 = 0;
void setup()
{
  pinMode(5, OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}
 
void loop()
{
  T2 = millis();
  if( (T2-T1) >= 1000)
  {
    digitalWrite(5, !digitalRead(5));
    T1 = millis();
  }
  if((T1-T3) >= 1000)
  {
    digitalWrite(13, !digitalRead(13));
    T3 = millis();
  }
  Serial.println(T3);
 
}
#endif

#if 1
const int led1 = 5;
const int led2 = 13; 

unsigned long previousMillis = 0; 
unsigned long previousMicros = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 300) {
    previousMillis = currentMillis; 
    digitalWrite(led1, !digitalRead(led1));
  }
  unsigned long currentMicros = micros();
  if (currentMicros - previousMicros >= 500) {
    previousMicros = currentMicros; 
    digitalWrite(led2, !digitalRead(led2)); 
  }
}
#endif
