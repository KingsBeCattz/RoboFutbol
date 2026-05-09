#ifdef ESP32
#include <BP32Gamepad.hpp>

ControllerPtr Bluepad32Gamepad::_controller = nullptr;
Bluepad32Gamepad *Bluepad32Gamepad::_instance = nullptr;
#endif