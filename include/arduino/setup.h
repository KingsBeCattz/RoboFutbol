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

#ifndef ARDUINO_SETUP_H
#define ARDUINO_SETUP_H

// 10 12 11 13

#ifdef USE_ENABLE_PINS
/// @brief Clock pin for PS2X controller.
#define CLK 8
/// @brief Attention pin for PS2X controller.
#define ATT 7
#else
/// @brief Clock pin for PS2X controller.
#define CLK 10
/// @brief Attention pin for PS2X controller.
#define ATT 11
#endif

/// @brief Command pin for PS2X controller.
#define CMD 12
/// @brief Data pin for PS2X controller.
#define DAT 13

/// @brief Sets up the PS2X controller.
void setupPS2X();

#endif