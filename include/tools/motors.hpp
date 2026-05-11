#pragma once

#include <MotorDriveUnit.h>
#include <tools/serial.hpp>
#include <types.h>
#include <pinout.hpp>
#include <input_modes.hpp>

#include <input_modes.hpp>
extern InputMode input_mode;

namespace MotorsTools
{
  inline void configure(MotorDriveUnit &driver, UnsignedPWM deadzone, const HBridgeConfig &cfg)
  {
#ifdef DEBUG
    SerialTools::printf("Configuring driver [%s] with pins: LF=%d, LB=%d, RF=%d, RB=%d, LE=%d, RE=%d, STBY=%d\n",
                        cfg.name, cfg.left_forward, cfg.left_backward, cfg.right_forward, cfg.right_backward,
                        cfg.left_enable, cfg.right_enable, cfg.standby);
#endif
    driver.getLeftMotor().setDirectionPins(cfg.left_forward, cfg.left_backward, cfg.use_digital_directions);
    driver.getRightMotor().setDirectionPins(cfg.right_forward, cfg.right_backward, cfg.use_digital_directions);
    if (cfg.left_enable != Motor::PIN_UNUSED)
      driver.getLeftMotor().setEnablePin(cfg.left_enable, cfg.use_digital_enables);
    if (cfg.right_enable != Motor::PIN_UNUSED)
      driver.getRightMotor().setEnablePin(cfg.right_enable, cfg.use_digital_enables);
    if (cfg.standby != Motor::PIN_UNUSED)
      driver.setDriverEnablePin(cfg.standby, cfg.use_digital_stby);
    set_input_mode(driver, input_mode);
    driver.setDeadzone(deadzone);
    driver.begin();
  }

  inline void stop(std::initializer_list<std::reference_wrapper<MotorDriveUnit>> drivers)
  {
    for (auto &d : drivers)
      d.get().stop();
  }

  inline void set_exposition(std::initializer_list<std::reference_wrapper<MotorDriveUnit>> drivers, bool active)
  {
    for (auto &d : drivers)
      d.get().setExpositionActive(active);
  }

  inline void use_tank_drive(std::initializer_list<std::reference_wrapper<MotorDriveUnit>> drivers)
  {
    for (auto &d : drivers)
      d.get().useTankDrive();
  }

  inline void set_input_mode(std::initializer_list<std::reference_wrapper<MotorDriveUnit>> drivers, InputMode mode)
  {
    for (auto &d : drivers)
      set_input_mode(d.get(), mode);
  }

  inline void update(std::initializer_list<std::reference_wrapper<MotorDriveUnit>> drivers)
  {
    for (auto &d : drivers)
      d.get().update();
  }
}