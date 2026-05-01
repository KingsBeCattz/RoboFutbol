#pragma once

#include <pinout.hpp>

#ifdef DUAL
#include <cloned_pinout.hpp>
#endif

#include <input_modes.hpp>
extern InputMode input_mode;

#include <MotorDriveUnit.h>

extern MotorDriveUnit motor_driver;

#if defined(DUAL) && defined(ESP32)
extern MotorDriveUnit motor_driver_clone;
#endif

inline void configure_drivers(UnsignedPWM deadzone)
{
  motor_driver.setDeadzone(deadzone);

  motor_driver.getLeftMotor().setDirectionPins(Pinout::LEFT_FORWARD_PIN, Pinout::LEFT_BACKWARD_PIN, Pinout::USE_DIGITAL_DIRECTIONS);
  motor_driver.getRightMotor().setDirectionPins(Pinout::RIGHT_FORWARD_PIN, Pinout::RIGHT_BACKWARD_PIN, Pinout::USE_DIGITAL_DIRECTIONS);

#if HBRIDGE != L298N
  motor_driver.getLeftMotor().setEnablePin(Pinout::LEFT_ENABLE_PIN, Pinout::USE_DIGITAL_ENABLES);
  motor_driver.getRightMotor().setEnablePin(Pinout::RIGHT_ENABLE_PIN, Pinout::USE_DIGITAL_ENABLES);
#endif

#if HBRIDGE == TB6612FNG
  motor_driver.setDriverEnablePin(STANDBY_PIN, USE_DIGITAL_STBY);
#endif

  motor_driver.setPowerSource(power_wrapper);
  set_input_mode(input_mode);
  motor_driver.begin();

#if defined(DUAL) && defined(ESP32)
  motor_driver_clone.setPowerSource(power_wrapper);
  setup_driver_clone(motor_driver_clone, deadzone);
#endif
}

inline void stop_motors()
{
  motor_driver.stop();

#if defined(DUAL) && defined(ESP32)
  motor_driver_clone.stop();
#endif
}

inline void set_exposition_active(bool active)
{
  motor_driver.setExpositionActive(active);
#if defined(DUAL) && defined(ESP32)
  motor_driver_clone.setExpositionActive(active);
#endif
}

inline void use_tank_drive()
{
  motor_driver.useTankDrive();
#if defined(DUAL) && defined(ESP32)
  motor_driver_clone.useTankDrive();
#endif
}

inline void update_drivers()
{
  motor_driver.update();
#if defined(DUAL) && defined(ESP32)
  motor_driver_clone.update();
#endif
}