#pragma once

#include <pinout.hpp>

#ifdef ESP32
#include <esp32_clones.hpp>
namespace ClonedPinout = ESP32ClonedPinout;
#else
#error "This header is not intended for use with Arduino; currently, there are no Arduino clones available due to hardware limitations."
#endif

inline void set_pines_driver_clone(MotorDriveUnit &motor_driver)
{
  motor_driver.getLeftMotor().setDirectionPins(ClonedPinout::LEFT_FORWARD_PIN, ClonedPinout::LEFT_BACKWARD_PIN, Pinout::USE_DIGITAL_DIRECTIONS);
  motor_driver.getRightMotor().setDirectionPins(ClonedPinout::RIGHT_FORWARD_PIN, ClonedPinout::RIGHT_BACKWARD_PIN, Pinout::USE_DIGITAL_DIRECTIONS);
#if HBRIDGE == BTS7960 || HBRIDGE == TB6612FNG
  motor_driver.getLeftMotor().setEnablePin(ClonedPinout::LEFT_ENABLE_PIN, Pinout::USE_DIGITAL_ENABLES);
  motor_driver.getRightMotor().setEnablePin(ClonedPinout::RIGHT_ENABLE_PIN, Pinout::USE_DIGITAL_ENABLES);
#endif
#if HBRIDGE == TB6612FNG
  motor_driver.setDriverEnablePin(ClonedPinout::STANDBY_PIN, Pinout::USE_DIGITAL_STBY);
#endif
}

inline void setup_driver_clone(MotorDriveUnit &motor_driver, UnsignedPWM deadzone)
{
  set_pines_driver_clone(motor_driver);
  motor_driver.setDeadzone(deadzone);
  motor_driver.begin();
}