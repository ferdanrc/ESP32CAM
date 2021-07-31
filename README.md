# ESP32CAM

 Repositorio para los programas en los que se utiliza el ESP32 en el curso. 
 
### Requisitos

 - ESP32 CAM con la cámara colocada
 - Módulo FTDI

 Conecciones entre ESP32 y el módulo FTDI para subir programas:

 FTDI     -    ESP32CAM
 
 ----------------------
 
 Vcc      -    Vcc
 
 GND      -    GND
 
 Rx       -    UOT
 
 Tx       -    OUR
 
 Para programar (subir un programa) el ESP32CAM conectar:
 
 GPIO0 -> GND
 
 - Instalar los drivers FTDI
 - Instalar IDE Arduino e instalar la placa ESP32 (Boards Manager)
 - Instalar MQTT Mosquitto
 - Instalar NodeRed y probar sobre un broker público
 
Adicionalmente
 - Instalar libreria PubSubClient en IDE Arduino (para protocolo MQTT)

### Guias

Drivers FTDI: https://edu.codigoiot.com/course/view.php?id=850

IDE de Arduino y ESP32: https://edu.codigoiot.com/course/view.php?id=850

MQTT Mosquitto: https://edu.codigoiot.com/course/view.php?id=818

NodeRed: https://edu.codigoiot.com/course/view.php?id=817

Libreria PubSubClient: https://edu.codigoiot.com/course/view.php?id=852


También revisar los repositorios, ya que de ellos se tomaron los códigos de este repositorio: 

https://github.com/codigo-iot/Estructura_Basica

https://github.com/codigo-iot/ESP32CAM-Flash

https://github.com/codigo-iot/ESP32CAM-WiFi-Basic

https://github.com/codigo-iot/ESP32CAM_MQTT-Basic

### Funcionamiento

27-julio-2021: EjCameraWebServer: Habilita la camara del ESP32 para que sea visible en una red

29-julio-2021: ESP32_Ej_Wifi: Prueba la conección a la red y prende LEDs

31-julio-2021: ESP32CAM_MQTT-Basic: Conecta el ESP32 utilizando el protocolo MQTT


*** IMPORTANTE ***

Sustituir siempre en cada programa de Arduino en las siguientes lineas con la informacion de la red a utilizar

const char* ssid = "**";

const char* password = "**";

Por: Fernando Daniel Ramirez
 
