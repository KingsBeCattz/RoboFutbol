#include <Arduino.h>
#include <types.h>
#include <serial_tools.hpp>

#include <pinout.hpp>
#include <gamepad.hpp>

CurrentGamepad gamepad;

// #ifdef ESP32
// #include <esp32_pinout.hpp>
// #include <BP32Gamepad.hpp>

// #ifdef DUAL
// #include <esp32_clones.hpp>
// #endif

// Bluepad32Gamepad gamepad;
// #else
// #include <arduino_pinout.hpp>
// #include <PS2XGamepad.hpp>
// PS2Gamepad gamepad;
// #endif

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
  pinMode(Pinout::LED_STATUS_PIN, OUTPUT);

  digitalWrite(Pinout::LED_STATUS_PIN, HIGH);
  gamepad.begin();
  UnsignedPWM deadzone = 70;
  configure_drivers(deadzone);
  digitalWrite(Pinout::LED_STATUS_PIN, LOW);
  printTools::printHBridgeType();
  printTools::printPinout();
}

void loop()
{
  gamepad.update();
  if (!gamepad.isConnected())
  {
    digitalWrite(Pinout::LED_STATUS_PIN, LOW);
    delay(130);
    digitalWrite(Pinout::LED_STATUS_PIN, HIGH);
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