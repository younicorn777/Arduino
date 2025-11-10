/*
// 불꽃 감지 센서 실습
int led_R = 5;
int led_B = 6;
int val;

void setup() {
  pinMode(led_R, OUTPUT);
  pinMode(led_B, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = analogRead(A0);
  Serial.println(val);
  if(val >= 800){
    digitalWrite(led_R, HIGH);
    digitalWrite(led_B, LOW);
  }
  else{
    digitalWrite(led_R, LOW);
    digitalWrite(led_B, HIGH);
  }
}
*/
/*
// 버저 실습
int buzzer = 5;
int sw = 4;
int melody[] = {262,294,330,349,392,440,494,523};

void setup(){
  pinMode(buzzer, OUTPUT);
  pinMode(sw, INPUT_PULLUP); // 기본 : digitalRead 값 = 1 
}

void loop(){
  // 스위치 누르면, 멜로디 실행
  if(digitalRead(sw) == 0){
    for(int a = 0; a < 8; a++){
      tone(buzzer, melody[a], 400);
      delay(500);
    }
  }
  else noTone(5); // 안 누르면 꺼짐
}
*/

// 미니 프로젝트 : 화재 경보 시스템 만들기
// 변수
int led_R = 5;
int led_B = 6;
int val;
int buzzer = 9;

void setup() {
    pinMode(led_R, OUTPUT);
    pinMode(led_B, OUTPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
    
    // 초기 상태 설정 (옵션: setup에서 평상시 상태로 시작)
    digitalWrite(led_R, LOW);
    digitalWrite(led_B, HIGH);
    noTone(buzzer);
}

void loop() {
    val = analogRead(A0);
    Serial.println(val);
    
    // 불꽃 감지되었을 때 (경보 상태)
    if (val >= 800) {
        // 청색 LED 끄기
        digitalWrite(led_B, LOW);
        
        // 적색 LED 켜고 버저 울림
        digitalWrite(led_R, HIGH);
        tone(buzzer, 392, 500); 
        delay(500);
        
        // 적색 LED 끄기
        digitalWrite(led_R, LOW);
        delay(500);
    }
    // 평상시
    else {
        digitalWrite(led_R, LOW); 
        digitalWrite(led_B, HIGH); 
        noTone(buzzer); 
    }
}