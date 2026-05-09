#pragma once

#if DUAL != 1
#error "This header is only intended for use in dual-motor configurations. Please ensure DUAL is set to 1 before including this file."
#endif

#ifdef ESP32
#include <variants/pinout/esp32.hpp>
namespace ClonedPinout = ESP32ClonedPinout;
#else
#error "This header is not intended for use with Arduino; currently, there are no Arduino clones available due to hardware limitations."
#endif