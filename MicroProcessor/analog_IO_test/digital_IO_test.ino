int led = 7;
void setup(){
  pinMode(led, OUTPUT);
}

void loop(){
  int input = analogRead(A0);
  analogWrite(led, input / 4);
}