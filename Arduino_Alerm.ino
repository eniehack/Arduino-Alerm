const int LED = 9;
const int BUTTON = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 255; i++){
    if (i < 100) {
      analogWrite(LED, i);
      delay(5000);
    }
    if (i >= 100) {
      analogWrite(LED, i);
      delay(100);
    }
  }
}
