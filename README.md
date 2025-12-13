# Robo-Futbol

Robo-Futbol is a project designed to simplify controlling RC cars using either a Bluetooth gamepad (via Bluepad32 on ESP32 boards) or a PS2 wireless receiver on Arduino-compatible boards.

> **Compatibility:** This code is **only compatible with PlatformIO** (Visual Studio Code + PlatformIO extension). Arduino IDE is no longer supported.

## Supported controllers

* Bluetooth gamepads via Bluepad32 (ESP32)
* PS2 Wireless Controller (Arduino-compatible boards)

---

## Quick installation (PlatformIO)

1. Download the repository as a `.zip` (or clone it).
2. Install Visual Studio Code.
3. Install PlatformIO (and the recommended C/C++ extensions) in VS Code.
4. Open the repository in VS Code with PlatformIO active.
5. Wait while PlatformIO downloads the required framework packages and libraries.
6. Select the target environment in PlatformIO (see `platformio.ini`) and upload the code to your board.

> The project provides two environments you can choose from in `platformio.ini`: `esp32` and `arduino-uno`.

### Example `platformio.ini`

```ini
[platformio]
default_envs = esp32

[env:esp32]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino

monitor_speed = 115200

platform_packages =
  framework-arduinoespressif32@https://github.com/maxgerhardt/pio-framework-bluepad32/archive/refs/heads/main.zip

lib_deps =
  https://github.com/KingsBeCattz/MotorDriveUnit.git#main

[env:arduino-uno]
platform = atmelavr
board = uno
framework = arduino

monitor_speed = 115200

lib_deps =
  https://github.com/KingsBeCattz/MotorDriveUnit.git#main
  https://github.com/madsci1016/Arduino-PS2X.git
```

---

## Pinout

**Important:** All pins that drive motor speed should be PWM-capable. If you use plain digital pins, ensure they are appropriate for your platform and configuration.

### ESP32

```cpp
#ifdef USE_ENABLE_PINS
/// @brief Pin definition for left enable. (EN1)
#define LEFT_ENABLE_PIN 32
/// @brief Pin definition for right enable. (EN2)
#define RIGHT_ENABLE_PIN 23
#endif

/// @brief Pin definition for left forward motion. (IN1)
#define LEFT_FORWARD_PIN 27
/// @brief Pin definition for left backward motion. (IN2)
#define LEFT_BACKWARD_PIN 14
/// @brief Pin definition for right forward motion. (IN3)
#define RIGHT_FORWARD_PIN 17
/// @brief Pin definition for right backward motion. (IN4)
#define RIGHT_BACKWARD_PIN 16
```

### Arduino-compatible board

```cpp
#ifdef USE_ENABLE_PINS
/// @brief Pin definition for left enable. (EN1)
#define LEFT_ENABLE_PIN 11
/// @brief Pin definition for right enable. (EN2)
#define RIGHT_ENABLE_PIN 10
#endif

/// @brief Pin definition for left forward motion. (IN1)
#define LEFT_FORWARD_PIN 9
/// @brief Pin definition for left backward motion. (IN2)
#define LEFT_BACKWARD_PIN 6
/// @brief Pin definition for right forward motion. (IN3)
#define RIGHT_FORWARD_PIN 5
/// @brief Pin definition for right backward motion. (IN4)
#define RIGHT_BACKWARD_PIN 3
```

**PS2 receiver pin warning (Arduino-compatible boards)**

The PS2 receiver pins depend on whether `USE_ENABLE_PINS` is defined. Adjust according to your configuration.

```cpp
#ifdef USE_ENABLE_PINS
/// @brief Clock pin for PS2X controller.
#define CLK 8
/// @brief Attention pin for PS2X controller.
#define ATT 7
#else
/// @brief Clock pin for PS2X controller.
#define CLK 10
/// @brief Attention pin for PS2X controller.
#define ATT 11
#endif

/// @brief Command pin for PS2X controller.
#define CMD 12
/// @brief Data pin for PS2X controller.
#define DAT 13
```

---

## Usage

All firmware is integrated in `src/main.cpp`. The code is ready to upload after selecting the correct PlatformIO environment.

### ESP32 (Bluepad32)

* Main code: `src/main.cpp`.
* Controller behavior:

  * **SELECT** button: toggles the speed source between the triggers/bumpers and the left stick Y-axis.
  * **START** button: toggles the turning (steering) source between the left stick X-axis and the right stick X-axis.
  * **X (Cross/A)** button: activates **tank drive** mode.
  * **Y (Triangle)** button: activates **exposition** mode.
  * **A (Circle/B)** button: activates **manual driving** mode.

> Use the compile/upload controls in PlatformIO to build and flash for the `esp32` environment.

### Arduino-compatible (PS2)

* Main code: `src/main.cpp`.
* Stick mappings:

  * Left joystick → forward/backward (Y-axis)
  * Right joystick → left/right (X-axis)
* Buttons for power/direction/modes:

  * **SELECT** → switch power source
  * **START** → switch direction source
  * **CROSS** → manual drive
  * **TRIANGLE** → exposition mode
  * **SQUARE** → tank drive

> Use the `arduino-uno` environment in PlatformIO to build and flash for Arduino Uno.

---

## Configuration flags (explained)

The following macros appear near the top of `src/main.cpp`. Uncomment the ones you need. All are documented below as in the source.

```cpp
// -----------------------------------------------------
// Configurate the Motor Control
// -----------------------------------------------------

// @brief If this macro is defined, the motor driver will use digital pins to control motor power. If not defined, PWM will be used.
// #define USE_DIGITAL_MOTOR_PIN
// @brief If this macro is defined, the motor driver will use digital pins to control h-bridge enable. If not defined, PWM will be used.
// #define USE_DIGITAL_ENABLE_PIN

// -----------------------------------------------------
// Enable H-Bridge Enable Pins
// -----------------------------------------------------

/// @brief If this macro is defined, the motor driver will use enable pins to control motor power.
// #define USE_ENABLE_PINS
```

### Macro explanations (individual)

* `USE_DIGITAL_MOTOR_PIN` — When defined, the firmware uses **digital output pins** to drive the motor direction/power pins (IN1/IN2 / IN3/IN4). This means the code will write `HIGH`/`LOW` states to those pins. If **not defined**, the code uses **PWM output** on those pins to control motor speed (analogWrite).

* `USE_DIGITAL_ENABLE_PIN` — When defined, the firmware uses **digital output pins** for the H-bridge enable pins (EN1/EN2), toggling them `HIGH`/`LOW`. If **not defined**, the enable pins are controlled with **PWM**, allowing variable motor enable behavior.

* `USE_ENABLE_PINS` — When defined, the firmware **uses separate enable pins** (EN1 / EN2) for each motor (useful with H-bridges that expose enable inputs). If **not defined**, the firmware assumes the motor driver does not require separate enable pins and controls the H-bridge only via the direction/power pins.

> Choose macros based on your motor driver hardware and whether you need PWM on direction vs enable pins.

---

## Note
* The repository includes `src/main.cpp` with all core code integrated. Select the correct PlatformIO environment before building.
