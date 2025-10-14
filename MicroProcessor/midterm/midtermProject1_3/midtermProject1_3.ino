/*
** 중간 프로젝트의 미니 프로젝트 3 : 가변 저항으로 조종 장치 구현 **
*/

int rows[] = {-1, 10, 11, 12, 13, 14, 15, 16, 17}; // 행에 해당하는 핀 번호
int cols[] = {-2, 2, 3, 4, 5, 6, 7, 8, 9}; // 열에 해당하는 핀 번호

int middle = 2; // 막대의 중앙 위치 (초기값)


void setup() {
  // 각 행과 열 핀을 출력 모드로 설정
  for(int i = 1; i < 9; i++){
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT);
  }
  clear(); // 모든 LED 초기화
}

void loop() {
  // 현재 위치에 막대를 그림
  drawBar(middle);

  // 가변저항에서 값을 읽어와 막대의 위치로 변환
  // 막대의 중앙이 2~7 사이여야 좌우 1칸씩 포함해 3칸이 화면에 표시됨
  int value = analogRead(A4);
  middle = map(value, 0, 1023, 7, 2); // 값을 2~7 범위로 매핑
}

// 막대를 그리는 함수 (막대의 너비 : 3칸)
void drawBar(int middle){
  clear();// 이전 LED 상태 초기화

  // 하단 행(8번 행)에 바를 그림
  digitalWrite(rows[8], HIGH);

  // 바의 중앙과 좌우 1칸을 켬
  digitalWrite(cols[middle - 1], LOW); // 왼쪽 열 ON
  digitalWrite(cols[middle], LOW);     // 중앙 열 ON
  digitalWrite(cols[middle + 1], LOW); // 오른쪽 열 ON
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
