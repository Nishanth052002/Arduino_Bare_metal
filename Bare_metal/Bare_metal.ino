#if 0
//LED blink
void setup() 
{
 DDRB = 0x20;
}

void loop() 
{
  //int *ptr = 0x25;
  //*ptr = 0x20;
  //delay(500);
  //*ptr=0;
  //delay(500);
  *((volatile int*)0x25) = 0x20; // Write to PORTB, setting PB5 high
  delay(500);
  *((volatile int*)0x25) = 0x0;  // Write to PORTB, setting PB5 low
  delay(500);
}
#endif

#if 0
//Button 
void setup()
{
  DDRB = 0x20;
}
void loop()
{
  //int res = (PINB & (1<<0));
  //if(res == 1)
  //PORTB = 0X20;
  //else
  //PORTB = 0;
  volatile int *ptr = (volatile int*)0x23; // volatile is crucial else compiler assumes the variable's value does not change unexpectedly
  volatile int *ptr1 = (volatile int*)0x25;
  int res = (*ptr & (1 << 0));
if (res != 0) 
    *ptr1 = 0x20; 
  else
    *ptr1 = 0x00; 
}
#endif

#if 1
void setup()
{
  DDRB = 0x20;
}
void loop()
{
  volatile int* ptr = (volatile int*)0x23;
  volatile int* ptr1 = (volatile int*)0x25;
  int res = (*ptr & (1<<0));
  if(res)
  *ptr1 = 0x20;
  else
  *ptr1 = 0;
}
#endif
