# ESP32CAM

 Repositorio para los programas en los que se utiliza el ESP32 en el curso. 
 
----------------------------------------------------------------------------------------------------

### Requisitos

 - ESP32 CAM con la cámara colocada
 - Módulo FTDI

 Conecciones entre ESP32 y el módulo FTDI para subir programas:

 FTDI-----ESP32CAM

 Vcc------Vcc
 
 GND------GND
 
 Rx-------UOT
 
 Tx-------OUR
 
 Para programar (subir un programa) el ESP32CAM conectar:
 
 GPIO0 -> GND
 
 - Instalar los drivers FTDI
 - Instalar IDE Arduino e instalar la placa ESP32 (Boards Manager)
 - Instalar MQTT Mosquitto
 - Instalar NodeRed y probar sobre un broker público
 
Adicionalmente
 - Instalar libreria PubSubClient en IDE Arduino (para protocolo MQTT)
 - Instalar libreria para sensores dht en IDE Arduino y dependencias ("DHT sensor library" de Adafruit)
 
Revisar
 - La direccion del broker a usar, tanto en el programa de Arduino como en NodeRed. 

----------------------------------------------------------------------------------------------------

### Guias

Drivers FTDI: https://edu.codigoiot.com/course/view.php?id=850

IDE de Arduino y ESP32: https://edu.codigoiot.com/course/view.php?id=850

MQTT Mosquitto: https://edu.codigoiot.com/course/view.php?id=818

NodeRed: https://edu.codigoiot.com/course/view.php?id=817

Libreria PubSubClient: https://edu.codigoiot.com/course/view.php?id=852

Ejemplo dht11: https://programarfacil.com/blog/arduino-blog/sensor-dht11-temperatura-humedad-arduino/

También revisar los repositorios, ya que de ellos se tomaron los códigos de este repositorio: 

https://github.com/codigo-iot/Estructura_Basica

https://github.com/codigo-iot/ESP32CAM-Flash

https://github.com/codigo-iot/ESP32CAM-WiFi-Basic

https://github.com/codigo-iot/ESP32CAM_MQTT-Basic

----------------------------------------------------------------------------------------------------

### Funcionamiento

27-julio-2021: EjCameraWebServer: Habilita la camara del ESP32 para que sea visible en una red

29-julio-2021: ESP32_Ej_Wifi: Prueba la conección a la red y prende LEDs

31-julio-2021: ESP32CAM_MQTT-Basic: Conecta el ESP32 utilizando el protocolo MQTT

5-agosto-2021: ESP32CAM_MQTT-Temperatura: Envía mediciones de temperatura y humedad con el ESP32 utilizando el protocolo MQTT. 


*** IMPORTANTE ***

Sustituir siempre en cada programa de Arduino en las siguientes lineas con la informacion de la red a utilizar. 

const char* ssid = "**"; // Aquí debes poner el nombre de tu red

const char* password = "**"; // Aquí debes poner la contraseña de tu red

----------------------------------------------------------------------------------------------------

### Notas adicionales

Sobre el programa ESP32CAM_MQTT-Basic:

 - Para este programa se agrega el archivo MQTT+ESP32CAM-Basic.json para importarse e implementar en Nodered

 - Linea 149: Si hay varios usuarios que acceden al mismo broquer, usar diferentes ID para recibir los datos correspondientes.
 - Modificar las lineas similares a la 102 si se quiere publicar a otro tema, lo mismo para la línea 151

Sobre el programa ESP32CAM_MQTT-Temperatura:

 - Para este programa se agrega el archivo MQTT+ESP32CAM-Temperatura.json para importarse e implementar en Nodered

Mismas observaciones que en el programa ESP32CAM_MQTT-Basic para el ID y tema. 


Por: Fernando Daniel Ramirez
