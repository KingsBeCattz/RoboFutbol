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
#include "arduino/sources.h"

inline int16_t use_left_x_axis() { return map_stick(left_stick[0]); }
inline int16_t use_left_y_axis() { return map_stick(left_stick[1]); }
inline int16_t use_right_x_axis() { return map_stick(right_stick[0]); }
inline int16_t use_right_y_axis() { return map_stick(right_stick[1]); }
#endif