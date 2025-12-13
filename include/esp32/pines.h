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

#ifndef ESP32_PINES_H
#define ESP32_PINES_H

#ifdef USE_ENABLE
/// @brief Pin definition for left enable. (EN1)
#define LEFT_ENABLE_PIN 32
/// @brief Pin definition for right enable. (EN2)
#define RIGHT_ENABLE_PIN 23
#endif

/// @brief Pin definition for left forward motion. (IN1)
#define LEFT_FORWARD_PIN 27
/// @brief Pin definition for left backward motion. (IN2)
#define LEFT_BACKWARD_PIN 14
/// @brief Pin definition for right forward motion. (IN3)
#define RIGHT_FORWARD_PIN 17
/// @brief Pin definition for right backward motion. (IN4)
#define RIGHT_BACKWARD_PIN 16

#endif