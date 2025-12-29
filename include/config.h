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

#pragma once

#include "Arduino.h"

constexpr bool USE_DIGITAL_MOTOR =
#if USE_DIGITAL_MOTOR_PIN == 1
    true;
#else
    false;
#endif

constexpr bool USE_DIGITAL_ENABLE =
#if USE_DIGITAL_ENABLE_PIN == 1
    true;
#else
    false;
#endif

#if USE_ENABLE_PINS == 1
#define USE_ENABLE
#endif

#if PAIRS_OF_MOTORS >= 2
constexpr uint8_t LEFT_CLONE_1_FWD = LEFT_MOTOR_CLONE_1_FORWARD;
constexpr uint8_t LEFT_CLONE_1_BWD = LEFT_MOTOR_CLONE_1_BACKWARD;
constexpr uint8_t LEFT_CLONE_1_EN = LEFT_MOTOR_CLONE_1_ENABLE;
constexpr uint8_t RIGHT_CLONE_1_FWD = RIGHT_MOTOR_CLONE_1_FORWARD;
constexpr uint8_t RIGHT_CLONE_1_BWD = RIGHT_MOTOR_CLONE_1_BACKWARD;
constexpr uint8_t RIGHT_CLONE_1_EN = RIGHT_MOTOR_CLONE_1_ENABLE;
#endif

#if PAIRS_OF_MOTORS >= 3
constexpr uint8_t LEFT_CLONE_2_FWD = LEFT_MOTOR_CLONE_2_FORWARD;
constexpr uint8_t LEFT_CLONE_2_BWD = LEFT_MOTOR_CLONE_2_BACKWARD;
constexpr uint8_t LEFT_CLONE_2_EN = LEFT_MOTOR_CLONE_2_ENABLE;
constexpr uint8_t RIGHT_CLONE_2_FWD = RIGHT_MOTOR_CLONE_2_FORWARD;
constexpr uint8_t RIGHT_CLONE_2_BWD = RIGHT_MOTOR_CLONE_2_BACKWARD;
constexpr uint8_t RIGHT_CLONE_2_EN = RIGHT_MOTOR_CLONE_2_ENABLE;
#endif
