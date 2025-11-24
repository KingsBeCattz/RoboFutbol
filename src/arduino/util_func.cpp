/*
 * Robo-Futbol - RC-Car control firmware
 * Copyright (C) 2025  Johan (KingsBeCattz)
 *
 * This file is part of Robo-Futbol.
 * Robo-Futbol is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * Robo-Futbol is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Robo-Futbol.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef ESP32
#include "arduino/util_func.h"

inline int16_t map_stick(uint8_t v)
{
  int16_t d = (int16_t)v - 128;
  if (d > 0)
    return d * 255 / 127;
  if (d < 0)
    return d * 255 / 128;
  return 0;
}

void set_stick_position(uint8_t (&stick)[2], uint8_t x, uint8_t y)
{
  stick[0] = x;
  stick[1] = 255 - y;
}
#endif