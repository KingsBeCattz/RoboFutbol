#pragma once

#include <Motor.h>
#include <stdint.h>
#include <types.h>

namespace ESP32Pinout
{

  constexpr Pin LED_STATUS_PIN = 2;
  constexpr Pin SPEED_LIMIT_PIN = 34;

#if HBRIDGE == L298N
  constexpr const char *hbridge = "L298N";
  constexpr bool USE_DIGITAL_DIRECTIONS = false;
  constexpr bool USE_DIGITAL_ENABLES = false;
  constexpr bool USE_DIGITAL_STBY = false;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin LEFT_ENABLE_PIN = Motor::PIN_UNUSED;
  /// @brief Pin definition for left forward motion. (IN1)
  constexpr Pin LEFT_FORWARD_PIN = 27;
  /// @brief Pin definition for left backward motion. (IN2)
  constexpr Pin LEFT_BACKWARD_PIN = 14;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin RIGHT_ENABLE_PIN = Motor::PIN_UNUSED;
  /// @brief Pin definition for right forward motion. (IN3)
  constexpr Pin RIGHT_FORWARD_PIN = 25;
  /// @brief Pin definition for right backward motion. (IN4)
  constexpr Pin RIGHT_BACKWARD_PIN = 26;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin STANDBY_PIN = Motor::PIN_UNUSED;

#elif HBRIDGE == TB6612FNG
  constexpr const char *hbridge = "TB6612FNG";
  constexpr bool USE_DIGITAL_DIRECTIONS = true;
  constexpr bool USE_DIGITAL_ENABLES = false;
  constexpr bool USE_DIGITAL_STBY = true;
  /// @brief Pin definition for left enable. (PWMA)
  constexpr Pin LEFT_ENABLE_PIN = 4;
  /// @brief Pin definition for left backward motion. (AIN2)
  constexpr Pin LEFT_BACKWARD_PIN = 16;
  /// @brief Pin definition for left forward motion. (AIN1)
  constexpr Pin LEFT_FORWARD_PIN = 17;
  /// @brief Pin definition for standby control (STBY)
  constexpr Pin STANDBY_PIN = 5;
  /// @brief Pin definition for right forward motion. (BIN1)
  constexpr Pin RIGHT_FORWARD_PIN = 18;
  /// @brief Pin definition for right backward motion. (BIN2)
  constexpr Pin RIGHT_BACKWARD_PIN = 19;
  /// @brief Pin definition for right enable. (PWMB)
  constexpr Pin RIGHT_ENABLE_PIN = 21;

#elif HBRIDGE == BTS7960
  constexpr const char *hbridge = "BTS7960";
  constexpr bool USE_DIGITAL_DIRECTIONS = true;
  constexpr bool USE_DIGITAL_ENABLES = true;
  constexpr bool USE_DIGITAL_STBY = false;
  /// @brief Pin definition for left enable. (R_EN and L_EN)
  constexpr Pin LEFT_ENABLE_PIN = 26;
  /// @brief Pin definition for left backward motion. (LPWM)
  constexpr Pin LEFT_BACKWARD_PIN = 27;
  /// @brief Pin definition for left forward motion. (RPWM)
  constexpr Pin LEFT_FORWARD_PIN = 14;
  /// @brief Pin definition for right forward motion. (RPWM)
  constexpr Pin RIGHT_FORWARD_PIN = 5;
  /// @brief Pin definition for right backward motion. (LPWM)
  constexpr Pin RIGHT_BACKWARD_PIN = 17;
  /// @brief Pin definition for right enable. (R_EN and L_EN)
  constexpr Pin RIGHT_ENABLE_PIN = 16;
  /// @brief This pin is a fallback; it should not be used.
  constexpr Pin STANDBY_PIN = Motor::PIN_UNUSED;

#else
#error "HBRIDGE not defined or not recognized. Define HBRIDGE as L298N, TB6612FNG, or BTS7960."
#endif

}