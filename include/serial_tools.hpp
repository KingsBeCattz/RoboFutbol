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
    Serial.println("H-Bridge Type:");
    Serial.println(hbridge);
  }
  void printPinout()
  {
    printPinout();
#if DUAL == 1
    print_clone_pinout();
#endif
  }
}