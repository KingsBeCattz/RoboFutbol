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
#include "arduino/loop.h"

void loop()
{
  ps2x.read_gamepad();

  set_stick_position(left_stick, ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY));
  set_stick_position(right_stick, ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY));

  if (ps2x.ButtonPressed(PSB_SELECT))
    switch_power_source();
  if (ps2x.ButtonPressed(PSB_START))
    switch_direction_source();

  motorDriver.setExpositionActive(ps2x.Button(PSB_GREEN));

  if (ps2x.Button(PSB_BLUE))
  {
    int16_t left = map_stick(left_stick[0]);
    int16_t right = map_stick(right_stick[0]);
    motorDriver.useManualDrive(
        (uint8_t)abs(left), left >= 0,
        (uint8_t)abs(right), right >= 0);
  }
  else
  {
    if (ps2x.Button(PSB_PINK))
      motorDriver.useTankDrive();

    motorDriver.update();
  }

  delay(10);
}
#endif