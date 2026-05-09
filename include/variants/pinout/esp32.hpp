#pragma once

#if DUAL != 1 || !defined(ESP32)
#error "This header is intended for use with ESP32. Please use ESP32 environments before including this file."
#else

#include "pinout/esp32.hpp"
#include "types.h"
#include <MotorDriveUnit.h>

namespace ESP32ClonedPinout
{
#if HBRIDGE == L298N
  constexpr HBridgeConfig HBridge = {
      .name = ESP32Pinout::HBridge.name,
      .use_digital_directions = ESP32Pinout::HBridge.use_digital_directions,
      .use_digital_enables = ESP32Pinout::HBridge.use_digital_enables,
      .use_digital_stby = ESP32Pinout::HBridge.use_digital_stby,
      .left_enable = Motor::PIN_UNUSED,
      .left_forward = 4,
      .left_backward = 16,
      .right_enable = Motor::PIN_UNUSED,
      .right_forward = 17,
      .right_backward = 5,
      .standby = Motor::PIN_UNUSED,
  };
#elif HBRIDGE == TB6612FNG
  constexpr HBridgeConfig HBridge = {
      .name = ESP32Pinout::HBridge.name,
      .use_digital_directions = ESP32Pinout::HBridge.use_digital_directions,
      .use_digital_enables = ESP32Pinout::HBridge.use_digital_enables,
      .use_digital_stby = ESP32Pinout::HBridge.use_digital_stby,
      .left_enable = 32,
      .left_forward = 25,
      .left_backward = 33,
      .right_enable = 12,
      .right_forward = 27,
      .right_backward = 14,
      .standby = 26,
  };
#elif HBRIDGE == BTS7960
  constexpr HBridgeConfig HBridge = {
      .name = ESP32Pinout::HBridge.name,
      .use_digital_directions = ESP32Pinout::HBridge.use_digital_directions,
      .use_digital_enables = ESP32Pinout::HBridge.use_digital_enables,
      .use_digital_stby = ESP32Pinout::HBridge.use_digital_stby,
      .left_enable = 26,
      .left_forward = 14,
      .left_backward = 27,
      .right_enable = 16,
      .right_forward = 5,
      .right_backward = 17,
      .standby = Motor::PIN_UNUSED,
  };
#else
#error "HBRIDGE not defined or not recognized. Define HBRIDGE as L298N, TB6612FNG, or BTS7960."
#endif
}
#endif