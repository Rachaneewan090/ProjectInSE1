#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN D2 // what pin we're connected to
#define DHTTYPE DHT22 // DHT 22 
#define PIN A0 //for light sensor

//setRainsensor
int rainsense= 0; // analog sensor input pin 0
int buzzerout= 10; // digital output pin 10 - buzzer output
int countval= 0; // counter value starting from 0 and goes up by 1 every second

//config wifi
const char* ssid = "racha"; // wifi ssid
const char* password = "qwertyuiop"; // wifi้ password

// Config MQTT Server
const char * topic = "keppa"; // name fo topic 
char message_buff[100];
#define mqtt_server "mean.psu.ac.th" // server
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
      //client.publish(topic, "hello world");
      // ... and resubscribe
      client.subscribe(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }//else
  }//while
}//reconnect

void loop() {
   int h = dht.readHumidity();
   int t = dht.readTemperature();
   int sensorValue = analogRead(A0);
   int rainSenseReading = analogRead(rainsense);

   String TF = "false";
   String sensorHumi = "H1,"+String(h);
   String sensorTemp = "T1,"+String(t);
   String sensor = "L1,"+String(sensorValue);

    if (!client.connected()) {
    reconnect();
    }//if not connect

    // from heavy rain - no rain.
   if (rainSenseReading <= 700){ 
      TF="True";
      String sensor = "R1,"+TF;
      client.publish(topic,(char *)sensor.c_str());
   }
   else if(rainSenseReading > 700){
    String sensor = "R1,"+TF;
    client.publish(topic,(char *)sensor.c_str());
    }
    client.publish(topic,(char *)sensorHumi.c_str());
    client.publish(topic,(char *)sensor.c_str());
    client.publish(topic,(char *)sensorTemp.c_str());
    delay(10000);
    client.loop();
}
