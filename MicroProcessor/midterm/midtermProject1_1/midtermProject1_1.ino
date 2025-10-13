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

/*
** 중간 프로젝트의 미니 프로젝트 1 : 공이 위 아래로 왕복하는 화면 구현 **
*/

int rows[] = {-1, 10, 11, 12, 13, 14, 15, 16, 17}; // 행에 해당하는 핀 번호
int cols[] = {-2, 2, 3, 4, 5, 6, 7, 8, 9}; // 열에 해당하는 핀 번호       

// 공의 위치 및 이동 방향 변수
int ballRow = 1;      // 공의 현재 행 위치 (1 ~ 8 사이) 
int direction = 1;    // 공의 이동 방향 (1 : 아래로, -1 : 위로)
const int delayTime = 50; // 공의 이동 속도 조절용 딜레이 시간

void setup() {
  for(int i = 1; i < 9; i++){
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
}

void loop() {
  drawBall(ballRow, 2, 100); // 공을 2열에 고정, 100ms 동안 표시

  // 공의 행 위치를 방향에 따라 업데이트
  ballRow += direction; 

  // 공이 위 또는 아래 끝에 도달했을 때 방향 반전
  if (ballRow > 8) {
    direction = -1; // 아래 끝에 도달했으면 위로 이동
    ballRow = 8;
  }
  else if (ballRow < 1) {
    direction = 1; // 위 끝에 도달했으면 아래로 이동
    ballRow = 1; 
  }

  // 공의 움직임 속도 조절을 위한 딜레이
  delay(delayTime);
}

// 모든 LED를 끄는 함수 (잔상 제거용)
void clear(){
  for(int i = 1; i < 9; i++){
    for(int j = 1; j < 9; j++){
        digitalWrite(rows[i], LOW);
        digitalWrite(cols[j], HIGH);
    }
  }
}

// 특정 위치에 공을 그리는 함수
void drawBall(int row, int col, int duration) {
  clear(); // 이전 LED 상태 초기화

  // 해당 위치의 LED 켜기
  digitalWrite(rows[row], HIGH);
  digitalWrite(cols[col], LOW);
  delay(duration); // 켜진 상태 유지

  clear(); // 다음 루프를 위해 LED OFF
}