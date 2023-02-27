#include <HTTPClient.h>
#include <ArduinoJson.h>

#define BASE_URL "http://house-metrics.butler.xin"

void metricsPost(String deviceId, String metricTime, String metricType, float metricValue) {

  WiFiClient client;
  HTTPClient http;

  String url = String(BASE_URL) + "/device/metrics/postMetrics";
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.setTimeout(1000 * 20);
  http.setConnectTimeout(1000 * 20);


  // Data to send with HTTP POST
  DynamicJsonDocument doc(1024);
  doc["deviceId"] = deviceId;
  doc["metricTime"] = metricTime;
  doc["metricType"] = metricType;
  doc["metricValue"] = String(metricValue, 2);
  String requestBody;
  serializeJson(doc, requestBody);

  int responseHttpCode = http.POST(requestBody);

  Serial.println("metricsPost=" + requestBody + ", responseHttpCode=" + responseHttpCode);

  // Free resources
  http.end();
}

void deviceInfo() {

  WiFiClient client;
  HTTPClient http;

  uint32_t deviceId = getDeviceId();
  String url = String(BASE_URL) + "/device/info?deviceId=" + String(deviceId);
  http.begin(client, url);
  http.addHeader("Content-Type", "application/text");
  http.setTimeout(1000 * 20);
  http.setConnectTimeout(1000 * 20);


  int responseHttpCode = http.GET();

  if (responseHttpCode > 0) {
    String responseBody = http.getString();

    Serial.println("deviceInfo=" + responseBody + ", responseHttpCode=" + responseHttpCode);

    DynamicJsonDocument doc(1024);
    deserializeJson(doc, responseBody);

    if (doc["data"]["reboot"] == 1) {
      Serial.println("rebooting...");
      ESP.restart();
      // int resetPin = 33;
      // digitalWrite(resetPin, LOW);
    }


  } else {
    Serial.println("[HTTP] GET... failed");
  }

  // Serial.println("metricsPost=" + requestBody + ", responseHttpCode=" + responseHttpCode);

  // Free resources
  http.end();
}

void updateDeviceReboot() {

  WiFiClient client;
  HTTPClient http;

  String url = String(BASE_URL) + "/device/reboot";
  http.begin(client, url);
  http.addHeader("Content-Type", "application/json");
  http.setTimeout(1000 * 20);
  http.setConnectTimeout(1000 * 20);

  uint32_t deviceId = getDeviceId();

  DynamicJsonDocument doc(1024);
  doc["deviceId"] = String(deviceId);
  String requestBody;
  serializeJson(doc, requestBody);

  int responseHttpCode = http.POST(requestBody);

  Serial.println("updateDeviceReboot, responseHttpCode=" + responseHttpCode);

  // Free resources
  http.end();
}
