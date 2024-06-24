


#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "main.h"
#include "DHT11.h"
#include "serialPort.h"
#include <stdio.h>

int Terminal_procesarcomando(char *);
void Terminal_sendDatos();

#endif /* TERMINAL_H_ */