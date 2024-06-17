
#include "DHT11.h"


void DHT11_startSignal_y_respuesta(){
	DDRC |= (1<<PORTC0);  //Configurar como salida
	PORTC &= ~(1<<PORTC0);  //Poner en valor bajo
	_delay_ms(18); // delay de al menos 18ms
	
	
	DDRC &=~(1<<PORTC0);  // Configurar como entrada
	PORTC |=(1<<PORTC0);  // Poner en alto la señal
	
	while(PINC & (1<<PINC0));// Esperar que el sensor ponga en bajo la señal
	while((PINC & (1<<PINC0))==0);//Esperar que el sensor ponga en alto la señal
}


uint8_t DHT11_bits(){
	uint8_t cant;
	uint8_t i;
	uint8_t valor = 0;
	for(i=0; i<8; i++){
		cant = 0;  //cantidad de us transcurridos
		while(PINC & (1<<PINC0));  //Esperar que el sensor ponga en bajo la señal
		while((PINC & (1<<PINC0))==0); //Esperar que el sensor suba la señal
		while(PINC & (1<<PINC0)){  //Mientras la señal esté en alto
			_delay_us(1);
			cant++;
		}
		if (cant < 29)
		{
			valor = valor * 2;
		} 
		else
		{
			valor = valor * 2 + 1;
		}
	}
	valor = valor * 2 + 1;
	return valor;
}

void DHT11_obtenerDatos(uint8_t *temperatura,uint8_t *temperatura_decimal, uint8_t *humedad, uint8_t *humedad_decimal){
	uint8_t sum = 0;
	uint8_t checksum = 0;
	
	DHT11_startSignal_y_respuesta();
	
	//Empieza la transmision de datos
	
// 	*humedad=BcdToDec(DHT11_bits());
// 	*humedad_decimal=BcdToDec(DHT11_bits());
// 	*temperatura=BcdToDec(DHT11_bits());
// 	*temperatura_decimal=BcdToDec(DHT11_bits());
	*humedad=DHT11_bits();
	*humedad_decimal=DHT11_bits();
	*temperatura=DHT11_bits();
	*temperatura_decimal=DHT11_bits();
	checksum=DHT11_bits();
	
	*humedad_decimal = 0;
	*temperatura_decimal = 0;
/*
	sum = *humedad + *humedad_decimal + *temperatura + *temperatura_decimal;
	if (checksum !=(sum & 0xFF))
	{
		*temperatura = 0;
	}
*/
}
	