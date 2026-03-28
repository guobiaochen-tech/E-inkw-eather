/**
 * @file E_ink_128x296.cpp
 * @brief 2.9 inch E-ink display driver implementation
 * @author PAUL
 * @date 2026-03
 */

#include "E_ink_128x296.h"

//============================================================
//                      Display Object
//============================================================

GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(
    GxEPD2_DRIVER_CLASS(/*CS=*/ 11, /*DC=*/ 10, /*RST=*/ 9, /*BUSY=*/ 8)
);

SPIClass hspi(HSPI);

//============================================================
//                      Function Implementation
//============================================================

/**
 * @brief Clear screen with specified color
 * @param color Screen color
 */
void clearScreenFull(uint16_t color)
{
    display.firstPage();
    do {
        display.fillScreen(color);
    } while (display.nextPage());
}

/**
 * @brief Initialize E-ink display
 */
void init_E_ink(void)
{
    hspi.begin(12, -1, 13, 11);
    display.epd2.selectSPI(hspi, SPISettings(4000000, MSBFIRST, SPI_MODE0));
    display.init(115200);
    DEBUG_PRINTLN("\ninit_E_ink done");
}

/**
 * @brief Draw main screen
 * @param temp Temperature value
 * @param humidity Humidity value
 * @param signal_num WiFi signal strength
 * @param batt_Level Battery level (0-3)
 */
void Draw_all(float temp, float humidity, uint8_t signal_num, uint8_t batt_Level)
{
    char tempStr[10], tempStr2[10];
    
    dtostrf(temp, 1, 1, tempStr);
    String num_str = String(tempStr);
    dtostrf(humidity, 1, 1, tempStr2);
    String num_str2 = String(tempStr2);
    
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        display.setFullWindow();
        
        // Draw large temperature
        display.setFont(&FreeSansBold24pt7b);
        if (temp < 20) {
            display.setTextColor(GxEPD_YELLOW);
        } else if (temp < 28) {
            display.setTextColor(GxEPD_BLACK);
        } else {
            display.setTextColor(GxEPD_RED);
        }
        display.setTextSize(1);
        
        int16_t tbx, tby;
        uint16_t tbw, tbh;
        display.getTextBounds(num_str, 0, 0, &tbx, &tby, &tbw, &tbh);
        uint16_t x = ((display.width() - tbw) / 2) - tbx;
        display.setCursor(x, 50);
        display.print(num_str);
        
        // Draw humidity
        display.setFont(&FreeSansBold9pt7b);
        display.setTextColor(GxEPD_BLACK);
        num_str2 += "%";
        display.getTextBounds(num_str2, 0, 0, &tbx, &tby, &tbw, &tbh);
        int x_pos = 126 - tbw;
        display.setCursor(x_pos, 76);
        display.print(num_str2);
        
        // Draw temperature unit
        u8g2_gfx.setFont(u8g2_font_wqy16_t_gb2312);
        u8g2_gfx.setFontMode(1);
        u8g2_gfx.drawUTF8(114, 50, "\'C");
        u8g2_gfx.setCursor(0, 76);
        u8g2_gfx.print("indoor");
        
        // Draw separator line
        display.fillRect(0, 82, 128, 1, GxEPD_BLACK);
        
        // Draw WiFi signal icon
        uint8_t signalLevel = 0;
        if (signal_num >= -50) signalLevel = 4;
        else if (signal_num >= -70) signalLevel = 3;
        else if (signal_num >= -85) signalLevel = 2;
        else if (signal_num >= -100) signalLevel = 1;
        
        switch (signalLevel) {
            case 4:
                display.fillRect(9, 0, 2, 8, GxEPD_BLACK);
            case 3:
                display.fillRect(6, 2, 2, 6, GxEPD_BLACK);
            case 2:
                display.fillRect(3, 4, 2, 4, GxEPD_BLACK);
            case 1:
                display.fillRect(0, 6, 2, 2, GxEPD_BLACK);
                break;
            default:
                display.fillRect(0, 6, 2, 2, GxEPD_BLACK);
                display.fillRect(2, 6, 2, 2, GxEPD_BLACK);
                break;
        }
        
        // Draw battery icon
        const uint8_t batt_x = 128 - 14;
        display.fillRect(batt_x, 1, 11, 1, GxEPD_BLACK);
        display.fillRect(batt_x, 1, 1, 6, GxEPD_BLACK);
        display.fillRect(batt_x, 6, 11, 1, GxEPD_BLACK);
        display.fillRect(batt_x + 11, 1, 1, 6, GxEPD_BLACK);
        display.fillRect(batt_x + 12, 3, 1, 2, GxEPD_BLACK);
        
        if (batt_Level >= 3) {
            display.fillRect(batt_x + 8, 2, 2, 4, GxEPD_BLACK);
        }
        if (batt_Level >= 2) {
            display.fillRect(batt_x + 5, 2, 2, 4, GxEPD_BLACK);
        }
        if (batt_Level >= 1) {
            display.fillRect(batt_x + 2, 2, 2, 4, GxEPD_BLACK);
        }
        
        // Draw weather icon
        uint8_t now_code_int = atoi(now_code1.c_str());
        uint8_t icon_y = 101;
        
        switch (now_code_int) {
            case 0: case 1:
                display.drawBitmap((128-90)/2, (90-90)/2+icon_y, icon_sun, 90, 90, GxEPD_RED);
                break;
            case 4:
                display.drawBitmap((128-86)/2, (90-67)/2+icon_y, icon_cloud, 86, 67, GxEPD_BLACK);
                break;
            case 9:
                display.drawBitmap((128-108)/2, (90-72)/2+icon_y, icon_Overcast, 108, 72, GxEPD_BLACK);
                break;
            case 13: case 14: case 15:
                display.drawBitmap((128-92)/2, (90-90)/2+icon_y, icon_rain, 92, 90, GxEPD_BLACK);
                break;
            case 22: case 23: case 24:
                display.drawBitmap((128-94)/2, (90-90)/2+icon_y, icon_snow, 94, 90, GxEPD_BLACK);
                break;
            case 30:
                display.drawBitmap((128-96)/2, (90-90)/2+icon_y, icon_fog, 96, 90, GxEPD_BLACK);
                break;
            case 31:
                display.drawBitmap((128-95)/2, (90-85)/2+icon_y, icon_rain, 95, 85, GxEPD_YELLOW);
                break;
            default:
                u8g2_gfx.setCursor(40, icon_y + 50);
                u8g2_gfx.print(now_code1 + " no icon");
                break;
        }
        
        // Draw city and temperature
        u8g2_gfx.setFont(u8g2_font_wqy16_t_gb2312);
        u8g2_gfx.setFontMode(1);
        
        uint8_t text_y = 204;
        u8g2_gfx.setCursor(0, text_y);
        u8g2_gfx.print(loc_name1);
        u8g2_gfx.setCursor(100, text_y);
        u8g2_gfx.print(now_temp1);
        
        display.getTextBounds(now_text1, 0, 0, &tbx, &tby, &tbw, &tbh);
        uint16_t x2 = ((display.width() - tbw) / 2) - tbx;
        u8g2_gfx.setCursor(x2, text_y);
        u8g2_gfx.print(now_text1);
        
        display.fillRect(0, 210, 128, 1, GxEPD_BLACK);
        
        // Draw weather forecast
        u8g2_gfx.setFont(u8g2_font_wqy12_t_gb2312);
        const uint8_t y_base = 295 - 14 * 6;
        const uint8_t x_right = 67;
        
        u8g2_gfx.setCursor(0, 101);
        u8g2_gfx.print("forecast");
        
        // Tomorrow
        u8g2_gfx.setCursor(0, y_base + 14);
        u8g2_gfx.print("tomorrow");
        u8g2_gfx.setCursor(0, y_base + 28);
        u8g2_gfx.print("day:" + text_day1);
        u8g2_gfx.setCursor(0, y_base + 42);
        u8g2_gfx.print("night:" + text_night1);
        u8g2_gfx.setCursor(0, y_base + 56);
        u8g2_gfx.print("wind:" + wind_scale1);
        u8g2_gfx.setCursor(0, y_base + 70);
        u8g2_gfx.print("humidity:" + humidity1);
        u8g2_gfx.setCursor(0, y_base + 84);
        u8g2_gfx.print("temp:" + temp1);
        
        // Day after tomorrow
        u8g2_gfx.setCursor(x_right, y_base + 14);
        u8g2_gfx.print("day after");
        u8g2_gfx.setCursor(x_right, y_base + 28);
        u8g2_gfx.print("day:" + text_day2);
        u8g2_gfx.setCursor(x_right, y_base + 42);
        u8g2_gfx.print("night:" + text_night2);
        u8g2_gfx.setCursor(x_right, y_base + 56);
        u8g2_gfx.print("wind:" + wind_scale2);
        u8g2_gfx.setCursor(x_right, y_base + 70);
        u8g2_gfx.print("humidity:" + humidity2);
        u8g2_gfx.setCursor(x_right, y_base + 84);
        u8g2_gfx.print("temp:" + temp2);
        
    } while (display.nextPage());
}
