# ESP32CAM_MQTT-Basic
Este repositorio contiene el programa básico para conectar el ESP32CAM a MQTT, enviar y recibir mensajes.

Puedes encontrar el curso correspondiente a este ejercicio en el siguiente enlace.

https://edu.codigoiot.com/

### Requisitos
Para que el código de este repositorio funcione, es necesario contar con lo siguiente:

- ESP32CAM AI-Thinker
- Camara OV2640
- Programador FTDI con su cable
- Ubuntu 20.04
- IDE de Arduino 1.8 o superior
- Biblioteca PubSubClient para Arduino IDE
- Broker Mosquitto funcionando de forma local en el puerto 1883
- NodeRed corriendo de forma local en el puerto 1880
- Nodos Dashboard para NodeRed

### Guías
Para configurar correctamente la IDE de Arduino para trabajar con el ESP32CAM, puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=850

Para configurar correctamente tu broker mosquitto puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=818

Para configurar correctamente NodeRed puedes consultar el siguiente enlace.

https://edu.codigoiot.com/course/view.php?id=817

Puedes obtener la biblioteca PubSubClient desde el siguiente enlace.

https://github.com/knolleary/pubsubclient

El flow de NodeRed lee en el tema `esp32/data` y publica en el tema `esp32/output`, por lo que deberás configurar los nodos MQTT para conectarse a estos temas y al broker de tu elección.

Los nodos switch y text de la sección dashboard deberán tener correctamente configurados el tab y group en el que se visualizarán.

### Funcionamiento

Para observar el funcionamiento de este proyecto deberás realizar lo siguiente.

1. Carga el flow MQTT+ESP32CAM-Basic.json en NodeRed.
2. Comprueba que el broker MQTT esté funcionando.
3. Carga el programa ES2CAM_MQTT-Basic.ino en el ESP32CAM.
4. Visita el dashboard de NodeRed

![](https://github.com/codigo-iot/ESP32CAM_MQTT-Basic/blob/main/esp32camMQTTbasic.jpg)

Podrás observar una cuenta progresiva, la cual envía el prográma base del ESP32CAM. Puedes controlar el led flash del ESP32CAM con el switch del dashboard.

Por: [Hugo Vargas](https://github.com/hugoescalpelo)
