#pragma once

#include <Arduino.h>
#include <pinout.hpp>

extern bool half_power;

void setHalfPower()
{
  pinMode(Pinout::SPEED_LIMIT_PIN, INPUT_PULLUP);

  if (digitalRead(Pinout::SPEED_LIMIT_PIN) == HIGH)
  {
    half_power = true;
    Serial.println("Half power mode activated due to SPEED_LIMIT_PIN state.");

    for (int i = 0; i < 3; i++)
    {
      digitalWrite(Pinout::LED_STATUS_PIN, HIGH);
      delay(100);
      digitalWrite(Pinout::LED_STATUS_PIN, LOW);
      delay(100);
    }
  }
}