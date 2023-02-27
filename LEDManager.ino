#include "ws2812.h"

#define DEFAULT_LED_COUNT 1
#define DEFAULT_LED_PIN 9
#define DEFAULT_LED_CHANNEL 0

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(DEFAULT_LED_COUNT, DEFAULT_LED_PIN, DEFAULT_LED_CHANNEL, TYPE_GRB);

void defaultLEDStartUp() {

  strip.begin();
  strip.setBrightness(30);

  xTaskCreate(
    TaskDefaultLED,
    "TaskDefaultLED",  // A name just for humans
    2048,              // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    NULL,              // When no parameter is used, simply pass NULL
    2,                 // Priority
    NULL               // Task handle is not used here - simply pass NULL
  );
}

void TaskDefaultLED(void *pvParameters) {  // This is a task.
  (void)pvParameters;


  strip.setLedColorData(0, strip.Wheel(100));
  delay(1000 * 10);

  for (;;) {
    uint32_t deviceId = getDeviceId();
    Serial.println("HelloWorld, Chip ID: " + String(deviceId));

    for (int j = 0; j < 255; j += 2) {
      for (int i = 0; i < DEFAULT_LED_COUNT; i++) {
        strip.setLedColorData(i, strip.Wheel((i * 256 / DEFAULT_LED_COUNT + j) & 255));
      }

      strip.show();

      delay(20);
    }
  }
}
