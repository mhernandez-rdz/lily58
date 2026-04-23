# Lily58 - Configuración Personal

Configuración personalizada para teclado Lily58 con trackpad Cirque Pinnacle usando QMK Firmware.

---

## 📋 Contenido

- [Características](#características)
- [Estructura del Repositorio](#estructura-del-repositorio)
- [Instalación](#instalación)
- [Workflow de Desarrollo](#workflow-de-desarrollo)
- [Compilación y Flasheo](#compilación-y-flasheo)
- [Layout del Teclado](#layout-del-teclado)
- [Configuración del Trackpad](#configuración-del-trackpad)

---

## ✨ Características

### Teclado
- ✅ **Layout personalizado:** Space y Enter intercambiados en los pulgares
- ✅ **Home Row Mods:** Modificadores en la fila home (Shift, Ctrl, Alt, GUI)
- ✅ **Caps Lock:** Tecla dedicada en la fila home (posición tradicional)
- ✅ **Acentos españoles:** Triple tap en vocales (eee=é, iii=í, ooo=ó, uuu=ú, nnn=ñ). La **A** usa Compose Key (RCtrl + ' + a) porque es tecla Home Row Mod Shift.
- ✅ **Teclas multimedia:** Control de volumen, brillo y reproducción en capas LOWER y RAISE
- ✅ **Print Screen:** Disponible en ambas capas (LOWER y RAISE)
- ✅ **Compose Key:** Ctrl derecho para caracteres especiales (¿, ¡)

### Trackpad Cirque Pinnacle
- ✅ **Modo absoluto** para gestos táctiles
- ✅ **Tap to click** habilitado
- ✅ **Scroll circular** en el borde del trackpad
- ✅ **Sensibilidad optimizada** (2X attenuation)
- ✅ **Sin inercia del cursor** (glide desactivado)

---

## 📁 Estructura del Repositorio

```
lily58/
├── README.md                                    # Este archivo
├── sync.sh                                      # Script de sincronización
├── lily58_cirque_configuracion_reporte.md      # Guía completa de configuración
└── keymap/                                      # Configuración del teclado
    ├── keymap.c                                 # Mapeo de teclas y funciones
    ├── config.h                                 # Configuración del hardware
    ├── rules.mk                                 # Características habilitadas
    └── lib/                                     # Librerías para OLED
```

---

## 🚀 Instalación

### Requisitos Previos

1. **QMK instalado en tu sistema:**
   ```bash
   # En Arch Linux
   sudo pacman -S qmk
   ```

2. **QMK firmware clonado:**
   ```bash
   qmk setup
   ```

### Restaurar Configuración

1. **Copiar keymap al directorio de QMK:**
   ```bash
   cp -r ~/lily58/keymap/* ~/qmk_firmware/keyboards/lily58/keymaps/miguel/
   ```

2. **Compilar:**
   ```bash
   qmk compile -kb lily58/rev1 -km miguel
   ```

3. **Flashear:**
   ```bash
   qmk flash -kb lily58/rev1 -km miguel
   ```

---

## 🔄 Workflow de Desarrollo

### Cuando haces cambios en QMK:

1. **Editar archivos en QMK:**
   ```bash
   nano ~/qmk_firmware/keyboards/lily58/keymaps/miguel/keymap.c
   # o config.h, rules.mk, etc.
   ```

2. **Compilar y probar:**
   ```bash
   qmk compile -kb lily58/rev1 -km miguel
   qmk flash -kb lily58/rev1 -km miguel
   ```

3. **Sincronizar cambios al repositorio:**
   ```bash
   ~/lily58/sync.sh
   ```

   El script:
   - Copia todos los archivos desde QMK al repositorio
   - Opcionalmente hace commit automático a git

4. **Subir a GitHub/GitLab (si tienes repo remoto):**
   ```bash
   cd ~/lily58
   git push
   ```

### Restaurar desde el repositorio:

```bash
cp -r ~/lily58/keymap/* ~/qmk_firmware/keyboards/lily58/keymaps/miguel/
qmk compile -kb lily58/rev1 -km miguel
```

---

## 🔧 Compilación y Flasheo

### Compilar sin flashear

```bash
qmk compile -kb lily58/rev1 -km miguel
```

**Salida:** Genera `lily58_rev1_miguel.hex` en `~/qmk_firmware/`

### Compilar y flashear

```bash
qmk flash -kb lily58/rev1 -km miguel
```

**Proceso:**
1. Compila el firmware
2. Espera a que presiones el botón de reset
3. Flashea automáticamente

**IMPORTANTE:** Debes flashear **ambos lados** del teclado para que funcionen correctamente.

### Limpiar compilación anterior

Si tienes problemas o cambiaste configuraciones importantes:

```bash
qmk clean -a
qmk compile -kb lily58/rev1 -km miguel
```

---

## ⌨️ Layout del Teclado

### Capa QWERTY (Base)

```
.-------------------------------------------------------------.                    .-------------------------------------------------------------.
|  ESC  |   1   |   2   |   3   |   4   |   5   |            |                    |            |   6   |   7   |   8   |   9   |   0   |   `   |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
|  Tab  |   Q   |   W   |   E   |   R   |   T   |            |                    |            |   Y   |   U   |   I   |   O   |   P   |   -   |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
| CAPS  |   A   |   S   |   D   |   F   |   G   |------------|                    |------------|   H   |   J   |   K   |   L   |   ;   |   '   |
|       | Shift | Ctrl  |  Alt  |  GUI  |       |     [      |                    |     ]      |       |  GUI  |  Alt  | Ctrl  | Shift |       |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
| Shift |   Z   |   X   |   C   |   V   |   B   |------------|                    |------------|   N   |   M   |   ,   |   .   |   /   | Shift |
'-------+-------+-------+-------+-------+-------+------------'                    '------------+-------+-------+-------+-------+-------+-------'
                        |  Alt  |  GUI  | Enter | LOWER |                                | RAISE | Space | BkSpc | RCtrl |
                        '-------+-------+-------+-------'                                '-------+-------+-------+-------'
                                                                                                               Compose Key
```

**Home Row Mods (mostrados en la fila home del diagrama):**
- **Mano izquierda:** A/Shift, S/Ctrl, D/Alt, F/GUI
- **Mano derecha:** J/GUI, K/Alt, L/Ctrl, ;/Shift
- **Uso:**
  - Tap corto = letra normal
  - Mantener presionado = modificador
  - Ejemplo: Mantener `A` + `C` = Ctrl+C (copiar)

**Otras teclas especiales:**
- **CAPS Lock:** Tecla dedicada en fila home (lado izquierdo)
- **Vocales (E, I, O, U) y N:** Triple tap = Carácter acentuado (eee=é, nnn=ñ)
- **A con acento:** Compose Key (RCtrl + ' + a) → á. La tecla A es Home Row Mod Shift, por lo que no puede tener Tap Dance.
- **RCtrl:** Compose Key para ¿ y ¡

### Capa LOWER (Símbolos y Multimedia)

```
.-------------------------------------------------------------.                    .-------------------------------------------------------------.
|       |       |       |       | Bri-  | Bri+  |            |                    |            | Stop  | Play  | Mute  | Vol-  | Vol+  | PrtSc |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
|  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |            |                    |            |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
|   `   |   !   |   @   |   #   |   $   |   %   |------------|                    |------------|   ^   |   &   |   *   |   (   |   )   |   ~   |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
|       |       |       |       |       |       |------------|                    |------------|       |   _   |   +   |   {   |   }   |   |   |
'-------+-------+-------+-------+-------+-------+------------'                    '------------+-------+-------+-------+-------+-------+-------'
                        |       |       |       |       |                                |       |       |       |       |
                        '-------+-------+-------+-------'                                '-------+-------+-------+-------'
```

**Multimedia:**
- **Brillo:** LOWER + 4/5 (lado izq)
- **Reproducción:** LOWER + 6/7/8 (lado der) - Stop, Play, Mute
- **Volumen:** LOWER + 9/0 (lado der) - Bajar, Subir
- **Print Screen:** LOWER + ` (esquina superior derecha)

### Capa RAISE (Números, Navegación y Multimedia)

```
.-------------------------------------------------------------.                    .-------------------------------------------------------------.
|       |       |       |       | Bri-  | Bri+  |            |                    |            | Stop  | Play  | Mute  | Vol-  | Vol+  | PrtSc |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
|   `   |   1   |   2   |   3   |   4   |   5   |            |                    |            |   6   |   7   |   8   |   9   |   0   |       |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
|  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |------------|                    |------------|  LEFT | DOWN  |  UP   | RIGHT |       |       |
|-------+-------+-------+-------+-------+-------|            |                    |            |-------+-------+-------+-------+-------+-------|
|  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |------------|                    |------------|   +   |   -   |   =   |   [   |   ]   |   \   |
'-------+-------+-------+-------+-------+-------+------------'                    '------------+-------+-------+-------+-------+-------+-------'
                        |       |       |       |       |                                |       |       |       |       |
                        '-------+-------+-------+-------'                                '-------+-------+-------+-------'
```

**Navegación Vim-style:**
- Las teclas de dirección están en la posición home right (HJKL) para no mover la mano
- Compatible con Home Row Mods: puedes usar Shift+Arrow, Ctrl+Arrow, etc.

**Multimedia (también disponibles en RAISE):**
- Mismas teclas que en LOWER para acceso simétrico desde ambas capas

### Capa ADJUST (LOWER + RAISE)

Activar manteniendo LOWER + RAISE simultáneamente. Actualmente vacía, disponible para futuras expansiones.

---

---

## 🎯 Home Row Mods

### ¿Qué son?

Los **Home Row Mods** colocan las teclas modificadoras (Shift, Ctrl, Alt, GUI) directamente en la fila home del teclado. Esto permite acceder a todos los modificadores sin mover las manos de la posición de escritura base.

### Configuración

**Mano izquierda:**
```
CAPS  A/Shift  S/Ctrl  D/Alt  F/GUI  G
```

**Mano derecha:**
```
H  J/GUI  K/Alt  L/Ctrl  ;/Shift  '
```

### Funcionamiento

- **Tap rápido:** Escribe la letra normal (a, s, d, f, j, k, l, ;)
- **Mantener presionado:** Activa el modificador (Shift, Ctrl, Alt, GUI)

### Ejemplos de uso

| Combinación | Acción | Resultado |
|-------------|--------|-----------|
| Mantener `A` + `C` | Shift + C | C mayúscula |
| Mantener `S` + `C` | Ctrl + C | Copiar |
| Mantener `D` + `C` | Alt + C | Depende del contexto/app |
| Mantener `F` + `T` | GUI + T | Abrir terminal (en muchos WMs) |
| Mantener `S` + `V` | Ctrl + V | Pegar |
| Mantener `L` + `Z` | Ctrl + Z | Deshacer |

### Configuración de Timing

Para evitar activaciones accidentales y optimizar la experiencia, se configuraron los siguientes parámetros en `config.h`:

```c
// Home Row Mods Configuration
#define TAPPING_TERM 200              // Tiempo base para detectar tap vs hold (200ms)
#define TAPPING_TERM_PER_KEY          // Permite ajustar timing por tecla
#define PERMISSIVE_HOLD               // Mejora respuesta de hold en typing rápido
#define QUICK_TAP_TERM 120            // Tiempo para repetición rápida de letra
#define QUICK_TAP_TERM_PER_KEY        // Ajuste fino por tecla
```

**Tiempos personalizados por tecla (en keymap.c):**
- **Shift (A, ;):** 250ms (200 + 50) - Más tiempo para evitar mayúsculas accidentales
- **GUI (F, J):** 230ms (200 + 30) - Ligeramente más tiempo
- **Ctrl y Alt (S, D, K, L):** 200ms - Tiempo estándar

### Ventajas

✅ **Ergonomía:** Manos siempre en posición home
✅ **Velocidad:** No necesitas mover las manos para modificadores
✅ **Simetría:** Ambas manos tienen acceso completo a modificadores
✅ **Combos complejos:** Fácil hacer Ctrl+Shift+algo usando ambas manos

### Consejos de uso

1. **Al principio puede sentirse extraño** - Dale tiempo (1-2 semanas de adaptación)
2. **Usa ambas manos para combos** - Ej: Shift derecho (;) + letra izquierda
3. **Para typing rápido** - El sistema detecta automáticamente si quieres la letra o el modificador
4. **Si activas modificador por error** - Ajusta tu velocidad de typing, el timing se puede afinar

---

## 🖱️ Configuración del Trackpad

### Especificaciones Actuales

```c
// En config.h
#define CIRQUE_PINNACLE_ADDR 0x2A
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
```

### Funciones Habilitadas

| Función | Estado | Descripción |
|---------|--------|-------------|
| **Modo Absoluto** | ✅ Activo | Posición exacta del dedo, mejor para gestos |
| **Tap to Click** | ✅ Activo | Toque simple = clic izquierdo |
| **Scroll Circular** | ✅ Activo | Movimiento circular en borde = scroll |
| **Cursor Glide** | ❌ Desactivado | Sin inercia del cursor |
| **Sensibilidad** | 2X | Optimizado para overlay rígido cóncavo |

### Uso del Trackpad

**Movimiento del cursor:**
- Desliza el dedo sobre el centro del trackpad

**Clic izquierdo:**
- Toca rápidamente el trackpad (tap)

**Scroll:**
- Mueve el dedo en círculos alrededor del **borde exterior** del trackpad
- Movimiento circular horario/antihorario = scroll arriba/abajo
- Funciona en todas direcciones

**Arrastrar (drag):**
- Doble tap + mantener en el segundo tap

### Problemas Conocidos

- **Detección de scroll:** Ocasionalmente el inicio del gesto de scroll no se detecta de inmediato
  - **Workaround:** Iniciar el movimiento circular ligeramente más cerca del centro
  - En pruebas para ver si mejora con el tiempo de uso

---

## 📟 Pantalla OLED

El Lily58 incluye una **pantalla OLED SSD1306 de 128×32 píxeles** en la mitad izquierda del teclado (offhand). La pantalla está **activada** (`OLED_ENABLE = yes`) y muestra información útil en tiempo real.

### ¿Qué muestra cada mitad?

| Mitad | Tipo | Contenido actual |
|-------|------|------------------|
| **Derecha (master)** | Información activa | Capa actual (`Layer: Base` / `Lower` / `Raise` / `Adjust`)<br>Última tecla presionada (`fila x columna, código : letra`)<br>Historial de las últimas 20 teclas |
| **Izquierda (offhand)** | Logo estático | Logo QMK (girado 180° para orientación correcta) |

### Archivos relacionados

```
keymap/
├── keymap.c              # oled_task_user() — lógica de renderizado
├── rules.mk              # OLED_ENABLE = yes, SRC += ./lib/*.c
└── lib/                  # Librerías OLED (compiladas como parte del keymap)
    ├── layer_state_reader.c   # Nombre de la capa activa
    ├── keylogger.c            # Última tecla + historial
    ├── logo_reader.c          # Logo QMK
    ├── host_led_state_reader.c # Estado Caps/Num/Scroll Lock (no usado actualmente)
    ├── mode_icon_reader.c      # Icono Mac/Windows (no usado actualmente)
    ├── rgb_state_reader.c      # Estado RGB (requiere RGBLIGHT_ENABLE)
    └── timelogger.c            # Timing entre pulsaciones (no usado actualmente)
```

### Funciones disponibles pero no activas

Estas funciones ya están declaradas en `keymap.c` y listas para usar. Solo hay que **descomentar** las líneas correspondientes en `oled_task_user()`:

- `read_host_led_state()` — Muestra si **Caps Lock**, **Num Lock** o **Scroll Lock** están activos
- `read_mode_icon(swap)` — Muestra icono de modo **Mac** o **Windows**
- `read_timelog()` — Muestra tiempo transcurrido entre pulsaciones

### Posibles mejoras futuras

| Mejora | Descripción | Archivos a modificar |
|--------|-------------|---------------------|
| **Timeout de apagado** | Apagar OLED tras X segundos de inactividad (evita burn-in) | `config.h` — agregar `#define OLED_TIMEOUT 30000` |
| **Fade out** | Apagado gradual suave | `config.h` — `#define OLED_FADE_OUT` |
| **Scroll del logo** | Logo izquierdo se desplaza horizontalmente | `keymap.c` — agregar `oled_scroll_left()` en offhand |
| **WPM** | Palabras por minuto en pantalla | `rules.mk` — `WPM_ENABLE = yes` + función custom en `keymap.c` |
| **Logo personalizado** | Reemplazar logo QMK por diseño propio | `lib/logo_reader.c` o fuente custom `glcdfont_lily.c` |
| **Brillo ajustable** | Reducir/aumentar brillo de la pantalla | `config.h` — `#define OLED_BRIGHTNESS 128` (0–255) |

---

## 📚 Documentación Adicional

- **Guía completa de configuración:** Ver `lily58_cirque_configuracion_reporte.md`
- **QMK OLED Docs:** https://docs.qmk.fm/features/oled_driver
- **QMK Docs:** https://docs.qmk.fm/
- **Cirque Pinnacle:** https://docs.qmk.fm/features/pointing_device

---

## 🔄 Control de Versiones

### Inicializar repositorio Git

```bash
cd ~/lily58
git init
git add .
git commit -m "Initial lily58 configuration"
```

### Conectar con GitHub

```bash
git remote add origin https://github.com/tu-usuario/lily58-config.git
git branch -M main
git push -u origin main
```

### Workflow con Git

1. Hacer cambios en QMK
2. Compilar y probar
3. Sincronizar: `~/lily58/sync.sh`
4. Push: `cd ~/lily58 && git push`

---

## 🛠️ Troubleshooting

### El teclado no compila

```bash
qmk clean -a
qmk compile -kb lily58/rev1 -km miguel
```

### El trackpad no funciona después de flashear

- Verifica que flasheaste **ambos lados** del teclado
- Verifica que el cable TRRS esté bien conectado
- Reconecta el USB

### Cambios no se reflejan después de flashear

- Asegúrate de flashear el lado correcto (trackpad está en el derecho)
- Haz `qmk clean -a` antes de compilar

### Sincronización no funciona

```bash
chmod +x ~/lily58/sync.sh
~/lily58/sync.sh
```

---

## 📝 Changelog

### 2026-04-16
- ✅ Configuración inicial del Lily58
- ✅ Trackpad Cirque configurado y funcionando
- ✅ Teclas multimedia implementadas
- ✅ Tap Dance para acentos españoles (vocales y ñ)
- ✅ Sensibilidad del trackpad ajustada a 2X
- ✅ Home Row Mods para acceso rápido a modificadores

---

## 📄 Licencia

Configuración personal basada en QMK Firmware (GPL v2)

---

*Última actualización: 2026-04-16*
