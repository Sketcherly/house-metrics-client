#include "message-manager.h"
#include "wifi-manager.h"
#include "board-led-manager.h"
#include "temperature-sensor-manager.h"
#include "system-time-manager.h"

void setup() {

  delay(5 * 1000);
  Serial.begin(115200);
  Serial.println("setup");

  BoardLedManager &boardLedManager = BoardLedManager::getInstance();
  boardLedManager.setLightColorLoop();

  WifiManager::startup();

  // setupRebootManager();

  SystemTimeManager systemTimeManager;
  systemTimeManager.setupSystemTime();

  delay(10000);

  // setupTemperatureDevice();
  TemperatureDevice temperatureDevice(4);
  xTaskCreate(temperatureDevice.RunTask, "TaskTemperatureDevice", 2048, &temperatureDevice, 2, NULL);
}

void loop() {
  // temperatureDevice.run();
}
