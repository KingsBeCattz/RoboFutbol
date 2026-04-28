#pragma once

#include <Arduino.h>

#ifdef ESP32
#include <esp32_pinout.hpp>
#if DUAL == 1
#include <esp32_clones.hpp>
#endif
#else
#include <arduino_pinout.hpp>
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