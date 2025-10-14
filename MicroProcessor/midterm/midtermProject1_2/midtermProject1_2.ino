/*
** 중간 프로젝트의 미니 프로젝트 2 : 공이 상하좌우로 움직이는 화면 구현 **
*/

int rows[] = {-1, 10, 11, 12, 13, 14, 15, 16, 17}; // 행에 해당하는 핀 번호
int cols[] = {-2, 2, 3, 4, 5, 6, 7, 8, 9}; // 열에 해당하는 핀 번호

// 공의 현재 위치 (1 ~ 8 범위)
int ballRow = 4; // 현재 행 위치(시작 : 4행) 
int ballCol = 3; // 현재 열 위치(시작 : 3열)

// 공의 이동 방향
int rowDirection = 1; // 행 이동 방향 (1 : 아래, -1 : 위)
int colDirection = 1; // 열 이동 방향 (1 : 오른쪽, -1 : 왼쪽)

const int delayTime = 100; // 공의 이동 속도 조절용 딜레이 시간


void setup() {
  // 각 행과 열 핀을 출력 모드로 설정
  for(int i = 1; i < 9; i++){
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
  clear(); // 모든 LED 초기화
}

void loop() {
  // 현재 위치에 공을 그림
  drawBall(ballRow, ballCol, 100);

  // 공의 위치를 방향에 따라 갱신
  ballRow += rowDirection;
  ballCol += colDirection;

  // 열 방향 경계 체크 및 반전
  if (ballCol >= 8 || ballCol <= 1) {
    colDirection *= -1; // 방향 반전
    if (ballCol > 8) ballCol = 8;
    if (ballCol < 1) ballCol = 1;
  }

  // 행 방향 경계 체크 및 반전
  if (ballRow >= 8 || ballRow <= 1) {
    rowDirection *= -1; // 방향 반전
    if (ballRow > 8) ballRow = 8;
    if (ballRow < 1) ballRow = 1;
  }
  
  // 공의 움직임 속도 조절을 위한 딜레이
  delay(delayTime); 
}

// 모든 LED를 끄는 함수
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