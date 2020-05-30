#include <Arduino.h>
#include <U8g2lib.h>
#include "ui.h"
#include "hass.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>

/** HassIO stuff **/
String auth = "eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiIzOTQwODgzMTFmMmI0OTI0ODA5ZGMyMDFiNzJhMDA0OCIsImlhdCI6MTU4NDg4ODE1MiwiZXhwIjoxOTAwMjQ4MTUyfQ.32CStLFyivAzNopWsdmUlGC_mg7dvQfLA6iSSN0y5D4";
WiFiClient client;
ESP8266WiFiMulti WiFiMulti;
HassConnection hass(&client, "molagnies.hd.free.fr", auth, "/api/states/", "/api/websocket");

/** Display stuff **/
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/14, /* data=*/13, /* CS=*/15, /* reset=*/16); // Feather HUZZAH ESP8266, E=clock=14, RW=data=13, RS=CS

UiPage main_page;
UiLabel dhw_temp_top_label(&u8g2, 0, 0, 100, 50);
UiLabel dhw_temp_middle_label(&u8g2, 0, 12, 100, 50);
UiLabel dhw_temp_bottom_label(&u8g2, 0, 24, 100, 50);

FloatSensor &dhw_temp_top = hass.AddFloatSensor("sensor.dhw_temp_top");
FloatSensor &dhw_temp_middle = hass.AddFloatSensor("sensor.dhw_temp");
FloatSensor &dhw_temp_bottom = hass.AddFloatSensor("sensor.dhw_temp_bottom");

BoolSensor &immersion_enabled = hass.AddBoolSensor("switch.ih_enable");

void update_main_page();

void setup()
{
  Serial.begin(9600);
  u8g2.begin();

  main_page.AddElement(dhw_temp_top_label);
  main_page.AddElement(dhw_temp_middle_label);
  main_page.AddElement(dhw_temp_bottom_label);

  WiFiMulti.addAP("Molagnies WiFi", "76M0lagnies");
  WiFiMulti.addAP("Molagnies_Free", "molagnies");
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.println("WiFi connecting.");
    delay(500);
  };

  hass.GetInitialValuesWithHTML();

  hass.websocket_setup();

  u8g2.firstPage();
  do
  {
    main_page.DrawAllElements();
  } while (u8g2.nextPage());
}

void loop()
{
  if (hass.socket_has_had_update)
  {
    hass.socket_has_had_update = false;
    update_main_page();
    u8g2.firstPage();
    do
    {
      main_page.DrawAllElements();
    } while (u8g2.nextPage());
  }

  hass.websocket_loop();
}

void update_main_page()
{
  Serial.println("updating values");
  dhw_temp_top_label.SetText(String(dhw_temp_top.value).c_str());
  dhw_temp_middle_label.SetText(String(dhw_temp_middle.value).c_str());
  dhw_temp_bottom_label.SetText(String(dhw_temp_bottom.value).c_str());
  Serial.println(dhw_temp_top.value);
}