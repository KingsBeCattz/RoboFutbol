#pragma once

#if DUAL != 1 || !defined(ESP32)
#error "This header is intended for use with ESP32. Please use ESP32 environments before including this file."
#endif

#include "esp32_pinout.hpp"
#include "types.h"
#include <MotorDriveUnit.h>

#if HBRIDGE == L298N
/// @brief Pin definition for left forward motion. (IN1)
constexpr Pin C_LEFT_FORWARD_PIN = 4;
/// @brief Pin definition for left backward motion. (IN2)
constexpr Pin C_LEFT_BACKWARD_PIN = 16;
/// @brief Pin definition for right forward motion. (IN3)
constexpr Pin C_RIGHT_FORWARD_PIN = 17;
/// @brief Pin definition for right backward motion. (IN4)
constexpr Pin C_RIGHT_BACKWARD_PIN = 5;
#elif HBRIDGE == BTS7960
/// @brief Pin definition clon for left enable. (R_EN and L_EN)
constexpr Pin C_LEFT_ENABLE_PIN = 32;
/// @brief Pin definition clon for left backward motion. (LPWM)
constexpr Pin C_LEFT_BACKWARD_PIN = 33;
/// @brief Pin definition clon for left forward motion. (RPWM)
constexpr Pin C_LEFT_FORWARD_PIN = 25;

/// @brief Pin definition clon for right forward motion. (RPWM)
constexpr Pin C_RIGHT_FORWARD_PIN = 18;
/// @brief Pin definition clon for right backward motion. (LPWM)
constexpr Pin C_RIGHT_BACKWARD_PIN = 19;
/// @brief Pin definition clon for right enable. (R_EN and L_EN)
constexpr Pin C_RIGHT_ENABLE_PIN = 21;
#elif HBRIDGE == TB6612FNG
/// @brief Pin definition for left enable. (PWMA)
constexpr Pin C_LEFT_ENABLE_PIN = 32;
/// @brief Pin definition for left backward motion. (AIN2)
constexpr Pin C_LEFT_BACKWARD_PIN = 33;
/// @brief Pin definition for left forward motion. (AIN1)
constexpr Pin C_LEFT_FORWARD_PIN = 25;
/// @brief Pin definition for standby control (STBY)
constexpr Pin C_STANDBY_PIN = 26;
/// @brief Pin definition for right forward motion. (BIN1)
constexpr Pin C_RIGHT_FORWARD_PIN = 27;
/// @brief Pin definition for right backward motion. (BIN2)
constexpr Pin C_RIGHT_BACKWARD_PIN = 14;
/// @brief Pin definition for right enable. (PWMB)
constexpr Pin C_RIGHT_ENABLE_PIN = 12;
#endif

void set_pines_driver_clone(MotorDriveUnit &motor_driver)
{
  motor_driver.getLeftMotor().setDirectionPins(C_LEFT_FORWARD_PIN, C_LEFT_BACKWARD_PIN, USE_DIGITAL_DIRECTIONS);
  motor_driver.getRightMotor().setDirectionPins(C_RIGHT_FORWARD_PIN, C_RIGHT_BACKWARD_PIN, USE_DIGITAL_DIRECTIONS);
#if HBRIDGE == BTS7960 || HBRIDGE == TB6612FNG
  motor_driver.getLeftMotor().setEnablePin(C_LEFT_ENABLE_PIN, USE_DIGITAL_ENABLES);
  motor_driver.getRightMotor().setEnablePin(C_RIGHT_ENABLE_PIN, USE_DIGITAL_ENABLES);
#endif
#if HBRIDGE == TB6612FNG
  motor_driver.setDriverEnablePin(C_STANDBY_PIN, USE_DIGITAL_STBY);
#endif
}

void setup_driver_clone(MotorDriveUnit &motor_driver, UnsignedPWM deadzone)
{
  set_pines_driver_clone(motor_driver);
  motor_driver.setDeadzone(deadzone);
  motor_driver.begin();
}

void print_clone_pinout()
{
  Serial.println("Clone Pinout:");
  Serial.print("C_LEFT_FORWARD_PIN: ");
  Serial.println(C_LEFT_FORWARD_PIN);
  Serial.print("C_LEFT_BACKWARD_PIN: ");
  Serial.println(C_LEFT_BACKWARD_PIN);
  Serial.print("C_RIGHT_FORWARD_PIN: ");
  Serial.println(C_RIGHT_FORWARD_PIN);
  Serial.print("C_RIGHT_BACKWARD_PIN: ");
  Serial.println(C_RIGHT_BACKWARD_PIN);
#if HBRIDGE == TB6612FNG || HBRIDGE == BTS7960
  Serial.print("C_LEFT_ENABLE_PIN: ");
  Serial.println(C_LEFT_ENABLE_PIN);
  Serial.print("C_RIGHT_ENABLE_PIN: ");
  Serial.println(C_RIGHT_ENABLE_PIN);
#endif
#if HBRIDGE == TB6612FNG
  Serial.print("C_STANDBY_PIN: ");
  Serial.println(C_STANDBY_PIN);
#endif
}