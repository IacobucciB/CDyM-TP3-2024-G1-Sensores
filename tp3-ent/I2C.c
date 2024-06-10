#include "I2C.h"
#include <avr/io.h> // Include AVR IO library

#define DS3231_ADDRESS 0x68

// I2C functions implementation
void I2C_Init(void) {
	TWSR = 0x00; // Set prescaler to 1
	TWBR = 0x47; // Set SCL frequency to 100 kHz (assuming 16 MHz clock)
	TWCR = (1 << TWEN); // Enable TWI
}

void I2C_Start(void) {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); // Send start condition
	while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
}

void I2C_Stop(void) {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT); // Send stop condition
	while (TWCR & (1 << TWSTO)); // Wait for stop condition to be executed
}

void I2C_Write(uint8_t data) {
	TWDR = data; // Load data into TWDR register
	TWCR = (1 << TWEN) | (1 << TWINT); // Start data transmission
	while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
}

uint8_t I2C_Read_Ack(void) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); // Enable TWI and ACK
	while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
	return TWDR; // Return received data
}

uint8_t I2C_Read_NAck(void) {
	TWCR = (1 << TWEN) | (1 << TWINT); // Enable TWI without ACK
	while (!(TWCR & (1 << TWINT))); // Wait for TWINT flag set
	return TWDR; // Return received data
}

// DS3231 functions implementation
void DS3231_Init(void) {
	I2C_Init();
}

void DS3231_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Send DS3231 address with write flag
	I2C_Write(0x00); // Start from register 0x00 (seconds register)
	I2C_Start(); // Repeat start
	I2C_Write((DS3231_ADDRESS << 1) | 1); // Send DS3231 address with read flag

	*seconds = I2C_Read_Ack();
	*minutes = I2C_Read_Ack();
	*hours = I2C_Read_NAck();

	I2C_Stop();
}

void DS3231_GetDate(uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Send DS3231 address with write flag
	I2C_Write(0x03); // Start from register 0x03 (day register)
	I2C_Start(); // Repeat start
	I2C_Write((DS3231_ADDRESS << 1) | 1); // Send DS3231 address with read flag

	*day = I2C_Read_Ack();
	*date = I2C_Read_Ack();
	*month = I2C_Read_Ack();
	*year = I2C_Read_NAck();

	I2C_Stop();
}

void DS3231_SetDate(uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Send DS3231 address with write flag
	I2C_Write(0x03); // Start from register 0x03 (day register)
	
	I2C_Write(decToBcd(day)); // Write day in BCD format
	I2C_Write(decToBcd(date)); // Write date in BCD format
	I2C_Write(decToBcd(month)); // Write month in BCD format
	I2C_Write(decToBcd(year)); // Write year in BCD format
	
	I2C_Stop();
}

uint8_t decToBcd(uint8_t val) {
	return ((val / 10 * 16) + (val % 10));
}

void DS3231_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | 0); // Send DS3231 address with write flag
	I2C_Write(0x00); // Start from register 0x00 (seconds register)
	
	I2C_Write(decToBcd(seconds)); // Write seconds in BCD format
	I2C_Write(decToBcd(minutes)); // Write minutes in BCD format
	I2C_Write(decToBcd(hours)); // Write hours in BCD format
	
	I2C_Stop();
}
