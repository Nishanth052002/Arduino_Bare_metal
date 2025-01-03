#if 0
#include <EEPROM.h>
float value;
void setup() 
{
  Serial.begin(9600);
  value = EEPROM.read(0);
  Serial.print(value);
  Serial.println();
}

void loop() 
{
  
}
#endif

#if 0
#include <EEPROM.h>

void setup()
{
   EEPROM.write(0, 10.2);
}
void loop()
{
  
}
#endif

#if 1
#include <EEPROM.h>

struct MyObject {
  float field1;
  byte field2;
  char name[10];
};

void setup() {
  float f;          // Variable to store data read from EEPROM
  int eeAddress = 0; // EEPROM address to start reading from

  Serial.begin(9600);

  // Write data to EEPROM
  float valueToWrite = 10.2;  // Value to write to EEPROM
  EEPROM.put(eeAddress, valueToWrite);  // Correctly store a float
  Serial.print("Written float to EEPROM: ");
  Serial.println(valueToWrite, 3);

  // Read the float data from the EEPROM
  EEPROM.get(eeAddress, f);  // Correctly read the float
  Serial.print("Read float from EEPROM: ");
  Serial.println(f, 3);

  // Move address to store the custom structure
  eeAddress += sizeof(float);

  // Create a custom structure and write to EEPROM
  MyObject customWrite = {5.67, 42, "Arduino"};
  EEPROM.put(eeAddress, customWrite);
  Serial.println("Written custom object to EEPROM.");

  // Read the custom structure from EEPROM
  MyObject customVar;
  EEPROM.get(eeAddress, customVar);

  Serial.println("Read custom object from EEPROM:");
  Serial.print("Field1: ");
  Serial.println(customVar.field1);
  Serial.print("Field2: ");
  Serial.println(customVar.field2);
  Serial.print("Name: ");
  Serial.println(customVar.name);
}

void loop() {
  // Empty loop
}
#endif
