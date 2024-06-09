#ifndef DHT11_H_
#define DHT11_H_
#include <inttypes.h>
#include <avr/io.h>
#include <avr/delay.h>
void DHT11_startSignal_y_respuesta();
int DHT11_bits();
void DHT11_obtenerDatos(int *temperatura,int *temperatura_decimal, int *humedad, int *humedad_decimal);
void DHT11_start();
void DHT11_getResponse();


#endif /* DHT11_H_ */