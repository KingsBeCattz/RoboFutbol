/**
 * ROBO-FUTBOL XOCHIMILCO 2025
 * ESP32-WROOM-32-N4
 * SUPPORTED GAMEPADS: https://bluepad32.readthedocs.io/en/latest/supported_gamepads/
 * Written by: Johan 4CMT
 */

#include <Arduino.h>
#include <Bluepad32.h>
#include "esp32/clk.h"

#define CONFIG_BLUEPAD32_MAX_DEVICES 1

#define BLINK (1 << 0)          // Defines the mask of the bit on the index 0
#define AXIS_LY (1 << 1)        // Defines the mask of the bit on the index 1
#define AXIS_RX (1 << 2)        // Defines the mask of the bit on the index 2
#define SELECT_PRESSED (1 << 3) // Defines the mask of the bit on the index 3
#define START_PRESSED (1 << 4)  // Defines the mask of the bit on the index 4

// Sets the flags to 0 and switch the bit on BLINK (index [0]) as true
uint8_t flags = 0 | BLINK;

// PIN_OUT
int PWM_SPEED = 23;
int ENABLE = 22;

int D_M1_IN1 = 25;
int D_M1_IN2 = 26;
int D_M2_IN1 = 19; 
int D_M2_IN2 = 18;

int PWM_M1_IN1 = 12;
int PWM_M1_IN2 = 13;
int PWM_M2_IN1 = 17;
int PWM_M2_IN2 = 16;

// Instances a new controller pointer
ControllerPtr Controllers[CONFIG_BLUEPAD32_MAX_DEVICES]; // Sets only one controller slot

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
  pinMode(PWM_SPEED, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(D_M1_IN1, OUTPUT);
  pinMode(D_M1_IN2, OUTPUT);
  pinMode(D_M2_IN1, OUTPUT);
  pinMode(D_M2_IN2, OUTPUT);
  pinMode(PWM_M1_IN1, OUTPUT);
  pinMode(PWM_M1_IN2, OUTPUT);
  pinMode(PWM_M2_IN1, OUTPUT);
  pinMode(PWM_M2_IN2, OUTPUT);

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
  } else {
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
float handleDirection(ControllerPtr gamepad, bool Rjoystick)
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

  float direction = (Rjoystick ? gamepad->axisRX() : gamepad->axisX()) / 512.0;
  if (abs(direction) < 0.15)
    return 0.0;

  return direction;
}

void writeOutputs(
  int PWM_M1_IN1_VALUE,
  int PWM_M1_IN2_VALUE,
  int PWM_M2_IN1_VALUE,
  int PWM_M2_IN2_VALUE,
  bool D_M1_IN1_VALUE,
  bool D_M1_IN2_VALUE,
  bool D_M2_IN1_VALUE,
  bool D_M2_IN2_VALUE) {
    // PWM PINS
    analogWrite(PWM_M1_IN1, PWM_M1_IN1_VALUE);
    analogWrite(PWM_M1_IN2, PWM_M1_IN2_VALUE);
    analogWrite(PWM_M2_IN1, PWM_M2_IN1_VALUE);
    analogWrite(PWM_M2_IN2, PWM_M2_IN2_VALUE);
    // DIGITAL PINS
    digitalWrite(D_M1_IN1, D_M1_IN1_VALUE);
    digitalWrite(D_M1_IN2, D_M1_IN2_VALUE);
    digitalWrite(D_M2_IN1, D_M2_IN1_VALUE);
    digitalWrite(D_M2_IN2, D_M2_IN2_VALUE);
}

void processGamepad(ControllerPtr gamepad)
{
  const float direction = handleDirection(gamepad, flags & AXIS_RX);
  const int general_speed = handleDualSpeed(gamepad, flags & AXIS_LY);
  const int speed_lwheel = round(abs(general_speed) * (direction < 0.0 ? 1.00 - abs(direction) : 1.00));
  const int speed_rwheel = round(abs(general_speed) * (direction > 0.0 ? 1.00 - abs(direction) : 1.00));

  analogWrite(PWM_SPEED, abs(general_speed));
  digitalWrite(ENABLE, HIGH);

  if (general_speed == 0)
  {
    analogWrite(PWM_SPEED, 0);
    digitalWrite(ENABLE, LOW);
    
    writeOutputs(
      0,     //PWM Output - Motor 1 - IN1
      0,     //PWM Output - Motor 1 - IN2
      0,     //PWM Output - Motor 2 - IN1
      0,     //PWM Output - Motor 2 - IN2
      false, //DIGITAL Output - Motor 1 - IN1
      false, //DIGITAL Output - Motor 1 - IN2
      false, //DIGITAL Output - Motor 2 - IN1
      false  //DIGITAL Output - Motor 2 - IN2
    );
  }
  else
  {
    if (general_speed > 0)
    {
      writeOutputs(
        speed_lwheel,                   //PWM Output - Motor 1 - IN1
        0,                              //PWM Output - Motor 1 - IN2
        speed_rwheel,                   //PWM Output - Motor 2 - IN1
        0,                              //PWM Output - Motor 2 - IN2
        direction < 0.0 ? false : true, //DIGITAL Output - Motor 1 - IN1
        false,                          //DIGITAL Output - Motor 1 - IN2
        direction > 0.0 ? false : true, //DIGITAL Output - Motor 2 - IN1
        false                           //DIGITAL Output - Motor 2 - IN2
      );
    }
    else
    {
      writeOutputs(
        0,                              //PWM Output - Motor 1 - IN1
        speed_lwheel,                   //PWM Output - Motor 1 - IN2
        0,                              //PWM Output - Motor 2 - IN1
        speed_rwheel,                   //PWM Output - Motor 2 - IN2
        false,                          //DIGITAL Output - Motor 1 - IN1
        direction < 0.0 ? false : true, //DIGITAL Output - Motor 1 - IN2
        false,                          //DIGITAL Output - Motor 2 - IN1
        direction > 0.0 ? false : true  //DIGITAL Output - Motor 2 - IN2
      );
    }
  }
}

void changeConfig(ControllerPtr gamepad)
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
    changeConfig(Controller);
    processGamepad(Controller);
  }

  if (flags & BLINK)
  {
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(2, HIGH);
  }
  delay(15);
}