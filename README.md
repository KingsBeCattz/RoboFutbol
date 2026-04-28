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

The project provides multiple environments split between ESP32 and Arduino platforms. The motor driver is selected via the environment name, and its configuration is loaded from `config.ini`.

#### ESP32 Environments

- **`esp32-l298n`**: ESP32 with L298N motor driver
- **`esp32-l298n-dual`**: ESP32 with two L298N motor drivers
- **`esp32-tb6612fng`**: ESP32 with TB6612FNG motor driver
- **`esp32-tb6612fng-dual`**: ESP32 with two TB6612FNG motor drivers
- **`esp32-bts7960`**: ESP32 with BTS7960 motor driver
- **`esp32-bts7960-dual`**: ESP32 with two BTS7960 motor drivers

#### Arduino Environments

- **`arduino-l298n`**: Arduino Uno with L298N motor driver
- **`arduino-tb6612fng`**: Arduino Uno with TB6612FNG motor driver
- **`arduino-bts7960`**: Arduino Uno with BTS7960 motor driver

### Project structure (`platformio.ini` + `config.ini`)

Configuration is split across two files. `platformio.ini` defines the platform, board, and base dependencies, while `config.ini` holds the build flags specific to each motor driver:

```ini
; platformio.ini (simplified)
[platformio]
extra_configs = config.ini

[env:esp32-l298n]
extends = esp32-base
build_flags = ${config_l298n.build_flags}

[env:esp32-l298n-dual]
extends = esp32-base
build_flags = ${config_l298n_dual.build_flags}

[env:esp32-tb6612fng]
extends = esp32-base
build_flags = ${config_tb6612fng.build_flags}

[env:esp32-tb6612fng-dual]
extends = esp32-base
build_flags = ${config_tb6612fng_dual.build_flags}

[env:esp32-bts7960]
extends = esp32-base
build_flags = ${config_bts7960.build_flags}

[env:esp32-bts7960-dual]
extends = esp32-base
build_flags = ${config_bts7960_dual.build_flags}

[env:arduino-l298n]
extends = arduino-base
build_flags = ${config_l298n.build_flags}

[env:arduino-tb6612fng]
extends = arduino-base
build_flags = ${config_tb6612fng.build_flags}

[env:arduino-bts7960]
extends = arduino-base
build_flags = ${config_bts7960.build_flags}
```

```ini
; config.ini
[config_l298n]
build_flags =
  -D USE_PWM_INPUTS
  -D L298N=1
  -D HBRIDGE=1

[config_l298n_dual]
build_flags =
  -D USE_PWM_INPUTS
  -D L298N=1
  -D HBRIDGE=1
  -D DUAL=1

[config_tb6612fng]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D USE_STANDBY
  -D TB6612FNG=2
  -D HBRIDGE=2

[config_tb6612fng_dual]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D USE_STANDBY
  -D TB6612FNG=2
  -D HBRIDGE=2
  -D DUAL=1

[config_bts7960]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D BTS7960=3
  -D HBRIDGE=3

[config_bts7960_dual]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D BTS7960=3
  -D HBRIDGE=3
  -D DUAL=1
```

---

## Pinout

Pin definitions are located in `esp32_pinout.hpp`, `esp32_clones.hpp`, and `arduino_pinout.hpp`. The correct set of pins is selected at compile time based on the `HBRIDGE` and `DUAL` macros defined by the chosen environment.

**Important:** Pins used for speed control (enable/PWM pins) must be PWM-capable on your board.

### ESP32

#### L298N

| Function | Pin |
|---|---|
| Left Forward (IN1) | 27 |
| Left Backward (IN2) | 14 |
| Right Forward (IN3) | 25 |
| Right Backward (IN4) | 26 |

#### L298N — Dual / Clone ⭐
> Use environment **`esp32-l298n-dual`** for this variant. Clone modules expose additional pins alongside the standard L298N pinout; using the wrong environment will result in the clone driver being left uninitialized and inactive.

| Function | Pin |
|---|---|
| Left Forward (IN1) | 27 |
| Left Backward (IN2) | 14 |
| Right Forward (IN3) | 25 |
| Right Backward (IN4) | 26 |
| -- | -- |
| Left Forward — Clone (IN1) | 4 |
| Left Backward — Clone (IN2) | 16 |
| Right Forward — Clone (IN3) | 17 |
| Right Backward — Clone (IN4) | 5 |

#### TB6612FNG

| Function | Pin |
|---|---|
| Left Enable (PWMA) | 4 |
| Left Forward (AIN1) | 16 |
| Left Backward (AIN2) | 17 |
| Standby (STBY) | 5 |
| Right Forward (BIN1) | 19 |
| Right Backward (BIN2) | 18 |
| Right Enable (PWMB) | 21 |

#### TB6612FNG — Dual / Clone ⭐
> Use environment **`esp32-tb6612fng-dual`** for this variant. Clone modules expose additional pins alongside the standard TB6612FNG pinout; using the wrong environment will result in the clone driver being left uninitialized and inactive.

| Function | Pin |
|---|---|
| Left Enable (PWMA) | 4 |
| Left Forward (AIN1) | 16 |
| Left Backward (AIN2) | 17 |
| Standby (STBY) | 5 |
| Right Forward (BIN1) | 19 |
| Right Backward (BIN2) | 18 |
| Right Enable (PWMB) | 21 |
| -- | -- |
| Left Enable — Clone (PWMA) | 32 |
| Left Forward — Clone (AIN1) | 25 |
| Left Backward — Clone (AIN2) | 33 |
| Standby — Clone (STBY) | 26 |
| Right Forward — Clone (BIN1) | 27 |
| Right Backward — Clone (BIN2) | 14 |
| Right Enable — Clone (PWMB) | 12 |

#### BTS7960

| Function | Pin |
|---|---|
| Left Enable (R_EN / L_EN) | 26 |
| Left Forward (RPWM) | 14 |
| Left Backward (LPWM) | 27 |
| Right Forward (RPWM) | 5 |
| Right Backward (LPWM) | 17 |
| Right Enable (R_EN / L_EN) | 16 |

#### BTS7960 — Dual / Clone ⭐
> Use environment **`esp32-bts7960-dual`** for this variant. Clone modules expose additional pins alongside the standard BTS7960 pinout; using the wrong environment will result in incorrect motor behavior.

| Function | Pin |
|---|---|
| Left Enable (R_EN / L_EN) | 26 |
| Left Forward (RPWM) | 14 |
| Left Backward (LPWM) | 27 |
| Right Forward (RPWM) | 5 |
| Right Backward (LPWM) | 17 |
| Right Enable (R_EN / L_EN) | 16 |
| -- | -- |
| Left Enable — Clone (R_EN / L_EN) | 32 |
| Left Forward — Clone (RPWM) | 25 |
| Left Backward — Clone (LPWM) | 33 |
| Right Forward — Clone (RPWM) | 18 |
| Right Backward — Clone (LPWM) | 19 |
| Right Enable — Clone (R_EN / L_EN) | 21 |

#### Speed Limit (all ESP32 environments)

| Function | Pin |
|---|---|
| Speed Limit (SPEED_LIMIT_PIN) | 34 |

> Pin 34 is input-only on the ESP32, making it ideal for a passive pullup read. See [Speed Limit](#speed-limit) for behavior details.

---

### Arduino Uno

PS2 receiver pins are fixed regardless of driver:

| Function | Pin |
|---|---|
| DAT | 2 |
| CMD | 12 |
| ATT | 7 |
| CLK | 8 |

#### L298N

| Function | Pin |
|---|---|
| Left Forward (IN1) | 9 |
| Left Backward (IN2) | 6 |
| Right Forward (IN3) | 5 |
| Right Backward (IN4) | 3 |

#### TB6612FNG

| Function | Pin |
|---|---|
| Left Enable (PWMA) | 11 |
| Left Forward (AIN1) | 9 |
| Left Backward (AIN2) | 6 |
| Standby (STBY) | 4 |
| Right Forward (BIN1) | 5 |
| Right Backward (BIN2) | 3 |
| Right Enable (PWMB) | 10 |

#### BTS7960

| Function | Pin |
|---|---|
| Left Enable (R_EN / L_EN) | 11 |
| Left Forward (RPWM) | 9 |
| Left Backward (LPWM) | 6 |
| Right Forward (RPWM) | 5 |
| Right Backward (LPWM) | 3 |
| Right Enable (R_EN / L_EN) | 10 |

#### Speed Limit (all Arduino environments)

| Function | Pin |
|---|---|
| Speed Limit (SPEED_LIMIT_PIN) | A0 |

> See [Speed Limit](#speed-limit) for behavior details.

---

## Usage

All firmware is integrated in `src/main.cpp`. The code is ready to upload after selecting the correct PlatformIO environment.

### Input Modes

Both platforms share the same input mode system. The **D-Pad** selects the active mode at runtime:

| D-Pad | Mode | Power source | Steering source |
|---|---|---|---|
| ↑ Up | Trigger + Left X | Triggers / Bumpers | Left stick X |
| ↓ Down | Trigger + Right X | Triggers / Bumpers (inverted) | Right stick X |
| → Right | Dual Stick Right | Left stick Y | Right stick X |
| ← Left | Dual Stick Left | Right stick Y | Left stick X |

The default mode on startup depends on the platform:

- **ESP32:** `↑ Up` (Trigger + Left X)
- **Arduino:** `→ Right` (Dual Stick Right)

### Speed Limit

By default, speed is soft-limited to 50% unless the **A button** (ESP32) or **Cross button** (Arduino) is held — holding it allows full 100% speed.

This behavior can be **permanently disabled at boot**: if `SPEED_LIMIT_PIN` is connected to GND when the board starts up, the speed cap is removed entirely and the button has no effect for the rest of the session. Disconnecting the pin after boot has no effect; the state is read only once at startup.

| Condition | Behavior |
|---|---|
| Pin floating / HIGH at boot | Soft limit active — hold A/Cross for 100% |
| Pin pulled to GND at boot | No limit — full speed always |

### ESP32 (Bluepad32)

* Main code: `src/main.cpp`.
* Button mappings:

  * **D-Pad** → select input mode (see table above)
  * **A** → hold for full speed (when speed limit is active)
  * **X (SQUARE/Y)** → activates **tank drive** mode
  * **Y (TRIANGLE/X)** → activates **exposition** mode

Choose the environment that matches your board and motor driver: `esp32-l298n`, `esp32-tb6612fng`, `esp32-tb6612fng-dual`, `esp32-bts7960`, or `esp32-bts7960-dual`.

### Arduino Uno (PS2)

* Main code: `src/main.cpp`.
* Button mappings:

  * **D-Pad** → select input mode (see table above)
  * **Cross** → hold for full speed (when speed limit is active)
  * **SQUARE** → tank drive
  * **TRIANGLE** → exposition mode

Choose the environment that matches your motor driver: `arduino-l298n`, `arduino-tb6612fng`, or `arduino-bts7960`.

---

## Notes

* Select the correct PlatformIO environment before building. The environment determines both the target platform and the motor driver configuration.
* Motor driver build flags (pin modes, HBRIDGE ID) are defined in `config.ini` and loaded automatically by `platformio.ini`.
* Pin assignments are defined in `esp32_pinout.hpp`, `esp32_clones.hpp`, and `arduino_pinout.hpp`, and selected at compile time via the `HBRIDGE` and `DUAL` macros.
* **Clone/dual modules** (BTS7960, TB6612FNG, and L298N) use a different pin mapping than their standard counterparts. Always use the `-dual` environment variant (`esp32-bts7960-dual`, `esp32-tb6612fng-dual`, `esp32-l298n-dual`) for these. Running standard firmware on a dual/clone circuit will leave the clone driver uninitialized and inactive. The reverse — running `-dual` firmware on a standard circuit — is harmless, as the extra pins simply go unused.
* **Speed limit pin** (`SPEED_LIMIT_PIN`) is read only once at startup. Connecting or disconnecting it after boot has no effect until the next reset.