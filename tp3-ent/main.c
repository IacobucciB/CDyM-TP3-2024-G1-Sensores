#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>
#include "dht11.h"

int main(void)
{

	while(1)
	{
		DHT11_start();
		_delay_ms(1000);
	}
	return 0;
}


