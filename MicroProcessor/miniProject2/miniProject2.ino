/*
// 실습 : fnd 0~9 점멸
int seg[] = {2,3,4,5,6,7,8,9};
byte digits[][8] = {
  {1,1,0,0,0,0,0,0},
  {1,1,1,1,1,0,0,1},
  {1,0,1,0,0,1,0,0},
  {1,0,1,1,0,0,0,0},
  {1,0,0,1,1,0,0,1},
  {1,0,0,1,0,0,1,0},
  {1,0,0,0,0,0,1,0},
  {1,1,1,1,1,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0}
};

void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(seg[i], OUTPUT);
  }
}

void loop() {
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 8; j++){
      digitalWrite(seg[j], digits[i][j]);
    }
    delay(1000);
  }
}
*/

/* 미니프로젝트
1) 시리얼 통신 사용
2) 시리얼 모니터링에 모드 번호(1~4)를 입력하면, FND에 모드 번호 출력됨
3) 각 모드에 따라 아래와 같이 동작
4) 모드 1: 적색 LED만 ON
5) 모드 2: 녹색 LED만 ON
6) 모드 3: 2개의 LED 모두 1초 간격으로 점멸
7) 모드 4: 2개의 LED가 번갈아가며 1초 간격으로 점멸
*/
int seg[] = {2,3,4,5,6,7,8,9};
byte digits[][8] = {
  {1,1,0,0,0,0,0,0},
  {1,1,1,1,1,0,0,1},
  {1,0,1,0,0,1,0,0},
  {1,0,1,1,0,0,0,0},
  {1,0,0,1,1,0,0,1},
  {1,0,0,1,0,0,1,0},
  {1,0,0,0,0,0,1,0},
  {1,1,1,1,1,0,0,0},
  {1,0,0,0,0,0,0,0},
  {1,0,0,1,0,0,0,0}
};

int led_G = 10;
int led_R = 11;
char op;

void setup() {
  for(int i = 0; i < 8; i++){
    pinMode(seg[i], OUTPUT);
  }
  pinMode(led_G, OUTPUT);
  pinMode(led_R, OUTPUT);
  Serial.begin(9600);
  Serial.println("시리얼 통신 시작");
}

void loop() {
  if(Serial.available()) op = Serial.read();

  for(int j = 0; j < 8; j++){
    digitalWrite(seg[j], digits[op - '0'][j]);
  }
  delay(1000);

  switch(op){
    case '1':
      digitalWrite(led_G, LOW);
      digitalWrite(led_R, HIGH);
      delay(100);
      break;
    
    case '2':
      digitalWrite(led_R, LOW);
      digitalWrite(led_G, HIGH);
      delay(100);
      break;

    case '3':
      digitalWrite(led_G, HIGH);
      digitalWrite(led_R, HIGH);
      delay(1000);
      digitalWrite(led_G, LOW);
      digitalWrite(led_R, LOW);
      break;
    case '4':
      digitalWrite(led_G, HIGH);
      digitalWrite(led_R, LOW);
      delay(1000);
      digitalWrite(led_G, LOW);
      digitalWrite(led_R, HIGH);
      break;

    default:
      digitalWrite(led_G, LOW);
      digitalWrite(led_R, LOW);
      delay(100);
  }
}
