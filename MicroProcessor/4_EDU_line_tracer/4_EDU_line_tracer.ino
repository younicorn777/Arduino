#include <SoftwareSerial.h>
#include <AFMotor.h>

// 모터드라이버 L293D  1: M1에 연결,  4: M4에 연결
AF_DCMotor motor_L(1); 
AF_DCMotor motor_R(4); 

void setup() {
  Serial.begin(9600); // PC와의 시리얼 통신속도
  Serial.println("Eduino Smart Car Start!");

  // turn on motor
  motor_L.setSpeed(230); // 왼쪽 모터의 속도   
  motor_L.run(RELEASE);
  motor_R.setSpeed(230); // 오른쪽 모터의 속도   
  motor_R.run(RELEASE);
}

void loop() {
    int val1 = digitalRead(A0); // 라인센서1
    int val2 = digitalRead(A5); // 라인센서2   
      
      // 직진
      if (val1 == 0 && val2 == 0) { 
       motor_L.run(FORWARD); 
       motor_R.run(FORWARD);
      }
      // 우회전
      else if (val1 == 0 && val2 == 1) {
       motor_L.run(FORWARD); 
       motor_R.run(RELEASE);
      }
      // 좌회전
      else if (val1 == 1 && val2 == 0) {
        motor_L.run(RELEASE); 
        motor_R.run(FORWARD);
      }
      // 정지(주차할 공간이 있는 경우)
      else if (val1 == 1 && val2 == 1) {
        motor_L.run(RELEASE); 
        motor_R.run(RELEASE);
      }           
}
    
