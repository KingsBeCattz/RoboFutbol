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

constexpr uint8_t LEFT_CLONE_1_FWD = LEFT_MOTOR_CLONE_1_FORWARD;
constexpr uint8_t LEFT_CLONE_1_BWD = LEFT_MOTOR_CLONE_1_BACKWARD;
constexpr uint8_t LEFT_CLONE_1_EN = LEFT_MOTOR_CLONE_1_ENABLE;
constexpr uint8_t RIGHT_CLONE_1_FWD = RIGHT_MOTOR_CLONE_1_FORWARD;
constexpr uint8_t RIGHT_CLONE_1_BWD = RIGHT_MOTOR_CLONE_1_BACKWARD;
constexpr uint8_t RIGHT_CLONE_1_EN = RIGHT_MOTOR_CLONE_1_ENABLE;

constexpr uint8_t LEFT_CLONE_2_FWD = LEFT_MOTOR_CLONE_2_FORWARD;
constexpr uint8_t LEFT_CLONE_2_BWD = LEFT_MOTOR_CLONE_2_BACKWARD;
constexpr uint8_t LEFT_CLONE_2_EN = LEFT_MOTOR_CLONE_2_ENABLE;
constexpr uint8_t RIGHT_CLONE_2_FWD = RIGHT_MOTOR_CLONE_2_FORWARD;
constexpr uint8_t RIGHT_CLONE_2_BWD = RIGHT_MOTOR_CLONE_2_BACKWARD;
constexpr uint8_t RIGHT_CLONE_2_EN = RIGHT_MOTOR_CLONE_2_ENABLE;
