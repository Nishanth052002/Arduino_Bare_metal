#if 1
#include <avr/io.h>

//Initialize ADC here
void ADC_Initilize()
{
  ADMUX |= (1<<REFS0);  // SET reference voltage to AVcc(Reserved(5v))
  ADMUX &= ~(1<<REFS1); //set REFS0 as 1 and REFS1 as 0 

  ADCSRA |= (1<<ADEN); //Enable ADC

 //Set ADC prescalar : ADPS2,1,0 is set to 1 so division factor is 128 = 16MHz/128 = 125Khz ADC clock.
  ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); 
}

//Select the input channel and read ADC channel
uint16_t ADC_read(uint8_t channel)
{
  //Select the ADC channel(0-7)
  ADMUX = (ADMUX & 0xF8) | (channel & 0x07); //0xF8 = 11111000

  //Start conversion
  ADCSRA |= (1<<ADSC);  

 // Wait for the conversion to complete
  while(ADCSRA & (1<<ADSC));  // After the conversion is complete the ADSC will return 0

 //Return ADC result
 return ADC;
}

void setup()
{
  ADC_Initilize();
  Serial.begin(9600);
}

void loop()
{
   while (1)
   {
        uint16_t adc_value = ADC_read(0); // Read from ADC channel 0
        Serial.println(adc_value);
        delay(500);
    }
}
#endif
