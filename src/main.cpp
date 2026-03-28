/**
 * @file main.cpp
 * @brief ESP32-S3 E-ink weather station main program
 * @author PAUL
 * @date 2026-03
 */

#include <Arduino.h>
#include "config.h"
#include "E_ink_128x296.h"
#include "SHT11.h"
#include "User_timer.h"
#include "User_u8g2.h"
#include "debug_config.h"

#include <PubSubClient.h>
#include <WiFiClient.h>

//============================================================
//                      Global Variables
//============================================================

WiFiClient espClient;
PubSubClient client(espClient);

float battery_v = 0.0;
uint8_t battery_level = 0;
int hour = 0, minute = 0, second = 0;
float temp_c = 0.0, temp_f = 0.0, humidity = 0.0;
uint64_t sleep_time_us = SLEEP_TIME_DAY_US;

union FloatBytes {
    float value;
    uint8_t bytes[4];
} fb;

//============================================================
//                      MQTT Reconnect
//============================================================
void reconnect_mqtt(void)
{
    while (!client.connected()) {
        DEBUG_PRINT("Connecting to MQTT...");
        if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
            DEBUG_PRINTLN("MQTT connected");
        } else {
            DEBUG_PRINT("MQTT failed, error: ");
            DEBUG_PRINTLN(client.state());
            delay(5000);
        }
    }
}

//============================================================
//                      Battery Voltage
//============================================================
void get_battery_voltage(void)
{
    const int total_samples = 20;
    uint32_t samples[total_samples];
    
    for (int i = 0; i < total_samples; i++) {
        samples[i] = analogReadMilliVolts(BAT_ADC_PIN);
        delay(10);
    }
    
    // Bubble sort
    for (int i = 0; i < total_samples - 1; i++) {
        for (int j = 0; j < total_samples - i - 1; j++) {
            if (samples[j] < samples[j + 1]) {
                uint32_t temp = samples[j];
                samples[j] = samples[j + 1];
                samples[j + 1] = temp;
            }
        }
    }
    
    uint32_t sum = 0;
    for (int i = 5; i < 15; i++) {
        sum += samples[i];
    }
    
    float avg_mv = sum / 10.0;
    battery_v = ((avg_mv * 2.0) / 1000.0) + (0.4 * 2);
    
    if (battery_v >= 3.90) battery_level = 3;
    else if (battery_v >= 3.75) battery_level = 2;
    else if (battery_v >= 3.60) battery_level = 1;
    else battery_level = 0;
    
    DEBUG_PRINTF("Battery: %.2f V, Level: %d\n", battery_v, battery_level);
}

//============================================================
//                      Main Program
//============================================================
void setup(void)
{
    Serial.begin(115200);
    delay(1000);
    DEBUG_PRINTF("Power on: %llu\n", esp_timer_get_time());
    
    init_E_ink();
    syncNTPTime();
    u8g2_init();
    getCurrentTime(hour, minute, second);
    
    User_getWeather_now();
    delay(500);
    User_getWeather_Daily();
    
    int wifi_signal = WIFI_signal();
    get_battery_voltage();
    Read_SHT11(temp_c, temp_f, humidity);
    DEBUG_PRINTF("Temp: %.2f C, Humidity: %.2f%%\n", temp_c, humidity);
    
    client.setServer(MQTT_SERVER, MQTT_PORT);
    if (!client.connected()) {
        reconnect_mqtt();
    }
    client.loop();
    
    char temp_str[10], humi_str[10], battery_str[10], wifi_str[10];
    dtostrf(temp_c, 4, 1, temp_str);
    dtostrf(humidity, 4, 1, humi_str);
    dtostrf(battery_v, 4, 2, battery_str);
    sprintf(wifi_str, "%d", wifi_signal);
    
    if (client.connected()) {
        client.publish(MQTT_TOPIC_TEMP, temp_str, true);
        client.publish(MQTT_TOPIC_HUMI, humi_str, true);
        client.publish(MQTT_TOPIC_BATTERY, battery_str, true);
        client.publish(MQTT_TOPIC_WIFI_SIGNAL, wifi_str, true);
        DEBUG_PRINTLN("MQTT publish success");
        client.loop();
        delay(500);
    }
    
    Draw_all(temp_c, humidity, wifi_signal, battery_level);
    
    DEBUG_PRINTF("Start sleep: %llu\n", esp_timer_get_time());
    if (hour >= SLEEP_NIGHT_START_HOUR) {
        sleep_time_us = SLEEP_TIME_NIGHT_US;
        DEBUG_PRINTLN("Night mode: sleep 6 hours");
    } else {
        sleep_time_us = SLEEP_TIME_DAY_US;
        DEBUG_PRINTLN("Day mode: sleep 30 min");
    }
    
    delay(100);
    esp_sleep_enable_timer_wakeup(sleep_time_us);
    esp_deep_sleep_start();
}

void loop(void)
{
    delay(100);
}
