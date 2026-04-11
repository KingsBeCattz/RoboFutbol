#pragma once
#include <stdint.h>
#include <types.h>

constexpr Pin LED_STATUS_PIN = 13;

// Controller pin definitions for Arduino Uno (PS2X library)
constexpr Pin PS2_DAT_PIN = 2;
constexpr Pin PS2_CMD_PIN = 12;
constexpr Pin PS2_ATT_PIN = 7;
constexpr Pin PS2_CLK_PIN = 8;
constexpr bool PS2_PRESSURES = false;
constexpr bool PS2_RUMBLE = false;

// Hbridge pin definitions for Arduino Uno
#if HBRIDGE == L298N
constexpr bool USE_DIGITAL_DIRECTIONS = false;
/// @brief Pin definition for left forward motion. (IN1)
constexpr Pin LEFT_FORWARD_PIN = 9;
/// @brief Pin definition for left backward motion. (IN2)
constexpr Pin LEFT_BACKWARD_PIN = 6;
/// @brief Pin definition for right forward motion. (IN3)
constexpr Pin RIGHT_FORWARD_PIN = 5;
/// @brief Pin definition for right backward motion. (IN4)
constexpr Pin RIGHT_BACKWARD_PIN = 3;
#elif HBRIDGE == TB6612FNG
constexpr bool USE_DIGITAL_DIRECTIONS = true;
constexpr bool USE_DIGITAL_ENABLES = false;
constexpr bool USE_DIGITAL_STBY = true;
/// @brief Pin definition for left enable. (PWMA)
constexpr Pin LEFT_ENABLE_PIN = 11;
/// @brief Pin definition for left backward motion. (AIN2)
constexpr Pin LEFT_BACKWARD_PIN = 6;
/// @brief Pin definition for left forward motion. (AIN1)
constexpr Pin LEFT_FORWARD_PIN = 9;
/// @brief Pin definition for standby control (STBY)
constexpr Pin STANDBY_PIN = 4;
/// @brief Pin definition for right forward motion. (BIN1)
constexpr Pin RIGHT_FORWARD_PIN = 5;
/// @brief Pin definition for right backward motion. (BIN2)
constexpr Pin RIGHT_BACKWARD_PIN = 3;
/// @brief Pin definition for right enable. (PWMB)
constexpr Pin RIGHT_ENABLE_PIN = 10;
#elif HBRIDGE == BTS7960
constexpr bool USE_DIGITAL_DIRECTIONS = false;
constexpr bool USE_DIGITAL_ENABLES = true;
/// @brief Pin definition for left enable. (R_EN and L_EN)
constexpr Pin LEFT_ENABLE_PIN = 11;
/// @brief Pin definition for left backward motion. (LPWM)
constexpr Pin LEFT_BACKWARD_PIN = 6;
/// @brief Pin definition for left forward motion. (RPWM)
constexpr Pin LEFT_FORWARD_PIN = 9;
/// @brief Pin definition for right forward motion. (RPWM)
constexpr Pin RIGHT_FORWARD_PIN = 5;
/// @brief Pin definition for right backward motion. (LPWM)
constexpr Pin RIGHT_BACKWARD_PIN = 3;
/// @brief Pin definition for right enable. (R_EN and L_EN)
constexpr Pin RIGHT_ENABLE_PIN = 10;
#else
#error "HBRIDGE not defined or not recognized. Define HBRIDGE as L298N, TB6612FNG, or BTS7960."
#endif