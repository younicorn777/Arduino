/*
// 실습 : 키패드로 값을 입력받기
#include <Key.h>
#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;
char myKeys[ROWS][COLS] = {
    {'0','1','2','3'},
    {'4','5','6','7'},
    {'8','9','A','B'},
    {'C','D','E','F'},
};

byte rowPins[ROWS] = {5,4,3,2};
byte colPins[COLS] = {8,9,10,11};
Keypad customKeypad = Keypad(makeKeymap(myKeys), rowPins, colPins, ROWS, COLS);

void setup(){
    Serial.begin(9600);
}

void loop(){
    char customKey = customKeypad.getKey();
    if(customKey){
        Serial.println(customKey);
    }
}
*/

// 미니프로젝트
#include <Key.h>
#include <Keypad.h>

const byte ROWS = 4; 
const byte COLS = 4; 
char myKeys[ROWS][COLS] = {
    {'0','1','2','3'},
    {'4','5','6','7'},
    {'8','9','A','B'},
    {'C','D','E','F'}
};
byte rowPins[ROWS] = {5,4,3,2}; 
byte colPins[COLS] = {8,9,10,11}; 
Keypad customKeypad = Keypad(makeKeymap(myKeys), rowPins, colPins, ROWS, COLS);

const String SECRET_PASSWORD = "1234"; 
const size_t PASSWORD_LENGTH = SECRET_PASSWORD.length();

String currentInput = "";

void setup() {
    Serial.begin(9600);
    Serial.print("비밀번호를 입력하세요 : ");
}

void loop() {
    char customKey = customKeypad.getKey();

    if (customKey) {
        Serial.print(customKey);
        currentInput.concat(customKey); 

        if (currentInput.length() == PASSWORD_LENGTH) {
            
            Serial.println("\n입력 완료. 확인 중...");
            if (currentInput.equals(SECRET_PASSWORD)) {
                Serial.println("잠금 해제되었습니다");
            } 
            else {
                Serial.println("비밀번호 오류입니다.");
            }
            currentInput = "";
            Serial.println("------------------------------------------");
            Serial.print("비밀번호를 입력하세요 : ");
        }
    }
    delay(50); 
}