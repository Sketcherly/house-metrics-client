#include <cstring>

#include <WiFi.h>

#include "datetime.h"

void setupTime() {
  configTime(TIME_ZONE_OFFSET_SECONDS, DAY_LIGHT_OFFSET_SECONDS, NTP_SERVER);
}

void getCurrentTime(char *s) {
  time_t now;
  char strftime_buf[64];
  struct tm timeinfo;

  time(&now);
  // 将时区设置为中国标准时间
  setenv("TZ", "CST-8", 1);
  tzset();

  localtime_r(&now, &timeinfo);
  strftime(strftime_buf, sizeof(strftime_buf), "%F %T", &timeinfo);

//  Serial.println(&timeinfo, "%F %T"); // 格式化输出

  strcpy(s, strftime_buf);
}
