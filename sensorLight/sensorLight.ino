void setup() {
 Serial.begin(9600);
}

void loop() {
 int sensorValue = analogRead(A0);
 Serial.println(sensorValue);
 delay(10000); 
 // เพราในระยะเวลา 10 ว แสงอาจเปลี่ยนแปลงไปไม่มาก 
 // และเพื่อไม่ให้ข้อมูลเยอะจนเกินความจำเป็น
}
