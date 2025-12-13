# ENV_CONFIG.md

## Pin Behavior Configuration

These variables control **how the motor driver pins are handled**.
They directly replace the macros defined in the source code (`#define`).

### Digital vs PWM control

```env
USE_DIGITAL_MOTOR_PIN=1
```

* **1** → Uses digital pins (`HIGH` / `LOW`) to control motor power.
* **0** → Uses PWM (`analogWrite`) to control motor speed.

Equivalent to:

```cpp
#define USE_DIGITAL_MOTOR_PIN
```

---

```env
USE_DIGITAL_ENABLE_PIN=0
```

* **1** → `ENABLE` pins operate in digital mode.
* **0** → `ENABLE` pins operate using PWM to control speed.

Equivalent to:

```cpp
#define USE_DIGITAL_ENABLE_PIN
```

---

### H-bridge ENABLE pin usage

```env
USE_ENABLE_PINS=1
```

* **1** → Motor power is controlled using the `ENABLE` pins.
* **0** → Power is controlled directly through the direction pins (`FORWARD` / `BACKWARD`).

Equivalent to:

```cpp
#define USE_ENABLE_PINS
```

---

## Motor Cloning Configuration

The following variables define **motor clones**, which replicate **exactly the same signal** as the master motor.

* Value **255** → **clone disabled**
* Value **0** or any other value → The pin is an **active clone**

---

### First pair of cloned motors

```env
LEFT_MOTOR_CLONE_1_FORWARD=255
LEFT_MOTOR_CLONE_1_BACKWARD=255
LEFT_MOTOR_CLONE_1_ENABLE=255

RIGHT_MOTOR_CLONE_1_FORWARD=255
RIGHT_MOTOR_CLONE_1_BACKWARD=255
RIGHT_MOTOR_CLONE_1_ENABLE=255
```

Replicates the behavior of the main left and right motors into a **first additional pair**.

---

### Second pair of cloned motors

```env
LEFT_MOTOR_CLONE_2_FORWARD=255
LEFT_MOTOR_CLONE_2_BACKWARD=255
LEFT_MOTOR_CLONE_2_ENABLE=255

RIGHT_MOTOR_CLONE_2_FORWARD=255
RIGHT_MOTOR_CLONE_2_BACKWARD=255
RIGHT_MOTOR_CLONE_2_ENABLE=255
```

Replicates the behavior of the main left and right motors into a **second additional pair**.

---

## Notes

* All clones receive **the same PWM or digital signal** as the master motor.
* This configuration allows scaling from **2 up to 6 motors per side** without modifying the source code.
* Changing the operating mode only requires editing the `.env` file and recompiling.

Add the following **explicit clarification** to `ENV_CONFIG.md` (ideally just before *Motor Cloning Configuration* or inside *Notes*):

---

### ESP32 Only – Output Cloning Support

⚠️ **Important**

The **output cloning functionality (Motor Cloning Configuration)** is **only available on ESP32**.

Reason:

* The ESP32 allows **flexible duplication of PWM and digital signals** using `ledc` and independent GPIOs.
* On classic AVR boards (Arduino Uno / Nano / Mega), the available PWM hardware is limited and **does not allow clean multi-output cloning** without severe penalties or software hacks.

Consequences:

* If the project is compiled for a **non-ESP32 platform**, all variables:

  * `*_MOTOR_CLONE_*`
  * will be **ignored or automatically disabled**.

* The firmware will operate **only with the main motors**.

* For configurations with **more than 2 motors per side**, an **ESP32 is required**.