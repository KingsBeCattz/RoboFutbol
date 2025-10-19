# Robo-Futbol

This project is created to manage cars using a single ESP32 and a single Bluetooth gamepad per car.
It now uses the **MotorDriveUnit library** to simplify motor control, making it easier to read, maintain, and reuse with other APIs.

---

## Installation to ESP32

1. Make sure you have the Arduino IDE installed. If not, download it [here](https://www.arduino.cc/en/software/#ide).
2. Go to Preferences (File > Preferences or Ctrl/⌘ + comma).
3. In **Additional Boards Manager URLs**, paste the following:

```
https://dl.espressif.com/dl/package_esp32_index.json,https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
```

4. Click OK, open the board manager, search for “esp32”, and install:

   * `esp32` from **Espressif**
   * `esp32_bluepad32` from **Ricardo Quesada**
5. Open the code, select your ESP32 board — **make sure to use the Ricardo Quesada version for Bluepad32**.
6. Before uploading, edit the **pin configuration section** in the sketch to select which pins will control the motors and whether PWM or digital outputs are used.

---

## Pin configuration

Instead of flags, the new version uses **defines** to choose which type of pins you want to use for motor and enable pins.

```cpp
#define USE_PWM_MOTOR_PIN          // Use PWM pins for motors
// #define USE_DIGITAL_MOTOR_PIN     // Use digital pins for motors

// #define USE_PWM_ENABLE_PIN        // Use PWM for enable pins
// #define USE_DIGITAL_ENABLE_PIN    // Use digital for enable pins
```

> ⚠️ You must choose **one and only one option** per group.
> If you select both PWM and Digital for the same group, the compiler will show an error.

### Default motor pinout:

```cpp
#define forward_left_pin 27
#define backward_left_pin 14
#define forward_right_pin 17
#define backward_right_pin 16
```

### Default enable pins (only active if `USE_PWM_ENABLE_PIN` or `USE_DIGITAL_ENABLE_PIN` is defined):

```cpp
#define enable_left_pin 32
#define enable_right_pin 23
```

If you don’t define any enable pins, the library automatically disables them using `PIN_UNUSED`.

---

## Gamepad configuration

* **Power source / speed control** can be switched dynamically using the **Back/Select button**.
* **Direction source / turning control** can be switched dynamically using the **Home/Start button**.
* **Exposition mode (demo mode)** is activated by pressing the **Y button**.
* **Manual drive** can be used by pressing **A**, allowing control via triggers and bumpers.
* **Tank drive** is activated by pressing **X**.

---

## Usage example

```cpp
motor_driver.setPowerSource(use_triggers);       // Use triggers for speed
motor_driver.setDirectionSource(use_left_x_axis); // Use left joystick X-axis for turning
motor_driver.setDeadzone(70);                   // Joystick deadzone
motor_driver.begin();                            // Initialize motor driver
```

### Alternative example with left joystick as speed:

```cpp
motor_driver.setPowerSource(use_left_y_axis);   // Use left joystick Y-axis for speed
motor_driver.setDirectionSource(use_right_x_axis); // Use right joystick X-axis for turning
motor_driver.begin();                            // Initialize motor driver
```

> The library handles all PWM/digital logic, stop/reset, and safety automatically.

---

## Supported Gamepads

* Check the latest [Bluepad32 supported gamepads](https://bluepad32.readthedocs.io/en/latest/supported_gamepads/).

---

## Notes

* The onboard LED on pin 2 will **blink** when no controller is connected.
* `MotorDriveUnit` allows easy migration to other APIs or hardware setups without changing the sketch logic.
* The sketch is compatible with any ESP32-WROOM-32 series.
