/**
 * ROBO-FUTBOL XOCHIMILCO 2025
 * ESP32-WROOM-32-N4
 * SUPPORTED GAMEPADS: https://bluepad32.readthedocs.io/en/latest/supported_gamepads/
 * Written by: Johan 4CMT
 */

#include <Flagger.h>
#include <Arduino.h>
#include <Bluepad32.h>
#include "esp32/clk.h"

#define ENABLE_DIGITAL_OUT (1 << 0)
#define ENABLE_PWM_OUT (1 << 1)
#define ENABLE_EN_OUT (1 << 2)
#define ENABLE_SPEED_OUT (1 << 3)
#define HOLD_DIGITAL (1 << 4)

#define flags 0 | (ENABLE_DIGITAL_OUT | ENABLE_SPEED_OUT | HOLD_DIGITAL)

#if flags == 0
#error You did not declare any configuration.
#endif
#if flags >= (1 << 5)
#warning You declared a configuration that seems to be invalid, the code will compile but there will be no effect to that declared flag.
#endif

#define BLINK (1 << 0)          // Defines the mask of the bit on the index 0
#define AXIS_LY (1 << 1)        // Defines the mask of the bit on the index 1
#define AXIS_RX (1 << 2)        // Defines the mask of the bit on the index 2
#define SELECT_PRESSED (1 << 3) // Defines the mask of the bit on the index 3
#define START_PRESSED (1 << 4)  // Defines the mask of the bit on the index 4

// Sets the game_flags to 0 and switch the bit on BLINK (index [0]) as true
uint8_t game_flags = 0 | BLINK;

int16_t exhibition_speed = 0;

// PIN_OUT
#if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT
const uint8_t D_M1_IN1 = 25;
const uint8_t D_M1_IN2 = 26;
const uint8_t D_M2_IN1 = 19;
const uint8_t D_M2_IN2 = 18;
#endif
#if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
const uint8_t PWM_M1_IN1 = 27;
const uint8_t PWM_M1_IN2 = 14;
const uint8_t PWM_M2_IN1 = 17;
const uint8_t PWM_M2_IN2 = 16;
#endif
#if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT
const uint8_t M1_ENABLE = 33;
const uint8_t M2_ENABLE = 22;
#endif
#if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT
const uint8_t M1_PWM_SPEED = 32;
const uint8_t M2_PWM_SPEED = 23;
#endif

// Instances a new void controller
ControllerPtr Controller = nullptr;

// Uses the flagger functions
using namespace flagger;

// Configure the joystick deadzone
const int JOYSTICK_DEAD_ZONE = 30;

void setup()
{
  setCpuFrequencyMhz(240);
  Serial.begin(115200);
  pinMode(2, OUTPUT);

#if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT
  pinMode(D_M1_IN1, OUTPUT);
  pinMode(D_M1_IN2, OUTPUT);
  pinMode(D_M2_IN1, OUTPUT);
  pinMode(D_M2_IN2, OUTPUT);
#endif
#if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
  pinMode(PWM_M1_IN1, OUTPUT);
  pinMode(PWM_M1_IN2, OUTPUT);
  pinMode(PWM_M2_IN1, OUTPUT);
  pinMode(PWM_M2_IN2, OUTPUT);
#endif
#if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT
  pinMode(M1_ENABLE, OUTPUT);
  pinMode(M2_ENABLE, OUTPUT);
#endif
#if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT
  pinMode(M1_PWM_SPEED, OUTPUT);
  pinMode(M2_PWM_SPEED, OUTPUT);
#endif

  BP32.setup(&onConnectedController, &onDisconnectedController);
  resetMotors();
  BP32.forgetBluetoothKeys();
}

void onConnectedController(ControllerPtr gamepad)
{
  if (Controller == nullptr)
  {
    Serial.print("--- Controller of ");
    Serial.print(gamepad->getModelName());
    Serial.println(" is connected ---");
    Controller = gamepad;
    remove(game_flags, BLINK);
    digitalWrite(2, HIGH);
    BP32.enableNewBluetoothConnections(false);
  }
  else
  {
    gamepad->disconnect();
  }

  resetMotors();
}

void onDisconnectedController(ControllerPtr gamepad)
{
  if (Controller == gamepad)
  {
    Serial.println("--- Controller is disconnected ---");
    Controller = nullptr;
    add(game_flags, BLINK);
    game_flags |= BLINK;
    resetMotors();
    BP32.enableNewBluetoothConnections(true);
  }
}

int16_t parseBumperAndTrigger(bumper: bool, trigger: int32_t)
{
  return bumper ? 255 : trigger;
}

/**
 * Just return a value from -255 to 255.
 * The first value is the bluepad32's controller and the second value is a boolean who represents if the speed is from the left joystick or not
 */
int16_t handleDualSpeed(ControllerPtr gamepad, bool joystick)
{
  int dpad_state_ud = gamepad->dpad();
  if (dpad_state_ud & 1)
    return 255;
  if (dpad_state_ud & 2)
    return -255;
  if (joystick)
  {
    const int X = gamepad->axisX();
    const int Y = gamepad->axisY() * -1;
    const float distance = constrain(sqrt(X * X + Y * Y), JOYSTICK_DEAD_ZONE * 3, 511);
    const uint8_t speed = map(round(distance), JOYSTICK_DEAD_ZONE * 3, 511, 0, 255);

    return Y > 0 ? speed : speed * -1;
  }

  return parseBumperAndTrigger(gamepad->r1(), gamepad->throttle()) - parseBumperAndTrigger(gamepad->l1(), gamepad->brake());
}

/**
 * Just return a value from -1.0 to 1.0 with middle points like 0.55.
 * The first value is the bluepad32's controller and the second value is a boolean who represents if the direction is from the right joystick or from the left stick
 */
int handleDirection(ControllerPtr gamepad, bool joystick)
{
  int dpad_state_lr = gamepad->dpad();
  if (dpad_state_lr & 4)
  {
    return 100;
  }

  if (dpad_state_lr & 8)
  {
    return -100;
  }

  const int direction = ((joystick ? gamepad->axisRX() : gamepad->axisX()) / 512.0) * 100;
  if (abs(direction) < JOYSTICK_DEAD_ZONE)
    return 0;
  int out = map(abs(direction), JOYSTICK_DEAD_ZONE, 90, 0, 100);
  if (out > 100)
    out = 100;
  return direction > 0 ? out : out * -1;
}

/// Resets the motors for safety
void resetMotors()
{
#if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT
  // This only compiles if the flags has the flag for PWM Enable, aka: "Speed Out"
  analogWrite(M1_PWM_SPEED, 0);
  analogWrite(M2_PWM_SPEED, 0);
#endif // #if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT

#if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT
  // This only compiles if the flags has the flag for Digital Enable
  digitalWrite(M1_ENABLE, false);
  digitalWrite(M2_ENABLE, false);
#endif // #if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT

#if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT
  digitalWrite(D_M1_IN1, false);
  digitalWrite(D_M2_IN1, false);
  digitalWrite(D_M1_IN2, false);
  digitalWrite(D_M2_IN2, false);
#endif // #if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT

#if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
  // This only compiles if the flags has the flag for PWM Output per In X
  analogWrite(PWM_M1_IN1, 0);
  analogWrite(PWM_M2_IN1, 0);
  analogWrite(PWM_M1_IN2, 0);
  analogWrite(PWM_M2_IN2, 0);
#endif // #if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
}

void handleMovement(ControllerPtr gamepad, uint8_t PWM, float DIRECTION, bool INX)
{
  const bool PANIC = gamepad->x();
  const int M1_PWM = round(PWM * (DIRECTION < 0.0f ? 1.00f - fabs(DIRECTION) : 1.00f));
  const int M2_PWM = round(PWM * (DIRECTION > 0.0f ? 1.00f - fabs(DIRECTION) : 1.00f));

#if ((flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT) || ((flags & ENABLE_EN_OUT) == ENABLE_EN_OUT)
  // This only compiles if the flags has the flag for Digital Enable or Digital Out per In X
  const bool DIGITAL_BASE_M1 = (M1_PWM > 0);
  const bool DIGITAL_BASE_M2 = (M2_PWM > 0);
#endif // #if ((flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT) || ((flags & ENABLE_EN_OUT) == ENABLE_EN_OUT)

#if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT
  // This only compiles if the flags has the flag for PWM Enable, aka: "Speed Out"
  analogWrite(M1_PWM_SPEED, M1_PWM);
  analogWrite(M2_PWM_SPEED, M2_PWM);
#endif // #if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT

#if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT
  // This only compiles if the flags has the flag for Digital Enable
  digitalWrite(M1_ENABLE, DIGITAL_BASE_M1);
  digitalWrite(M2_ENABLE, DIGITAL_BASE_M2);
#endif // #if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT

#if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT
  // This only compiles if the flags has the flag for Digital Output per In X
  const bool HOLD = has(flags, HOLD_DIGITAL); // This checks if the flags has the flag to hold the digital pins
  const bool DIGITAL_M1 = HOLD ? DIGITAL_BASE_M1 : !(DIRECTION < 0.0f);
  const bool DIGITAL_M2 = HOLD ? DIGITAL_BASE_M2 : !(DIRECTION > 0.0f);
  digitalWrite(!INX ? D_M1_IN1 : D_M1_IN2, DIGITAL_M1 && PANIC ? DIGITAL_M1 : false);
  digitalWrite(!INX ? D_M2_IN1 : D_M2_IN2, DIGITAL_M2 && PANIC ? DIGITAL_M2 : false);
  digitalWrite(INX ? D_M1_IN1 : D_M1_IN2, DIGITAL_M1 && PANIC ? false : DIGITAL_M1);
  digitalWrite(INX ? D_M2_IN1 : D_M2_IN2, DIGITAL_M2 && PANIC ? false : DIGITAL_M2);
#endif // #if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT

#if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
  // This only compiles if the flags has the flag for PWM Output per In X
  analogWrite(INX ? PWM_M1_IN1 : PWM_M1_IN2, M1_PWM < PWM && PANIC ? 0 : M1_PWM);
  analogWrite(INX ? PWM_M2_IN1 : PWM_M2_IN2, M2_PWM < PWM && PANIC ? 0 : M2_PWM);
  analogWrite(!INX ? PWM_M1_IN1 : PWM_M1_IN2, M1_PWM < PWM && PANIC ? 255 - M1_PWM : 0);
  analogWrite(!INX ? PWM_M2_IN1 : PWM_M2_IN2, M2_PWM < PWM && PANIC ? 255 - M2_PWM : 0);
#endif // #if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
}

void checkConfig(ControllerPtr gamepad)
{
  if (!has(game_flags, SELECT_PRESSED) && gamepad->miscSelect())
  {
    add(game_flags, SELECT_PRESSED);
    toggle(game_flags, AXIS_LY);
  }
  if (has(game_flags, SELECT_PRESSED) && !gamepad->miscSelect())
  {
    remove(game_flags, SELECT_PRESSED);
  }
  if (!has(game_flags, START_PRESSED) && gamepad->miscStart())
  {
    add(game_flags, START_PRESSED);
    toggle(game_flags, AXIS_RX);
  }
  if (has(game_flags, START_PRESSED) && !gamepad->miscStart())
  {
    toggle(game_flags, START_PRESSED);
  }
  if (gamepad->y())
  {
    exhibition_speed = handleDualSpeed(gamepad, game_flags & AXIS_LY);
  }
  if (exhibition_speed != 0 && gamepad->b())
  {
    exhibition_speed = 0;
  }
}

void exhibition(int16_t PWM)
{
#if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT
  // This only compiles if the flags has the flag for PWM Enable, aka: "Speed Out"
  analogWrite(M1_PWM_SPEED, abs(PWM));
  analogWrite(M2_PWM_SPEED, abs(PWM));
#endif // #if (flags & ENABLE_SPEED_OUT) == ENABLE_SPEED_OUT

#if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT
  // This only compiles if the flags has the flag for Digital Enable
  digitalWrite(M1_ENABLE, abs(PWM) > 0);
  digitalWrite(M2_ENABLE, abs(PWM) > 0);
#endif // #if (flags & ENABLE_EN_OUT) == ENABLE_EN_OUT

#if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT
  // This only compiles if the flags has the flag for Digital Output per In X
  digitalWrite(PWM > 0 ? D_M1_IN1 : D_M1_IN2, true);
  digitalWrite(!(PWM > 0) ? D_M1_IN1 : D_M1_IN2, false);
  digitalWrite(PWM < 0 ? D_M2_IN1 : D_M2_IN2, true);
  digitalWrite(!(PWM < 0) ? D_M2_IN1 : D_M2_IN2, false);
#endif // #if (flags & ENABLE_DIGITAL_OUT) == ENABLE_DIGITAL_OUT

#if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
  // This only compiles if the flags has the flag for PWM Output per In X
  analogWrite(PWM > 0 ? PWM_M1_IN1 : PWM_M1_IN2, abs(PWM));
  analogWrite(!(PWM > 0) ? PWM_M1_IN1 : PWM_M1_IN2, 0);
  analogWrite(PWM < 0 ? PWM_M2_IN1 : PWM_M2_IN2, abs(PWM));
  analogWrite(!(PWM < 0) ? PWM_M2_IN1 : PWM_M2_IN2, 0);
#endif // #if (flags & ENABLE_PWM_OUT) == ENABLE_PWM_OUT
}

void loop()
{
  BP32.update();
  if (Controller && Controller->isConnected() && Controller->isGamepad())
  {
    checkConfig(Controller);

    if (exhibition_speed != 0)
    {
      exhibition(exhibition_speed);
    }
    else
    {
      const int16_t speed = handleDualSpeed(Controller, game_flags & AXIS_LY);
      if (speed != 0)
        handleMovement(Controller, abs(speed), float(handleDirection(Controller, game_flags & AXIS_RX)) / 100.0, speed > 0);
      else
        resetMotors();
    }
  }

  if (has(game_flags, BLINK))
  {
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(85);
  }
  delay(15);
}