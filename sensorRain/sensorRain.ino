/*Arduino Rain Sensor sketch*/
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

int rainsense= 0; // analog sensor input pin 0
int buzzerout= 10; // digital output pin 10 - buzzer output
int countval= 0; // counter value starting from 0 and goes up by 1 every second

//config wifi
const char* ssid = "kap"; // wifi ssid
const char* password = "asdfghjk"; // wifi้ password

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
 
void setup(){
   Serial.begin(9600);
   pinMode(buzzerout, OUTPUT);
   pinMode(rainsense, INPUT);

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

void loop(){
  if (!client.connected()) {
    reconnect();
  }
   int rainSenseReading = analogRead(rainsense);
   String TF = "false";
   Serial.println(rainSenseReading); // serial monitoring message 
   delay(1000);// rain sensing value from 0 to 1023.
   // from heavy rain - no rain.
   if (rainSenseReading <= 700){ 
      TF="True";
      String sensor = "Rain,"+TF;
      client.publish(topic,(char *)sensor.c_str());
   }
   else if(rainSenseReading > 700){
    String sensor = "Rain,"+TF;
    client.publish(topic,(char *)sensor.c_str());
    }
   delay(1000);
   client.loop();
}
