#pragma once

#include <tools/serial.hpp>
#include <Arduino.h>
#include <GamepadState.hpp>
#include <StickState.hpp>
#include <ButtonState.hpp>

namespace DebugTools
{
  inline void advice()
  {
    Serial.println("-> Debug mode active: Verbose gamepad state will be printed every loop.");
    Serial.println("-> To disable debug mode, comment out the #define DEBUG line in src/main.cpp and re-upload the firmware.");
  }
  inline void snitchJoystick(const StickState &stick, const char *name)
  {
    SerialTools::printf("%s - Raw: (%.2f, %.2f) | Filtered: (%.2f, %.2f) | Delta: (%.2f, %.2f)\n",
                        name,
                        stick.raw.x, stick.raw.y,
                        stick.filtered.x, stick.filtered.y,
                        stick.delta().x, stick.delta().y);
  }

  inline void snitchButtons(const ButtonState &buttons)
  {
    uint16_t raw = buttons.raw();
    SerialTools::printf("Buttons - Raw: 0x%04X | A: %d | B: %d | X: %d | Y: %d | RB: %d | LB: %d | D-Pad: 0x%02X\n",
                        raw,
                        buttons.held(Button::A),
                        buttons.held(Button::B),
                        buttons.held(Button::X),
                        buttons.held(Button::Y),
                        buttons.held(Button::RB),
                        buttons.held(Button::LB),
                        raw & Button::DPAD_MASK);
  }

  inline void snitchTrigger(uint8_t value, const char *name)
  {
    SerialTools::printf("%s: %d\n", name, value);
  }

  inline void snitchGamepad(const GamepadState &state)
  {
    snitchJoystick(state.leftStick, "Left Stick");
    snitchJoystick(state.rightStick, "Right Stick");
    snitchTrigger(state.leftTrigger, "Left Trigger");
    snitchTrigger(state.rightTrigger, "Right Trigger");
    snitchButtons(state.buttons);
  }
}