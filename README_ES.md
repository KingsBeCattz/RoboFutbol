# Robo-Futbol

[[EN](./README.MD)/**ES**]

Robo-Futbol es un proyecto diseñado para simplificar el control de autos RC usando un gamepad Bluetooth (vía Bluepad32 en placas ESP32) o un receptor inalámbrico PS2 en placas compatibles con Arduino.

> **Compatibilidad:** Este código es **únicamente compatible con PlatformIO** (Visual Studio Code + extensión PlatformIO). Arduino IDE ya no está soportado.

## Controladores compatibles

* Gamepads Bluetooth vía Bluepad32 (ESP32)
* Control inalámbrico PS2 (placas compatibles con Arduino)

---

## Instalación rápida (PlatformIO)

1. Descarga el repositorio como `.zip` (o clónalo).
2. Instala Visual Studio Code.
3. Instala PlatformIO (y las extensiones recomendadas de C/C++) en VS Code.
4. Abre el repositorio en VS Code con PlatformIO activo.
5. Espera a que PlatformIO descargue los paquetes de framework y librerías necesarios.
6. Selecciona el entorno objetivo en PlatformIO (ver `platformio.ini`) y sube el código a tu placa.

### Entornos disponibles

El proyecto incluye múltiples entornos divididos entre las plataformas ESP32 y Arduino. El driver de motores se selecciona según el nombre del entorno, y su configuración se carga desde `config.ini`.

#### Entornos ESP32

- **`esp32-l298n`**: ESP32 con driver de motores L298N
- **`esp32-tb6612fng`**: ESP32 con driver de motores TB6612FNG
- **`esp32-tb6612fng-dual`**: ESP32 con dos drivers de motores TB6612FNG
- **`esp32-bts7960`**: ESP32 con driver de motores BTS7960
- **`esp32-bts7960-dual`**: ESP32 con dos drivers de motores BTS7960

#### Entornos Arduino

- **`arduino-l298n`**: Arduino Uno con driver de motores L298N
- **`arduino-tb6612fng`**: Arduino Uno con driver de motores TB6612FNG
- **`arduino-bts7960`**: Arduino Uno con driver de motores BTS7960

### Estructura del proyecto (`platformio.ini` + `config.ini`)

La configuración está dividida en dos archivos. `platformio.ini` define la plataforma, la placa y las dependencias base, mientras que `config.ini` contiene los build flags específicos de cada driver de motores:

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

[env:esp32-tb6612fng-dual]
extends = esp32-base
build_flags = ${config_tb6612fng_dual.build_flags}

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

[config_tb6612fng_dual]
build_flags =
  -D USE_PWM_INPUTS
  -D USE_DIGITAL_ENABLE
  -D USE_STANDBY
  -D TB6612FNG=2
  -D HBRIDGE=2
  -D DUAL=1

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
  -D BTS7960=3
  -D HBRIDGE=3
  -D DUAL=1
```

---

## Pinout

Las definiciones de pines se encuentran en `esp32_pinout.hpp`, `esp32_clones.hpp` y `arduino_pinout.hpp`. El conjunto correcto de pines se selecciona en tiempo de compilación según los macros `HBRIDGE` y `DUAL` definidos por el entorno elegido.

**Importante:** Los pines usados para control de velocidad (pines de habilitación/PWM) deben ser compatibles con PWM en tu placa.

### ESP32

#### L298N

| Función | Pin |
|---|---|
| Izquierda Adelante (IN1) | 27 |
| Izquierda Atrás (IN2) | 14 |
| Derecha Adelante (IN3) | 25 |
| Derecha Atrás (IN4) | 26 |

#### TB6612FNG

| Función | Pin |
|---|---|
| Habilitación Izquierda (PWMA) | 21 |
| Izquierda Adelante (AIN1) | 18 |
| Izquierda Atrás (AIN2) | 19 |
| Standby (STBY) | 5 |
| Derecha Adelante (BIN1) | 17 |
| Derecha Atrás (BIN2) | 16 |
| Habilitación Derecha (PWMB) | 4 |

#### TB6612FNG — Dual / Clon ⭐
> Usa el entorno **`esp32-tb6612fng-dual`** para esta variante. Los módulos clon exponen pines adicionales junto al pinout estándar del TB6612FNG; usar el entorno incorrecto dejará el driver clon sin inicializar e inactivo.

| Función | Pin |
|---|---|
| Habilitación Izquierda (PWMA) | 21 |
| Izquierda Adelante (AIN1) | 18 |
| Izquierda Atrás (AIN2) | 19 |
| Standby (STBY) | 5 |
| Derecha Adelante (BIN1) | 17 |
| Derecha Atrás (BIN2) | 16 |
| Habilitación Derecha (PWMB) | 4 |
| -- | -- |
| Habilitación Izquierda — Clon (PWMA) | 32 |
| Izquierda Adelante — Clon (AIN1) | 25 |
| Izquierda Atrás — Clon (AIN2) | 33 |
| Standby — Clon (STBY) | 26 |
| Derecha Adelante — Clon (BIN1) | 27 |
| Derecha Atrás — Clon (BIN2) | 14 |
| Habilitación Derecha — Clon (PWMB) | 12 |

#### BTS7960

| Función | Pin |
|---|---|
| Habilitación Izquierda (R_EN / L_EN) | 26 |
| Izquierda Adelante (RPWM) | 14 |
| Izquierda Atrás (LPWM) | 27 |
| Derecha Adelante (RPWM) | 5 |
| Derecha Atrás (LPWM) | 17 |
| Habilitación Derecha (R_EN / L_EN) | 16 |

#### BTS7960 — Dual / Clon ⭐
> Usa el entorno **`esp32-bts7960-dual`** para esta variante. Los módulos clon exponen pines adicionales junto al pinout estándar del BTS7960; usar el entorno incorrecto resultará en un comportamiento incorrecto de los motores.

| Función | Pin |
|---|---|
| Habilitación Izquierda (R_EN / L_EN) | 26 |
| Izquierda Adelante (RPWM) | 14 |
| Izquierda Atrás (LPWM) | 27 |
| Derecha Adelante (RPWM) | 5 |
| Derecha Atrás (LPWM) | 17 |
| Habilitación Derecha (R_EN / L_EN) | 16 |
| -- | -- |
| Habilitación Izquierda — Clon (R_EN / L_EN) | 32 |
| Izquierda Adelante — Clon (RPWM) | 25 |
| Izquierda Atrás — Clon (LPWM) | 33 |
| Derecha Adelante — Clon (RPWM) | 18 |
| Derecha Atrás — Clon (LPWM) | 19 |
| Habilitación Derecha — Clon (R_EN / L_EN) | 21 |

#### Límite de velocidad (todos los entornos ESP32)

| Función | Pin |
|---|---|
| Límite de velocidad (SPEED_LIMIT_PIN) | 34 |

> El pin 34 es de solo entrada en el ESP32, lo que lo hace ideal para una lectura pasiva con pullup. Ver [Límite de velocidad](#límite-de-velocidad) para más detalles.

---

### Arduino Uno

Los pines del receptor PS2 son fijos independientemente del driver:

| Función | Pin |
|---|---|
| DAT | 2 |
| CMD | 12 |
| ATT | 7 |
| CLK | 8 |

#### L298N

| Función | Pin |
|---|---|
| Izquierda Adelante (IN1) | 9 |
| Izquierda Atrás (IN2) | 6 |
| Derecha Adelante (IN3) | 5 |
| Derecha Atrás (IN4) | 3 |

#### TB6612FNG

| Función | Pin |
|---|---|
| Habilitación Izquierda (PWMA) | 11 |
| Izquierda Adelante (AIN1) | 9 |
| Izquierda Atrás (AIN2) | 6 |
| Standby (STBY) | 4 |
| Derecha Adelante (BIN1) | 5 |
| Derecha Atrás (BIN2) | 3 |
| Habilitación Derecha (PWMB) | 10 |

#### BTS7960

| Función | Pin |
|---|---|
| Habilitación Izquierda (R_EN / L_EN) | 11 |
| Izquierda Adelante (RPWM) | 9 |
| Izquierda Atrás (LPWM) | 6 |
| Derecha Adelante (RPWM) | 5 |
| Derecha Atrás (LPWM) | 3 |
| Habilitación Derecha (R_EN / L_EN) | 10 |

#### Límite de velocidad (todos los entornos Arduino)

| Función | Pin |
|---|---|
| Límite de velocidad (SPEED_LIMIT_PIN) | A0 |

> Ver [Límite de velocidad](#límite-de-velocidad) para más detalles.

---

## Uso

Todo el firmware está integrado en `src/main.cpp`. El código está listo para subir después de seleccionar el entorno correcto de PlatformIO.

### Modos de entrada

Ambas plataformas comparten el mismo sistema de modos de entrada. El **D-Pad** selecciona el modo activo en tiempo de ejecución:

| D-Pad | Modo | Fuente de potencia | Fuente de dirección |
|---|---|---|---|
| ↑ Arriba | Gatillo + X Izquierdo | Gatillos / Bumpers | Stick izquierdo X |
| ↓ Abajo | Gatillo + X Derecho | Gatillos / Bumpers (invertido) | Stick derecho X |
| → Derecha | Doble Stick Derecho | Stick izquierdo Y | Stick derecho X |
| ← Izquierda | Doble Stick Izquierdo | Stick derecho Y | Stick izquierdo X |

El modo predeterminado al arrancar depende de la plataforma:

- **ESP32:** `↑ Arriba` (Gatillo + X Izquierdo)
- **Arduino:** `→ Derecha` (Doble Stick Derecho)

### Límite de velocidad

Por defecto, la velocidad está limitada al 50% a menos que se mantenga presionado el **botón A** (ESP32) o **botón Cruz** (Arduino), lo que permite el 100% de velocidad.

Este comportamiento puede **desactivarse permanentemente al arrancar**: si `SPEED_LIMIT_PIN` está conectado a GND cuando la placa inicia, el límite se elimina por completo y el botón no tiene efecto durante toda la sesión. Desconectar el pin después del arranque no tiene efecto; el estado se lee una sola vez al inicio.

| Condición | Comportamiento |
|---|---|
| Pin flotante / HIGH al arrancar | Límite activo — mantén A/Cruz para 100% |
| Pin conectado a GND al arrancar | Sin límite — velocidad completa siempre |

### ESP32 (Bluepad32)

* Código principal: `src/main.cpp`.
* Mapeo de botones:

  * **D-Pad** → seleccionar modo de entrada (ver tabla anterior)
  * **A** → mantener para velocidad completa (cuando el límite está activo)
  * **X (SQUARE/Y)** → activa el modo **tank drive**
  * **Y (TRIANGLE/X)** → activa el modo **exposición**

Elige el entorno que corresponda a tu placa y driver de motores: `esp32-l298n`, `esp32-tb6612fng`, `esp32-tb6612fng-dual`, `esp32-bts7960` o `esp32-bts7960-dual`.

### Arduino Uno (PS2)

* Código principal: `src/main.cpp`.
* Mapeo de botones:

  * **D-Pad** → seleccionar modo de entrada (ver tabla anterior)
  * **Cruz** → mantener para velocidad completa (cuando el límite está activo)
  * **SQUARE** → tank drive
  * **TRIANGLE** → modo exposición

Elige el entorno que corresponda a tu driver de motores: `arduino-l298n`, `arduino-tb6612fng` o `arduino-bts7960`.

---

## Notas

* Selecciona el entorno correcto de PlatformIO antes de compilar. El entorno determina tanto la plataforma objetivo como la configuración del driver de motores.
* Los build flags del driver de motores (modos de pin, ID de HBRIDGE) se definen en `config.ini` y son cargados automáticamente por `platformio.ini`.
* Las asignaciones de pines se definen en `esp32_pinout.hpp`, `esp32_clones.hpp` y `arduino_pinout.hpp`, y se seleccionan en tiempo de compilación mediante los macros `HBRIDGE` y `DUAL`.
* **Los módulos clon de TB6612FNG** usan un mapeo de pines diferente al de las placas estándar. Usa siempre `esp32-tb6612fng-dual` para estos. Ejecutar el firmware `esp32-tb6612fng` en un circuito dual/clon dejará el driver clon sin inicializar e inactivo. Lo contrario — ejecutar `esp32-tb6612fng-dual` en un circuito TB6612FNG estándar — es inofensivo, ya que los pines extra simplemente no se usan.
* **Los módulos clon de BTS7960** usan un mapeo de pines diferente al de las placas estándar. Usa siempre `esp32-bts7960-dual` para estos. Ejecutar el firmware `esp32-bts7960` en un circuito dual/clon dejará el driver clon sin inicializar e inactivo. Lo contrario — ejecutar `esp32-bts7960-dual` en un circuito BTS7960 estándar — es inofensivo, ya que los pines extra simplemente no se usan.
* **El pin de límite de velocidad** (`SPEED_LIMIT_PIN`) se lee una sola vez al arrancar. Conectarlo o desconectarlo después del arranque no tiene efecto hasta el siguiente reinicio.