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
#include "esp32/loop.h"

void loop()
{
  BP32.update();

  if (!currentController)
  {
    // In case a controller was disconnected but the timer wasn't reset
    if (controllerDisconnectTimer > 0)
      controllerDisconnectTimer = 0;

    // Flash LED while waiting for connection and ensure motors are stopped
    motorDriver.stop();
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(100);
    return;
  }

  // Solid LED when connected
  digitalWrite(2, HIGH);

  if (currentController->isConnected() && currentController->isGamepad())
  {

    if (currentController->miscSystem())
    {
      controllerDisconnectTimer += 10;
    }
    else if (controllerDisconnectTimer > 0)
    {
      controllerDisconnectTimer = 0;
    }

    if (controllerDisconnectTimer >= 2000)
    {
      currentController->disconnect();
      return;
    }

    // Handle mode switches
    listenButtonState(currentController->miscBack(), SELECT_PRESSED, switchPowerSource, nullptr);
    listenButtonState(currentController->miscHome(), START_PRESSED, switchDirectionSource, nullptr);

    // Exposition mode
    motorDriver.setExpositionActive(currentController->y());

    // Manual drive (A button)
    if (currentController->a())
    {
      motorDriver.useManualDrive(
          unsignedCeil(currentController->brake() / 4), !currentController->l1(),
          unsignedCeil(currentController->throttle() / 4), !currentController->r1());
    }
    else
    {
      if (currentController->x())
        motorDriver.useTankDrive();

      motorDriver.update();
    }
  }

  delay(10);
}
#endif