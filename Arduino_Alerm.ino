#include "WiFi.h"
#include <RTClib.h>

RTC_DS3231 rtc;

const int LEDC_CHANNEL = 0;
const int LED = 16;
const int freq = 5000;
const int resolution = 8;

void wifiConfig() {
  WiFi.mode(WIFI_AP_STA);
  WiFi.beginSmartConfig();

  Serial.println("Waiting");
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("received");

  Serial.println("waiting for WiFi");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("WiFi Connected");
}

void timeConfig() {
  configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
  delay(1000);
  struct tm timeInfo;
  getLocalTime(&timeInfo);

  rtc.begin();
  rtc.adjust(DateTime(timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
          timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec));
}

void displayTime() {
  char s[20];
  DateTime now = rtc.now();
  sprintf(s, "Time: %04d/%02d/%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());
  Serial.println(s);
}

void setup() {  
  Serial.begin(115200);
  delay(1000);

  wifiConfig();
  timeConfig();
  
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
        displaytime();
    }
}
/*
void snooze() {
  analogWrite(LED, 0);
  // スヌーズ時間分delayを発生させる
  delay(5000);
}
*/
