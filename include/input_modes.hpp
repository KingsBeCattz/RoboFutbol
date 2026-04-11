#pragma once

#ifdef ESP32
#include <BP32Gamepad.hpp>
extern Bluepad32Gamepad gamepad;
#else
#include <PS2XGamepad.hpp>
extern PS2Gamepad gamepad;
#endif

#include <MotorDriveUnit.h>

extern MotorDriveUnit motor_driver;

#if defined(DUAL) && defined(ESP32)
extern MotorDriveUnit motor_driver_clone;
#endif

#include <types.h>

enum class InputMode : uint8_t
{
  TRIGGER_STICK_RIGHT = 0, // D-Up
  TRIGGER_STICK_LEFT = 1,  // D-Down
  DUAL_STICK_RIGHT = 2,    // D-Right
  DUAL_STICK_LEFT = 3,     // D-Left
};

SourceFn raw_power_fn = nullptr;

inline SignedPWM power_wrapper()
{
  SignedPWM raw_power = raw_power_fn ? raw_power_fn() : 0;
  if (gamepad.held(Button::A))
    return raw_power;
  return raw_power / 2;
}

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

inline void set_input_mode(InputMode mode)
{
  switch (mode)
  {
  case InputMode::TRIGGER_STICK_RIGHT:
    raw_power_fn = trigger_power_right;
    motor_driver.setDirectionSource(left_stick_x);
    break;
  case InputMode::TRIGGER_STICK_LEFT:
    raw_power_fn = trigger_power_left;
    motor_driver.setDirectionSource(right_stick_x);
    break;
  case InputMode::DUAL_STICK_RIGHT:
    raw_power_fn = left_stick_y;
    motor_driver.setDirectionSource(right_stick_x);
    break;
  case InputMode::DUAL_STICK_LEFT:
    raw_power_fn = right_stick_y;
    motor_driver.setDirectionSource(left_stick_x);
    break;
  }

#if defined(DUAL) && defined(ESP32)
  motor_driver_clone.setDirectionSource(motor_driver.getDirectionSourceFunction());
#endif
}

inline void change_input_mode(InputMode &current_mode)
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
    set_input_mode(current_mode);
}