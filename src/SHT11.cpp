/**
 * @file SHT11.cpp
 * @brief SHT11 temperature/humidity sensor driver implementation
 * @author PAUL
 * @date 2026-03
 */

#include "SHT11.h"

SHT1x sht1x(dataPin, clockPin);

void Read_SHT11(float& temp_c, float& temp_f, float& humidity)
{
    temp_c = sht1x.readTemperatureC();
    temp_f = sht1x.readTemperatureF();
    humidity = sht1x.readHumidity();
    
    DEBUG_PRINT("Temp: "); DEBUG_PRINT(temp_c);
    DEBUG_PRINT(" C, Humidity: "); DEBUG_PRINT(humidity);
    DEBUG_PRINTLN(" %");
}
