#pragma once
#include "StickState.hpp"
#include "ButtonState.hpp"

struct GamepadState
{
  StickState leftStick;
  StickState rightStick;
  uint8_t leftTrigger = 0;     // 0-255
  uint8_t rightTrigger = 0;    // 0-255
  ButtonState buttons;         // bitmask
  bool connected = false;      // gamepad detected and initialized
  bool last_connected = false; // previous frame connection state
};

class IGamepad
{
public:
  virtual ~IGamepad() = default;
  virtual bool begin() = 0;
  virtual void update() = 0;
  virtual const GamepadState &getState() const = 0;

  const StickState &leftStick() const { return getState().leftStick; }
  const StickState &rightStick() const { return getState().rightStick; }

  uint8_t leftTrigger() const { return getState().leftTrigger; }
  uint8_t rightTrigger() const { return getState().rightTrigger; }

  bool held(Button b) const { return getState().buttons.held(b); }
  bool pressed(Button b) const { return getState().buttons.pressed(b); }
  bool released(Button b) const { return getState().buttons.released(b); }

  bool isConnected() const
  {
    return getState().connected;
  }
  bool newlyConnected() const { return isConnected() && !getState().last_connected; }
};