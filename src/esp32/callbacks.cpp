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
#include "esp32/callbacks.h"

void onConnect(ControllerPtr pad)
{
  if (!currentController)
  {
    Serial.printf("--- Controller %s connected ---\n", pad->getModelName());
    currentController = pad;

    digitalWrite(2, HIGH);
    delay(5);

    BP32.enableNewBluetoothConnections(false);
  }
  else
  {
    pad->disconnect();
  }
}

void onDisconnect(ControllerPtr pad)
{
  if (currentController == pad)
  {
    Serial.println("--- Controller disconnected ---");
    currentController = nullptr;

    motorDriver.stop();
    BP32.enableNewBluetoothConnections(true);
  }
}
#endif