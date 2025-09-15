int led_R = 7;
int led_G = 5;
int led_Y = 6;

void setup() {
  pinMode(led_R, OUTPUT);
  pinMode(led_G, OUTPUT);
  pinMode(led_Y, OUTPUT);
}

void loop() {
  digitalWrite(led_R, HIGH);
  digitalWrite(led_G, HIGH);
  digitalWrite(led_Y, HIGH);
  delay(1000);

  digitalWrite(led_R, LOW);
  digitalWrite(led_G, LOW);
  digitalWrite(led_Y, LOW);
  delay(1000);
}
