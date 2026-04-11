#pragma once
#ifdef ESP32
#include <util.hpp>
#include <GamepadState.hpp>
#include <Bluepad32.h>
class Bluepad32Gamepad : public IGamepad
{
public:
  bool begin() override
  {
    _instance = this;
    BP32.setup(&onConnected, &onDisconnected);
    return true;
  }
  void update() override
  {
    BP32.update();
    if (_controller && _controller->isConnected())
    {
      _state.connected = true;
      _state.buttons.update(_mapButtons());
      _state.leftStick.update(
          clamp(_controller->axisX() / 512.0f, -1.0f, 1.0f),
          clamp(_controller->axisY() / 512.0f, -1.0f, 1.0f));
      _state.rightStick.update(
          clamp(_controller->axisRX() / 512.0f, -1.0f, 1.0f),
          clamp(_controller->axisRY() / 512.0f, -1.0f, 1.0f));
      _state.leftTrigger = _controller->brake() / 4;
      _state.rightTrigger = _controller->throttle() / 4;
    }
    else
    {
      _state.connected = false;
      reset();
    }
    _state.last_connected = _state.connected;
  }
  const GamepadState &getState() const override { return _state; }
  bool isConnected() const { return _state.connected; }
  bool newlyConnected() const { return isConnected() && !_state.last_connected; }
  void reset()
  {
    _state.buttons.reset();
    _state.leftStick.update(0.0f, 0.0f);
    _state.rightStick.update(0.0f, 0.0f);
    _state.leftTrigger = 0;
    _state.rightTrigger = 0;
    _state.connected = false;
  }

private:
  GamepadState _state;
  static ControllerPtr _controller;
  static Bluepad32Gamepad *_instance;

  static void onConnected(ControllerPtr ctl)
  {
    BP32.enableNewBluetoothConnections(false);
    _controller = ctl;
  }
  static void onDisconnected(ControllerPtr ctl)
  {
    BP32.enableNewBluetoothConnections(true);
    _controller = nullptr;
    if (_instance)
      _instance->reset();
  }
  uint16_t _mapButtons() const
  {
    uint16_t result = 0;
    if (_controller->a())
      result |= Button::A;
    if (_controller->b())
      result |= Button::B;
    if (_controller->x())
      result |= Button::X;
    if (_controller->y())
      result |= Button::Y;
    if (_controller->dpad() & DPAD_UP)
      result |= Button::Up;
    if (_controller->dpad() & DPAD_DOWN)
      result |= Button::Down;
    if (_controller->dpad() & DPAD_LEFT)
      result |= Button::Left;
    if (_controller->dpad() & DPAD_RIGHT)
      result |= Button::Right;
    if (_controller->l1())
      result |= Button::LB;
    if (_controller->r1())
      result |= Button::RB;
    if (_controller->thumbL())
      result |= Button::LS;
    if (_controller->thumbR())
      result |= Button::RS;
    if (_controller->miscSelect())
      result |= Button::Select;
    if (_controller->miscStart())
      result |= Button::Start;
    return result;
  }
};

ControllerPtr Bluepad32Gamepad::_controller = nullptr;
Bluepad32Gamepad *Bluepad32Gamepad::_instance = nullptr;
#endif