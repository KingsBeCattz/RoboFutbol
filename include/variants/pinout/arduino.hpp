#pragma once

#if DUAL == 1 && !defined(ESP32)
#error "This header is intended for use with Arduino. Please use Arduino environments before including this file."
#endif