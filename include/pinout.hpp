#pragma once

#ifdef ESP32
#include <esp32_pinout.hpp>
namespace Pinout = ESP32Pinout;
#else
#include <arduino_pinout.hpp>
namespace Pinout = ArduinoPinout;
#endif