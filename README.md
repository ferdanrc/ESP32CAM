# ESP32CAM
 Repositorio para los programas en los que se utiliza el ESP32
 
Requisitos
 - ESP32 CAM con la cámara colocada
 - Módulo FTDI
 Conecciones:
 FTDI     -    ESP32CAM
 Vcc      -    Vcc
 GND      -    GND
 Rx       -    UOT
 Tx       -    OUR
 
 Para programar (subir un programa) el ESP32CAM conectar:
 GPIO0 -> GND
 
 - Haber realizado la instalación de los drivers FTDI
 - IDE Arduino e instalar la placa del ESP32 (Boards Manager)

Guias
Instalación de los drivers FTDI: 
IDE de Arduino y ESP32: 



Funcionamiento
EjCameraWebServer: Habilita la camara del ESP32 para que sea visible en una red
ESP32_Ej_Wifi: Prueba la conección a la red y prende LEDs


*** IMPORTANTE ***
Sustituir siempre en cada programa en las siguientes lineas con la informacion de la red a utilizar
const char* ssid = "**";
const char* password = "**";

Autoria
Fernando Daniel Ramirez
 
