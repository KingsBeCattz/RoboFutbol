#pragma once

#include <types.h>

struct HBridgeConfig
{
  const char *name;
  bool use_digital_directions;
  bool use_digital_enables;
  bool use_digital_stby;
  Pin left_enable;
  Pin left_forward;
  Pin left_backward;
  Pin right_enable;
  Pin right_forward;
  Pin right_backward;
  Pin standby;
};

#ifdef ESP32
#include <pinout/esp32.hpp>
namespace Pinout = ESP32Pinout;
#else
#include <pinout/arduino.hpp>
namespace Pinout = ArduinoPinout;
#endif