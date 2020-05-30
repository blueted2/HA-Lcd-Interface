#include <Arduino.h>
#include <U8g2lib.h>
#include "ui.h"
#include "hass.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/14, /* data=*/13, /* CS=*/15, /* reset=*/16); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS

UiPage ui_first_page;
UiLabel lb_first_label(&u8g2, 0, 0, 100, 50);

String auth = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiIzOTQwODgzMTFmMmI0OTI0ODA5ZGMyMDFiNzJhMDA0OCIsImlhdCI6MTU4NDg4ODE1MiwiZXhwIjoxOTAwMjQ4MTUyfQ.32CStLFyivAzNopWsdmUlGC_mg7dvQfLA6iSSN0y5D4";

WiFiClient client;
ESP8266WiFiMulti WiFiMulti;

HassConnection hass(&client, "molagnies.hd.free.fr", auth, "/api/states/", "/api/websocket/");

void setup()
{
  lb_first_label.SetAutomaticBorderHeight(true);
  Serial.begin(9600);
  u8g2.begin();

  ui_first_page.AddElement(lb_first_label);

  WiFiMulti.addAP("Molagnies WiFi", "76M0lagnies");
  WiFiMulti.addAP("Molagnies_Free", "molagnies");
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.println("WiFi connecting.");
    delay(500);
  };

  FloatSensor &grid_usage = hass.AddFloatSensor("sensor.grid_usage");
  BoolSensor &immersion_enabled = hass.AddBoolSensor("switch.ih_enable");
  hass.GetInitialValuesWithHTML();
  Serial.println(immersion_enabled.value);
}

void loop()
{
  u8g2.firstPage();
  do
  {
    ui_first_page.DrawAllElements();
  } while (u8g2.nextPage());

  lb_first_label.SetSize(millis() / 100 % 128, millis() / 200 % 64).SetAnchorPosition(0, millis() / 500 % 64);
}