#include "hass.h"

HassConnection::HassConnection(WiFiClient *client, String host, String auth_key, String http_path, String socket_path)
{
  this->client = client;
  this->host = host;
  this->auth_key = auth_key;
  this->http_path = http_path;
  this->socket_path = socket_path;
}

void HassConnection::GetInitialValuesWithHTML()
{
  for (FloatSensor &float_sensor : float_sensors)
  {
    float_sensor.value = GetFloatValueWithHTML(float_sensor.entity_id);
  }

  for (BoolSensor &bool_sensor : bool_sensors)
  {
    bool_sensor.value = GetBoolValueWithHTML(bool_sensor.entity_id);
  }
}

String HassConnection::GetHTMLPayload(String entity_id)
{
  http.begin(*client, String("http://") + this->host + this->http_path + entity_id); //Specify request destination
  http.addHeader("Authorization", String("Bearer ") + this->auth_key);
  int code = http.GET();
  if (code != 200)
  {
    Serial.print("Error code: ");
    Serial.println(code);
    return "";
  }
  return http.getString();
}

float HassConnection::GetFloatValueWithHTML(String entity_id)
{
  float value = ParseValueFromHTMLPayload(GetHTMLPayload(entity_id)).toFloat();
  return value;
}

bool HassConnection::GetBoolValueWithHTML(String entity_id)
{
  return ParseValueFromHTMLPayload(GetHTMLPayload(entity_id)) == "on";
}

String HassConnection::ParseValueFromHTMLPayload(String payload)
{

  DeserializationError error = deserializeJson(doc, payload);
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    Serial.println(payload);
    return "";
  }
  return doc["state"].as<String>();
}

FloatSensor &HassConnection::AddFloatSensor(String entity_id)
{
  this->float_sensors.push_back(FloatSensor{entity_id, 0});
  return this->float_sensors.back();
}

BoolSensor &HassConnection::AddBoolSensor(String entity_id)
{
  this->bool_sensors.push_back(BoolSensor{entity_id, 0});
  return this->bool_sensors.back();
}