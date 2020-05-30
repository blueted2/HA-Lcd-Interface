#include <Arduino.h>
#include "ui.h"

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/14, /* data=*/13, /* CS=*/15, /* reset=*/16); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS

UiPage ui_first_page;
UiLabel lb_first_label(0, 0, 100, 50);

void setup()
{
  Serial.begin(9600);
  u8g2.begin();

  ui_first_page.AddElement(lb_first_label);
}

void loop()
{
  u8g2.firstPage();
  do
  {
    ui_first_page.DrawAllElements(u8g2);
  } while (u8g2.nextPage());
}