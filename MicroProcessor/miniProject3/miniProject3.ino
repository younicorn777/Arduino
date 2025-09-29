/*
// 실습 1 : 택트 스위치 with led
int sw = 8;
int led = 7;

void setup() {
  pinMode(sw, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  if(digitalRead(sw) == 0){
    digitalWrite(led, LOW);
  }
  else{
    digitalWrite(led, HIGH);
  }
  delay(100);
}
*/

// 미니프로젝트
int sw1 = 8, led_R = 6;
int sw2 = 9, led_G = 7;
int run_state = 0;

void setup() {
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  digitalWrite(led_G, HIGH);
  digitalWrite(led_R, LOW);
}

void loop() {
  if(digitalRead(sw1) == HIGH && run_state == 0){
    run_state = 1;
  }
  if(digitalRead(sw2) == HIGH && run_state == 1){
    run_state = 0;
  }

  if(run_state == 1){
    digitalWrite(led_R, HIGH);
    digitalWrite(led_G, LOW);
  }
  else{
    digitalWrite(led_R, LOW);
    digitalWrite(led_G, HIGH);
  }

  delay(50);
}