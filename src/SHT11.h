/**
 * @file SHT11.h
 * @brief SHT11 temperature/humidity sensor driver
 * @author PAUL
 * @date 2026-03
 */

#ifndef SHT11_H
#define SHT11_H

#include <SHT1x-ESP.h>
#include "debug_config.h"
#include "config.h"

#define dataPin  SHT11_DATA_PIN
#define clockPin SHT11_CLOCK_PIN

void Read_SHT11(float& temp_c, float& temp_f, float& humidity);

#endif /* SHT11_H */
