/*
// 온도 센서 실습
void setup() {
  Serial.begin(9600);
}

void loop() {
  int volt = analogRead(A0);
  int temp = 5.0 * volt * 100.0 / 1024;
  Serial.print(temp);
  Serial.println("℃");
  delay(1000);
}
*/

/*
// 온습도 센서 실습
#include <DFRobot_DHT11.h>
#define DHT11_PIN 5

DFRobot_DHT11 DHT; // 인스턴스 생성

void setup(){
  Serial.begin(9600);
  Serial.println("DHT11 test!");
}

void loop(){
  DHT.read(DHT11_PIN);
  Serial.print("Humidity : ");
  Serial.print(DHT.humidity);
  Serial.print("%   ");
  Serial.print("Temperature : ");
  Serial.print(DHT.temperature);
  Serial.println("℃");
  delay(1000);
}
*/

// 미니프로젝트 5 : 온도를 RGB LED로 표시하기
#include <DFRobot_DHT11.h>
#define DHT11_PIN 5

DFRobot_DHT11 DHT; // 인스턴스 생성

int led_R = 10;
int led_G = 9;
int led_B = 8;

void setup() {
  Serial.begin(9600);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(led_B, OUTPUT);
}
/*
void loop() {
  DHT.read(DHT11_PIN);
  
  int temp = DHT.temperature;
  Serial.print("temp : ");
  Serial.println(temp);

  // RGB LED 모듈에 표시
  if(temp >= 27){
    digitalWrite(led_R, HIGH);
    digitalWrite(led_G, LOW);
    digitalWrite(led_B, LOW);
  }
  else {
    digitalWrite(led_R, LOW);
    digitalWrite(led_G, LOW);
    digitalWrite(led_B, HIGH);
  }
  delay(1000);
}
*/

void loop() {
  DHT.read(DHT11_PIN);
  
  int humi = DHT.humidity;
  Serial.print("humidity : ");
  Serial.println(humi);

  // RGB LED 모듈에 표시
  if(humi >= 90){
    digitalWrite(led_R, HIGH);
    digitalWrite(led_G, LOW);
    digitalWrite(led_B, LOW);
  }
  else {
    digitalWrite(led_R, LOW);
    digitalWrite(led_G, LOW);
    digitalWrite(led_B, HIGH);
  }
  delay(1000);
}
