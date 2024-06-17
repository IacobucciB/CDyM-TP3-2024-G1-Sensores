
#ifndef DHT11_H_
#define DHT11_H_

#include "main.h"
#include "UART.h"

void DHT11_startSignal_y_respuesta();
int DHT11_bits();
void DHT11_obtenerDatos(int *, int *, int *, int *);

#endif /* DHT11_H_ */