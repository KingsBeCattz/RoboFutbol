#include <drivers.hpp>

MotorDriveUnit motor_driver;
#if defined(DUAL) && defined(ESP32)
MotorDriveUnit motor_driver_clone;
#endif