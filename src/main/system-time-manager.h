#ifndef _SYSTEM_TIME_MANAGER_H_
#define _SYSTEM_TIME_MANAGER_H_

#include <cstring>
#include <WiFi.h>

class SystemTimeManager {
public:
  SystemTimeManager() {
    // Constructor, add any initialization logic here.
  }

  void setupSystemTime() {
    xTaskCreate(
      SystemTimeManager::taskSystemTime,
      "TaskSystemTime",
      2048,
      NULL,
      2,
      NULL
    );
  }

private:
  static void taskSystemTime(void *pvParameters) {
    (void)pvParameters;

    for (;;) {
      Serial.println("TaskSystemTime start");
      configTime(TIME_ZONE_OFFSET_SECONDS, DAY_LIGHT_OFFSET_SECONDS, NTP_SERVER);
      Serial.println("TaskSystemTime end");

      delay(1000 * 60 * 60 * 24);
    }
  }

  static const char* NTP_SERVER;
  static const long TIME_ZONE_OFFSET_SECONDS = 8 * 60 * 60;
  static const long DAY_LIGHT_OFFSET_SECONDS = 0;
};

const char* SystemTimeManager::NTP_SERVER = "ntp.aliyun.com";

#endif
