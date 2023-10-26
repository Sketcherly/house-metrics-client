#ifndef _BOARD_LED_MANAGER_H_
#define _BOARD_LED_MANAGER_H_


#include "Freenove_WS2812_Lib_for_ESP32.h"
#include "utils.h"

#define DEFAULT_LED_COUNT 1
#define DEFAULT_LED_PIN 9
#define DEFAULT_LED_CHANNEL 0

class BoardLedManager {
public:
  // 获取 BoardLedManager 单例
  static BoardLedManager &getInstance() {
    static BoardLedManager instance;
    return instance;
  }

  // 启动 LED 循环颜色变化任务
  void setLightColorLoop() {
    xTaskCreate(
      BoardLedManager::lightColorLoopTask,
      "TaskDefaultLED",
      2048,
      NULL,
      2,
      NULL);
  }

private:
  Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(DEFAULT_LED_COUNT, DEFAULT_LED_PIN, DEFAULT_LED_CHANNEL, TYPE_GRB);

  // 构造函数，设置 LED 初始化参数
  BoardLedManager() {
    strip.begin();
    strip.setBrightness(30);
  }

  // 禁用复制构造函数和赋值操作符
  BoardLedManager(const BoardLedManager &) = delete;
  BoardLedManager(const BoardLedManager &&) = delete;
  BoardLedManager &operator=(const BoardLedManager &) = delete;

  // 启动 LED 颜色循环
  void ligthColorLoopStartUp() {
    strip.setLedColorData(0, strip.Wheel(100));

    for (;;) {
      // 获取设备ID
      uint32_t deviceId = SimpleUtils::getDeviceId();

      for (int j = 0; j < 255; j += 2) {
        for (int i = 0; i < DEFAULT_LED_COUNT; i++) {
          strip.setLedColorData(i, strip.Wheel((i * 256 / DEFAULT_LED_COUNT + j) & 255));
        }

        strip.show();

        delay(20);
      }
    }
  }

  // LED 颜色循环任务
  static void lightColorLoopTask(void *pvParameters) {
    (void)pvParameters;

    BoardLedManager &boardLedManager = BoardLedManager::getInstance();
    boardLedManager.ligthColorLoopStartUp();
  }
};


#endif
