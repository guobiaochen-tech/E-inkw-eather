/**
 * @file User_timer.h
 * @brief WiFi connection, time sync, and weather API module
 * @author PAUL
 * @date 2026-03
 */

#ifndef USER_TIMER_H
#define USER_TIMER_H

#include <Arduino.h>
#include <WiFi.h>
#include <time.h>
#include "debug_config.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

//============================================================
//                      Configuration
//============================================================

#define TIME_ZONE 8
#define REFRESH_INTERVAL 1000

//============================================================
//                      Weather Data
//============================================================

extern String loc_name1;
extern String now_text1;
extern String now_code1;
extern String now_temp1;
extern String last_update1;

extern String text_day1;
extern String text_night1;
extern String temp1;
extern String humidity1;
extern String wind_scale1;

extern String text_day2;
extern String text_night2;
extern String temp2;
extern String humidity2;
extern String wind_scale2;

//============================================================
//                      Weather Icons (declared here, defined in User_timer.cpp)
//============================================================

extern const unsigned char icon_sun[];
extern const unsigned char icon_cloud[];
extern const unsigned char icon_Overcast[];
extern const unsigned char icon_fog[];
extern const unsigned char icon_rain[];
extern const unsigned char icon_snow[];

//============================================================
//                      Functions
//============================================================

uint8_t syncNTPTime(void);
void getCurrentTime(int& hour, int& minute, int& second);
int WIFI_signal(void);
void User_getWeather_now(void);
void User_getWeather_Daily(void);

#endif /* USER_TIMER_H */
