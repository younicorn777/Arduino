int sensor = A0;        // 라인트레이서 센서을 A0번 핀에 연결

void setup(){
  Serial.begin(9600);
  pinMode(sensor, INPUT);   // 라인트레이서 센서는 '입력'
}
void loop(){
  int val = digitalRead(sensor);  // 센서 값을 읽어와서
  Serial.println(val);
}
