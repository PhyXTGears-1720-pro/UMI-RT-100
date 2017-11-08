#define forward 5
#define backward 6

#define del 5
#define ma 255

void setup() {
  Serial.begin(9600);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);

}

void loop() {
  for (int i = 0; i < ma + 1; i++) {
    analogWrite(forward, i);
    analogWrite(backward, 0);
    delay(del);
  }
  Serial.println("Forward fast");
  for (int i = ma; i >= 0; i--) {
    analogWrite(forward, i);
    analogWrite(backward, 0);
    delay(del);
  }
  Serial.println("Off");
  for (int i = 0; i < ma + 1; i++) {
    analogWrite(forward, 0);
    analogWrite(backward, i);
    delay(del);
  }
  Serial.println("Backward fast");
  for (int i = ma; i >= 0; i--) {
    analogWrite(forward, 0);
    analogWrite(backward, i);
    delay(del);
  }
  Serial.println("Off");
}
