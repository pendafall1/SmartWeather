
void setup() {
  Serial.begin(115200);
 // Serial.begin(9600, SERIAL_8N1,RXD0,TXD0);
  // put your setup code here, to run once:

}

void loop() {
  if(Serial.available()){
    Serial.println("donnée recu:");
    Serial.write(Serial.read());
  }
  
//  Serial.println(Serial2.readString());
  delay(1000);
  // put your main code here, to run repeatedly:

}
