#include <Arduino.h>

#include <pinout.hpp>

#if DUAL == 1
#include <variants/pinout.hpp>
#endif

#include <gamepad.hpp>
#include <drivers.hpp>
#include <debug.hpp>
#include <tools/serial.hpp>
#include <tools/motors.hpp>
#include <input_modes.hpp>

// #define DEBUG

CurrentGamepad gamepad;

InputMode input_mode = DEFAULT_INPUT_MODE;

void setup()
{
  BP32.forgetBluetoothKeys();
  Serial.begin(115200);
  pinMode(Pinout::LED_STATUS_PIN, OUTPUT);

#ifdef DEBUG
  DebugTools::advice();
#endif

  digitalWrite(Pinout::LED_STATUS_PIN, HIGH);
  gamepad.begin();

  configure_all_drivers(DEFAULT_DEADZONE);

  digitalWrite(Pinout::LED_STATUS_PIN, LOW);
  SerialTools::printVersion();
#ifndef ESP32
  Pinout::printControllerPins();
#endif
  SerialTools::printHBridgeType();
  SerialTools::printHbridgePinout(Pinout::HBridge);
#if DUAL == 1
  SerialTools::printHbridgePinout(ClonedPinout::HBridge);
#endif
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

    MotorsTools::stop(ALL_DRIVERS);

    return;
  }

  if (gamepad.getState().buttons.raw() & Button::DPAD_MASK)
    MotorsTools::set_input_mode(ALL_DRIVERS, input_mode);

  MotorsTools::set_exposition(ALL_DRIVERS, gamepad.held(Button::Y));

  if (gamepad.held(Button::X))
    MotorsTools::use_tank_drive(ALL_DRIVERS);

  MotorsTools::update(ALL_DRIVERS);

#ifdef DEBUG
  DebugTools::snitchGamepad(gamepad.getState());
#endif

  delay(10);
}