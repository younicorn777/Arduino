/*
// 초음파 센서 실습
const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW); // 초기화
  delayMicroseconds(10);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.print("Distance : ");
  Serial.println(distance);
}
*/

/*
// LCD 실습
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.begin();        // I2C LCD 초기화
  lcd.backlight();   // 백라이트 켜기
  Serial.begin(9600);
  Serial.println("LCD통신 시작");
}

void loop() {
  if (Serial.available()) {
    String a = "";
    lcd.clear();
    while (Serial.available()) {
      char b = char(Serial.read());
      if (b == '\n') break;   // 줄바꿈에서 입력 종료
      else a += b;
    }

    lcd.setCursor(0,0);       // 항상 첫 줄 첫 칸부터 출력
    if (a.length() <= 16) {
      Serial.print("입력: ");
      Serial.println(a);
      lcd.print(a);
    } else {
      Serial.println("plz 16char below");
      lcd.print("plz 16char below");
    }
  }
}
*/

// 미니프로젝트
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.println("측정 시작");

  lcd.begin();
  lcd.backlight();
}

void loop() {
  digitalWrite(trigPin, LOW); // 초기화
  delayMicroseconds(10);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("거리 : ");
  Serial.print(distance);
  Serial.println("cm");

  lcd.setCursor(2,0);
  lcd.clear(); // 없애야 될지도
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print("cm");
  delay(1000);
}
