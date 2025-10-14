/* 
// 실습 1 : led 2개 사용
int led_G = 6;
int led_R = 7;

void setup() {
  Serial.begin(9600);
  pinMode(led_G, OUTPUT);
  pinMode(led_R, OUTPUT);
  Serial.println("시리얼 통신 시작");
}

// 켜진 상태가 유지되는 이유? : LOW 신호를 주지 않았으므로
void loop() {
  if(Serial.available()){
    char a = Serial.read();
    if(a == '1'){
      digitalWrite(led_G, HIGH);
      digitalWrite(led_R, HIGH);
      Serial.println("LED ON");
    }
    else{
      digitalWrite(led_G, LOW);
      digitalWrite(led_R, LOW);
      Serial.println("LED OFF");
    }
  }
  delay(1000);
}
*/

/*
//실습2 : RGB LED 모듈 활용
int led_R = 9;
int led_G = 10;
int led_B = 11;

void setup(){
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(led_B, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  digitalWrite(led_R, HIGH);
  delay(1000);
  digitalWrite(led_R, LOW);
  delay(100);

  digitalWrite(led_R, HIGH);
  digitalWrite(led_G, HIGH);
  delay(1000);
  digitalWrite(led_R, LOW);
  digitalWrite(led_G, LOW);
  delay(100);

  
  digitalWrite(led_B, HIGH);
  digitalWrite(led_G, HIGH);
  delay(1000);
  digitalWrite(led_B, LOW);
  digitalWrite(led_G, LOW);
  delay(100);
}
*/

/*
// 미니 프로젝트(변경 전)
int LED_R = 9;
int LED_G = 10; 
int LED_B = 11; 

int colors[][3] = {
  {255,204,229}, 
  {255,153,51}, 
  {153,204,255} 
};

void setup(){
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop(){
  for(int i = 0; i < 3; i++){
    int red = colors[i][0];
    int green = colors[i][1];
    int blue = colors[i][2];

    // fade in
    for(int j = 0; j < 256; j++){
      analogWrite(LED_R, red * j / 255);
      analogWrite(LED_G, green * j / 255);
      analogWrite(LED_B, blue* j / 255);
      delay(10);
    }
    delay(1000);
    
    // fade out
    for(int j = 255; j >= 0; j--){
      analogWrite(LED_R, red * j / 255);
      analogWrite(LED_G, green * j / 255);
      analogWrite(LED_B, blue* j / 255);
      delay(10);
    }
    delay(100);
  }
}
*/

// 미니 프로젝트(변경 후)
int LED_R = 9; 
int LED_G = 10; 
int LED_B = 11;

int colors[][3] = {
  {255,204,229}, 
  {255,153,51}, 
  {153,204,255}
};

void setup(){
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
}

void loop(){
  for(int i = 0; i < 3; i++){
    analogWrite(LED_R, colors[i][0]);
    analogWrite(LED_G, colors[i][1]);
    analogWrite(LED_B, colors[i][2]);
    delay(1000);
    
    analogWrite(LED_R, 0);
    analogWrite(LED_G, 0);
    analogWrite(LED_B, 0);
    delay(100);
  }
}