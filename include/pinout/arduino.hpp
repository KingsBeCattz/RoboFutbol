#pragma once

#include <pinout.hpp>
#include <Arduino.h>
#include <stdint.h>
#include <Motor.h>
#include <types.h>

namespace ArduinoPinout
{
  constexpr Pin LED_STATUS_PIN = 13;

  // Controller pin definitions for Arduino Uno (PS2X library)
  constexpr Pin PS2_DAT_PIN = 2;
  constexpr Pin PS2_CMD_PIN = 12;
  constexpr Pin PS2_ATT_PIN = 7;
  constexpr Pin PS2_CLK_PIN = 8;
  constexpr bool PS2_PRESSURES = false;
  constexpr bool PS2_RUMBLE = false;

#if HBRIDGE == L298N
  constexpr HBridgeConfig HBridge = {
      .name = "L298N",
      .use_digital_directions = false,
      .use_digital_enables = false,
      .use_digital_stby = false,
      .left_enable = Motor::PIN_UNUSED,
      .left_forward = 9,
      .left_backward = 6,
      .right_enable = Motor::PIN_UNUSED,
      .right_forward = 5,
      .right_backward = 3,
      .standby = Motor::PIN_UNUSED,
  };
#elif HBRIDGE == TB6612FNG
  constexpr HBridgeConfig HBridge = {
      .name = "TB6612FNG",
      .use_digital_directions = true,
      .use_digital_enables = false,
      .use_digital_stby = true,
      .left_enable = 11,
      .left_forward = 9,
      .left_backward = 6,
      .right_enable = 10,
      .right_forward = 5,
      .right_backward = 3,
      .standby = 4,
  };
#elif HBRIDGE == BTS7960
  constexpr HBridgeConfig HBridge = {
      .name = "BTS7960",
      .use_digital_directions = false,
      .use_digital_enables = true,
      .use_digital_stby = false,
      .left_enable = 11,
      .left_forward = 9,
      .left_backward = 6,
      .right_enable = 10,
      .right_forward = 5,
      .right_backward = 3,
      .standby = Motor::PIN_UNUSED,
  };
#else
#error "HBRIDGE not defined or not recognized. Define HBRIDGE as L298N, TB6612FNG, or BTS7960."
#endif

  inline void printControllerPins()
  {
    Serial.println("PS2 Controller Pins:");
    Serial.printf("DAT: -GPIO%02d  CMD: -GPIO%02d\n", PS2_DAT_PIN, PS2_CMD_PIN);
    Serial.printf("ATT: -GPIO%02d  CLK: -GPIO%02d\n", PS2_ATT_PIN, PS2_CLK_PIN);
  }
}