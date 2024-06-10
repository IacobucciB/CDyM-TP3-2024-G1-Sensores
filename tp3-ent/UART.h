

#ifndef UART_H_
#define UART_H_

#include "main.h"
#include "SerialPort.h"

void UART_init();
void UART_sendString(char* s);
char UART_hayComando();
void UART_setHayComando();
char UART_getComando();
extern volatile int transmision_activa;

#endif /* UART_H_ */