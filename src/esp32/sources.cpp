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

#ifdef ESP32
#include "esp32/sources.h"

int16_t useTriggers()
{
  // Map triggers to ±255
  uint8_t LT = currentController->l1() ? 255 : unsignedCeil(currentController->brake() / 4);
  uint8_t RT = currentController->r1() ? 255 : unsignedCeil(currentController->throttle() / 4);

  return RT - LT;
}

int16_t useLeftYAxis()
{
  if (currentController->l1() || currentController->r1())
  {
    uint8_t forward = currentController->r1() ? 255 : 0;
    uint8_t backward = currentController->l1() ? 255 : 0;
    return forward - backward;
  }

  int16_t axis = currentController->axisY();
  bool positive = axis <= 0;

  axis = abs(axis);
  axis = unsignedCeil(axis / 2);

  return positive ? axis : -axis;
}

int16_t useLeftXAxis()
{
  if (currentController->dpad())
  {
    uint8_t left = (currentController->dpad() & 8) ? 255 : 0;
    uint8_t right = (currentController->dpad() & 4) ? 255 : 0;
    return right - left;
  }

  int16_t axis = currentController->axisX();
  axis -= 2;

  bool positive = axis >= 0;
  axis = unsignedCeil(abs(axis) / 2);

  return positive ? axis : -axis;
}

int16_t useRightXAxis()
{
  if (currentController->dpad())
  {
    uint8_t left = (currentController->dpad() & 8) ? 255 : 0;
    uint8_t right = (currentController->dpad() & 4) ? 255 : 0;
    return right - left;
  }

  int16_t axis = currentController->axisRX();
  axis -= 2;

  bool positive = axis >= 0;
  axis = unsignedCeil(abs(axis) / 2);

  return positive ? axis : -axis;
}
#endif