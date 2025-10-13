/*
//실습 : 하트모양
int rows[] = {-1,10,11,12,13,14,15,16,17};
int cols[] = {-2,2,3,4,5,6,7,8,9};

void setup() {
  for(int i = 1; i < 9; i++){
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
}

void loop() {
  clear();
  digitalWrite(rows[2], HIGH);
  digitalWrite(cols[2], LOW);
  digitalWrite(cols[3], LOW);
  digitalWrite(cols[6], LOW);
  digitalWrite(cols[7], LOW);
  delay(2);

  clear(); // 모든 행 지움
  digitalWrite(rows[3], HIGH);
  digitalWrite(cols[1], LOW);
  digitalWrite(cols[4], LOW);
  digitalWrite(cols[5], LOW);
  digitalWrite(cols[8], LOW);
  delay(2);

  clear();
  digitalWrite(rows[4], HIGH);
  digitalWrite(cols[1], LOW);
  digitalWrite(cols[8], LOW);
  delay(2);
  
  clear();
  digitalWrite(rows[5], HIGH);
  digitalWrite(cols[1], LOW);
  digitalWrite(cols[8], LOW);
  delay(2);

  clear();
  digitalWrite(rows[6], HIGH);
  digitalWrite(cols[2], LOW);
  digitalWrite(cols[7], LOW);
  delay(2);

  clear();
  digitalWrite(rows[7], HIGH);
  digitalWrite(cols[3], LOW);
  digitalWrite(cols[6], LOW);
  delay(2);

  clear();
  digitalWrite(rows[8], HIGH);
  digitalWrite(cols[4], LOW);
  digitalWrite(cols[5], LOW);
  delay(2);
}

void clear(){
  for(int i = 1; i < 9; i++){ // 행번호
    for(int j = 1; j < 9; j++){ // 열번호
        digitalWrite(rows[i], LOW); 
        digitalWrite(cols[j], HIGH);
    }
  }
}
*/

// 중간 프로젝트의 미니 프로젝트1
int rows[] = {-1, 10, 11, 12, 13, 14, 15, 16, 17};
int cols[] = {-2, 2, 3, 4, 5, 6, 7, 8, 9};       

// 공의 위치 및 이동 방향 변수
int ballRow = 1;      // 공의 현재 행 위치 
int direction = 1;    // 공의 이동 방향 (1: 아래로, -1: 위로)
const int delayTime = 50; // 공의 속도 조절 딜레이 (밀리초)

void clear(){
  for(int i = 1; i < 9; i++){
    for(int j = 1; j < 9; j++){
        digitalWrite(rows[i], LOW);
        digitalWrite(cols[j], HIGH);
    }
  }
}

void drawBall(int row, int col, int duration) {
  clear(); // 잔상 방지

  // 공 이동
  digitalWrite(rows[row], HIGH);
  digitalWrite(cols[col], LOW);
  delay(duration);

  clear(); // 잔상 방지
}

void setup() {
  for(int i = 1; i < 9; i++){
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
}

void loop() {
  drawBall(ballRow, 2, 100); // duration 수정필요

  ballRow += direction; // 공 이동

  if (ballRow > 8) {
    direction = -1;
    ballRow = 8;
  }
  else if (ballRow < 1) {
    direction = 1;
    ballRow = 1; 
  }
  delay(delayTime);
}