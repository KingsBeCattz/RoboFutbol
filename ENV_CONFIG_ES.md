# ENV_CONFIG.md

## Pin Behavior Configuration

Estas variables controlan **cómo se manejan los pines del driver de motores**.
Reemplazan directamente a las macros del código fuente (`#define`).

### Digital vs PWM control

```env
USE_DIGITAL_MOTOR_PIN=1
```

* **1** → Usa pines digitales (`HIGH` / `LOW`) para controlar la potencia del motor.
* **0** → Usa PWM (`analogWrite`) para controlar la velocidad.

Equivalente a:

```cpp
#define USE_DIGITAL_MOTOR_PIN
```

---

```env
USE_DIGITAL_ENABLE_PIN=0
```

* **1** → Los pines `ENABLE` funcionan en modo digital.
* **0** → Los pines `ENABLE` funcionan con PWM para controlar la velocidad.

Equivalente a:

```cpp
#define USE_DIGITAL_ENABLE_PIN
```

---

### Uso de pines ENABLE del puente H

```env
USE_ENABLE_PINS=1
```

* **1** → El control de potencia del motor se hace usando pines `ENABLE`.
* **0** → El control se hace directamente desde los pines de dirección (`FORWARD` / `BACKWARD`).

Equivalente a:

```cpp
#define USE_ENABLE_PINS
```

---

## Motor Cloning Configuration

Las siguientes variables definen **clones de motores**, que replican exactamente la señal del motor maestro.

* Valor **255** → **clon deshabilitado**
* Valor **0** u otro valor → El pin es un **clon activo**

---

### First pair of cloned engines

```env
LEFT_MOTOR_CLONE_1_FORWARD=255
LEFT_MOTOR_CLONE_1_BACKWARD=255
LEFT_MOTOR_CLONE_1_ENABLE=255

RIGHT_MOTOR_CLONE_1_FORWARD=255
RIGHT_MOTOR_CLONE_1_BACKWARD=255
RIGHT_MOTOR_CLONE_1_ENABLE=255
```

Replica el comportamiento del motor izquierdo y derecho principal en un **primer par adicional**.

---

### Second pair of cloned engines

```env
LEFT_MOTOR_CLONE_2_FORWARD=255
LEFT_MOTOR_CLONE_2_BACKWARD=255
LEFT_MOTOR_CLONE_2_ENABLE=255

RIGHT_MOTOR_CLONE_2_FORWARD=255
RIGHT_MOTOR_CLONE_2_BACKWARD=255
RIGHT_MOTOR_CLONE_2_ENABLE=255
```

Replica el comportamiento del motor izquierdo y derecho principal en un **segundo par adicional**.

---

## Notes

* Todos los clones reciben **la misma señal PWM o digital** que el motor maestro.
* Esta configuración permite escalar de **2 hasta 6 motores por lado** sin modificar el código fuente.
* Cambiar el modo de operación solo requiere editar el `.env` y recompilar.

Añade esta **aclaración explícita** en `ENV_CONFIG.md` (idealmente justo antes de *Motor Cloning Configuration* o en *Notes*):

### ESP32 Only – Output Cloning Support

⚠️ **Importante**

La funcionalidad de **clonado de salidas (Motor Cloning Configuration)** **solo está disponible en ESP32**.

Motivo:

* El ESP32 permite **duplicar señales PWM y digitales** de forma flexible usando `ledc` y GPIO independientes.
* En placas AVR clásicas (Arduino Uno / Nano / Mega), el hardware PWM es limitado y **no permite clonado limpio de múltiples salidas** sin penalizaciones graves o hacks por software.

Consecuencia:

* Si el proyecto se compila para una plataforma **no ESP32**, todas las variables:

  * `*_MOTOR_CLONE_*`
  * serán **ignoradas o deshabilitadas automáticamente**.
* El firmware funcionará únicamente con los motores principales.

* Para configuraciones con **más de 2 motores por lado**, se **requiere ESP32**.
