#pragma once

#ifdef ESP32
#include <BP32Gamepad.hpp>
typedef Bluepad32Gamepad CurrentGamepad;
#else
#include <PS2XGamepad.hpp>
typedef PS2Gamepad CurrentGamepad;
#endif