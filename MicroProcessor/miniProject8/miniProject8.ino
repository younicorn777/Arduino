/*
// 사운드 센서 실습
int led = 9;
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A2);
  int adjust = map(value, 0, 1023, 0, 255);
  analogWrite(led, adjust);
  Serial.println(led, adjust);
  Serial.println(value);
  delay(100);
}
*/
/*
// PIR 센서 실습
int LED = 8;
int PIR = 7;
int state = 0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  Serial.begin(9600);
}

void loop(){
  state = digitalRead(PIR);
  digitalWrite(LED, LOW);

  if(state == 0){
    Serial.println("ON");
    digitalWrite(LED,HIGH);
  }
  else{
    Serial.println("OFF");
    digitalWrite(LED,LOW);
  }

  delay(100);
}
*/

/*
// 전역 변수 설정 (핀 번호)
int PIR_PIN = 7;      // PIR 센서 핀
int SOUND_PIN = A1;   // 사운드 센서 핀
int TEMP_PIN = A0;    // 온도 센서 핀
int LED_R = 5;        // 적색 LED 핀
int BUZZER_PIN = 9;   // 버저 핀

float BASE_TEMP = 25.0;     // 기준 온도
float TEMP_THRESHOLD = 3.0; // 온도 변화 허용 범위 
int SOUND_THRESHOLD = 500;  // 소리 크기 임계값 


// 전역 변수 설정 (센서 값 저장)
float currentTemp;
int soundLevel;
int motion;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("--- 침입 감지 시스템 시작 ---");
  
  // 초기 상태 설정
  digitalWrite(LED_R, LOW);
  noTone(BUZZER_PIN);
}

// 아날로그 값을 섭씨 온도로 변환 (TMP36 기준)
float readTemperature() {
  float voltage = analogRead(TEMP_PIN) * (5.0 / 1024.0);
  float temperatureC = (voltage - 0.5) * 100;
  return temperatureC;
}

// 경보 작동 함수: LED 빠르게 점멸 및 버저음
void alarm_on() {
  // LED와 버저를 짧은 간격으로 켜고 끄며 빠른 경보음을 만듭니다.
  digitalWrite(LED_R, HIGH);
  tone(BUZZER_PIN, 1800, 50); // 1800Hz 주파수로 50ms간 소리
  delay(50);
  
  digitalWrite(LED_R, LOW);
  delay(50);
}

void loop() {
  // 1. 센서 값 읽기 및 전역 변수에 저장
  currentTemp = readTemperature();
  soundLevel = analogRead(SOUND_PIN);
  motion = digitalRead(PIR_PIN); 

  // 2. 침입 판단 조건 검사 (OR 조건)
  bool isTempChange = (currentTemp > BASE_TEMP + TEMP_THRESHOLD || currentTemp < BASE_TEMP - TEMP_THRESHOLD);
  bool isLoudSound = (soundLevel > SOUND_THRESHOLD);
  bool isMotion = (motion == HIGH); 

  // 3. 경보 실행 로직
  if (isTempChange || isLoudSound || isMotion) {
    alarm_on(); // 셋 중 하나라도 감지되면 경보 실행
  } 
  else {
    // 평상시 상태
    digitalWrite(LED_R, LOW); // LED 끔
    noTone(BUZZER_PIN);       // 버저 끔
    delay(100); 
  }
}
*/

// 미니프로젝트
#include <DFRobot_DHT11.h>
#define DHT11_PIN 6
DFRobot_DHT11 DHT; // 인스턴스 생성

int PIR_PIN = 7;      // PIR 센서 핀
int SOUND_PIN = A1;   // 사운드 센서 핀
int LED_R = 5;        // 적색 LED 핀
int BUZZER_PIN = 9;   // 버저 핀

int SOUND_THRESHOLD = 14;  // 소리 크기 임계값 (0~1023 사이)

int soundLevel;
int motion;
int temp;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("--- 침입 감지 시스템 시작 ---");
  
  // 초기 상태 설정
  digitalWrite(LED_R, LOW);
  noTone(BUZZER_PIN);
}

// 경보 작동 함수: LED 빠르게 점멸 및 버저음
void alarm_on() {
  digitalWrite(LED_R, HIGH);
  tone(BUZZER_PIN, 1800, 50); 
  delay(50);
  
  digitalWrite(LED_R, LOW);
  delay(50);
}

void loop() {
  // 1. 센서 값 읽기 및 전역 변수에 저장
  DHT.read(DHT11_PIN);
  soundLevel = map(analogRead(SOUND_PIN), 0, 1023, 0, 255);
  motion = digitalRead(PIR_PIN); 
  temp = DHT.temperature;

  // 2. 침입 판단 조건 검사 (OR 조건: 둘 중 하나라도 참이면 경보)
  bool isLoudSound = (soundLevel > SOUND_THRESHOLD);
  bool isMotion = (motion == HIGH); // PIR 센서는 동작 감지 시 HIGH(1)
  bool isTemp = (temp > 27);

  // 3. 경보 실행 로직 : 둘 중 하나라도 감지되면 경보 실행
  if (isLoudSound || isMotion || isTemp) {
    alarm_on();
    
    Serial.print("감지! Sound:"); Serial.print(soundLevel); 
    Serial.print(", Motion:"); Serial.println(motion);
    Serial.print("temp : "); Serial.println(temp);
  } 
  else {
    // 평상시 상태
    digitalWrite(LED_R, LOW); // LED 끔
    noTone(BUZZER_PIN);       // 버저 끔
    delay(100); 
  }
}
