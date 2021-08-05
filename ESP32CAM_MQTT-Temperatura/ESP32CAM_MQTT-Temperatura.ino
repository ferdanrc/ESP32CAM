/*
 * Medicion de temperatura con el ESP32 por MQTT del NodeMCU
 * por: Fernando Daniel Ramirez basado en el programa de comunicacion basica realizado por Hugo Escalpelo
 * Fecha: 5 de agosto de 2021
 * 
 * Este programa envía las mediciones del sensor dht11 por Internet a través del protocolo MQTT. Para poder 
 * comprobar el funcionamiento de este programa, es necesario conectarse a un broker y usar NodeRed para 
 * visualizar que la información se está recibiendo correctamente.
 * Este programa requiere del sensor dht11 conectado al ESP32. 
 * 
 * Componente     PinESP32CAM     Estados lógicos
 * ledStatus------GPIO 33---------On = LOW, Off = HIGH
 * ledFlash-------GPIO 4----------On = HIGH, Off = LOW
 * dht11----------GPIO 12---------comunicacion por libreria dht11
 */

//Bibliotecas y definiciones
#include <WiFi.h>  // Biblioteca para el control de WiFi
#include <PubSubClient.h> //Biblioteca para conexion MQTT

#include "DHT.h" // Biblioteca del sensor DHT

#define DHTPIN 12 // Se define el sensor DHT en el pin 12
#define DHTTYPE DHT11 // Define el tipo del sensor como DHT11

DHT dht(DHTPIN, DHTTYPE); // Inicializa el pin DHT

//Datos de WiFi
const char* ssid = "**";  // Aqui debes poner el nombre de tu red
const char* password = "**";  // Aqui debes poner la contraseña de tu red

//Datos del broker MQTT
const char* mqtt_server = "3.66.119.222"; // Si estas en una red local, coloca la IP asignada, en caso contrario, coloca la IP publica
// Para ubicar la ip, ejecutar en una terminal nslookup broker.hivemq.com y colocar ip publica o privada
IPAddress server(3,66,119,222);

// Objetos
WiFiClient espClient; // Este objeto maneja los datos de conexion WiFi
PubSubClient client(espClient); // Este objeto maneja los datos de conexion al broker

// Variables
int flashLedPin = 4;  // Para indicar el estatus de conexión
int statusLedPin = 33; // Para ser controlado por MQTT
long timeNow, timeLast; // Variables de control de tiempo no bloqueante
float data = 0; // Contador
int wait = 5000;  // Indica la espera cada 5 segundos para envío de mensajes MQTT

// Inicialización del programa
void setup() {
  // Iniciar comunicación serial
  Serial.begin (115200);
  pinMode (flashLedPin, OUTPUT);
  pinMode (statusLedPin, OUTPUT);
  digitalWrite (flashLedPin, LOW); 
  digitalWrite (statusLedPin, HIGH);

  Serial.println();
  Serial.println();
  Serial.print("Conectar a ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password); // Esta es la función que realiz la conexión a WiFi
 
  while (WiFi.status() != WL_CONNECTED) { // Este bucle espera a que se realice la conexión
    digitalWrite (statusLedPin, HIGH);
    delay(500); //dado que es de suma importancia esperar a la conexión, debe usarse espera bloqueante
    digitalWrite (statusLedPin, LOW);
    Serial.print(".");  // Indicador de progreso
    delay (5);
  }
  
  // Cuando se haya logrado la conexión, el programa avanzará, por lo tanto, puede informarse lo siguiente
  Serial.println();
  Serial.println("WiFi conectado");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  // Si se logro la conexión, encender led
  if (WiFi.status () > 0){
  digitalWrite (statusLedPin, LOW);
  }
  
  delay (1000); // Esta espera es solo una formalidad antes de iniciar la comunicación con el broker

  // Conexión con el broker MQTT
  client.setServer(server, 1883); // Conectarse a la IP del broker en el puerto indicado
  client.setCallback(callback); // Activar función de CallBack, permite recibir mensajes MQTT y ejecutar funciones a partir de ellos
  delay(1500);  // Esta espera es preventiva, espera a la conexión para no perder información

  timeLast = millis (); // Inicia el control de tiempo

  // Mensaje para probar la conexion del sensor DHT
  //Serial.println(F("Prueba de conexion a sensor dht"));

  dht.begin();
  
}// fin del void setup ()

// Cuerpo del programa, bucle principal
void loop() {
  //Verificar siempre que haya conexión al broker
  if (!client.connected()) {
    reconnect();  // En caso de que no haya conexión, ejecutar la función de reconexión, definida despues del void setup ()
  }// fin del if (!client.connected())
  client.loop(); // Esta función es muy importante, ejecuta de manera no bloqueante las funciones necesarias para la comunicación con el broker

  timeNow = millis(); // Control de tiempo para esperas no bloqueantes
  if (timeNow - timeLast > wait) { // Manda un mensaje por MQTT cada cinco segundos
    timeLast = timeNow; // Actualización de seguimiento de tiempo
    
    publicar_info(); // Publica la informacion utilizando mqtt
    
  }// fin del if (timeNow - timeLast > wait)
}// fin del void loop ()

// Funciones de usuario

// Funcion que publica la informacion que se quiere enviar a la red utilizando mqtt
void publicar_info(){
  data++; // Incremento a la variable para ser enviado por MQTT
  publicar_mqtt(data,"Contador: ","esp32/datafdrc"); // Envio del numero de dato a enviar

  float t = dht.readTemperature(); // Se lee del sensor la temperatura en grados centigrados
  float f = dht.readTemperature(true); // Se lee del sensor la temperatura en grados fahrenheit
  float h = dht.readHumidity(); // Se lee del sensor la humedad relativa

  // Si alguno en alguno de los parametros no hay lectura del sensor, es porque el sensor no esta conectado
  if ( isnan(t) || isnan(f) || isnan(h)) {
    Serial.println(F("Sensor dht no encontrado"));
  }
  else
  {
    // En caso de haber obtenido las lecturas, realizar el envio de datos utilizando mqtt
    publicar_mqtt(t,"Temperatura °C: ","esp32/datafdrc/temperatura_c");
    publicar_mqtt(f,"Temperatura °F: ","esp32/datafdrc/temperatura_f");
    publicar_mqtt(h,"Humedad: ","esp32/datafdrc/humedad");
  }
  

}

// Funcion que publica datos en un tema utilizando mqtt, este envio tambien se envia al monitor serial para obversar lo que se envia
void publicar_mqtt(float datos,const char* label,const char* topic)
{
  char dataString[8]; // Define una arreglo de caracteres para enviarlos por MQTT, especifica la longitud del mensaje en 8 caracteres
  dtostrf(datos, 1, 2, dataString);  // Esta es una función nativa de leguaje AVR que convierte un arreglo de caracteres en una variable String
  Serial.print(label); // Se imprime en monitor solo para poder visualizar que el evento sucede
  Serial.println(dataString);
  client.publish(topic, dataString); // Esta es la función que envía los datos por MQTT, especifica el tema y el valor
}


// Esta función permite tomar acciones en caso de que se reciba un mensaje correspondiente a un tema al cual se hará una suscripción
void callback(char* topic, byte* message, unsigned int length) {

  // Indicar por serial que llegó un mensaje
  Serial.print("Llegó un mensaje en el tema: ");
  Serial.print(topic);

  // Concatenar los mensajes recibidos para conformarlos como una varialbe String
  String messageTemp; // Se declara la variable en la cual se generará el mensaje completo  
  for (int i = 0; i < length; i++) {  // Se imprime y concatena el mensaje
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }

  // Se comprueba que el mensaje se haya concatenado correctamente
  Serial.println();
  Serial.print ("Mensaje concatenado en una sola variable: ");
  Serial.println (messageTemp);

  // En esta parte puedes agregar las funciones que requieras para actuar segun lo necesites al recibir un mensaje MQTT

  // Ejemplo, en caso de recibir el mensaje true - false, se cambiará el estado del led soldado en la placa.
  // El ESP323CAM está suscrito al tema esp/output
  if (String(topic) == "esp32/outputfdrc") {  // En caso de recibirse mensaje en el tema esp32/outputfdrc
    if(messageTemp == "true"){
      Serial.println("Led encendido");
      digitalWrite(flashLedPin, HIGH);
    }// fin del if (String(topic) == "esp32/outputfdrc")
    else if(messageTemp == "false"){
      Serial.println("Led apagado");
      digitalWrite(flashLedPin, LOW);
    }// fin del else if(messageTemp == "false")
  }// fin del if (String(topic) == "esp32/outputfdrc")
}// fin del void callback

// Función para reconectarse
void reconnect() {
  // Bucle hasta lograr conexión
  while (!client.connected()) { // Pregunta si hay conexión
    Serial.print("Tratando de contectarse...");
    // Intentar reconexión
    if (client.connect("ESP32CAMClient")) { //Pregunta por el resultado del intento de conexión
      Serial.println("Conectado");
      client.subscribe("esp32/outputfdrc"); // Esta función realiza la suscripción al tema
    }// fin del  if (client.connect("ESP32CAMClient"))
    else {  //en caso de que la conexión no se logre
      Serial.print("Conexion fallida, Error rc=");
      Serial.print(client.state()); // Muestra el codigo de error
      Serial.println(" Volviendo a intentar en 5 segundos");
      // Espera de 5 segundos bloqueante
      delay(5000);
      Serial.println (client.connected ()); // Muestra estatus de conexión
    }// fin del else
  }// fin del bucle while (!client.connected())
}// fin de void reconnect(
