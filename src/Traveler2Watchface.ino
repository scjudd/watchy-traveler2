#include <Watchy.h>
#include "settings.h"
#include "print_bold_tt13pt7b.h"
#include "bitmaps.h"

class Traveler2Watchface : public Watchy {
  public:
    Traveler2Watchface(const watchySettings& s) : Watchy(s) {}

    void drawWatchFace() {
      int16_t x, y;
      uint16_t w, h;

      display.fillScreen(GxEPD_WHITE);
      display.setFont(&print_bold_tt13pt7b);
      display.setTextColor(GxEPD_BLACK);
      display.setCursor(0, 32);

      uint16_t hour;
      if (currentTime.Hour == 0) {
        hour = 12;
      } else if (currentTime.Hour > 12) {
        hour = currentTime.Hour - 12;
      } else {
        hour = currentTime.Hour;
      }

      char am_pm[3];
      if (currentTime.Hour < 12) {
        strcpy(am_pm, "AM");
      } else {
        strcpy(am_pm, "PM");
      }

      char lineOne[30];
      snprintf(lineOne, 30, "It is %d:%02d %s on\n", hour, currentTime.Minute, am_pm);
      display.print(lineOne);

      char suffix[3];
      uint16_t lastDigit = currentTime.Day % 10;
      if (currentTime.Day >= 11 && currentTime.Day <= 19) {
        strcpy(suffix, "th");
      } else if (lastDigit == 1) {
        strcpy(suffix, "st");
      } else if (lastDigit == 2) {
        strcpy(suffix, "nd");
      } else if (lastDigit == 3) {
        strcpy(suffix, "rd");
      } else {
        strcpy(suffix, "th");
      }

      char lineTwo[30];
      snprintf(lineTwo, 30, "%s the %d%s...", dayStr(currentTime.Wday), currentTime.Day, suffix);

      display.getTextBounds(lineTwo, 0, 0, &x, &y, &w, &h);
      if (w > 160) {
        snprintf(lineTwo, 30, "%s the\n%d%s...", dayStr(currentTime.Wday), currentTime.Day, suffix);
      }

      display.print(lineTwo);
      display.drawBitmap(172, 48, bitmap_more_dialog, 26, 28, GxEPD_WHITE, GxEPD_BLACK);

      display.setCursor(0, 120);

      char osvald_quotes[][100] = {
        "\"So what are\nyou waiting\nfor? Let's go.\"",
        "\"You have \nchosen well...\"",
      };

      char tenemos_quotes[][100] = {
        "\"You are quite\nthe capable\ncompanion...\"",
        "\"The Sacred \nFlame shall light\nour path...\nProbably.\"",
      };

      char throne_quotes[][100] = {
        "\"...You idiot.\nEnough about\nthe cheese!\"",
        "\n\"Good night.\"",
      };

      uint16_t character = currentTime.Minute % 3;
      switch (character) {
      case 0:
        display.print(osvald_quotes[currentTime.Minute % 2]);
        display.drawBitmap(200-60, 200-96, bitmap_osvald, 60, 96, GxEPD_WHITE, GxEPD_BLACK);
        break;
      case 1:
        display.print(tenemos_quotes[currentTime.Minute % 2]);
        display.drawBitmap(200-47, 200-97, bitmap_tenemos, 47, 97, GxEPD_WHITE, GxEPD_BLACK);
        break;
      case 2:
        display.print(throne_quotes[currentTime.Minute % 2]);
        display.drawBitmap(200-55, 200-99, bitmap_throne, 55, 99, GxEPD_WHITE, GxEPD_BLACK);
        break;
      }
    }
};

Traveler2Watchface watchy(settings);

void setup() {
  watchy.init();
}

void loop() {}
