//11시35분
#include <AFMotor.h>
AF_DCMotor motor_L(1); 
AF_DCMotor motor_R(4); 

// 상태 변수
int diff = 30; // 30 확정 (32 ~ 35 사이에서 고민함)

// 1. 직진: 무조건 최대 속도 (0~255 중 Max)
int speed_max = 253; // 250 ~ 254 / 255(문제) 

// 2. 코너링: 직진 관성을 이겨내기 위해 강력한 힘 필요
// 바깥쪽 바퀴는 속도를 살짝 줄여서 접지력 확보
int speed_turn_outer = 150; 
// 안쪽 바퀴는 아주 강하게 뒤로 당겨서(역회전) 차머리를 억지로 돌림
int speed_turn_inner = 180; 

void setup() {
  motor_L.setSpeed(speed_max);
  motor_R.setSpeed(speed_max);
  motor_L.run(RELEASE);
  motor_R.run(RELEASE);
}

void loop() {
  int val1 = digitalRead(A0); // 왼쪽
  int val2 = digitalRead(A5); // 오른쪽
    
  // 1. 직진 (둘 다 흰색)
  if (val1 == 0 && val2 == 0) { 
    motor_L.setSpeed(speed_max-diff); 
    motor_R.setSpeed(speed_max); 
    motor_L.run(FORWARD); 
    motor_R.run(FORWARD);
  }
  
  // 2. 우회전 (오른쪽이 검은 선)
  else if (val1 == 0 && val2 == 1) { 
    motor_L.setSpeed(speed_turn_outer-diff); 
    motor_R.setSpeed(speed_turn_inner); 
    
    motor_L.run(FORWARD); 
    motor_R.run(BACKWARD); // 빡! 하고 뒤로 당김
  }
  
  // 3. 좌회전 (왼쪽이 검은 선)
  else if (val1 == 1 && val2 == 0) { 
    motor_L.setSpeed(speed_turn_inner - diff); 
    motor_R.setSpeed(speed_turn_outer); 
    
    motor_L.run(BACKWARD); // 빡! 하고 뒤로 당김
    motor_R.run(FORWARD);
  } 
  
  // 4. 교차로/십자 구간 (둘 다 검은 선)
  else if (val1 == 1 && val2 == 1) { 
    motor_L.setSpeed(speed_max-diff); 
    motor_R.setSpeed(speed_max); 
    motor_L.run(FORWARD); 
    motor_R.run(FORWARD);
  }           
}
