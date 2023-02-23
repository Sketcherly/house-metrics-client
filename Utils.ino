#include <HTTPClient.h>

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

void httpPost(String deviceId, String metricTime, float temperature) {

  WiFiClient client;
  HTTPClient http;

  String url = "http://green-house-metrics.butler.xin/metrics/temperature/postMetrics";
  // Your Domain name with URL path or IP address with path
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/json");
  // Data to send with HTTP POST
  String httpRequestData = "{\"deviceId\":\"" + deviceId + "\", \"temperature\": " + String(temperature, 2) + ", \"metricTime\": \"" + metricTime + "\"}";
  // Send HTTP POST request
  int httpResponseCode = http.POST(httpRequestData);

  // If you need an HTTP request with a content type: application/json, use the following:
  //http.addHeader("Content-Type", "application/json");
  //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

  // If you need an HTTP request with a content type: text/plain
  //http.addHeader("Content-Type", "text/plain");
  //int httpResponseCode = http.POST("Hello, World!");

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);

  // Free resources
  http.end();
}

uint32_t getDeviceId() {
  uint32_t chipId = 0;
  for (int i = 0; i < 17; i = i + 8) {
    chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }

  //  Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
  //  Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: ");
  Serial.println(chipId);

  return chipId;
}