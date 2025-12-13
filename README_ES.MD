# Robo-Futbol

[[EN](./README.MD)/**ES**]

Robo-Futbol es un proyecto diseñado para simplificar el control de coches RC usando ya sea un gamepad Bluetooth (mediante Bluepad32 en placas ESP32) o un receptor inalámbrico PS2 en placas compatibles con Arduino.

> **Compatibilidad:** Este código es **sólo compatible con PlatformIO** (Visual Studio Code + extensión PlatformIO). El IDE de Arduino ya no es compatible.

## Controladores soportados

* Gamepads Bluetooth vía Bluepad32 (ESP32)
* Controlador inalámbrico PS2 (placas compatibles con Arduino)

---

## Instalación rápida (PlatformIO)

1. Descarga el repositorio como `.zip` (o clónalo).
2. Instala Visual Studio Code.
3. Instala PlatformIO (y las extensiones recomendadas de C/C++) en VS Code.
4. Abre el repositorio en VS Code con PlatformIO activo.
5. Espera mientras PlatformIO descarga los paquetes de framework y librerías necesarias.
6. Selecciona el entorno objetivo en PlatformIO (ver `platformio.ini`) y sube el código a tu placa.

### Entornos disponibles

El proyecto proporciona múltiples entornos en `platformio.ini`:

#### Entornos ESP32

- **`esp32_2_motores`** (por defecto): Usa configuración de archivo `.env` para 1 par de motores (2 motores en total)
- **`esp32_4_motores`**: Usa configuración de archivo `.env` para 2 pares de motores (4 motores en total)
- **`esp32_6_motores`**: Usa configuración de archivo `.env` para 3 pares de motores (6 motores en total)
- **`esp32_preset_l298n`**: Preconfigurado para controlador de motor L298N (no requiere archivo `.env`)
- **`esp32_preset_tb6612fng`**: Preconfigurado para controlador de motor TB6612FNG (no requiere archivo `.env`)

#### Entorno Arduino

- **`arduino-uno`**: Para placas Arduino Uno con controlador PS2

### Ejemplo de `platformio.ini` (simplificado)

```ini
[platformio]
default_envs = esp32_2_motors

[env:esp32_2_motors]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
monitor_speed = 115200

platform_packages =
  framework-arduinoespressif32@https://github.com/maxgerhardt/pio-framework-bluepad32/archive/refs/heads/main.zip

lib_deps =
  https://github.com/KingsBeCattz/MotorDriveUnit.git#main

extra_scripts = pre:load_env_vars.py
build_flags = -DPAIRS_OF_MOTORS=1

[env:esp32_preset_l298n]
extends = esp32_2_motors
build_flags = 
  -DUSE_DIGITAL_MOTOR_PIN=0
  -DUSE_DIGITAL_ENABLE_PIN=0
  -DUSE_ENABLE_PINS=0
  -DPAIRS_OF_MOTORS=1

[env:esp32_preset_tb6612fng]
extends = esp32_2_motors
build_flags = 
  -DUSE_DIGITAL_MOTOR_PIN=1
  -DUSE_DIGITAL_ENABLE_PIN=0
  -DUSE_ENABLE_PINS=1
  -DPAIRS_OF_MOTORS=1

[env:esp32_4_motors]
extends = esp32_2_motors
build_flags = -DPAIRS_OF_MOTORS=2

[env:esp32_6_motors]
extends = esp32_2_motors
build_flags = -DPAIRS_OF_MOTORS=3

[env:arduino-uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 115200

lib_deps =
  https://github.com/KingsBeCattz/MotorDriveUnit.git#main
  https://github.com/madsci1016/Arduino-PS2X.git
```

> **Nota:** Los entornos con sufijo `_motors` (como `esp32_2_motors`, `esp32_4_motors`, `esp32_6_motors`) leen la configuración desde un archivo `.env`. Los entornos preconfigurados (como `esp32_preset_l298n`, `esp32_preset_tb6612fng`) tienen configuraciones fijas y no requieren archivo `.env`.

---

## Configuración mediante archivo `.env`

Toda la configuración del firmware para los entornos `esp32_*_motors` se realiza mediante un archivo `.env`. Guías de configuración detalladas están disponibles en dos idiomas:

- **[ENV_CONFIG_EN.md](./ENV_CONFIG_EN.md)**: Guía en inglés para configuración de archivo `.env`
- **[ENV_CONFIG_ES.md](./ENV_CONFIG_ES.md)**: Guía en español para configuración de archivo `.env`

### Configuración de comportamiento de pines

Estas variables controlan **cómo se manejan los pines del controlador de motor**.

#### Control digital vs PWM
*   `USE_DIGITAL_MOTOR_PIN=1` → Usa pines digitales (`HIGH`/`LOW`) para la potencia del motor. `=0` para control PWM.
*   `USE_DIGITAL_ENABLE_PIN=1` → Los pines `ENABLE` operan en modo digital. `=0` para control de velocidad PWM.
*   `USE_ENABLE_PINS=1` → La potencia del motor se controla usando los pines `ENABLE`. `=0` para controlar la potencia directamente a través de los pines de dirección.

### Configuración de clonación de motores (Sólo ESP32)

⚠️ **Importante:** La **funcionalidad de clonación de salida solo está disponible en ESP32**. En placas AVR (Arduino Uno/Nano/Mega), estas configuraciones son ignoradas y el firmware opera solo con los motores principales.

Las siguientes variables definen **clones de motor**, que replican **exactamente la misma señal** que el motor maestro.
*   Valor **255** → **clon desactivado**
*   Cualquier otro valor → El pin es un **clon activo**

#### Primer par de motores clonados
```env
LEFT_MOTOR_CLONE_1_FORWARD=255
LEFT_MOTOR_CLONE_1_BACKWARD=255
LEFT_MOTOR_CLONE_1_ENABLE=255
RIGHT_MOTOR_CLONE_1_FORWARD=255
RIGHT_MOTOR_CLONE_1_BACKWARD=255
RIGHT_MOTOR_CLONE_1_ENABLE=255
```

#### Segundo par de motores clonados
```env
LEFT_MOTOR_CLONE_2_FORWARD=255
LEFT_MOTOR_CLONE_2_BACKWARD=255
LEFT_MOTOR_CLONE_2_ENABLE=255
RIGHT_MOTOR_CLONE_2_FORWARD=255
RIGHT_MOTOR_CLONE_2_BACKWARD=255
RIGHT_MOTOR_CLONE_2_ENABLE=255
```

> Esta configuración permite escalar de **2 hasta 6 motores por lado** sin modificar el código fuente. Cambiar el modo de operación solo requiere editar el archivo `.env` y recompilar.

---

## Configuración de pines

**Importante:** Todos los pines que controlan la velocidad del motor deben ser capaces de PWM. Si usas pines digitales simples, asegúrate de que sean apropiados para tu plataforma y configuración.

### ESP32

```cpp
#ifdef USE_ENABLE_PINS
/// @brief Definición de pin para habilitación izquierda. (EN1)
#define LEFT_ENABLE_PIN 32
/// @brief Definición de pin para habilitación derecha. (EN2)
#define RIGHT_ENABLE_PIN 23
#endif

/// @brief Definición de pin para movimiento hacia adelante izquierdo. (IN1)
#define LEFT_FORWARD_PIN 27
/// @brief Definición de pin para movimiento hacia atrás izquierdo. (IN2)
#define LEFT_BACKWARD_PIN 14
/// @brief Definición de pin para movimiento hacia adelante derecho. (IN3)
#define RIGHT_FORWARD_PIN 17
/// @brief Definición de pin para movimiento hacia atrás derecho. (IN4)
#define RIGHT_BACKWARD_PIN 16
```

### Placa compatible con Arduino

```cpp
#ifdef USE_ENABLE_PINS
/// @brief Definición de pin para habilitación izquierda. (EN1)
#define LEFT_ENABLE_PIN 11
/// @brief Definición de pin para habilitación derecha. (EN2)
#define RIGHT_ENABLE_PIN 10
#endif

/// @brief Definición de pin para movimiento hacia adelante izquierdo. (IN1)
#define LEFT_FORWARD_PIN 9
/// @brief Definición de pin para movimiento hacia atrás izquierdo. (IN2)
#define LEFT_BACKWARD_PIN 6
/// @brief Definición de pin para movimiento hacia adelante derecho. (IN3)
#define RIGHT_FORWARD_PIN 5
/// @brief Definición de pin para movimiento hacia atrás derecho. (IN4)
#define RIGHT_BACKWARD_PIN 3
```

**Advertencia sobre pines del receptor PS2 (placas compatibles con Arduino)**

Los pines del receptor PS2 dependen de si `USE_ENABLE_PINS` está definido. Ajusta según tu configuración.

```cpp
#ifdef USE_ENABLE_PINS
/// @brief Pin de reloj para controlador PS2X.
#define CLK 8
/// @brief Pin de atención para controlador PS2X.
#define ATT 7
#else
/// @brief Pin de reloj para controlador PS2X.
#define CLK 10
/// @brief Pin de atención para controlador PS2X.
#define ATT 11
#endif

/// @brief Pin de comando para controlador PS2X.
#define CMD 12
/// @brief Pin de datos para controlador PS2X.
#define DAT 13
```

---

## Uso

Todo el firmware está integrado en `src/main.cpp`. El código está listo para subir después de seleccionar el entorno PlatformIO correcto.

### ESP32 (Bluepad32)

* Código principal: `src/main.cpp`.
* Comportamiento del controlador:

  * Botón **SELECT**: alterna la fuente de velocidad entre los gatillos/paragolpes y el eje Y del stick izquierdo.
  * Botón **START**: alterna la fuente de giro (dirección) entre el eje X del stick izquierdo y el eje X del stick derecho.
  * Botón **X (Cruz/A)**: activa el modo **conducción tipo tanque**.
  * Botón **Y (Triángulo)**: activa el modo **exposición**.
  * Botón **A (Círculo/B)**: activa el modo **conducción manual**.

**Elige el entorno apropiado según tu configuración:**
- Usa `esp32_2_motors`, `esp32_4_motors`, o `esp32_6_motors` con un archivo `.env` para configuraciones personalizadas
- Usa `esp32_preset_l298n` para controlador de motor L298N sin archivo `.env`
- Usa `esp32_preset_tb6612fng` para controlador de motor TB6612FNG sin archivo `.env`

### Compatible con Arduino (PS2)

* Código principal: `src/main.cpp`.
* Mapeo de sticks:

  * Joystick izquierdo → adelante/atrás (eje Y)
  * Joystick derecho → izquierda/derecha (eje X)
* Botones para potencia/dirección/modos:

  * **SELECT** → cambiar fuente de potencia
  * **START** → cambiar fuente de dirección
  * **CRUZ** → conducción manual
  * **TRIÁNGULO** → modo exposición
  * **CUADRADO** → conducción tipo tanque

> Usa el entorno `arduino-uno` en PlatformIO para compilar y subir para Arduino Uno.

---

## Nota
* El repositorio incluye `src/main.cpp` con todo el código principal integrado. Selecciona el entorno PlatformIO correcto antes de compilar.
* **Para ESP32:** Elige entre entornos basados en `.env` (`esp32_*_motors`) o entornos preconfigurados (`esp32_preset_*`) según tus necesidades. Guías de configuración detalladas están disponibles en [inglés](./ENV_CONFIG_EN.md) y [español](./ENV_CONFIG_ES.md).
* **Para Arduino:** Usa el entorno `arduino-uno`. La configuración es fija solo para 2 motores.