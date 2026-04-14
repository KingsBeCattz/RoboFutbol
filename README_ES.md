# Robo-Futbol

[[EN](./README.MD)/**ES**]

Robo-Futbol es un proyecto diseñado para simplificar el control de carros RC usando un gamepad Bluetooth (via Bluepad32 en placas ESP32) o un receptor inalámbrico PS2 en placas compatibles con Arduino.

> **Compatibilidad:** Este código es **solo compatible con PlatformIO** (Visual Studio Code + extensión PlatformIO). Arduino IDE ya no es compatible.

## Controladores compatibles

* Gamepads Bluetooth via Bluepad32 (ESP32)
* Control inalámbrico PS2 (placas compatibles con Arduino)

---

## Instalación rápida (PlatformIO)

1. Descarga el repositorio como `.zip` (o clónalo).
2. Instala Visual Studio Code.
3. Instala PlatformIO (y las extensiones de C/C++ recomendadas) en VS Code.
4. Abre el repositorio en VS Code con PlatformIO activo.
5. Espera mientras PlatformIO descarga los paquetes de framework y librerías necesarios.
6. Selecciona el entorno objetivo en PlatformIO (ver `platformio.ini`) y sube el código a tu placa.

### Entornos disponibles

El proyecto ofrece múltiples entornos divididos entre las plataformas ESP32 y Arduino. El driver de motores se selecciona mediante el nombre del entorno, y su configuración se carga desde `config.ini`.

#### Entornos ESP32

- **`esp32-l298n`**: ESP32 con driver de motores L298N
- **`esp32-tb6612fng`**: ESP32 con driver de motores TB6612FNG
- **`esp32-bts7960`**: ESP32 con driver de motores BTS7960
- **`esp32-bts7960-dual`**: ESP32 con dos drivers de motores BTS7960

#### Entornos Arduino

- **`arduino-l298n`**: Arduino Uno con driver de motores L298N
- **`arduino-tb6612fng`**: Arduino Uno con driver de motores TB6612FNG
- **`arduino-bts7960`**: Arduino Uno con driver de motores BTS7960

### Estructura del proyecto (`platformio.ini` + `config.ini`)

La configuración está dividida en dos archivos. `platformio.ini` define la plataforma, la placa y las dependencias base, mientras que `config.ini` contiene los flags de compilación específicos de cada driver de motores:

```ini
; platformio.ini (simplificado)
[platformio]
extra_configs = config.ini

[env:esp32-l298n]
extends = esp32-base
build_flags = ${config_l298n.build_flags}

[env:esp32-tb6612fng]
extends = esp32-base
build_flags = ${config_tb6612fng.build_flags}

[env:esp32-bts7960]
extends = esp32-base
build_flags = ${config_bts7960.build_flags}

[env:esp32-bts7960-dual]
extends = esp32-base
build_flags = ${config_bts7960_dual.build_flags}

[env:arduino-l298n]
extends = arduino-base
build_flags = ${config_l298n.build_flags}

[env:arduino-tb6612fng]
extends = arduino-base
build_flags = ${config_tb6612fng.build_flags}

[env:arduino-bts7960]
extends = arduino-base
build_flags = ${config_bts7960.build_flags}
```

```ini
; config.ini
[config_l298n]
build_flags =
  -D USE_PWM_INPUTS
  -D L298N=1
  -D HBRIDGE=1

[config_tb6612fng]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D USE_STANDBY
  -D TB6612FNG=2
  -D HBRIDGE=2

[config_bts7960]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D BTS7960=3
  -D HBRIDGE=3

[config_bts7960_dual]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D BTS7960_DUAL=4
  -D HBRIDGE=4
  -D DUAL=1
```

---

## Pinout

Las definiciones de pines se encuentran en `esp32_pinout.hpp` y `arduino_pinout.hpp`. El conjunto correcto de pines se selecciona en tiempo de compilación según el macro `HBRIDGE` definido por el entorno elegido.

**Importante:** Los pines usados para control de velocidad (pines enable/PWM) deben ser capaces de generar PWM en tu placa.

### ESP32

#### L298N

| Función | Pin |
|---|---|
| Avance izquierdo (IN1) | 27 |
| Retroceso izquierdo (IN2) | 14 |
| Avance derecho (IN3) | 25 |
| Retroceso derecho (IN4) | 26 |

#### TB6612FNG

| Función | Pin |
|---|---|
| Enable izquierdo (PWMA) | 21 |
| Avance izquierdo (AIN1) | 18 |
| Retroceso izquierdo (AIN2) | 19 |
| Standby (STBY) | 5 |
| Avance derecho (BIN1) | 17 |
| Retroceso derecho (BIN2) | 16 |
| Enable derecho (PWMB) | 4 |

#### BTS7960

| Función | Pin |
|---|---|
| Enable izquierdo (R_EN / L_EN) | 26 |
| Avance izquierdo (RPWM) | 14 |
| Retroceso izquierdo (LPWM) | 27 |
| Avance derecho (RPWM) | 5 |
| Retroceso derecho (LPWM) | 17 |
| Enable derecho (R_EN / L_EN) | 16 |

#### BTS7960 — Dual / Clon ⭐
> Usa el entorno **`esp32-bts7960-dual`** para esta variante. Los módulos clon exponen pines adicionales además del pinout estándar del BTS7960.

| Función | Pin |
|---|---|
| Enable izquierdo (R_EN / L_EN) | 26 |
| Avance izquierdo (RPWM) | 14 |
| Retroceso izquierdo (LPWM) | 27 |
| Avance derecho (RPWM) | 5 |
| Retroceso derecho (LPWM) | 17 |
| Enable derecho (R_EN / L_EN) | 16 |
| -- | -- |
| Enable izquierdo — Clon (R_EN / L_EN) | 32 |
| Avance izquierdo — Clon (RPWM) | 25 |
| Retroceso izquierdo — Clon (LPWM) | 33 |
| Avance derecho — Clon (RPWM) | 18 |
| Retroceso derecho — Clon (LPWM) | 19 |
| Enable derecho — Clon (R_EN / L_EN) | 21 |

---

### Arduino Uno

Los pines del receptor PS2 son fijos independientemente del driver:

| Función | Pin |
|---|---|
| DAT | 13 |
| CMD | 12 |
| ATT | 7 |
| CLK | 8 |

#### L298N

| Función | Pin |
|---|---|
| Avance izquierdo (IN1) | 9 |
| Retroceso izquierdo (IN2) | 6 |
| Avance derecho (IN3) | 5 |
| Retroceso derecho (IN4) | 3 |

#### TB6612FNG

| Función | Pin |
|---|---|
| Enable izquierdo (PWMA) | 11 |
| Avance izquierdo (AIN1) | 9 |
| Retroceso izquierdo (AIN2) | 6 |
| Standby (STBY) | 4 |
| Avance derecho (BIN1) | 5 |
| Retroceso derecho (BIN2) | 3 |
| Enable derecho (PWMB) | 10 |

#### BTS7960

| Función | Pin |
|---|---|
| Enable izquierdo (R_EN / L_EN) | 11 |
| Avance izquierdo (RPWM) | 9 |
| Retroceso izquierdo (LPWM) | 6 |
| Avance derecho (RPWM) | 5 |
| Retroceso derecho (LPWM) | 3 |
| Enable derecho (R_EN / L_EN) | 10 |

---

## Uso

Todo el firmware está integrado en `src/main.cpp`. El código está listo para subir después de seleccionar el entorno de PlatformIO correcto.

### Modos de input

Ambas plataformas comparten el mismo sistema de modos de input. El **D-Pad** selecciona el modo activo en tiempo de ejecución:

| D-Pad | Modo | Fuente de potencia | Fuente de dirección |
|---|---|---|---|
| ↑ Arriba | Trigger + Stick izquierdo X | Triggers / Bumpers | Stick izquierdo X |
| ↓ Abajo | Trigger + Stick derecho X | Triggers / Bumpers (invertido) | Stick derecho X |
| → Derecha | Doble Stick Derecho | Stick izquierdo Y | Stick derecho X |
| ← Izquierda | Doble Stick Izquierdo | Stick derecho Y | Stick izquierdo X |

El modo por defecto al encender depende de la plataforma:

- **ESP32:** `↑ Arriba` (Trigger + Stick izquierdo X)
- **Arduino:** `→ Derecha` (Doble Stick Derecho)

### ESP32 (Bluepad32)

* Código principal: `src/main.cpp`.
* Mapeo de botones:

  * **D-Pad** → selecciona el modo de input (ver tabla arriba)
  * **X (CUADRADO/Y)** → activa el modo **tank drive**
  * **Y (TRIÁNGULO/X)** → activa el modo **exposición**

Elige el entorno que corresponda a tu placa y driver de motores: `esp32-l298n`, `esp32-tb6612fng`, `esp32-bts7960`, o `esp32-bts7960-dual`.

### Arduino Uno (PS2)

* Código principal: `src/main.cpp`.
* Mapeo de botones:

  * **D-Pad** → selecciona el modo de input (ver tabla arriba)
  * **CUADRADO** → tank drive
  * **TRIÁNGULO** → modo exposición

Elige el entorno que corresponda a tu driver de motores: `arduino-l298n`, `arduino-tb6612fng`, o `arduino-bts7960`.

---

## Notas

* Selecciona el entorno de PlatformIO correcto antes de compilar. El entorno determina tanto la plataforma objetivo como la configuración del driver de motores.
* Los flags de compilación del driver de motores (modos de pines, ID de HBRIDGE) están definidos en `config.ini` y son cargados automáticamente por `platformio.ini`.
* Las asignaciones de pines están definidas en `esp32_pinout.hpp` y `arduino_pinout.hpp`, y se seleccionan en tiempo de compilación mediante el macro `HBRIDGE`.
* **Los módulos clon del BTS7960** exponen pines adicionales además del pinout estándar. Usar el firmware `esp32-bts7960` en un circuito diseñado para el clon dejará el segundo driver sin inicializar e inactivo. Lo inverso — usar el firmware `esp32-bts7960-dual` en un circuito estándar de BTS7960 — no causa ningún problema, ya que los pines extra simplemente quedan sin usar.