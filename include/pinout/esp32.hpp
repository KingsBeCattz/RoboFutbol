#pragma once

#include <pinout.hpp>
#include <Motor.h>
#include <types.h>

namespace ESP32Pinout
{
  constexpr Pin LED_STATUS_PIN = 2;

#if HBRIDGE == L298N
  constexpr HBridgeConfig HBridge = {
      .name = "L298N",
      .use_digital_directions = false,
      .use_digital_enables = false,
      .use_digital_stby = false,
      .left_enable = Motor::PIN_UNUSED,
      .left_forward = 27,
      .left_backward = 14,
      .right_enable = Motor::PIN_UNUSED,
      .right_forward = 25,
      .right_backward = 26,
      .standby = Motor::PIN_UNUSED,
  };
#elif HBRIDGE == TB6612FNG
  constexpr HBridgeConfig HBridge = {
      .name = "TB6612FNG",
      .use_digital_directions = true,
      .use_digital_enables = false,
      .use_digital_stby = true,
      .left_enable = 4,
      .left_forward = 17,
      .left_backward = 16,
      .right_enable = 21,
      .right_forward = 18,
      .right_backward = 19,
      .standby = 5,
  };
#elif HBRIDGE == BTS7960
  constexpr HBridgeConfig HBridge = {
      .name = "BTS7960",
      .use_digital_directions = false,
      .use_digital_enables = true,
      .use_digital_stby = false,
      .left_enable = 26,
      .left_forward = 14,
      .left_backward = 27,
      .right_enable = 16,
      .right_forward = 5,
      .right_backward = 17,
      .standby = Motor::PIN_UNUSED,
  };
#else
#error "HBRIDGE not defined or not recognized."
#endif
}