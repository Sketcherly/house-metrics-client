#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 4;             // 选择DS18B20数字信号连接的IO口
OneWire oneWire(oneWireBus);          // 设置oneWire实例可与任意OneWire器件通信
DallasTemperature sensors(&oneWire);  // 将oneWire参数提供给Dallas温度传感器

void setupTemperatureDevice() {
  sensors.begin();

  xTaskCreate(
    TaskTemperatureDevice,
    "TaskTemperatureDevice",  // A name just for humans
    2048,                     // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    NULL,                     // When no parameter is used, simply pass NULL
    2,                        // Priority
    NULL                      // Task handle is not used here - simply pass NULL
  );
}

void TaskTemperatureDevice(void *pvParameters) {  // This is a task.
  (void)pvParameters;

  for (;;) {
    uint32_t deviceId = getDeviceId();

    float temperature = getTemperature();

    char datetime[64];
    getCurrentTime(datetime);

    Serial.print(datetime);
    Serial.print(" - ");
    Serial.print(temperature);
    Serial.println("ºC");

    httpPost(String(deviceId), datetime, temperature);

    delay(1000 * 60);
  }
}

float getTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

