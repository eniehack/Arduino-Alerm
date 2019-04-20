const int LEDC_CHANNEL = 0;
const int LED = 16;
const int freq = 5000;
const int resolution = 8;

void setup() {
  Serial.begin(115200);
  ledcSetup(LEDC_CHANNEL, freq, resolution);
  ledcAttachPin(LED, LEDC_CHANNEL);
}

void loop() {
  for (int i = 0; i < 255; i++){
      if (i < 100) {
        Serial.println(i, DEC);
        ledcWrite(LEDC_CHANNEL, i);
        delay(5000);
      }
      if (i >= 100) {
        Serial.println(i, DEC);
        ledcWrite(LEDC_CHANNEL, i);
        delay(100);
      }
  }
}
/*
void snooze() {
  analogWrite(LED, 0);
  // スヌーズ時間分delayを発生させる
  delay(5000);
}
*/
