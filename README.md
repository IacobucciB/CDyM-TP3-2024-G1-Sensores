# CDyM TP3 2024 Grupo 1 Sensores

Este proyecto implementa un registrador de temperatura y humedad relativa utilizando el sensor DHT11, el módulo RTC DS3231 y un microcontrolador (MCU) conectado a una PC mediante la interfaz USB. El proyecto está desarrollado utilizando Atmel Studio y Proteus.

## Contenido del Repositorio
- tp3-ent/: Contiene el proyecto completo desarrollado en Atmel Studio.
- tp3.pdsprj: Contiene el diseño del circuito en Proteus.
- README.md: Este archivo, proporcionando una visión general del proyecto y las instrucciones para su uso.

## Requerimientos del Sistema
- Sensor DHT11: Conectado al terminal PORTC 0 del MCU.
- Módulo RTC DS3231: Conectado mediante la interfaz I2C del MCU.
- Comunicación Serie UART: Para la transmisión de datos a una PC.

## Funcionalidades
- Lectura de Sensor: El MCU encuesta al sensor DHT11 para obtener medidas de temperatura y humedad relativa cada 2 segundos.
- Registro con Fecha y Hora: Utilizando el módulo RTC, el MCU agrega la fecha y hora actual a cada medida obtenida del sensor.
- Formato de Datos: Los datos se formatean para transmitir un mensaje a una terminal serie en la PC. Ejemplo de formato: TEMP: 20 °C HUM: 40% FECHA: 10/06/24 HORA:15:30:56\r\n.
- Control desde la PC: El envío de datos puede detenerse o reanudarse desde la PC presionando la tecla 's' o 'S' sucesivamente.
- Comunicación Serie Asincrónica: Implementada utilizando interrupciones de recepción y transmisión del periférico UART0.

## Instrucciones para la Instalación y Uso

### Atmel Studio
Clonar el Repositorio:

```
git clone https://github.com/IacobucciB/CDyM-TP3-2024-G1-Sensores
```
Abrir el Proyecto:
Abre el archivo del proyecto (tp3-ent.atsln) en Atmel Studio.

### Configurar el Hardware:

- Asegúrate de que el sensor DHT11 esté conectado al terminal PORTC 0 del MCU.
- Conecta el módulo RTC DS3231 a la interfaz I2C del MCU.
- Conecta el MCU a la PC mediante la interfaz USB.

### Compilar y Cargar el Código:

- Compila el proyecto en Atmel Studio.
- Carga el firmware al MCU utilizando Atmel Studio y el programador correspondiente.

### Proteus
Abrir el Diseño:
Abre el archivo del diseño (tp3.pdsprj) en Proteus.

Simulación:
Ejecuta la simulación en Proteus para verificar el funcionamiento del circuito antes de implementarlo físicamente.

## Uso del Sistema
Iniciar el Sistema:

Conecta el MCU a la PC y abre una terminal serie (por ejemplo, PuTTY o Tera Term).

Configura la terminal serie con la velocidad en baudios especificada en el código (por ejemplo, 9600 baudios).

### Visualización de Datos:

Observa los datos de temperatura y humedad junto con la fecha y hora en la terminal serie.
Presiona la tecla 's' o 'S' para detener o reanudar el envío de datos.