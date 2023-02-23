void setup() {
  Serial.begin(115200);

  defaultLEDStartUp();

  wifiStartUp();

  setupSystemTime();

  delay(10000);

  setupTemperatureDevice();

  Serial.printf("Basic Multi Threading Arduino Example\n");
}

void loop() {
  
}
