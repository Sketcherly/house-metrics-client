// #define WIFI_SSID "TP-LINK_1755"
// #define WIFI_PASSWORD "1234567890"

// #define WIFI_SSID "rigongyizu"
// #define WIFI_PASSWORD "xiaozu100000"

#define WIFI_SSID "TP-LINK_F65D"
#define WIFI_PASSWORD "lidongpo"

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
