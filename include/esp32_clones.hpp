#pragma once
#if DUAL != 1 || !defined(ESP32)
#error "This header is intended for use with ESP32. Please use ESP32 environments before including this file."
#endif

#include "esp32_pinout.hpp"
#include "types.h"
#include <MotorDriveUnit.h>

namespace ESP32ClonedPinout
{
#if HBRIDGE == L298N
  /// @brief Pin definition for left forward motion. (IN1)
  constexpr Pin LEFT_FORWARD_PIN = 4;
  /// @brief Pin definition for left backward motion. (IN2)
  constexpr Pin LEFT_BACKWARD_PIN = 16;
  /// @brief Pin definition for right forward motion. (IN3)
  constexpr Pin RIGHT_FORWARD_PIN = 17;
  /// @brief Pin definition for right backward motion. (IN4)
  constexpr Pin RIGHT_BACKWARD_PIN = 5;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin LEFT_ENABLE_PIN = Motor::PIN_UNUSED;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin RIGHT_ENABLE_PIN = Motor::PIN_UNUSED;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin STANDBY_PIN = Motor::PIN_UNUSED;
#elif HBRIDGE == BTS7960
  /// @brief Pin definition clon for left enable. (R_EN and L_EN)
  constexpr Pin LEFT_ENABLE_PIN = 32;
  /// @brief Pin definition clon for left backward motion. (LPWM)
  constexpr Pin LEFT_BACKWARD_PIN = 33;
  /// @brief Pin definition clon for left forward motion. (RPWM)
  constexpr Pin LEFT_FORWARD_PIN = 25;
  /// @brief Pin definition clon for right forward motion. (RPWM)
  constexpr Pin RIGHT_FORWARD_PIN = 18;
  /// @brief Pin definition clon for right backward motion. (LPWM)
  constexpr Pin RIGHT_BACKWARD_PIN = 19;
  /// @brief Pin definition clon for right enable. (R_EN and L_EN)
  constexpr Pin RIGHT_ENABLE_PIN = 21;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin STANDBY_PIN = Motor::PIN_UNUSED;
#elif HBRIDGE == TB6612FNG
  /// @brief Pin definition for left enable. (PWMA)
  constexpr Pin LEFT_ENABLE_PIN = 32;
  /// @brief Pin definition for left backward motion. (AIN2)
  constexpr Pin LEFT_BACKWARD_PIN = 33;
  /// @brief Pin definition for left forward motion. (AIN1)
  constexpr Pin LEFT_FORWARD_PIN = 25;
  /// @brief Pin definition for standby control (STBY)
  constexpr Pin STANDBY_PIN = 26;
  /// @brief Pin definition for right forward motion. (BIN1)
  constexpr Pin RIGHT_FORWARD_PIN = 27;
  /// @brief Pin definition for right backward motion. (BIN2)
  constexpr Pin RIGHT_BACKWARD_PIN = 14;
  /// @brief Pin definition for right enable. (PWMB)
  constexpr Pin RIGHT_ENABLE_PIN = 12;
#else
#error "HBRIDGE not defined or not recognized. Define HBRIDGE as L298N, TB6612FNG, or BTS7960."
#endif
}