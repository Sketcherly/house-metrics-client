#include <WiFi.h>
#include <HTTPClient.h>

// #include "led.1.c"
#include "wifi.1.h"
#include "datetime.h"
#include "temperature.h"

/* Entry point ----------------------------------------------------------------*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  delay(5000);

  wifiStartUp();

  setupTime();

  delay(10000);

  setupTemperatureDevice();

}

/* The main loop -------------------------------------------------------------*/
void loop() {
  //  Serial.println("Hello World!");

  uint32_t deviceId = getDeviceId();

  float temperature = getTemperature();

  char datetime[64];
  getCurrentTime(datetime);

  Serial.print(datetime);
  Serial.print(" - ");
  Serial.print(temperature);
  Serial.println("ºC");

  httpPost(String(deviceId), datetime, temperature);

  //  delay(2000);
  delay(1000 * 60);
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
  Serial.print("Chip ID: "); Serial.println(chipId);

  return chipId;
}
