#include <cstring>

#define NTP_SERVER "ntp.aliyun.com"
#define TIME_ZONE_OFFSET_SECONDS 8 * 60 * 60
#define DAY_LIGHT_OFFSET_SECONDS 0

void setupRebootManager() {

  updateDeviceReboot();

  xTaskCreate(
    TaskRebootManager,
    "TaskRebootManager",  // A name just for humans
    2048,                 // The stack size can be checked by calling `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
    NULL,                 // When no parameter is used, simply pass NULL
    2,                    // Priority
    NULL                  // Task handle is not used here - simply pass NULL
  );
}

void TaskRebootManager(void *pvParameters) {  // This is a task.
  (void)pvParameters;

  for (;;) {
    Serial.println("TaskRebootManager start");

    deviceInfo();
    Serial.println("TaskRebootManager end");

    delay(1000 * 60);
  }
}
