#ifndef DS3231_H
#define DS3231_H

#include <stdint.h>

// I2C functions
void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
uint8_t I2C_Read_Ack(void);
uint8_t I2C_Read_NAck(void);

// DS3231 functions
void DS3231_GetTime(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
void DS3231_GetDate(uint8_t *day, uint8_t *month, uint8_t *year);
void DS3231_GetClock(uint8_t *hour, uint8_t *minute, uint8_t *second, uint8_t *day, uint8_t *date, uint8_t *month, uint8_t *year);
void DS3231_SetDateTime(uint8_t hour, uint8_t minute, uint8_t second, uint8_t day, uint8_t date, uint8_t month, uint8_t year);

#endif
