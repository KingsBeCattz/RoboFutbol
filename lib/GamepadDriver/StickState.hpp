#pragma once

#include <math.h>

struct StickVector
{
  float x = 0.0f;
  float y = 0.0f;

  constexpr StickVector() = default;
  constexpr StickVector(float x, float y) : x(x), y(y) {}

  float magnitude() const
  {
    return sqrtf(x * x + y * y);
  }

  float angle() const
  {
    return atan2f(y, x);
  }

  StickVector normalized() const
  {
    float m = magnitude();
    return (m > 0.0f) ? StickVector(x / m, y / m) : StickVector{};
  }

  void clamp(float min = -1.0f, float max = 1.0f)
  {
    x = fmaxf(min, fminf(max, x));
    y = fmaxf(min, fminf(max, y));
  }
};

// Declaration of operator*
inline StickVector operator*(const StickVector &v, float s)
{
  return {v.x * s, v.y * s};
}

struct StickState
{
  StickVector raw;      // Direct input from driver (normalized)
  StickVector filtered; // After deadzone/smoothing
  StickVector previous; // Previous frame state
  // float deadzone = 0.1f;

  void update(float newX, float newY)
  {
    previous = filtered;
    raw = {newX, newY};
    raw.clamp();
    filtered = applyDeadzone(raw);
  }

  StickVector delta() const
  {
    return {filtered.x - previous.x, filtered.y - previous.y};
  }

private:
  StickVector applyDeadzone(const StickVector &v) const
  {
    float mag = v.magnitude();
    // if (mag < deadzone)
    // return {};
    float scaled = mag / 1.0f; //(mag - deadzone) / (1.0f - deadzone);
    return v.normalized() *
           scaled;
  }
};