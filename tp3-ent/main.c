#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdint.h>
#include <stdlib.h>

#define PIN DDC0

void digitalWrite(uint8_t pin, uint8_t value) {
	if (value)
	PORTC |= (1 << pin);
	else
	PORTC &= ~(1 << pin);
}

void pinMode(uint8_t pin, uint8_t mode) {
	if (mode)
	DDRC &= ~(1 << pin);
	else
	DDRC |= (1 << pin);
}

int digitalRead(uint8_t pin) {
	return (PINC & (1 << pin)) ? 1 : 0;
}

void delay(int millis) {
	_delay_ms(millis);
}

void delayMicroseconds(int micros) {
	_delay_us(micros);
}

uint8_t lee_data() {
	uint8_t result = 0;
	for (uint8_t i = 0; i < 8; i++) {
		// Esperamos hasta que HIGH, inicio byte data
		while (!digitalRead(PIN)) {
			delayMicroseconds(30);
		}
		// Datos debe estar HIGH durante 27 a 70us, dependiendo si es un "0" o un "1"
		if (digitalRead(PIN)) {
			result |= (1 << (7 - i)); // Si después de los 30us continúa HIGH, añadimos un 1 al byte
		}
		// Esperamos hasta que LOW, fin de byte data
		while (digitalRead(PIN));
	}
	return result;
}

void ReadDHT() {
	uint8_t bGlobalErr = 0;

	// Primero: ponemos a LOW durante 18 ms
	digitalWrite(PIN, 0);
	delay(18);
	delay(5);  // Transición

	// Segundo: ponemos a HIGH durante 40us (start read)
	digitalWrite(PIN, 1);
	delayMicroseconds(40);
	
	// Tercero: Reconfigura como entrada y espera 40 us
	pinMode(PIN, 1);
	delayMicroseconds(40);
	// Si es HIGH, indicamos que hay error de tipo 1
	if (digitalRead(PIN))  {
		bGlobalErr = 1;
		return;
	}
	delayMicroseconds(80);
	// Si es LOW, indicamos que hay error de tipo 2
	if (!digitalRead(PIN)){
		bGlobalErr = 2;
		return;
	}
	// Después de 40us en LOW debe pasar a HIGH por 80 us.
	delayMicroseconds(80);

	// Ahora lee los 5 bytes
	uint8_t DATA[5] = {0, 0, 0, 0};
	for (uint8_t i = 0; i < 5; i++) {
		DATA[i] = lee_data();
	}

	// Cuarto: Reconfiguramos como salida y ponemos en HIGH
	pinMode(PIN, 0);
	digitalWrite(PIN, 1);

	// Comprobamos checksum
	if (DATA[4] != DATA[0] + DATA[1] + DATA[2] + DATA[3]) {
		bGlobalErr = 3;
	}
}


int main() {
	// Configurar el pin como salida
	pinMode(PIN, 0);
	
	while(1){
		// Código de ejemplo para probar la función ReadDHT
		ReadDHT();
	}
	
	return 0;
}


