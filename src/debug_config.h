/**
 * @file debug_config.h
 * @brief Debug configuration
 * @author PAUL
 * @date 2026-03
 */

#ifndef DEBUG_CONFIG_H
#define DEBUG_CONFIG_H

#include <Arduino.h>

#define DEBUG 1

#if DEBUG
    #define DEBUG_PRINT(x)      Serial.print(x)
    #define DEBUG_PRINTF(...)   Serial.printf(__VA_ARGS__)
    #define DEBUG_PRINTLN(x)    Serial.println(x)
#else
    #define DEBUG_PRINT(x)
    #define DEBUG_PRINTF(...)
    #define DEBUG_PRINTLN(x)
#endif

#endif /* DEBUG_CONFIG_H */
