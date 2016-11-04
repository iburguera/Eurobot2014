/*--------------------------------------------------------------------*/
/*--            Comunicacion Android-Arduino Bluetooth              --*/
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
/*--  Proyecto:   Proyecto Comunicacion Android-Arduino Bluetooth   --*/
/*--  Autor   :   MammothBusters                                    --*/
/*--  Email   :   mammothbusters@googlegroups.com                   --*/
/*--  Date    :   02/12/2013                                        --*/
/*--  Version :   1.0                                               --*/
/*--------------------------------------------------------------------*/


#include <SoftwareSerial.h>                                                                      // Incluimos la librería Serial

#define  pinRX  10                                                                               // Definimos el pin 10 que utilizaremos para recibir los datos
#define  pinTX   9                                                                               // Definimos el pin  9 que utilizaremos para enviar datos si fuera necesario

SoftwareSerial mySerial(pinRX, pinTX);                                                           // Creamos el objeto mySerial donde establecemos los pines de TX y RX 

String datos = "";                                                                               // Variable donde guardaremos los valores recibidos por Bluetooth. 
                                                                                                 // Los mensajes se separan con un \n en cada envio
                                    
void setup() 
{
   Serial.begin(9600);                                                                           // Empezamos las comunicacion serial en ARDUINO a 9600 Baudios
   Serial.println("Introduce comandos AT!");                                                     // Mostramos este mensaje si quieremos introducir comandos AT para configurar el dispositivo Bluetooth (Cambiar nombre, PIN, etc) 
   mySerial.begin(9600);                                                                         // Empezamos comunicacion serial entre ARDUINO y el MODULO BLUETOOTH a 9600 Baudios (Por defecto el modulo JY-MCU viene a 9600b)
}

void loop()
{
   if (mySerial.available())                                                                     // Miramos si existe algún dato en el buffer de entrada serial del Modulo Bluetooth
   {
     while(mySerial.available())                                                                 // Mientras existan datos por leer, seguimos leyendo
     { 
       datos += (char)mySerial.read();                                                           // Convertimos los datos obtenido por Serial en caracteres y lo agregamos a la cadena String datos
     } 
     Serial.println(datos);                                                                    // Ya no quedan más datos por leer en la linea Serial, por lo tanto lo imprimimos por pantalla
     datos = "";                                                                                 // Limpiamos la cadena datos para que no se acumulen los datos
   }
   

   if (Serial.available())                                                                       // Miramos si existe algún dato en el buffer de entrada serial Arduino para introducir los commandos AT 
   {
       delay(80);                                                                                // Metemos un pequeño delay
       mySerial.write(Serial.read());                                                            // Escribimos en el Serial del Modulo Bluetooth lo que hemos leido en el Serial de Arduino (Escribir comandos AT)
   }
   
   delay(80);                                                                                    // Metemos un pequeño delay para no saturarlo
}
