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

#ifndef ESP32_CONTROLLER_STATE_H
#define ESP32_CONTROLLER_STATE_H
#include "Bluepad32.h"

/// @brief Indicates whether the SELECT button is currently pressed.
extern bool SELECT_PRESSED;
/// @brief Indicates whether the START button is currently pressed.
extern bool START_PRESSED;

/// @brief Timer tracking how long the controller has signaled a system menu request.
extern unsigned short controllerDisconnectTimer;

#endif