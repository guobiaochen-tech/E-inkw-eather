/**
 * @file User_u8g2.cpp
 * @brief U8g2 Chinese font library implementation
 * @author PAUL
 * @date 2026-03
 */

#include "User_u8g2.h"
#include "E_ink_128x296.h"

U8G2_FOR_ADAFRUIT_GFX u8g2_gfx;

void u8g2_init(void)
{
    u8g2_gfx.begin(display);
    u8g2_gfx.setFont(u8g2_font_wqy16_t_gb2312);
    u8g2_gfx.setFontMode(1);
    u8g2_gfx.setForegroundColor(GxEPD_BLACK);
    DEBUG_PRINTLN("\nu8g2_init done");
}
