#pragma once

#include <Arduino.h>

#include <Motor.h>
#include <pinout.hpp>

#if DUAL == 1
#include <cloned_pinout.hpp>
#endif

namespace printTools
{
  void printHBridgeType()
  {
    Serial.printf("H-Bridge Type: %s\n", Pinout::hbridge);
  }

  const char *direction_type = Pinout::USE_DIGITAL_DIRECTIONS ? "-" : "~";
  const char *enable_type = Pinout::USE_DIGITAL_ENABLES ? "-" : "~";
  const char *stby_type = Pinout::USE_DIGITAL_STBY ? "-" : "~";

  void _printPinoutBySide(const char *side, Pin forwardPin, Pin backwardPin, Pin enablePin = Motor::PIN_UNUSED)
  {
    if (enablePin != Motor::PIN_UNUSED)
    {
      Serial.printf("%s %sGPIO%d / %sGPIO%d | %sGPIO%d\n", side, direction_type, forwardPin, direction_type, backwardPin, enable_type, enablePin);
    }
    else
    {
      Serial.printf("%s %sGPIO%d / %sGPIO%d |\n", side, direction_type, forwardPin, direction_type, backwardPin);
    }
  }

  void _printCurrentPinout()
  {
    Serial.println("Side: FORWARD / BACKWARD | ENABLE (if applicable)");

    _printPinoutBySide("LEFT ", Pinout::LEFT_FORWARD_PIN, Pinout::LEFT_BACKWARD_PIN, Pinout::LEFT_ENABLE_PIN);
    _printPinoutBySide("RIGHT", Pinout::RIGHT_FORWARD_PIN, Pinout::RIGHT_BACKWARD_PIN, Pinout::RIGHT_ENABLE_PIN);

    if (Pinout::STANDBY_PIN != Motor::PIN_UNUSED)
    {
      Serial.printf("STANDBY: %sGPIO%d\n", stby_type, Pinout::STANDBY_PIN);
    }
  }

#if DUAL == 1
  void _printClonedPinout()
  {
    Serial.println("\nExtra pinout:");
    Serial.println("Side: FORWARD / BACKWARD | ENABLE (if applicable)");

    _printPinoutBySide("LEFT ", ClonedPinout::LEFT_FORWARD_PIN, ClonedPinout::LEFT_BACKWARD_PIN, ClonedPinout::LEFT_ENABLE_PIN);
    _printPinoutBySide("RIGHT", ClonedPinout::RIGHT_FORWARD_PIN, ClonedPinout::RIGHT_BACKWARD_PIN, ClonedPinout::RIGHT_ENABLE_PIN);

    if (ClonedPinout::STANDBY_PIN != Motor::PIN_UNUSED)
    {
      Serial.printf("STANDBY: %sGPIO%d\n", stby_type, ClonedPinout::STANDBY_PIN);
    }
  }
#endif

  void printPinout()
  {
    _printCurrentPinout();
#if DUAL == 1
    _printClonedPinout();
#endif
  }
}