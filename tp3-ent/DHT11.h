
#ifndef DHT11_H_
#define DHT11_H_

#include "main.h"
#include "UART.h"

void DHT11_startSignal_y_respuesta();
uint8_t DHT11_bits();
void DHT11_obtenerDatos(uint8_t *, uint8_t *, uint8_t *, uint8_t *);

#endif /* DHT11_H_ */