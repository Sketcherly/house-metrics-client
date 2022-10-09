#include <WiFi.h>

#include "wifi.1.h"

void wifiStartUp() {
  // connect to WiFi
  Serial.printf("Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED ");
  Serial.println(WiFi.localIP());

  // delay(5000);

  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
}
