#pragma once

#include <Arduino.h>

#ifdef ESP32
#include <esp32_pinout.hpp>
#else
#include <arduino_pinout.hpp>
#endif

extern bool half_power;

void setHalfPower()
{
  pinMode(SPEED_LIMIT_PIN, INPUT_PULLUP);

  if (digitalRead(SPEED_LIMIT_PIN) == HIGH)
  {
    half_power = true;
    Serial.println("Half power mode activated due to SPEED_LIMIT_PIN state.");

    // 3 parpadeos rápidos → half power activo
    for (int i = 0; i < 3; i++)
    {
      digitalWrite(LED_STATUS_PIN, HIGH);
      delay(100);
      digitalWrite(LED_STATUS_PIN, LOW);
      delay(100);
    }
  }
}