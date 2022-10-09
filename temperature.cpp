#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "temperature.h"

const int oneWireBus = 4;             // 选择DS18B20数字信号连接的IO口
OneWire oneWire(oneWireBus);          // 设置oneWire实例可与任意OneWire器件通信
DallasTemperature sensors(&oneWire);  // 将oneWire参数提供给Dallas温度传感器

void setupTemperatureDevice() {
  sensors.begin();
}

float getTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}