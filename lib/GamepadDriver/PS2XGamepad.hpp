#pragma once
#ifdef ESP32
#error "This header is intended for use with Arduino Uno. Please use Arduino Uno environments before including this file."
#else
#include <Arduino.h>
#include <util.hpp>
#include <GamepadState.hpp>
#include <PS2X_lib.h>
#include <pinout/arduino.hpp>

class PS2Gamepad : public IGamepad
{
public:
  bool begin() override
  {
    int error = _ps2x.config_gamepad(
        ArduinoPinout::PS2_CLK_PIN,
        ArduinoPinout::PS2_CMD_PIN,
        ArduinoPinout::PS2_ATT_PIN,
        ArduinoPinout::PS2_DAT_PIN,
        ArduinoPinout::PS2_PRESSURES,
        ArduinoPinout::PS2_RUMBLE);
    _initialized = (error == 0);
    return _initialized;
  }

  void reset()
  {
    _state.buttons.reset();
    _state.leftStick.update(0.0f, 0.0f);
    _state.rightStick.update(0.0f, 0.0f);
    _state.leftTrigger = 0;
    _state.rightTrigger = 0;
    _state.connected = false;
  }

  void update() override
  {
    if (!_initialized)
      return;
    _ps2x.read_gamepad(false, 0);
    uint8_t type = _ps2x.readType();
    bool nowConnected = (type == 1 || type == 2); // DualShock or Guitar

    // Detectar desconexion y resetear
    if (_state.connected && !nowConnected)
      reset();

    _state.connected = nowConnected;

    if (_state.connected)
    {
      _state.buttons.update(_mapButtons());
      // Left stick
      _state.leftStick.update(
          clamp((_ps2x.Analog(PSS_LX) - 128) / 128.0f, -1.0f, 1.0f),
          clamp((_ps2x.Analog(PSS_LY) - 128) / 128.0f, -1.0f, 1.0f));
      // Right stick
      _state.rightStick.update(
          clamp((_ps2x.Analog(PSS_RX) - 128) / 128.0f, -1.0f, 1.0f),
          clamp((_ps2x.Analog(PSS_RY) - 128) / 128.0f, -1.0f, 1.0f));
      // Triggers (L2 / R2) — pressure sensitive if PS2_PRESSURES = true
      _state.leftTrigger = _ps2x.Analog(PSAB_L2);
      _state.rightTrigger = _ps2x.Analog(PSAB_R2);
    }

    _state.last_connected = _state.connected;
  }
  const GamepadState &getState() const override { return _state; }
  bool isConnected() const { return _state.connected; }
  bool newlyConnected() const { return isConnected() && !_state.last_connected; }

private:
  PS2X _ps2x;
  bool _initialized = false;
  GamepadState _state;

  uint16_t _mapButtons()
  {
    uint16_t result = 0;
    // Face buttons — PS2X uses Button::NEW_BUTTON(btn) style checks
    if (_ps2x.Button(PSB_CROSS))
      result |= Button::A; // ✕  → A
    if (_ps2x.Button(PSB_CIRCLE))
      result |= Button::B; // ○  → B
    if (_ps2x.Button(PSB_SQUARE))
      result |= Button::X; // □  → X
    if (_ps2x.Button(PSB_TRIANGLE))
      result |= Button::Y; // △  → Y
    // D-Pad
    if (_ps2x.Button(PSB_PAD_UP))
      result |= Button::Up;
    if (_ps2x.Button(PSB_PAD_DOWN))
      result |= Button::Down;
    if (_ps2x.Button(PSB_PAD_LEFT))
      result |= Button::Left;
    if (_ps2x.Button(PSB_PAD_RIGHT))
      result |= Button::Right;
    // Shoulders
    if (_ps2x.Button(PSB_L1))
      result |= Button::LB;
    if (_ps2x.Button(PSB_R1))
      result |= Button::RB;
    // Stick clicks
    if (_ps2x.Button(PSB_L3))
      result |= Button::LS;
    if (_ps2x.Button(PSB_R3))
      result |= Button::RS;
    // Select / Start
    if (_ps2x.Button(PSB_SELECT))
      result |= Button::Select;
    if (_ps2x.Button(PSB_START))
      result |= Button::Start;
    return result;
  }
};
#endif