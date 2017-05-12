#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN D2 // what pin we're connected to
#define DHTTYPE DHT22 // DHT 22 


//setRainsensor
int rainsense= 0; // analog sensor input pin 0
int buzzerout= 10; // digital output pin 10 - buzzer output

//config wifi
const char* ssid = "PAINAIMA"; // wifi ssid
const char* password = "0805205425"; // wifi้ password

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
  HTTPClient http;
  int httpCode;
  String response,url;
  if (!client.connected()) {
    reconnect();
  }//if not connect

   //humi sensor & temp sensor
   int h = dht.readHumidity();//humi
   int t = dht.readTemperature();//temp
   String sensorHumi = "H1,"+String(h);
   String sensorTemp = "T1,"+String(t);
   client.publish(topic,(char *)sensorHumi.c_str());
   client.publish(topic,(char *)sensorTemp.c_str());
   Serial.println(sensorHumi);
   Serial.println(sensorTemp);
   delay(5000);
    //Humi to azure
    url="http://keppa.azurewebsites.net/record?id=H1&value="+String(h);
    http.begin(url);
    httpCode = http.GET();
    if(httpCode == HTTP_CODE_OK)
  {
      Serial.print("HTTP response code ");
      Serial.println(httpCode);
      response = http.getString();
      Serial.println(response);
      delay(5000);
  } else{
    Serial.println("Error in HTTP request");
  }
  //Temp to azure
  url="http://keppa.azurewebsites.net/record?id=T1&value="+String(t);
  http.begin(url);
  httpCode = http.GET();
  if(httpCode == HTTP_CODE_OK)
  {
      Serial.print("HTTP response code ");
      Serial.println(httpCode);
      response = http.getString();
      Serial.println(response);
      delay(5000);
  } else{
    Serial.println("Error in HTTP request");
  }
  //sensorlight
  int sensorValue = analogRead(A0);//light
  String sensorLight = "L1,"+String(sensorValue);
  client.publish(topic,(char *)sensorLight.c_str());
  Serial.println(sensorLight);
  delay(5000);
  //Light to azure
  url="http://keppa.azurewebsites.net/record?id=L1&value="+String(sensorValue);
  http.begin(url);
  httpCode = http.GET();;
  if(httpCode == HTTP_CODE_OK)
  {
    Serial.print("HTTP response code ");
    Serial.println(httpCode);
    response = http.getString();
    Serial.println(response);
    delay(5000);
   } else
   {
    Serial.println("Error in HTTP request");
   }
      
  //rainsensor
   String TF="0"; // counter value starting from 0 and goes up by 1 every second
   int rainSenseReading = analogRead(rainsense);//rain
   if (rainSenseReading <= 700){ 
      TF="1";
      String sensor = "R1,"+TF;
      client.publish(topic,(char *)sensor.c_str());
      Serial.println(rainSenseReading);
   }
   else if(rainSenseReading > 700){
    String sensor = "R1,"+TF;
    client.publish(topic,(char *)sensor.c_str());
    Serial.println(rainSenseReading);
    }
    delay(5000);
    //Rain to azure
    url="http://keppa.azurewebsites.net/record?id=R1&value=1";
    http.begin(url);
    httpCode = http.GET();
    if(httpCode == HTTP_CODE_OK)
  {
      Serial.print("HTTP response code ");
      Serial.println(httpCode);
      response = http.getString();
      Serial.println(response);
      delay(5000);
  } else{
    Serial.println("Error in HTTP request");
  }
  delay(5000);
  http.end();

    delay(5000);
    client.loop();
}
