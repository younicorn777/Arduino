#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor_1(1); // 1번 모터 객체            

void setup() {
  motor_1.setSpeed(200); // 회전 속도 : pwm(0~255)              
  motor_1.run(RELEASE); // release : 정지, forward : 정회전, backward : 역회전
}

void loop() {
 motor_1.run(FORWARD); 
 delay(2000);
 
 motor_1.run(RELEASE);
 delay(1000);

 motor_1.run(BACKWARD);
 delay(2000);
 
 motor_1.run(RELEASE);
 delay(1000);
}
