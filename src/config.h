/**
 * @file config.h
 * @brief Project configuration - sensitive info and parameters
 * @author PAUL
 * @date 2026-03
 */

#ifndef CONFIG_H
#define CONFIG_H

//============================================================
//                      WiFi Configuration
//============================================================

#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASS "YOUR_WIFI_PASSWORD"

//============================================================
//                      MQTT Configuration
//============================================================

#define MQTT_SERVER "192.168.1.3"
#define MQTT_PORT 1883
#define MQTT_USER "YOUR_MQTT_USER"
#define MQTT_PASS "YOUR_MQTT_PASSWORD"
#define MQTT_CLIENT_ID "PAUL_sht11_ink"

#define MQTT_TOPIC_TEMP "home/sensor/temp"
#define MQTT_TOPIC_HUMI "home/sensor/humi"
#define MQTT_TOPIC_BATTERY "home/sensor/battery"
#define MQTT_TOPIC_WIFI_SIGNAL "home/sensor/wifi_signal"

//============================================================
//                      Weather API Configuration
//============================================================

#define SENI_KEY "YOUR_SENIVERSE_API_KEY"
#define LOCATION "101210901"

//============================================================
//                      Sleep Configuration
//============================================================

#define SLEEP_TIME_DAY_SEC 1800
#define SLEEP_TIME_NIGHT_SEC 21600
#define SLEEP_TIME_DAY_US (SLEEP_TIME_DAY_SEC * 1000000ULL)
#define SLEEP_TIME_NIGHT_US (SLEEP_TIME_NIGHT_SEC * 1000000ULL)
#define SLEEP_NIGHT_START_HOUR 23

//============================================================
//                      Battery ADC Configuration
//============================================================

#define BAT_ADC_PIN 3
#define BAT_VOLTAGE_DIVIDER 2.0

//============================================================
//                      SHT11 Sensor Pins
//============================================================

#define SHT11_DATA_PIN 7
#define SHT11_CLOCK_PIN 6

#endif /* CONFIG_H */
