# Robo-Futbol

This project is created to manage cars by means of an single ESP32 and a single bluetooth control per car.

## Installation to ESP32
1. You need to have installed the arduino IDE, in case you don't have it download it from here: [Click here](https://www.arduino.cc/en/software/#ide).
2. Go to Preferences (File > Preferences or Ctrl/⌘ + comma).
3. In “Additional boards manager URLs” paste the following:
```
https://dl.espressif.com/dl/package_esp32_index.json,https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
```
4. Click OK and go to the board manager, then search for “esp32” and install esp32 from espressif and esp32_bluepad32 from Ricardo Quesada.
5. Once everything is installed, open the code, select your board esp32 but make sure you use the one from Ricardo Quesada and not espressif.
6. Congratulations, you may now proceed with connecting your bridges h

## Explanation of the outputs
> **[PinOut](https://robo-futbol.vercel.app/en/guides/pinout/)**
- If your H-bridge only needs pwm outputs, use GPIO pins 12, 13, 16 and 17.
- If your H-bridge needs only I/O outputs, use GPIO pins 25, 26, 19 and 18.
- If you need it to be I/O pins and one PWM, you can pull the overall speed from GPIO 23.