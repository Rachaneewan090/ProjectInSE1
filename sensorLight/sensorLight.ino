#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#define PIN A0

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

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to ");
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
 // client.setCallback(callback); // สร้างฟังก์ชันเมื่อมีการติดต่อจาก mqtt มา
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
 int sensorValue = analogRead(A0);
 Serial.println(sensorValue);
 delay(10000);
 String sensor = "Light,"+String(sensorValue);

 if (!client.connected()) {
    reconnect();
  }
  
 client.publish(topic,(char *)sensor.c_str());
 delay(1000);
 client.loop();
  }
