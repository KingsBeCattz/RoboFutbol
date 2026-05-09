#pragma once

#include <MotorDriveUnit.h>
#include <gamepad.hpp>
#include <types.h>

extern CurrentGamepad gamepad;

extern MotorDriveUnit motor_driver;

#if defined(DUAL) && defined(ESP32)
extern MotorDriveUnit motor_driver_clone;
#endif

enum class InputMode : uint8_t
{
  TRIGGER_STICK_RIGHT = 0, // D-Up
  TRIGGER_STICK_LEFT = 1,  // D-Down
  DUAL_STICK_RIGHT = 2,    // D-Right
  DUAL_STICK_LEFT = 3,     // D-Left
};

#ifdef ESP32
constexpr InputMode DEFAULT_INPUT_MODE = InputMode::TRIGGER_STICK_RIGHT;
#else
constexpr InputMode DEFAULT_INPUT_MODE = InputMode::DUAL_STICK_RIGHT;
#endif

inline SignedPWM
trigger_power_right()
{
  return (gamepad.held(Button::LB) ? 255 : gamepad.leftTrigger()) - (gamepad.held(Button::RB) ? 255 : gamepad.rightTrigger());
}

inline SignedPWM trigger_power_left()
{
  return -trigger_power_right();
}

inline SignedPWM left_stick_y()
{
  // Use the left stick's Y axis for steering control.
  return static_cast<SignedPWM>(gamepad.leftStick().filtered.y * 255);
}

inline SignedPWM right_stick_y()
{
  // Use the right stick's Y axis for steering control.
  return static_cast<SignedPWM>(gamepad.rightStick().filtered.y * 255);
}

inline SignedPWM left_stick_x()
{
  // Use the left stick's X axis for steering control.
  return static_cast<SignedPWM>(gamepad.leftStick().filtered.x * 255);
}

inline SignedPWM right_stick_x()
{
  // Use the right stick's X axis for steering control.
  return static_cast<SignedPWM>(gamepad.rightStick().filtered.x * 255);
}

inline void set_input_mode(MotorDriveUnit &driver, InputMode mode)
{
  switch (mode)
  {
  case InputMode::TRIGGER_STICK_RIGHT:
    driver.setPowerSource(trigger_power_right);
    driver.setDirectionSource(left_stick_x);
    break;
  case InputMode::TRIGGER_STICK_LEFT:
    driver.setPowerSource(trigger_power_left);
    driver.setDirectionSource(right_stick_x);
    break;
  case InputMode::DUAL_STICK_RIGHT:
    driver.setPowerSource(left_stick_y);
    driver.setDirectionSource(right_stick_x);
    break;
  case InputMode::DUAL_STICK_LEFT:
    driver.setPowerSource(right_stick_y);
    driver.setDirectionSource(left_stick_x);
    break;
  }
}

inline void change_input_mode(MotorDriveUnit &driver, InputMode &current_mode)
{
  auto previous_mode = current_mode;

  if (gamepad.pressed(Button::Up))
    current_mode = InputMode::TRIGGER_STICK_RIGHT;
  else if (gamepad.pressed(Button::Down))
    current_mode = InputMode::TRIGGER_STICK_LEFT;
  else if (gamepad.pressed(Button::Right))
    current_mode = InputMode::DUAL_STICK_RIGHT;
  else if (gamepad.pressed(Button::Left))
    current_mode = InputMode::DUAL_STICK_LEFT;

  if (current_mode != previous_mode)
    set_input_mode(driver, current_mode);
}