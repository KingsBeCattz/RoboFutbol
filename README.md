# Robo-Futbol

This project is created to manage cars by means of an single ESP32 and a single bluetooth control per car.

## Installation to ESP32
1. You need to have installed the Arduino IDE. In case you don't have it, download it from here: [Click here](https://www.arduino.cc/en/software/#ide).
2. Go to Preferences (File > Preferences or Ctrl/⌘ + comma).
3. In “Additional boards manager URLs” paste the following:
```
https://dl.espressif.com/dl/package_esp32_index.json,https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
```
4. Click OK and go to the board manager, then search for “esp32” and install `esp32` from *Espressif* and `esp32_bluepad32` from *Ricardo Quesada*.
5. Once everything is installed, open the code, select your ESP32 board — **make sure you use the one from Ricardo Quesada and not Espressif**.
6. **Before uploading the code, edit line 19 to specify the flags for the outputs you will be using.** These flags determine which output modules will be enabled (e.g., digital outputs, PWM, etc.).
   > *Note: A detailed pinout per flag is provided later in this README.*
7. Congratulations, you may now proceed with connecting your H-bridges.

## Explanation of the flags
Line 19 looks like this:
```cpp
 #define flags 0 | ()
````
There are several flags `ENABLE_DIGITAL_OUT`, `ENABLE_PWM_OUT`, `ENABLE_EN_OUT`, `ENABLE_SPEED_OUT`, and `HOLD_DIGITAL`.

You must include the flags you need inside the `()` with the `Or` (`|`) operator to add the flags.
Example: ` #define flags 0 | (ENABLE_DIGITAL_OUT | HOLD_DIGITAL)`.

## PinOut
```cpp
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
```

If you understand how the flags work, you will see which pinouts are valid when one flag or the other is active.