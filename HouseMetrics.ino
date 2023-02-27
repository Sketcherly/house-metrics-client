void setup() {
  Serial.begin(115200);

  defaultLEDStartUp();

  wifiStartUp();

  setupRebootManager();

  setupSystemTime();

  delay(10000);

  setupTemperatureDevice();

}

void loop() {
  
}
