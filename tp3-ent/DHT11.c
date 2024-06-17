
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


int DHT11_bits(){
	int cant;
	int i;
	int valor=0;
	for(i=0; i<8; i++){
		cant=0;  //cantidad de us transcurridos
		while(PINC & (1<<PINC0));  //Esperar que el sensor ponga en bajo la señal
		while((PINC & (1<<PINC0))==0); //Eperar que el sensor suba la señal 
		while(PINC & (1<<PINC0)){  //Mietras la señal este en alto
			_delay_us(1); 
			cant++; 
		}
		if(cant < 29) //Si pasaron menos de 29us es un "0"
			valor = (valor<<1);
		else //sino es un "1"
			valor = (valor<<1)|(0x01);
	}
	return valor;
}

void DHT11_obtenerDatos(int *temperatura,int *temperatura_decimal, int *humedad, int *humedad_decimal){
	int sum=0;

	DHT11_startSignal_y_respuesta();
	
	//Empieza la transmision de datos
	
	*humedad=DHT11_bits();
	*humedad_decimal=DHT11_bits();
	*temperatura=DHT11_bits();
	*temperatura_decimal=DHT11_bits();
	sum=DHT11_bits();
}
	