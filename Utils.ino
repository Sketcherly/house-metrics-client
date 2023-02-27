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

uint32_t getDeviceId() {
  uint32_t chipId = 0;
  for (int i = 0; i < 17; i = i + 8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  //  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
  //  Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  // Serial.print("Chip ID: ");
  // Serial.println(chipId);

  return chipId;
}