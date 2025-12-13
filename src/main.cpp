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

#include <Arduino.h>

#ifdef ESP32
#include <Bluepad32.h>
#include "config.h"
#else
#include "PS2X_lib.h"
#endif

// -----------------------------------------------------
// Motor pin definitions
// -----------------------------------------------------

#ifdef ESP32
#include "esp32/pines.h"
#else
#include "arduino/pines.h"
#endif

// -----------------------------------------------------
// Utility Functions
// -----------------------------------------------------

#ifdef ESP32
#include "esp32/util_func.h"
#else
#include "arduino/util_func.h"
#endif

// -----------------------------------------------------
// Controller State
// -----------------------------------------------------

#ifdef ESP32
#include "esp32/controller_state.h"
#include "esp32/controller.h"
#else
#include "arduino/stick_state.h"
#include "arduino/controller.h"
#endif

// -----------------------------------------------------
// Motor Driver
// -----------------------------------------------------
#include "driver.h"

#ifdef ESP32

// -----------------------------------------------------
// Controller Connection Callbacks
// -----------------------------------------------------

#include "esp32/callbacks.h"
#endif

// -----------------------------------------------------
// Input Mapping Functions
// -----------------------------------------------------
#ifdef ESP32
#include "esp32/sources.h"
#else
#include "arduino/sources.h"
#endif

// -----------------------------------------------------
// Power / Direction Input Switching
// -----------------------------------------------------
#ifdef ESP32
#include "esp32/switch_sources.h"
#else
#include "arduino/switch_sources.h"
#endif

// -----------------------------------------------------
// Setup & Loop
// -----------------------------------------------------
void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);

#ifdef ESP32
#include "esp32/setup.h"
  setupBluepad();
#else
#include "arduino/setup.h"
  setupPS2X();
#endif

  motorDriver.begin();
  motorDriver.setDeadzone(70);

  motorDriver.getLeftMotor().setDirectionPins(LEFT_FORWARD_PIN, LEFT_BACKWARD_PIN, USE_DIGITAL_MOTOR);

  motorDriver.getRightMotor().setDirectionPins(RIGHT_FORWARD_PIN, RIGHT_BACKWARD_PIN, USE_DIGITAL_ENABLE);

#ifdef USE_ENABLE
  motorDriver.getLeftMotor().setEnablePin(LEFT_ENABLE_PIN, USE_DIGITAL_ENABLE);
  motorDriver.getRightMotor().setEnablePin(RIGHT_ENABLE_PIN, USE_DIGITAL_ENABLE);
#endif

#ifdef ESP32
#include "esp32/pin_clone.h"
  init_clone();
#endif

#ifdef ESP32
#include "esp32/set_sources.h"
  setSources();
#else
#include "arduino/set_sources.h"
  setSources();
#endif
}

#ifdef ESP32
#include "esp32/loop.h"
#else
#include "arduino/loop.h"
#endif