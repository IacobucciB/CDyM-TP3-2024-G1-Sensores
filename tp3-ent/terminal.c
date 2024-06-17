
#include "terminal.h"

int Terminal_procesarcomando(char *s){
	if (!strcmp(s,'S') || !strcmp(s,'s')) { // Comando para detener/reanudar transmisión
		return 1;
	}
	else {
		return 2;// Comando no válido
	}
}


void Terminal_sendDatos(){
	char temperaturayhumedad[50]; // Ampliamos el tamaño del buffer para dar espacio a la fecha y hora
	char dataBuffer[100];
	int humedad, humedad_decimal, temperatura_decimal, temperatura;
	uint8_t hours, minutes, seconds;
	uint8_t day, date, month, year;
	DHT11_obtenerDatos(&temperatura, &temperatura_decimal, &humedad, &humedad_decimal);
	
	// Obtain time from DS3231
	//DS3231_GetTime(&hours, &minutes, &seconds);

	// Obtain date from DS3231
	//DS3231_GetDate(&day, &date, &month, &year);
	//DS3231_GetDate(&date, &month, &year);
	// Obtener datos del sensor y formatearlos
	
	DS3231_GetClock(&hours, &minutes, &seconds, &day, &date, &month, &year);
	
	if (humedad > 100)
	{
		humedad = humedad - 100;
	}
	
//	sprintf(dataBuffer, "TEMP: %d.%d °C HUM: %02d%% FECHA: %02d/%02d/%02d HORA: %02d:%02d:%02d\r\n",
//	temperatura, temperatura_decimal, humedad, date, month, year, hours, minutes, seconds);


	sprintf(dataBuffer, "TEMP: %d.%d °C HUM: %02d.%02d FECHA: %02d/%02d/%02d HORA: %02d:%02d:%02d\r\n",
	temperatura, temperatura_decimal, humedad, humedad_decimal,date, month, year, hours, minutes, seconds);


	// Send the formatted string over UART
	UART_sendString(dataBuffer);
}