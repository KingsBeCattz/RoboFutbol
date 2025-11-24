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
#include "esp32/switch_sources.h"

void switchPowerSource()
{
  auto current = motorDriver.getPowerSourceFunction();
  motorDriver.setPowerSource(
      current == useTriggers ? useLeftYAxis : useTriggers);
}

void switchDirectionSource()
{
  auto current = motorDriver.getDirectionSourceFunction();
  motorDriver.setDirectionSource(
      current == useLeftXAxis ? useRightXAxis : useLeftXAxis);
}
#endif