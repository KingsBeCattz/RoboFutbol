#pragma once
#include <stdint.h>

enum Button : uint16_t
{
  // Botones (XBOX / PS / NINTENDO)

  /// @brief (A / X / B)
  A = 1 << 0,
  /// @brief (B / O / A)
  B = 1 << 1,
  /// @brief (X / [] / Y)
  X = 1 << 2,
  /// @brief (Y / Δ / X)
  Y = 1 << 3,

  // D-Pad
  Up = 1 << 4,
  Down = 1 << 5,
  Left = 1 << 6,
  Right = 1 << 7,
  DPAD_MASK = 1 << 4 | 1 << 5 | 1 << 6 | 1 << 7,

  // Bumpers
  LB = 1 << 8,
  RB = 1 << 9,

  // Stick Buttons
  LS = 1 << 10,
  RS = 1 << 11,

  // Sistema
  Select = 1 << 12, // PS: Share, XBOX: View, NINTENDO: Minus
  Start = 1 << 13,  // PS: Option, XBOX: Menu, NINTENDO: Plus

};

inline uint16_t operator|(Button a, Button b)
{
  return static_cast<uint16_t>(a) | static_cast<uint16_t>(b);
}
inline uint16_t operator|(uint16_t a, Button b)
{
  return a | static_cast<uint16_t>(b);
}

// Helper para leer el estado
class ButtonState
{
public:
  explicit ButtonState(uint16_t mask = 0) : _current(mask) {}

  void reset()
  {
    _current = 0;
    _previous = 0;
  }

  void update(uint16_t newMask)
  {
    _previous = _current;
    _current = newMask;
  }

  // Está presionado ahora
  bool held(Button b) const
  {
    return _current & static_cast<uint16_t>(b);
  }

  // Acaba de presionarse este frame
  bool pressed(Button b) const
  {
    uint16_t bit = static_cast<uint16_t>(b);
    return (_current & bit) && !(_previous & bit);
  }

  // Acaba de soltarse este frame
  bool released(Button b) const
  {
    uint16_t bit = static_cast<uint16_t>(b);
    return !(_current & bit) && (_previous & bit);
  }

  // Varios botones a la vez (combo)
  bool combo(uint16_t mask) const
  {
    return (_current & mask) == mask;
  }

  uint16_t raw() const { return _current; }

private:
  uint16_t _current = 0;
  uint16_t _previous = 0;
};