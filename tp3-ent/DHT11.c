
#include "DHT11.h"
#include "I2C.h"

#define DHT11_PIN PORTC0
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PIN_INPUT PINC


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
	int cant;
	uint8_t i;
	uint8_t valor=0;
	for(i=0; i<8; i++){
		cant=0;  //cantidad de us transcurridos
		while(PINC & (1<<PINC0));  //Esperar que el sensor ponga en bajo la señal
		
// 		while((PINC & (1<<PINC0))==0); //Eperar que el sensor suba la señal 
// 		
// 		while(PINC & (1<<PINC0)){  //Mietras la señal este en alto
// 			_delay_us(1); 
// 			cant++; 
// 		}
// 		if(cant < 29) //Si pasaron menos de 29us es un "0"
// 			//valor = (valor<<1);
// 			//valor |= (1 << (7 - i));
// 			_delay_us(1);
// 		else //sino es un "1"
// 			valor |= (1 << (7 - i));

		//Esperar q se ponga en alto
		while (!(DHT11_PIN_INPUT & (1 << DHT11_PIN)));

		_delay_us(29); // Espera 40 us

		// Si despues de 40 us esta:
		// -En alto: bit = 1
		// -En bajo: bit = 0
		
		//Si esta en alto
		if (DHT11_PIN_INPUT & (1 << DHT11_PIN)) {
			valor |= (1 << (7 - i)); // Establece el bit 'i' en 1
			//_delay_us(30);
			//Esperar q se ponga en bajo
			while ((DHT11_PIN_INPUT & (1 << DHT11_PIN)));
		}
	}
	return valor;
}

void DHT11_obtenerDatos(uint8_t *temperatura,uint8_t *temperatura_decimal, uint8_t *humedad, uint8_t *humedad_decimal){
	uint8_t sum=0;

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
	sum=DHT11_bits();
}
	