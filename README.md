# Proyecto_Estación Meteorológica Interactiva 
Proyecto de Evaluación Primer Parcial: Estación Meteorológica Interactiva

En el siguiente proyecto se realizo un circuito que permitiera medir temperatura, humedad y intensidad de luz, mediante un sensor DTH11 y un LDR, esto con el fin de mandar los datos de lectura a un monitor serial, en java swing.

Para el caso especifico de que la humedad o la temperatura excedieran de un umbral establecido, entonces un ventiolador de 5V, se encenderia, este debe de ser controlado mediante PWM para incrementar o dismunuir su velocidad, segun ell excedente.

El trabajo se dividio en dos partes, basicamente, la elaboracion del circuito, y la elaboracion del codigo.

EL CODIGO
en el caso del codigo se determinaron los pines virtuales en donde se controlarian los distintos sensores, y el transistor para el ventidalor, ademas de la conexion de la pantalla LCD.
En nuestro caso el DHT se coloco en el pin digital 10, el transistor al pin digital 6, y 3 leds a los pines 7, 8 y 9, estos Leds utilizados para verificar que el ventilador y el sistema esten encendidos, o en su defecto apagados.
Dentro del codigo se inicializaron variables tipo float para almacenar las lecturas de temperatura y humedad, y una variable tipo Int para la intensidad de luz.
Los datos leidos se enviaron mediante el codigo String.Print(); para que puedan ser recibidos por el monitor virtual en java Swing



EL CIRCUITO

El circuito esta comprendido por:
-Arduino Uno 
-Sensor de temperatura y humedad (DHT11 )
-Sensor de luz 
-Display LCD 16x2
-Resistencias y cables de conexión
-Transistor NPN (2N2222)
-Ventilador de 5V.
-Diodo
- Resistencias de 1k, 150, y 10k
- Potenciometro (para el display )
- LED`s(para indicar el estado del sistema)


Las conexiones fueron las siguientes: 

1. Sensor DHT11
   - Pin de Datos al pin digital 10.
   - VCC: Conectar a 5V de Arduino.
   - GND: Conectar a GND de Arduino.

2. Sensor de Luz (LDR)
   - Un extremo a 5V.
   - El otro extremo entre A0 y GND, pasndo por una resitencia de 10k.

3. Display LCD 
- VSS: GND 
VDD: 5V del Arduino
V0: Potenciómetro 
RS: pin 12)
RW: GND
E:  pin 11
D4: pin 5
D5: pin 4
D6: pin 3
D7: pin 2
A: a 5V 
K: GND 

4. Ventilador/LED (controlado por PWM)
     - *Base: Al pin 6 de Arduino a través de una resistencia de 1kΩ
     - *Colector: Al negativo del ventilador.
     - *Emisor: Conectar a GND.
   - positivo del ventilador a 5V.
   - 
5. *LED Indicador*
-Led 1: Al pin 8 y a tierra pasando por una resistencia de 150.
-Led 2: Al pin  9 y a tierra pasando por una resistencia de 150.
-Led 3: Al in 7 y a tierra pasando por una resistencia de 150.


