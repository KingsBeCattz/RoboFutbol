#include <Arduino.h>
#include <types.h>

#ifdef ESP32
#include <esp32_pinout.hpp>
#include <BP32Gamepad.hpp>

#ifdef DUAL
#include <esp32_clones.hpp>
#endif

Bluepad32Gamepad gamepad;
#else
#include <arduino_pinout.hpp>
#include <PS2XGamepad.hpp>
PS2Gamepad gamepad;
#endif

bool half_power = false;

#include <MotorDriveUnit.h>
MotorDriveUnit motor_driver;
#if defined(DUAL) && defined(ESP32)
MotorDriveUnit motor_driver_clone;
#endif

#include <input_modes.hpp>
InputMode input_mode =
#ifdef ESP32
    InputMode::TRIGGER_STICK_RIGHT
#else
    InputMode::DUAL_STICK_RIGHT
#endif
    ;

#include <driver_utils.hpp>

void setup()
{
  Serial.begin(115200);
  pinMode(LED_STATUS_PIN, OUTPUT);
  pinMode(SPEED_LIMIT_PIN, INPUT_PULLUP);
  if (digitalRead(SPEED_LIMIT_PIN) == LOW)
  {
    half_power = true;
    Serial.println("Half power mode activated due to SPEED_LIMIT_PIN state.");
  }
  gamepad.begin();
  UnsignedPWM deadzone = 70;

  configure_drivers(deadzone);
}

void loop()
{
  gamepad.update();
  if (!gamepad.isConnected())
  {
    digitalWrite(LED_STATUS_PIN, LOW);
    delay(130);
    digitalWrite(LED_STATUS_PIN, HIGH);
    delay(130);
    gamepad.reset();
    stop_motors();

    return;
  }

  if (gamepad.getState().buttons.raw() & Button::DPAD_MASK)
    change_input_mode(input_mode);

  set_exposition_active(gamepad.held(Button::Y));

  if (gamepad.held(Button::X))
    use_tank_drive();

  update_drivers();
  delay(10);
}