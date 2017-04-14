#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN D2 // what pin we're connected to
#define DHTTYPE DHT11 // DHT 11 

//config wifi
const char* ssid = "ARADA"; // wifi ssid
const char* password = "0815350228"; // wifi้ password

// Config MQTT Server
const char * topic = "keppa"; // name fo topic 
char message_buff[100];
#define mqtt_server "broker.hivemq.com" // server
#define mqtt_port 1883   // เลข port
#define mqtt_user "555555666777" // user
#define mqtt_password "" // password

// MQTT Server address
WiFiClient keppa;
PubSubClient client(keppa);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(9600); 
Serial.println("DHTxx test!");
dht.begin();
WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }//while
  // จบการเชื่อมต่อ network
  
  if (client.connect("555555666777")) {
    client.publish(topic,"Keppa si!!!");
    client.subscribe(topic);
    }
    client.setServer(mqtt_server, mqtt_port); // เชื่อมต่อ mqtt server
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("555555666777")) {
    Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish(topic, "hello world");
      // ... and resubscribe
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }//else
  }//while
}//reconnect

void loop() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   delay(10000);
   String sensorHumi = "Humi,"+String(h);
   String sensorTemp = "Temp,"+String(t);
   
if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }

  if (!client.connected()) {
    reconnect();
  }//if not connect
  
    client.publish(topic,(char *)sensorHumi.c_str());
    delay(5000);

    client.publish(topic,(char *)sensorTemp.c_str());
    delay(5000);
    client.loop();
}