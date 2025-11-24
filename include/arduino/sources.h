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

#ifndef ARDUINO_SOURCES_H
#define ARDUINO_SOURCES_H

#include "Arduino.h"
#include "stick_state.h"
#include "util_func.h"

/// @brief Uses the controller triggers as the power source.
inline int16_t use_left_x_axis();
/// @brief Uses the left joystick Y-axis as the power source.
inline int16_t use_left_y_axis();
/// @brief Uses the right joystick X-axis as the direction source.
inline int16_t use_right_x_axis();
/// @brief Uses the right joystick Y-axis as the direction source.
inline int16_t use_right_y_axis();

#endif