/*
** 중간 프로젝트2 : 스페이스 인베이더 게임 **
*/

int rows[] = {-1, 10, 11, 12, 13, 14, 15, 16, 17}; // 행 핀 번호
int cols[] = {-2, 2, 3, 4, 5, 6, 7, 8, 9};         // 열 핀 번호       

// 조이스틱 및 버튼 핀 설정
const int MOVEX_PIN = A4; // 조이스틱 X축 (좌우 이동 감지)
const int SHOOT_PIN = 1;  // 발사 버튼 핀 (INPUT_PULLUP 방식)

// 디스플레이 설정
const int REFRESH_DELAY = 1; // 1ms로 깜빡임 최소화

// 게임 상태 변수
int cannonPos = 4; // 대공포의 중앙 열 위치 (1~8 중간, 실제로는 3칸 차지)
int bulletX = -1, bulletY = -1;  // 포탄의 X 좌표, Y 좌표
bool isBulletFired = false;      // 포탄 발사 여부

// 외계인 (단일 개체)
int invaderX = 1, invaderY = 1; // 외계인의 X 좌표, Y 좌표
bool isInvaderAlive = true; // 외계인 생존 여부
int invaderDirection = 1;   // 외계인 이동 방향 (1: 오른쪽, -1: 왼쪽)

// 게임 타이머 (Millis 기반)
unsigned long cannonMoveTime = 0;        // 대공포 이동 시간 기록
unsigned long invaderMoveTime = 0;       // 외계인 좌우 이동 시간 기록
unsigned long bulletMoveTime = 0;        // 포탄 이동 시간 기록
unsigned long invaderLayerMoveTime = 0;  // 외계인이 아래로 내려오는 시간 기록

// 각 요소의 움직임 간격 설정 (ms)
const unsigned long cannonDelay = 100;  // 대공포 이동 속도
const unsigned long invaderDelay = 500; // 외계인 이동 속도
const unsigned long bulletDelay = 100;   // 포탄 이동 속도
const unsigned long invaderLayerDelay = 3500;  //외계인 내려오는 딜레이

// 함수 선언
void moveInvader();         // 외계인 이동 처리
void checkCollision();      // 포탄과 외계인의 충돌 감지
void resetGame();           // 게임 초기화
void allLedsON(long duration); // 모든 LED 점등 효과
void GameLogic();           // 게임 로직 처리
void displayGame();         // LED 매트릭스에 게임 화면 표시 

void setup() {
  for(int i = 1; i < 9; i++){
    pinMode(rows[i], OUTPUT);
    pinMode(cols[i], OUTPUT); 
    digitalWrite(rows[i], LOW);
    digitalWrite(cols[i], HIGH);
  }
  pinMode(SHOOT_PIN, INPUT_PULLUP); // 버튼 입력 설정
  resetGame(); // 게임 초기화
}

void loop() {
  displayGame(); // 화면 표시
  GameLogic();   // 게임 로직 실행
}

// 외계인 이동 처리
void moveInvader() {
  unsigned long currentMillis = millis(); // 현재 시간

  // 외계인이 열의 경계에 도달한 경우 : X축 이동 방향 반전
  if (invaderX >= 8) {
    invaderDirection = -1;
  } 
  else if (invaderX <= 1) {
    invaderDirection = 1;
  }
  
  // 외계인의 위치 이동 
  invaderX += invaderDirection; 
  if(currentMillis - invaderLayerMoveTime >= invaderLayerDelay){
    invaderLayerMoveTime = currentMillis;
    invaderY++;
  }
}

// 포탄과 외계인의 충돌 감지
void checkCollision() {
  if (!isBulletFired) return;

  // 포탄과 외계인이 충돌한 경우(격추한 경우)
  if (isInvaderAlive && bulletX == invaderX && bulletY == invaderY) {
    isInvaderAlive = false; // 외계인 격추 처리

    // 포탄 발사 여부 및 좌표 초기화
    isBulletFired = false; 
    bulletX = -1;
    bulletY = -1;
    
    allLedsON(2000); // 명중 시 모든 LED 점등 효과
    resetGame();     // 게임 재시작
  }
}

// 게임 초기화
void resetGame() {
  cannonPos = 4;
  invaderX = 1;
  invaderY = 1;
  invaderDirection = 1;
  isInvaderAlive = true;
  invaderLayerMoveTime = millis();
  isBulletFired = false;
  bulletX = -1;
  bulletY = -1;
}

// 모든 LED 점등 효과
void allLedsON(long duration) {
  unsigned long startTime = millis(); // 현재 시간
  
  for(int i = 1; i < 9; i++){
    digitalWrite(rows[i], HIGH);
    digitalWrite(cols[i], LOW);
  }

  // duration 시간 동안 LED 점등
  while (millis() - startTime < duration) {
    // 대기
  }

  for(int i = 1; i < 9; i++){
    digitalWrite(rows[i], LOW);
    digitalWrite(cols[i], HIGH);
  }
}

// 게임 로직 처리
void GameLogic() {
  unsigned long currentMillis = millis();

  // 대공포 이동
  if (currentMillis - cannonMoveTime >= cannonDelay) {
    cannonMoveTime = currentMillis;
    
    int xValue = analogRead(MOVEX_PIN); 
    
    // 이동 범위 조정: 대포가 3칸이므로 중앙 cannonPos가 2~7 범위에 있어야 함
    if (xValue < 350) {
      if (cannonPos > 2) { 
        cannonPos--;
      }
    } 
    else if (xValue > 650) {
      if (cannonPos < 7) { 
        cannonPos++;
      }
    }
  }

  // 포탄 발사
  if (digitalRead(SHOOT_PIN) == LOW && !isBulletFired) { 
    delay(50); 
    if (digitalRead(SHOOT_PIN) == LOW && !isBulletFired) {
      // 포탄은 대공포의 중앙 (cannonPos) 위, 즉 Y=7에서 발사
      bulletX = cannonPos; // 대공포 중앙에서 발사
      bulletY = 7;         // 대공포 위에서 시작 
      isBulletFired = true;
    }
  }

  // 포탄 이동 및 충돌 감지
  if (currentMillis - bulletMoveTime >= bulletDelay) {
    bulletMoveTime = currentMillis;

    if (isBulletFired) {
      checkCollision(); // 충돌 여부 확인
      
      if (isBulletFired) { 
        bulletY--; // 충돌이 없으면 계속 이동
        
        // 화면 밖으로 나가면 비활성화
        if (bulletY < 1) { 
          isBulletFired = false; 
          bulletX = -1;
          bulletY = -1;
        }
      }
    }

    // 외계인을 격추하지 못해, 포신 행에 도달한 경우
    if(invaderY == 7){
      allLedsON(2000); // 모든 LED 점등 효과
      resetGame();     // 게임 재시작
    }
  }

  // 외계인 이동 처리
  if (isInvaderAlive && currentMillis - invaderMoveTime >= invaderDelay) {
    invaderMoveTime = currentMillis;
    moveInvader();
  }
}

// LED 매트릭스에 게임 화면 표시
void displayGame() {
  for (int i = 1; i < 9; i++) {
    
    // 모든 핀 비활성화 (화면 지우기)
    for(int j = 1; j < 9; j++) {
      for (int k = 1; k < 9; k++){
        digitalWrite(rows[j], LOW); 
        digitalWrite(cols[k], HIGH);
      } 
    }
    
    // 현재 행 활성화
    digitalWrite(rows[i], HIGH);
    
    int y = i; // 현재 행 좌표 (1-8)
    
    for (int j = 1; j < 9; j++) {
      int x = j; // 현재 열 좌표 (1-8)
      bool shouldLight = false;

      // 외계인 그리기 (Y=1 고정)
      if (isInvaderAlive && y == invaderY && x == invaderX) {
        shouldLight = true;
      }

      // 대공포 및 포신 그리기
      // 대공포 본체 (Y=8, 3칸)
      if (y == 8) { 
        // cannonPos-1, cannonPos, cannonPos+1 위치 켜기
        if (x >= cannonPos - 1 && x <= cannonPos + 1) { 
          shouldLight = true;
        }
      } 
      // 포신 (Y=7, 중앙 1칸)
      else if (y == 7) { 
        // cannonPos 위치 켜기
        if (x == cannonPos) { 
          shouldLight = true;
        }
      }

      // 포탄 그리기
      if (isBulletFired && x == bulletX && y == bulletY) {
        shouldLight = true;
      }
      
      // 열 핀 제어
      digitalWrite(cols[j], shouldLight ? LOW : HIGH); 
    }
    
    delay(REFRESH_DELAY);
  }
}