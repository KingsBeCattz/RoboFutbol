# Robo-Futbol

This project is created to manage cars by means of an ESP32 or Arduino-compatible board and a single bluetooth or PS2 control per car.

Supported controllers:

* Bluetooth gamepads via Bluepad32 (ESP32)
* PS2 Wireless Controller (Arduino-compatible boards)

## Installation for ESP32 (Bluepad32)

1. You need to have installed the Arduino IDE. If not, download it from here: [Arduino IDE](https://www.arduino.cc/en/software/#ide).
2. Go to Preferences (File > Preferences or Ctrl/⌘ + comma).
3. In “Additional boards manager URLs” paste the following:

```
https://dl.espressif.com/dl/package_esp32_index.json,https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
```

4. Click OK and go to the board manager, then search for “esp32” and install `esp32` from *Espressif* and `esp32_bluepad32` from *Ricardo Quesada*.
5. Download or clone the [MotorDriveUnit library](./libraries/) as .ZIP and install it via Library Manager (`Sketch > Include Library > Add .ZIP library` → search for `MotorDriveUnit`).
6. Once everything is installed, open the code, select your ESP32 board — **make sure you use the one from Ricardo Quesada and not Espressif**.

## Installation for Arduino (PS2 Controller)

1. Install Arduino IDE as above.
2. Download or clone the [MotorDriveUnit library](./libraries/) and [PS2X library](./libraries/), both as .ZIP and install it via Library Manager (`Sketch > Include Library > Add .ZIP library` → search for `MotorDriveUnit` and `PS2X`).
3. Connect your PS2 wireless receiver to the specified pins (see below).

---

## PinOut

> **Important:** All pins should be PWM pins. Digital pins can be used **only if explicitly configured** for the specific platform and use case.

### ESP32

```cpp
#define forward_left_pin 27
#define backward_left_pin 14
#define forward_right_pin 17
#define backward_right_pin 16
#define enable_left_pin 32   // Optional
#define enable_right_pin 23  // Optional
```

### Arduino-compatible board (PS2)

```cpp
#define forward_left_pin 9
#define backward_left_pin 6
#define forward_right_pin 5
#define backward_right_pin 3
#define enable_left_pin 10   // Optional
#define enable_right_pin 11  // Optional
```

> Pins `enable_left_pin` and `enable_right_pin` are optional depending on whether you want PWM/digital enable functionality.

---

## Usage

* **ESP32 (Bluepad32)**
  The main code is `sources/esp32/esp32.ino`. Supports Bluetooth controllers. Use the flags at the top of the file to enable or disable digital/PWM outputs and speed outputs.

* **Arduino-compatible (PS2)**
  The main code is `sources/ps2x/ps2x.ino`. Supports PS2 controllers. Stick mappings:

  * Left joystick → forward/backward (Y-axis)
  * Right joystick → left/right (X-axis)
  * Buttons for power/direction switching:

    * **SELECT** → switch power source
    * **START** → switch direction source
    * **CROSS** → manual drive
    * **TRIANGLE** → exposition mode
    * **SQUARE** → tank drive

---

## Configuration Flags

The configuration is divided into two groups: the pins that control the direction of the motor and the other two pins that enable the H-bridge of each motor.

To use a configuration by group, you must uncomment the one you want to use. Only one should be used at a time.

### Motor direction pins
USE_PWM_MOTOR_PIN -> Indicates that pwm pins will be used.
USE_DIGITAL_MOTOR_PIN -> Indicates that digital pins will be used.
```cpp
// #define USE_PWM_MOTOR_PIN
// #define USE_DIGITAL_MOTOR_PIN
```

### Enable pins
USE_PWM_ENABLE_PIN -> Indicates that pwm pins will be used.
USE_DIGITAL_ENABLE_PIN -> Indicates that digital pins will be used.
```cpp
// #define USE_PWM_ENABLE_PIN
// #define USE_DIGITAL_ENABLE_PIN
```