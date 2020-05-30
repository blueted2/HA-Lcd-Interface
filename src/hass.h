#include <Arduino.h>
#include <vector>

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
public:
  HassConnection();

  std::vector<FloatSensor> float_sensors;
  std::vector<BoolSensor> bool_sensors;

  FloatSensor &AddFloatSensor(String entity_id);
  BoolSensor &AddBoolSensor(String entity_id);

  void GetInitialValuesWithHTML();
  void SubscribeAllDevices();

  void ConnectToHass();
};
