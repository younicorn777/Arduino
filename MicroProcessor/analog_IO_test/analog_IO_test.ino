int led = 9;
void setup(){
  pinMode(led, OUTPUT);
}

void loop(){
  int input = analogRead(A0);
  analogWrite(led, input / 4);
}