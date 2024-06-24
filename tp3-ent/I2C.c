#include "I2C.h"
#include <avr/io.h> // Include AVR IO library
#define DS3231_ADDRESS 0x68
#include <util/twi.h>

void I2C_Init(void) {
	TWSR = 0x00;
	TWBR = 0x47;
	TWCR = (1 << TWEN);
}

void I2C_Start(void) {
	TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

void I2C_Stop(void) {
	TWCR = (1 << TWSTO) | (1 << TWEN) | (1 << TWINT);
}

void I2C_Write(uint8_t data) {
	TWDR = data;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t I2C_Read_Ack(void) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t I2C_Read_NAck(void) {
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t DecToBcd(uint8_t val) {
	return ((val / 10 * 16) + (val % 10));
}

uint8_t BcdToDec(uint8_t val) {
	return ((val / 16 * 10) + (val % 16));
}

void DS3231_GetTime(uint8_t *hour, uint8_t *minute, uint8_t *second) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x00);
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_READ);
	*second = I2C_Read_Ack();
	*minute = I2C_Read_Ack();
	*hour = I2C_Read_NAck();
	I2C_Stop();
}

void DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x04);
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_READ);
	*day = I2C_Read_Ack();
	*month = I2C_Read_Ack();
	*year = I2C_Read_Ack();
	I2C_Stop();
}

void DS3231_GetClock(uint8_t *hour, uint8_t *minute, uint8_t *second, uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year){
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x00);
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_READ);
	*second = BcdToDec(I2C_Read_Ack());
	*minute = BcdToDec(I2C_Read_Ack());
	*hour = BcdToDec(I2C_Read_Ack());
	*day = BcdToDec(I2C_Read_Ack());
	*date = BcdToDec(I2C_Read_Ack());
	*month = BcdToDec(I2C_Read_Ack());
	*year = BcdToDec(I2C_Read_NAck());
	I2C_Stop();
	
}

void DS3231_SetDateTime(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t date, uint8_t month, uint8_t year) {
	I2C_Start();
	I2C_Write((DS3231_ADDRESS << 1) | TW_WRITE);
	I2C_Write(0x00); // Start from register 0x00
	I2C_Write(DecToBcd(second));
	I2C_Write(DecToBcd(minute));
	I2C_Write(DecToBcd(hour));
	I2C_Write(DecToBcd(day)); // Weekday register (not used)
	I2C_Write(DecToBcd(date)); // Weekday register (not used)
	I2C_Write(DecToBcd(month));
	I2C_Write(DecToBcd(year));
	I2C_Stop();
}