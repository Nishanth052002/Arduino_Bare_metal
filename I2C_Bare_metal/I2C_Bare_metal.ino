#include <avr/io.h> // Input/output (I/O) registers of the AVR microcontroller
#include <util/delay.h> // Provides a function for creating time delays
#include <stdio.h> // For sprintf

#define cpu_freq 16000000UL
#define I2C_scl_freq 100000UL
#define RTC_ADDRESS 0x68 // I2C address of DS3231 RTC (7-bit address)

void I2C_init()
{
    TWBR = ((cpu_freq / I2C_scl_freq) - 16) / 2; // Set bit rate register
    TWSR = 0x00; // Clear prescaler bits in TWSR
    TWCR = (1 << TWEN); // Enable TWI
}

uint8_t I2C_start()
{
    TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT); // Send Start condition
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set. Indicates that START is transmitted.
    if ((TWSR & 0xF8) != 0x08) // 0x08: START condition transmitted
        return 0;
    else
        return 1;
}

void I2C_stop()
{
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO); // Set STOP condition
    while (TWCR & (1 << TWSTO)); // Wait for TWSTO flag to set. Indicates the STOP
}

uint8_t I2C_write(uint8_t data)
{
    TWDR = data; // Load data to TWDR
    TWCR = (1 << TWINT) | (1 << TWEN); // Start transmission
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag
    if ((TWSR & 0xF8) != 0x28) // 0x28: Data transmitted, ACK received
        return 0;
    return 1;
}

uint8_t I2C_read_ACK()
{
    TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Enable ACK and start reception
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag
    return TWDR; // Return received data
}

uint8_t I2C_read_NACK()
{
    TWCR = (1 << TWEN) | (1 << TWINT); // Enable NACK and start reception
    while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag
    return TWDR; // Return received data
}

uint8_t bcd_to_decimal(uint8_t bcd)
{
    return ((bcd >> 4) * 10) + (bcd & 0x0F); // Convert BCD to decimal
}

void read_rtc()
{
    char buffer[50];
    uint8_t seconds, minutes, hours, day, date, month, year;

    // Start I2C communication
    if (I2C_start())
    {
        I2C_write((RTC_ADDRESS << 1) | 0x00); // RTC address + Write
        I2C_write(0x00); // Set pointer to seconds register

        I2C_start(); // Restart
        I2C_write((RTC_ADDRESS << 1) | 0x01); // RTC address + Read

        // Read RTC data
        seconds = bcd_to_decimal(I2C_read_ACK());
        minutes = bcd_to_decimal(I2C_read_ACK());
        hours = bcd_to_decimal(I2C_read_ACK());
        day = bcd_to_decimal(I2C_read_ACK());
        date = bcd_to_decimal(I2C_read_ACK());
        month = bcd_to_decimal(I2C_read_ACK());
        year = bcd_to_decimal(I2C_read_NACK()); // Last read: NACK

        I2C_stop();

        // Print RTC data
        sprintf(buffer, "Time: %02d:%02d:%02d", hours, minutes, seconds);
        Serial.println(buffer);

        sprintf(buffer, "Date: %02d/%02d/20%02d", date, month, year);
        Serial.println(buffer);
    }
    else
    {
        Serial.println("Failed to communicate with RTC.");
    }
}

void setup()
{
    Serial.begin(9600); // Initialize serial communication
    Serial.println("Initializing I2C...");
    I2C_init(); // Initialize I2C
    Serial.println("I2C Initialized");
}

void loop()
{
    Serial.println("Reading RTC...");
    read_rtc(); // Read and print RTC data
    delay(2000); // Delay before next reading
}
