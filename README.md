# Robo-Futbol

[**EN**/[ES](./README_ES.MD)]

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

### Available Environments

The project provides multiple environments in `platformio.ini`:

#### ESP32 Environments

- **`esp32_2_motors`** (default): Uses `.env` file configuration for 1 pair of motors (2 motors total)
- **`esp32_4_motors`**: Uses `.env` file configuration for 2 pairs of motors (4 motors total)
- **`esp32_6_motors`**: Uses `.env` file configuration for 3 pairs of motors (6 motors total)
- **`esp32_preset_l298n`**: Pre-configured for L298N motor driver (no `.env` file needed)
- **`esp32_preset_tb6612fng`**: Pre-configured for TB6612FNG motor driver (no `.env` file needed)

#### Arduino Environment

- **`arduino-uno`**: For Arduino Uno boards with PS2 controller

### Example `platformio.ini` (simplified)

```ini
[platformio]
default_envs = esp32_2_motors

[env:esp32_2_motors]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
monitor_speed = 115200

platform_packages =
  framework-arduinoespressif32@https://github.com/maxgerhardt/pio-framework-bluepad32/archive/refs/heads/main.zip

lib_deps =
  https://github.com/KingsBeCattz/MotorDriveUnit.git#main

extra_scripts = pre:load_env_vars.py
build_flags = -DPAIRS_OF_MOTORS=1

[env:esp32_preset_l298n]
extends = esp32_2_motors
build_flags = 
  -DUSE_DIGITAL_MOTOR_PIN=0
  -DUSE_DIGITAL_ENABLE_PIN=0
  -DUSE_ENABLE_PINS=0
  -DPAIRS_OF_MOTORS=1

[env:esp32_preset_tb6612fng]
extends = esp32_2_motors
build_flags = 
  -DUSE_DIGITAL_MOTOR_PIN=1
  -DUSE_DIGITAL_ENABLE_PIN=0
  -DUSE_ENABLE_PINS=1
  -DPAIRS_OF_MOTORS=1

[env:esp32_4_motors]
extends = esp32_2_motors
build_flags = -DPAIRS_OF_MOTORS=2

[env:esp32_6_motors]
extends = esp32_2_motors
build_flags = -DPAIRS_OF_MOTORS=3

[env:arduino-uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 115200

lib_deps =
  https://github.com/KingsBeCattz/MotorDriveUnit.git#main
  https://github.com/madsci1016/Arduino-PS2X.git
```

> **Note:** Environments with `_motors` suffix (like `esp32_2_motors`, `esp32_4_motors`, `esp32_6_motors`) read configuration from a `.env` file. Preset environments (like `esp32_preset_l298n`, `esp32_preset_tb6612fng`) have hardcoded configurations and don't require a `.env` file.

---

## Configuration via `.env` file

All firmware configuration for the `esp32_*_motors` environments is done via a `.env` file. Detailed configuration guides are available in two languages:

- **[ENV_CONFIG_EN.md](./ENV_CONFIG_EN.md)**: English guide for `.env` file configuration
- **[ENV_CONFIG_ES.md](./ENV_CONFIG_ES.md)**: Spanish guide for `.env` file configuration

### Pin Behavior Configuration

These variables control **how the motor driver pins are handled**.

#### Digital vs PWM control
*   `USE_DIGITAL_MOTOR_PIN=1` → Uses digital pins (`HIGH`/`LOW`) for motor power. `=0` for PWM control.
*   `USE_DIGITAL_ENABLE_PIN=1` → `ENABLE` pins operate in digital mode. `=0` for PWM speed control.
*   `USE_ENABLE_PINS=1` → Motor power is controlled using the `ENABLE` pins. `=0` to control power directly through direction pins.

### Motor Cloning Configuration (ESP32 Only)

⚠️ **Important:** The **output cloning functionality is only available on ESP32**. On AVR boards (Arduino Uno/Nano/Mega), these settings are ignored and the firmware operates only with the main motors.

The following variables define **motor clones**, which replicate **exactly the same signal** as the master motor.
*   Value **255** → **clone disabled**
*   Any other value → The pin is an **active clone**

#### First pair of cloned motors
```env
LEFT_MOTOR_CLONE_1_FORWARD=255
LEFT_MOTOR_CLONE_1_BACKWARD=255
LEFT_MOTOR_CLONE_1_ENABLE=255
RIGHT_MOTOR_CLONE_1_FORWARD=255
RIGHT_MOTOR_CLONE_1_BACKWARD=255
RIGHT_MOTOR_CLONE_1_ENABLE=255
```

#### Second pair of cloned motors
```env
LEFT_MOTOR_CLONE_2_FORWARD=255
LEFT_MOTOR_CLONE_2_BACKWARD=255
LEFT_MOTOR_CLONE_2_ENABLE=255
RIGHT_MOTOR_CLONE_2_FORWARD=255
RIGHT_MOTOR_CLONE_2_BACKWARD=255
RIGHT_MOTOR_CLONE_2_ENABLE=255
```

> This configuration allows scaling from **2 up to 6 motors per side** without modifying the source code. Changing the operating mode only requires editing the `.env` file and recompiling.

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

**Choose the appropriate environment based on your setup:**
- Use `esp32_2_motors`, `esp32_4_motors`, or `esp32_6_motors` with a `.env` file for custom configurations
- Use `esp32_preset_l298n` for L298N motor driver without `.env` file
- Use `esp32_preset_tb6612fng` for TB6612FNG motor driver without `.env` file

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

## Note
* The repository includes `src/main.cpp` with all core code integrated. Select the correct PlatformIO environment before building.
* **For ESP32:** Choose between `.env`-based environments (`esp32_*_motors`) or preset environments (`esp32_preset_*`) based on your needs. Detailed configuration guides are available in [English](./ENV_CONFIG_EN.md) and [Spanish](./ENV_CONFIG_ES.md).
* **For Arduino:** Use the `arduino-uno` environment. Configuration is fixed for 2 motors only.