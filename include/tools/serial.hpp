#pragma once

#include <Arduino.h>

#include <Motor.h>
#include <pinout.hpp>

#if DUAL == 1
#include <variants/pinout.hpp>
#endif

namespace SerialTools
{
  inline void printf(const char *fmt, ...)
  {
    va_list args;
    va_start(args, fmt);
#if defined(ARDUINO_ARCH_AVR)
    char buf[128];
#else
    char buf[256];
#endif
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    Serial.print(buf);
  }

  void printVersion()
  {
    printf("RoboFutbol Controller - Version %s\n", FIRMWARE_VERSION);
  }

  void printHBridgeType()
  {
    printf("H-Bridge Type: %s\n", Pinout::HBridge.name);
  }

  const char *direction_type = Pinout::HBridge.use_digital_directions ? "-" : "~";
  const char *enable_type = Pinout::HBridge.use_digital_enables ? "-" : "~";
  const char *stby_type = Pinout::HBridge.use_digital_stby ? "-" : "~";

  void _printPinoutBySide(const char *side, Pin forwardPin, Pin backwardPin, Pin enablePin = Motor::PIN_UNUSED)
  {
    if (enablePin != Motor::PIN_UNUSED)
    {
      printf("%s: %sGPIO%02d / %sGPIO%02d | %sGPIO%02d\n", side, direction_type, forwardPin, direction_type, backwardPin, enable_type, enablePin);
    }
    else
    {
      printf("%s: %sGPIO%02d / %sGPIO%02d |\n", side, direction_type, forwardPin, direction_type, backwardPin);
    }
  }

  void printHbridgePinout(const HBridgeConfig &cfg)
  {
    _printPinoutBySide("LEFT ", cfg.left_forward, cfg.left_backward, cfg.left_enable);
    _printPinoutBySide("RIGHT", cfg.right_forward, cfg.right_backward, cfg.right_enable);
    if (cfg.standby != Motor::PIN_UNUSED)
    {
      printf("STANDBY: %sGPIO%02d\n", stby_type, cfg.standby);
    }
  }
}