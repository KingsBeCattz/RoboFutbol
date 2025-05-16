/**
 * ROBO-FUTBOL XOCHIMILCO 2025
 * ESP32-WROOM-32-N4
 * SUPPORTED GAMEPADS: https://bluepad32.readthedocs.io/en/latest/supported_gamepads/
 * Written by: Johan 4CMT
 */

#include <Arduino.h>
#include <Bluepad32.h>
#include "esp32/clk.h"

#define BLINK (1 << 0)          // Defines the mask of the bit on the index 0
#define AXIS_LY (1 << 1)        // Defines the mask of the bit on the index 1
#define AXIS_RX (1 << 2)        // Defines the mask of the bit on the index 2
#define SELECT_PRESSED (1 << 3) // Defines the mask of the bit on the index 3
#define START_PRESSED (1 << 4)  // Defines the mask of the bit on the index 4

// Sets the flags to 0 and switch the bit on BLINK (index [0]) as true
uint8_t flags = 0 | BLINK;

// PIN_OUT
const uint8_t M1_PWM_SPEED = 27;
const uint8_t M1_ENABLE = 14;
const uint8_t M2_PWM_SPEED = 23;
const uint8_t M2_ENABLE = 22;

const uint8_t DIRECTIONAL_SENSIVITY = 32;

const uint8_t D_M1_IN1 = 25;
const uint8_t D_M1_IN2 = 26;
const uint8_t D_M2_IN1 = 19;
const uint8_t D_M2_IN2 = 18;

const uint8_t PWM_M1_IN1 = 12;
const uint8_t PWM_M1_IN2 = 13;
const uint8_t PWM_M2_IN1 = 17;
const uint8_t PWM_M2_IN2 = 16;

// Instances a new controller pointer array
ControllerPtr Controllers[1]; // Sets only one controller slot

void setup()
{
  setCpuFrequencyMhz(240);
  Serial.begin(115200);
  while (!Serial)
  {
  }

  String fv = BP32.firmwareVersion();
  Serial.print("Firmware version installed: ");
  Serial.println(fv);
  pinMode(2, OUTPUT);

  pinMode(M1_PWM_SPEED, OUTPUT);
  pinMode(M1_ENABLE, OUTPUT);
  pinMode(M2_PWM_SPEED, OUTPUT);
  pinMode(M2_ENABLE, OUTPUT);

  pinMode(D_M1_IN1, OUTPUT);
  pinMode(D_M1_IN2, OUTPUT);
  pinMode(D_M2_IN1, OUTPUT);
  pinMode(D_M2_IN2, OUTPUT);

  pinMode(PWM_M1_IN1, OUTPUT);
  pinMode(PWM_M1_IN2, OUTPUT);
  pinMode(PWM_M2_IN1, OUTPUT);
  pinMode(PWM_M2_IN2, OUTPUT);

  pinMode(DIRECTIONAL_SENSIVITY, INPUT_PULLUP);

  // To get the BD Address (MAC address) call:
  const uint8_t *addr = BP32.localBdAddress();
  Serial.print("BD Address: ");
  for (int i = 0; i < 6; i++)
  {
    Serial.print(addr[i], HEX);
    if (i < 5)
      Serial.print(":");
    else
      Serial.println();
  }

  BP32.setup(&onConnectedController, &onDisconnectedController);

  BP32.forgetBluetoothKeys();
}

void onConnectedController(ControllerPtr gamepad)
{
  if (Controllers[0] == nullptr)
  {
    Serial.print("--- Controller of ");
    Serial.print(gamepad->getModelName());
    Serial.println(" is connected ---");
    Controllers[0] = gamepad;
    flags &= ~BLINK;
    BP32.enableNewBluetoothConnections(false);
  }
  else
  {
    gamepad->disconnect();
  }
}

void onDisconnectedController(ControllerPtr gamepad)
{
  if (Controllers[0] == gamepad)
  {
    Serial.println("--- Controller is disconnected ---");
    Controllers[0] = nullptr;
    flags |= BLINK;
    handleMovement(0, 0.0, false);
    handleMovement(0, 0.0, true);
    BP32.enableNewBluetoothConnections(true);
  }
}

/**
 * Just return a value from -255 to 255.
 * The first value is the bluepad32's controller and the second value is a boolean who represents if the speed is from the left joystick or not
 */
long handleDualSpeed(ControllerPtr gamepad, bool joystick)
{
  int dpad_state_ud = gamepad->dpad();
  if (dpad_state_ud & 1)
    return 255;
  if (dpad_state_ud & 2)
    return -255;
  if (joystick)
  {
    long speed = map(gamepad->axisY(), 0, 512, 0, 255);
    if (abs(speed) < 15)
      return 0;
    return speed * -1;
  }
  long LB = gamepad->l1();
  long RB = gamepad->r1();
  long LT = gamepad->brake();
  long RT = gamepad->throttle();

  long L = LB ? 255 : map(LT, 0, 1023, 0, 255);
  long R = RB ? 255 : map(RT, 0, 1023, 0, 255);

  return R + (L * -1);
}

/**
 * Just return a value from -1.0 to 1.0 with middle points like 0.55.
 * The first value is the bluepad32's controller and the second value is a boolean who represents if the direction is from the right joystick or from the left stick
 */
float handleDirection(ControllerPtr gamepad, bool joystick)
{
  int dpad_state_lr = gamepad->dpad();
  if (dpad_state_lr & 4)
  {
    return 1.0;
  }

  if (dpad_state_lr & 8)
  {
    return -1.0;
  }

  float direction = (joystick ? gamepad->axisRX() : gamepad->axisX()) / 512.0;
  if (abs(direction) < 0.30)
    return 0.0;
  return direction;
}

void handleMovement(int PWM, float DIRECTION, bool INX)
{
  int M1_PWM = round(PWM * (DIRECTION < 0.0f ? 1.00f - fabs(DIRECTION) : 1.00f));
  int M2_PWM = round(PWM * (DIRECTION > 0.0f ? 1.00f - fabs(DIRECTION) : 1.00f));
  bool SENSIVITY = !digitalRead(DIRECTIONAL_SENSIVITY);
  bool DIGITAL_BASE_M1 = (M1_PWM > 0);
  bool DIGITAL_BASE_M2 = (M2_PWM > 0);

  bool M1_DIGITAL = SENSIVITY ? DIGITAL_BASE_M1 : !(DIRECTION < 0.0f);
  bool M2_DIGITAL = SENSIVITY ? DIGITAL_BASE_M2 : !(DIRECTION > 0.0f);

  analogWrite(M1_PWM_SPEED, M1_PWM);
  digitalWrite(M1_ENABLE, DIGITAL_BASE_M1);
  analogWrite(M2_PWM_SPEED, M2_PWM);
  digitalWrite(M2_ENABLE, DIGITAL_BASE_M2);

  analogWrite(INX ? PWM_M1_IN1 : PWM_M1_IN2, M1_PWM);
  analogWrite(INX ? PWM_M2_IN1 : PWM_M2_IN2, M2_PWM);
  analogWrite(!INX ? PWM_M1_IN1 : PWM_M1_IN2, 0);
  analogWrite(!INX ? PWM_M2_IN1 : PWM_M2_IN2, 0);

  digitalWrite(!INX ? D_M1_IN1 : D_M1_IN2, false);
  digitalWrite(!INX ? D_M2_IN1 : D_M2_IN2, false);
  digitalWrite(INX ? D_M1_IN1 : D_M1_IN2, M1_DIGITAL);
  digitalWrite(INX ? D_M2_IN1 : D_M2_IN2, M2_DIGITAL);
}

void checkConfig(ControllerPtr gamepad)
{
  if (!(flags & SELECT_PRESSED) && gamepad->miscSelect())
  {
    flags |= SELECT_PRESSED;
    flags ^= AXIS_LY;
  }
  if ((flags & SELECT_PRESSED) && !gamepad->miscSelect())
  {
    flags &= ~SELECT_PRESSED;
  }
  if (!(flags & START_PRESSED) && gamepad->miscStart())
  {
    flags |= START_PRESSED;
    flags ^= AXIS_RX;
  }
  if ((flags & START_PRESSED) && !gamepad->miscStart())
  {
    flags &= ~START_PRESSED;
  }
}

void loop()
{
  BP32.update();
  ControllerPtr Controller = Controllers[0];
  if (Controller && Controller->isConnected() && Controller->isGamepad())
  {
    const int speed = handleDualSpeed(Controller, flags & AXIS_LY);
    checkConfig(Controller);

    if (speed != 0)
      handleMovement(abs(speed), handleDirection(Controller, flags & AXIS_RX), speed > 0);
    else
    {
      analogWrite(M1_PWM_SPEED, 0);
      digitalWrite(M1_ENABLE, false);
      analogWrite(M2_PWM_SPEED, 0);
      digitalWrite(M2_ENABLE, false);

      analogWrite(PWM_M1_IN1, 0);
      analogWrite(PWM_M1_IN2, 0);
      analogWrite(PWM_M2_IN1, 0);
      analogWrite(PWM_M2_IN2, 0);

      digitalWrite(D_M1_IN1, false);
      digitalWrite(D_M1_IN2, false);
      digitalWrite(D_M2_IN1, false);
      digitalWrite(D_M2_IN2, false);
    }
  }

  if (flags & BLINK)
  {
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(85);
  }
  else
  {
    digitalWrite(2, HIGH);
  }
  delay(15);
}