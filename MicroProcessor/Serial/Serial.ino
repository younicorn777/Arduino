#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  if(Serial.available())
  mySerial.write(Serial.read());

  if(mySerial.available())
  Serial.write(mySerial.read());
}
/*
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()){
    char a;
    a = Serial.read();
    Serial.println(a);
  }
}
*/