#define NTP_SERVER "ntp.aliyun.com"
#define TIME_ZONE_OFFSET_SECONDS 8 * 60 * 60
#define DAY_LIGHT_OFFSET_SECONDS 0

void setupTime();

void getCurrentTime(char *s);