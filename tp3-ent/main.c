#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#include "SerialPort.h"


#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

//mensajes de bienvenida y despedida
char msg1[] = "Hola Mundo, si presiona 's' termina el programa, por favor ingrese una tecla:\n\r";
char msg2[] = "\n\rHasta luego!";


int main(void)
{

	volatile char dato = 0;

	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	SerialPort_Send_String(msg1);   // Envío el mensaje de Bienvenida

	DDRC |= 1 << PINC0; //output
	_delay_ms(2000); // wait for 2s according to datasheet
	PORTC &= ~ (1 << PINC0); //set low for at least 18 ms
	_delay_ms(20);
	PORTC |= 1 << PINC0; // set high

	while(1)
	{
		
		SerialPort_Wait_Until_New_Data();	  // Pooling - Bloqueante, puede durar indefinidamente.
		dato = SerialPort_Recive_Data();

		// Si presionan 's' se termina el programa
		if( dato == 's')
		{
			SerialPort_Send_String(msg2);  // Envío el string de despedida
			while(1);
		}
		else
		{	// Eco:
			SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisión este libre (bloqueante)
			SerialPort_Send_Data(dato);			  // Envío el dato recibido
		}
	}
	return 0;
}


