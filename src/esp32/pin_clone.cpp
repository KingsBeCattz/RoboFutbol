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
#include "config.h"
#include <Motor.h>
#include "esp32/pin_clone.h"
#include "esp32/pines.h"

#include "driver/gpio.h"
#include "soc/gpio_sig_map.h"

static inline void clone_gpio(unsigned char master, unsigned char clone)
{
  gpio_set_direction((gpio_num_t)clone, GPIO_MODE_OUTPUT);
  gpio_matrix_out((gpio_num_t)clone, master, false, false);
}

static inline void clone_motor_pins(unsigned char FWD[2], unsigned char BWD[2], unsigned char EN[2])
{
  if (FWD[1] != Motor::PIN_UNUSED)
    clone_gpio(FWD[0], FWD[1]);
  if (BWD[1] != Motor::PIN_UNUSED)
    clone_gpio(BWD[0], BWD[1]);

#ifdef USE_ENABLE_PINS
  if (EN[1] != Motor::PIN_UNUSED)
    clone_gpio(EN[0], EN[1]);
#endif
}

void init_clone()
{
#if PAIRS_OF_MOTORS >= 2
  unsigned char LEFT_FORWARD_PINS[2] = {LEFT_FORWARD_PIN, LEFT_CLONE_1_FWD};
  unsigned char LEFT_BACKWARD_PINS[2] = {LEFT_BACKWARD_PIN, LEFT_CLONE_1_BWD};
  unsigned char LEFT_ENABLE_PINS[2] = {LEFT_ENABLE_PIN, LEFT_CLONE_1_EN};

  unsigned char RIGHT_FORWARD_PINS[2] = {RIGHT_FORWARD_PIN, RIGHT_CLONE_1_FWD};
  unsigned char RIGHT_BACKWARD_PINS[2] = {RIGHT_BACKWARD_PIN, RIGHT_CLONE_1_BWD};
  unsigned char RIGHT_ENABLE_PINS[2] = {RIGHT_ENABLE_PIN, RIGHT_CLONE_1_EN};

  clone_motor_pins(LEFT_FORWARD_PINS, LEFT_BACKWARD_PINS, LEFT_ENABLE_PINS);
  clone_motor_pins(RIGHT_FORWARD_PINS, RIGHT_BACKWARD_PINS, RIGHT_ENABLE_PINS);
#endif

#if PAIRS_OF_MOTORS >= 3
  unsigned char LEFT_FORWARD_PINS_2[2] = {LEFT_FORWARD_PIN, LEFT_CLONE_2_FWD};
  unsigned char LEFT_BACKWARD_PINS_2[2] = {LEFT_BACKWARD_PIN, LEFT_CLONE_2_BWD};
  unsigned char LEFT_ENABLE_PINS_2[2] = {LEFT_ENABLE_PIN, LEFT_CLONE_2_EN};

  unsigned char RIGHT_FORWARD_PINS_2[2] = {RIGHT_FORWARD_PIN, RIGHT_CLONE_2_FWD};
  unsigned char RIGHT_BACKWARD_PINS_2[2] = {RIGHT_BACKWARD_PIN, RIGHT_CLONE_2_BWD};
  unsigned char RIGHT_ENABLE_PINS_2[2] = {RIGHT_ENABLE_PIN, RIGHT_CLONE_2_EN};

  clone_motor_pins(LEFT_FORWARD_PINS_2, LEFT_BACKWARD_PINS_2, LEFT_ENABLE_PINS_2);
  clone_motor_pins(RIGHT_FORWARD_PINS_2, RIGHT_BACKWARD_PINS_2, RIGHT_ENABLE_PINS_2);
#endif
}
#endif