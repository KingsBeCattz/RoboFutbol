#pragma once

#include <types.h>
#include <MotorDriveUnit.h>
#include <tools/motors.hpp>
#include <pinout.hpp>

constexpr UnsignedPWM DEFAULT_DEADZONE = 70;

extern MotorDriveUnit motor_driver;

#if defined(DUAL) && defined(ESP32)

#include <variants/pinout.hpp>
extern MotorDriveUnit motor_driver_clone;
#define ALL_DRIVERS {motor_driver, motor_driver_clone}

#else
#define ALL_DRIVERS {motor_driver}
#endif

inline void configure_all_drivers(UnsignedPWM deadzone)
{
  MotorsTools::configure(motor_driver, deadzone, Pinout::HBridge);
#if defined(DUAL) && defined(ESP32)
  MotorsTools::configure(motor_driver_clone, deadzone, ClonedPinout::HBridge);
#endif
}