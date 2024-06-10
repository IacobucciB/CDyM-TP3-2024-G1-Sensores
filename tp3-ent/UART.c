
#include "UART.h"

unsigned char TX_indicelectura = 0, TX_indiceescritura = 0;
unsigned char RX_indice = 0;
static char TX_Buffer[105];
static char RX_Buffer[10];

static unsigned char hayString = 0;


static char dato;


volatile int transmision_activa = 1; // Bandera para indicar si la transmisión está activa (1) o detenida (0)

volatile unsigned char nuevoDato = 0;

static int nuevoComando = 0;

void UART_init(){
	SerialPort_Init(0x67); //inicializar puerto serie
	SerialPort_TX_Enable(); //habilitar transmisor TX
	SerialPort_RX_Enable(); //habilitar receptor RX
	SerialPort_RX_Interrupt_Enable(); //habilitar interrupciones de recepción
}

void UART_sendString(char* s){
	unsigned char indice = 0;
	while(s[indice] != '\0'){ //Mientras no llegue al fin de la cadena
		if(TX_indiceescritura < 105){ // si el indice es menor al tamaño máximo del buffer
			TX_Buffer[TX_indiceescritura] = s[indice]; //Guardar caracter en buffer
			TX_indiceescritura++;
		}
		indice++;
	}
	hayString = 1; //Activo flag
	SerialPort_TX_Interrupt_Enable(); // Activo interrupción de transmisión
}

char UART_hayComando(){
	return nuevoComando; //Retorna si 1 si hay comando para procesar y 0 en caso contrario
}

void UART_setHayComando(){
	nuevoComando=0; // Setea el valor de nuevo comando en 0
}

char* UART_getComando(){
	return RX_Buffer; //Retorna la cadena de caracteres del comando ingresado
}

ISR(USART_RX_vect){
	dato = UDR0;
	nuevoDato = 1; // Activa el indicador de nuevo dato
	// El resto del código ISR sigue igual
}

ISR(USART_UDRE_vect){
	if(hayString){ // Si hay cadena para transmitir
		if (TX_indicelectura<TX_indiceescritura){ //si sigue habiendo datos
			SerialPort_Send_Data(TX_Buffer[TX_indicelectura]); //Envio dato
			TX_indicelectura++;
		}
		else {
			hayString = 0; // Termino de transmitir
			TX_indicelectura = 0;
			TX_indiceescritura = 0;
			SerialPort_TX_Interrupt_Disable(); //Deshabilitar interrupción de transmisión
		}
	}
}