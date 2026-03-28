/**
 * @file E_ink_128x296.h
 * @brief 2.9 inch 4-color e-ink display driver
 * @author PAUL
 * @date 2026-03
 */

#ifndef E_INK_128X296_H
#define E_INK_128X296_H

#include <GxEPD2_4C.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include "User_u8g2.h"
#include "debug_config.h"
#include "User_timer.h"

#define GxEPD2_DISPLAY_CLASS GxEPD2_4C
#define GxEPD2_DRIVER_CLASS GxEPD2_290c_GDEY029F51H
#define MAX_DISPLAY_BUFFER_SIZE 65536ul
#define MAX_HEIGHT(EPD) (EPD::HEIGHT <= (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8) ? EPD::HEIGHT : (MAX_DISPLAY_BUFFER_SIZE / 2) / (EPD::WIDTH / 8))

extern GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display;

void init_E_ink(void);
void clearScreenFull(uint16_t color);
void Draw_all(float temp, float humidity, uint8_t signal_num, uint8_t batt_Level);

#endif
