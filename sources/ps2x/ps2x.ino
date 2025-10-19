/**
 * ROBO-FUTBOL XOCHIMILCO 2025
 * Arduino Compatible Board
 * SUPPORTED GAMEPADS: PS2 Wireless Controller
 * Written by: Johan 5CMT
 */

// This code has not been tested at the time of publication. Please report any problems.

#include <PS2X_lib.h>
#include <MotorDriveUnit.h>

#define USE_PWM_MOTOR_PIN
// #define USE_DIGITAL_MOTOR_PIN
// #define USE_PWM_ENABLE_PIN
// #define USE_DIGITAL_ENABLE_PIN

#if (defined(USE_PWM_MOTOR_PIN) + defined(USE_DIGITAL_MOTOR_PIN)) != 1
    #error "You can only choose between using one or the other for the pins that control both motors."
#endif

#if (defined(USE_PWM_ENABLE_PIN) + defined(USE_DIGITAL_ENABLE_PIN)) > 1
    #error "You can only choose between using one or the other so that the enable pins are PWM or not."
#endif

#ifdef USE_PWM_MOTOR_PIN
  #define DIGITAL_DIRECTION false
#else
  #define DIGITAL_DIRECTION true
#endif

#define forward_left_pin 9
#define backward_left_pin 6
#define forward_right_pin 5
#define backward_right_pin 3

#if (defined(USE_PWM_ENABLE_PIN) || defined(USE_DIGITAL_ENABLE_PIN))
  #define enable_left_pin 10
  #define enable_right_pin 11
#else
  #define enable_left_pin Motor::PIN_UNUSED
  #define enable_right_pin Motor::PIN_UNUSED
#endif

#ifdef USE_PWM_ENABLE_PIN
  #define DIGITAL_ENABLE false
#else
  #define DIGITAL_ENABLE true
#endif

PS2X ps2x;
MotorDriveUnit motor_driver(DIGITAL_DIRECTION, DIGITAL_ENABLE, forward_left_pin, backward_left_pin, forward_right_pin, backward_right_pin, enable_left_pin, enable_right_pin);

uint8_t left_stick[2] = {128, 128};
uint8_t right_stick[2] = {128, 128};

uint8_t *x_stick = right_stick;
uint8_t *y_stick = left_stick;

// --- Stick helpers ---
inline int16_t map_stick(uint8_t value)
{
  int16_t delta = (int16_t)value - 128;
  if (delta > 0)
    return delta * 255 / 127;
  if (delta < 0)
    return delta * 255 / 128;
  return 0;
}

inline int16_t use_left_y_axis()
{
  return map_stick(y_stick[1]);
}

inline int16_t use_left_x_axis()
{
  return map_stick(x_stick[0]);
}

void set_stick_position(uint8_t (&stick)[2], uint8_t x, uint8_t y)
{
  stick[0] = x;
  stick[1] = 255 - y;
}

// --- Stick swapping ---
void switch_power_source()
{
  int16_t (*current_source)() = motor_driver.getPowerSourceFunction();
  if (current_source == use_left_y_axis)
    motor_driver.setPowerSource(use_left_x_axis);
  else
    motor_driver.setPowerSource(use_left_y_axis);
}

void switch_direction_source()
{
  int16_t (*current_source)() = motor_driver.getDirectionSourceFunction();
  if (current_source == use_left_x_axis)
    motor_driver.setDirectionSource(use_left_y_axis);
  else
    motor_driver.setDirectionSource(use_left_x_axis);
}

void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);

  motor_driver.begin();
  motor_driver.setDeadzone(70);
  motor_driver.setPowerSource(use_left_y_axis);
  motor_driver.setDirectionSource(use_left_x_axis);

  switch (ps2x.config_gamepad(4, 12, 7, 13, false, false))
  {
  case 0:
    Serial.println("Controller found.");
    break;
  case 1:
    Serial.println("No controller found.");
    break;
  case 2:
    Serial.println("Controller found but not accepting commands.");
    break;
  case 3:
    Serial.println("Controller refusing to enter Pressures mode.");
    break;
  }
}

void loop()
{
  ps2x.read_gamepad();
  set_stick_position(left_stick, ps2x.Analog(PSS_LX), ps2x.Analog(PSS_LY));
  set_stick_position(right_stick, ps2x.Analog(PSS_RX), ps2x.Analog(PSS_RY));

  if (ps2x.ButtonPressed(PSB_SELECT))
    switch_power_source();
  if (ps2x.ButtonPressed(PSB_START))
    switch_direction_source();

  if (ps2x.Button(PSB_BLUE))
  {
    int16_t left_power = map_stick(y_stick[0]);
    int16_t right_power = map_stick(y_stick[0]);
    motor_driver.useManualDrive(static_cast<uint8_t>(abs(left_power)), left_power >= 0, static_cast<uint8_t>(abs(right_power)), right_power >= 0);
  }

  else if (ps2x.Button(PSB_GREEN))
  {
    motor_driver.setExpositionActive(map_stick(y_stick[1]));
  }
  else if (ps2x.Button(PSB_PINK))
  {
    motor_driver.useTankDrive();
  }
  else
  {
    motor_driver.update();
  }

  delay(10);
}
