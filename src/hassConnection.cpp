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
    float value = GetFloatValueWithHTML(float_sensor.entity_id);
    float_sensor.value = value;
    Serial.println(float_sensor.entity_id + ": " + String(float_sensor.value));
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

void HassConnection::websocket_setup()
{
  // server address, port and URL
  webSocket.begin(host, 80, socket_path);

  // event handler
  webSocket.onEvent([&](WStype_t t, uint8_t *p, size_t l) {
    this->handle_websocket_event(t, p, l);
  });

  // try ever 5000 again if connection has failed
  webSocket.setReconnectInterval(5000);

  /*start heartbeat (optional)
  ping server every 15000 ms
  expect pong from server within 3000 ms
  consider connection disconnected if pong is not received 2 times */
  webSocket.enableHeartbeat(15000, 3000, 2);
}

void HassConnection::handle_websocket_event(WStype_t type, uint8_t *payload, size_t length)
{
  switch (type)
  {
  case WStype_DISCONNECTED:
    Serial.printf("[WSc] Disconnected!\n");
    socket_connected = false;
    break;
  case WStype_CONNECTED:
  {
    socket_connected = true;
    Serial.printf("[WSc] Connected to url: %s\n", payload);

    // send message to server when Connected
    // webSocket.sendTXT("Connected");
  }
  break;
  case WStype_TEXT:
    // Serial.println((char*)payload);
    handle_socket_payload(String((char *)payload));

    break;

  case WStype_BIN:
    Serial.printf("[WSc] get binary length: %u\n", length);
    hexdump(payload, length);

    // send data to server
    // webSocket.sendBIN(payload, length);
    break;
  case WStype_PING:
    // pong will be send automatically
    Serial.printf("[WSc] get ping\n");
    break;
  case WStype_PONG:
    // answer to a ping we send
    Serial.printf("[WSc] get pong\n");
    break;
  }
};

void HassConnection::handle_socket_payload(String payload)
{
  DeserializationError error = deserializeJson(doc, payload);
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    Serial.println(payload);
    return;
  }

  if (strcmp(doc["type"], "auth_required") == 0)
  { // If authentification needed

    Serial.println("Authenfying...");

    webSocket.sendTXT("{\"type\":\"auth\",\"access_token\":\"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiIzOTQwODgzMTFmMmI0OTI0ODA5ZGMyMDFiNzJhMDA0OCIsImlhdCI6MTU4NDg4ODE1MiwiZXhwIjoxOTAwMjQ4MTUyfQ.32CStLFyivAzNopWsdmUlGC_mg7dvQfLA6iSSN0y5D4\"}");
  }
  else if (strcmp(doc["type"], "auth_ok") == 0)
  { // If authentification successful
    Serial.println("Authenfication successful");
    webSocket.sendTXT("{\"id\": 2,\"type\": \"subscribe_events\",\"event_type\": \"state_changed\"}");
  }
  else if (strcmp(doc["type"], "event") == 0)
  {

    String entity_id = doc["event"]["data"]["entity_id"];
    String state = doc["event"]["data"]["new_state"]["state"];

    socket_has_had_update = false;
    for (FloatSensor &float_sensor : float_sensors)
    {
      if (float_sensor.entity_id == entity_id)
      {
        float_sensor.value = state.toFloat();
        socket_has_had_update = true;
        Serial.println(String(entity_id) + ": " + String(state.toFloat()));
      }
    }

    for (BoolSensor &bool_sensor : bool_sensors)
    {
      if (bool_sensor.entity_id == entity_id)
      {
        bool_sensor.value = state == "on";
        socket_has_had_update = true;
        Serial.println(String(entity_id) + ": " + String(state));
      }
    }
  }

  else
  {
    Serial.println(payload);
  }
}

void HassConnection::websocket_loop()
{
  webSocket.loop();
}