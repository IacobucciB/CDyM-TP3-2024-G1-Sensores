#include "main.h"

static char bienvenida[] = "Registrador de temperatura y humedad \n\r Ingrese s: para reanudar, S para detener,\n\r ";
static char novalido[] = "Comando no valido\n\r";
volatile int comando_anterior;

int main(void){

	UART_init();   // Inicializar UART
	sei();         // Activar máscara de interrupciones
	
	UART_sendString(bienvenida); // Enviar mensaje de inicio/bienvenida

	// Initialize the DS3231
	DS3231_Init();

	// Set the desired time: hours, minutes, seconds
	DS3231_SetTime(14, 30, 0); // 14:30:00 (2:30 PM)

	// Set the desired date: day, date, month, year
	DS3231_SetDate(1, 9, 6, 24); // Monday, 09 June 2024 (1 for Monday, 0 for Sunday)
	
	while (1){
		if (UART_hayComando()) {
			char comando = UART_getComando();
			if (comando == 's') {
				transmision_activa = 1; // Reanudar transmisión
				} else if (comando == 'S') {
				transmision_activa = 0; // Detener transmisión
				} else {
				UART_sendString(novalido); // Enviar mensaje de comando no válido
			}
			UART_setHayComando(); // Avisar que el comando ya fue procesado
		}

		if (transmision_activa) {
			Terminal_sendDatos();  // Obtener y enviar datos del sensor
			_delay_ms(2000);
		}
	}
}
