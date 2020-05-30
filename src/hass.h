#include <Arduino.h>
#include <vector>
#include <ESP8266HTTPClient.h>
#define ARDUINOJSON_DECODE_UNICODE 1
#include <ArduinoJson.h>
#include <WebSocketsClient.h>

struct FloatSensor
{
  String entity_id;
  float value;
};

struct BoolSensor
{
  String entity_id;
  bool value;
};

class HassConnection
{
private:
  HTTPClient http;
  WiFiClient *client;
  WebSocketsClient webSocket;
  String host;
  String auth_key;
  String http_path;
  String socket_path;
  StaticJsonDocument<8192> doc;

public:
  bool socket_connected = false;
  bool socket_has_had_update = true;
  HassConnection(WiFiClient *client, String host, String auth_key, String http_path, String socket_path);

  std::vector<FloatSensor> float_sensors;
  std::vector<BoolSensor> bool_sensors;

  FloatSensor &AddFloatSensor(String entity_id);
  BoolSensor &AddBoolSensor(String entity_id);

  void GetInitialValuesWithHTML();
  String GetHTMLPayload(String entity_id);
  float GetFloatValueWithHTML(String entity_id);
  bool GetBoolValueWithHTML(String entity_id);
  String ParseValueFromHTMLPayload(String payload);

  void websocket_setup();
  void websocket_loop();

  void handle_websocket_event(WStype_t type, uint8_t *payload, size_t length);
  void handle_socket_payload(String payload);
};
