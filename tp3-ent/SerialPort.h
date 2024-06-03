#ifndef SERIALPORT_H_
#define SERIALPORT_H_
#include <inttypes.h>
#include <avr/io.h>
void SerialPort_Init(uint8_t config);
void SerialPort_TX_Enable(void);
void SerialPort_TX_Interrupt_Enable(void);
void SerialPort_TX_Interrupt_Disable(void);
void SerialPort_RX_Enable(void);
void SerialPort_RX_Interrupt_Enable(void);
void SerialPort_Wait_For_TX_Buffer_Free(void);
void SerialPort_Send_Data(char data);
void SerialPort_Send_String(char * msg);
void SerialPort_Wait_Until_New_Data(void);
char SerialPort_Recive_Data(void);
void SerialPort_Send_uint8_t(uint8_t num);
void SerialPort_send_int16_t(int val,unsigned int field_length);
#endif