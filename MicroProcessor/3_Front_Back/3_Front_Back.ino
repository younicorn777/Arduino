#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor_L(1);              
AF_DCMotor motor_R(4); 

void setup() {
  Serial.begin(9600);
  motor_L.setSpeed(175); // 전압으로 속도 조절(0-255)(pwm)         
  motor_L.run(RELEASE);
  motor_R.setSpeed(200); // 속도차이 -> 조향                 
  motor_R.run(RELEASE);
}

// 빠르게 주행하면서도, 정확하게 운행해야. 
// 직진 코스 : 속도 높임 
// 코너 코스 : 속도 줄임
// 후진할 때는 정확히 동작하지 않는다.

//1. 직진
// 최저 속도 : L(106), R(119) / 오른쪽 모터 성능 안 좋음
// but, 차이는 30 (오른쪽을 255 기준으로 왼쪽을 줄임)
// => 직진 : L(225), R(255)
 
//2. 
// 좌회전 속도 : L(80), R(255) / 차이 : 175
// 우회전 속도 : L(230), R(110) / 차이 : 120

// 회전 
/*
void loop() {

 // 좌회전
 motor_L.run(FORWARD); 
 motor_R.run(FORWARD); 
 delay(2000);
 
 motor_L.run(RELEASE);
 motor_R.run(RELEASE);
 delay(1000);
 
 // 후진
 motor_L.run(BACKWARD);
 motor_R.run(BACKWARD);
 delay(2000);

 motor_L.run(RELEASE); 
 motor_R.run(RELEASE); 
 delay(1000);
}
*/
/*
void loop(){
  for(int i = 0; i < 256; i++){
    motor_L.setSpeed(i);
    motor_R.setSpeed(i);
    motor_L.run(FORWARD); 
    motor_R.run(FORWARD);
    Serial.println(i);

    delay(500);
  }
}
*/

// 40 < 사이에 직진 찾기< 50
void loop(){
  motor_L.setSpeed(225);
  motor_R.setSpeed(255); // 성능이 안좋음
  motor_L.run(FORWARD); 
  motor_R.run(FORWARD); 
}