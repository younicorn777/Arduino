/*
// 실습
int led = 12;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(A1); // 전압값 읽어온다.
  Serial.println(val);

  if(val > 512) digitalWrite(led, HIGH);
  else digitalWrite(led, LOW);
  delay(1000);
}
*/


#include <DFRobot_DHT11.h>

// DHT11 온습도 센서 핀 설정
const int DHT_PIN = 5;       // DHT11 DATA 핀 (디지털 5번)
DFRobot_DHT11 DHT;           // DHT 객체 생성

// 조도 센서 (CDS) 핀 설정
const int LIGHT_SENSOR_PIN = A1; // 조도 센서 아날로그 핀 (A1)

// 출력 장치 (LED로 대체) 핀 설정
const int WATER_PUMP_LED_PIN = 12;   // 물 펌프 : 녹색 LED
const int AWNING_LED_PIN = 11;      // 차양막 : 청색 LED
const int FAN_LED_PIN = 10;         // 환풍기 : 황색 LED
const int HEATER_LED_PIN = 9;      // 난방기 : 적색 LED

// 제어 조건에 사용되는 임계값 설정(기준치 1)
const float SET_TEMP_1 = 25.0;     // [난방기] 설정온도1 (25.0°C)
const int SET_LIGHT_1 = 200;       // [차양막] 설정조도1 
const float SET_HUMIDITY_1 = 80.0; // [환풍기] 설정습도1 (70.0%)

// 물 펌프 복합 제어 조건(기준치 2)
const float SET_TEMP_2 = 20.0;     // [물 펌프] 설정온도2 (28.0°C)
const int SET_LIGHT_2 = 135;       // [물 펌프] 설정조도2 
const float SET_HUMIDITY_2 = 70.0; // [물 펌프] 설정습도2 (60.0%)


void setup() {
  Serial.begin(9600);
  Serial.println("Smart Farm Start");

  // 출력 핀 설정 (LED)
  pinMode(WATER_PUMP_LED_PIN, OUTPUT);
  pinMode(AWNING_LED_PIN, OUTPUT);
  pinMode(FAN_LED_PIN, OUTPUT);
  pinMode(HEATER_LED_PIN, OUTPUT);

  // 모든 LED 초기 Off
  digitalWrite(WATER_PUMP_LED_PIN, LOW);
  digitalWrite(AWNING_LED_PIN, LOW);
  digitalWrite(FAN_LED_PIN, LOW);
  digitalWrite(HEATER_LED_PIN, LOW);
}

/*
void loop() {
  delay(2000);

  // 센서값 읽기
  // 1. DHT11 온습도 값 읽기
  DHT.read(DHT_PIN); 
  
  // 예외 처리
  if (isnan(DHT.temperature) || isnan(DHT.humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // 성공적으로 읽은 값은 DHT 객체의 멤버 변수에 저장됨
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;

  // 2. 조도 센서 값 읽기
  int lightValue = analogRead(LIGHT_SENSOR_PIN);

  // 현재 센서 값 시리얼 모니터 출력
  Serial.println("\n--- Current Sensor Readings ---");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("Light (CDS Value): "); Serial.println(lightValue);


  //제어 로직 실행
  Serial.println("--- Control Status ---");

  // 1. 난방기 제어 (적색 LED)
  if (temperature < SET_TEMP_1) {
    digitalWrite(HEATER_LED_PIN, HIGH); // 난방기 On
    Serial.println("[Heater/Red] ON");
  } else {
    digitalWrite(HEATER_LED_PIN, LOW);  // 난방기 Off
    Serial.println("[Heater/Red] OFF");
  }

  // 2. 차양막 제어 (청색 LED)
  if (lightValue <= SET_LIGHT_1) {
    digitalWrite(AWNING_LED_PIN, HIGH); // 차양막 On (빛을 가리는 작동)
    Serial.println("[Awning/Blue] ON");
  } else {
    digitalWrite(AWNING_LED_PIN, LOW);  // 차양막 Off
    Serial.println("[Awning/Blue] OFF");
  }

  // 3. 환풍기 제어 (황색 LED)
  if (humidity >= SET_HUMIDITY_1) {
    digitalWrite(FAN_LED_PIN, HIGH);    // 환풍기 On
    Serial.println("[Fan/Yellow] ON");
  } else {
    digitalWrite(FAN_LED_PIN, LOW);     // 환풍기 Off
    Serial.println("[Fan/Yellow] OFF");
  }

  Serial.println("-------------------------------------------");
}
*/

void loop(){
  DHT.read(DHT_PIN); 
  
  // 예외 처리
  if (isnan(DHT.temperature) || isnan(DHT.humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  // 성공적으로 읽은 값은 DHT 객체의 멤버 변수에 저장됨
  float temperature = DHT.temperature;
  float humidity = DHT.humidity;

  // 2. 조도 센서 값 읽기
  int lightValue = analogRead(LIGHT_SENSOR_PIN);

  bool pumpCondition = (temperature >= SET_TEMP_2) && (lightValue <= SET_LIGHT_2) && (humidity < SET_HUMIDITY_2);

  if (pumpCondition) {
    digitalWrite(WATER_PUMP_LED_PIN, HIGH); // 물 펌프 On
    Serial.println("[Water Pump/Green] ON");
  } else {
    digitalWrite(WATER_PUMP_LED_PIN, LOW);  // 물 펌프 Off
    Serial.println("[Water Pump/Green] OFF");
  }
}
