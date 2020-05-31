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
UiLabel dhw_temp_top_label(&u8g2, 0, 0, -1, -1);
UiLabel dhw_temp_middle_label(&u8g2, 0, dhw_temp_top_label.label_box.y2 + 1, -1, -1);
UiLabel dhw_temp_bottom_label(&u8g2, 0, dhw_temp_middle_label.label_box.y2 + 1, -1, -1);
UiLabel solar_power_label(&u8g2, 128, 0, -1, -1);
UiLabel power_usage_label(&u8g2, 128, solar_power_label.label_box.y2 + 1, -1, -1);
UiLabel charge_power_label(&u8g2, 128, power_usage_label.label_box.y2 + 1, -1, -1);

UiPage connection_page;
UiLabel wifi_status_label(&u8g2, 64, 0, 128, -1);
UiLabel values_status_label(&u8g2, 64, 12, 128, -1);

FloatSensor &dhw_temp_top = hass.AddFloatSensor("sensor.dhw_temp_top");
FloatSensor &dhw_temp_middle = hass.AddFloatSensor("sensor.dhw_temp");
FloatSensor &dhw_temp_bottom = hass.AddFloatSensor("sensor.dhw_temp_bottom");
FloatSensor &solar_power = hass.AddFloatSensor("sensor.total_pv_power");
FloatSensor &power_usage = hass.AddFloatSensor("sensor.house_power_usage");
FloatSensor &charge_power = hass.AddFloatSensor("sensor.solar_battery_power");

BoolSensor &immersion_enabled = hass.AddBoolSensor("switch.ih_enable");

void update_main_page();
void update_connection_page();
bool wifi_connect();

void setup()
{
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);

  main_page.AddElement(dhw_temp_top_label);
  main_page.AddElement(dhw_temp_middle_label);
  main_page.AddElement(dhw_temp_bottom_label);
  main_page.AddElement(solar_power_label);
  main_page.AddElement(power_usage_label);
  main_page.AddElement(charge_power_label);

  solar_power_label.label_box.SetAlignment(right);
  power_usage_label.label_box.SetAlignment(right);
  charge_power_label.label_box.SetAlignment(right);

  connection_page.AddElement(wifi_status_label);
  connection_page.AddElement(values_status_label);

  wifi_status_label.label_box.SetAlignment(center);
  values_status_label.label_box.SetAlignment(center);
  values_status_label.SetText("");

  // dhw_temp_middle_label.SetAutomaticBorderHeight(false)
  //     .SetAutomaticBorderWidth(true)
  //     .SetSize(0, dhw_temp_bottom_label.label_box.y2 - dhw_temp_top_label.label_box.y1)
  //     .SetAnchorPosition(dhw_temp_top_label.label_box.x1, dhw_temp_top_label.label_box.y1)
  //     .draw_border = true;

  WiFiMulti.addAP("Molagnies WiFi", "76M0lagnies");
  WiFiMulti.addAP("Molagnies_Free", "molagnies");
  /*
  while (WiFiMulti.run() != WL_CONNECTED)
  {
    Serial.println("WiFi connecting.");
    delay(500);
  };

  hass.GetInitialValuesWithHTML();

  hass.websocket_setup();
  */
}

void loop()
{
  if (!wifi_connect() || !hass.has_received_first_values)
  {
    update_connection_page();

    if (wifi_connect())
    {
      hass.GetInitialValuesWithHTML();
      hass.websocket_setup();
    }
    u8g2.firstPage();
    do
    {
      connection_page.DrawAllElements();
    } while (u8g2.nextPage());
  }

  else if (hass.socket_has_had_update)
  {
    hass.socket_has_had_update = false;
    update_main_page();
    u8g2.firstPage();
    do
    {
      main_page.DrawAllElements();
    } while (u8g2.nextPage());
  }
  else
  {
    hass.websocket_loop();
  }
}

void update_connection_page()
{
  Serial.println("Updating connection page");
  if (wifi_connect())
  {
    wifi_status_label.SetText("WiFi Connected").draw_border = true;
    values_status_label.SetText("Waiting for values");
  }
  else
  {
    wifi_status_label.SetText(millis() % 2000 < 1000 ? "WiFi Connecting" : "** WiFi Connecting **");
  }
}

void update_main_page()
{
  Serial.println("updating values");

  dhw_temp_top_label.SetText((String(dhw_temp_top.value, 1) + "°C").c_str());
  dhw_temp_middle_label.SetText((String(dhw_temp_middle.value, 1) + "°C").c_str());
  dhw_temp_bottom_label.SetText((String(dhw_temp_bottom.value, 1) + "°C").c_str());

  solar_power_label.SetText(String("Solar:") + String(solar_power.value, 0) + " W");
  power_usage_label.SetText(String("Usage:") + String(power_usage.value, 0) + " W");
  charge_power_label.SetText(String("Charge:") + String(charge_power.value, 0) + " W");
}

bool wifi_connect()
{
  return WiFiMulti.run() == WL_CONNECTED;
}
