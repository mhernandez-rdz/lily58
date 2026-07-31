# Instrucciones para Claude Code

Este es un repositorio de configuración de teclado **Lily58** con trackpad **Cirque Pinnacle** usando **QMK Firmware**.

## 🎯 Contexto del Proyecto

### Usuario
- **Nombre:** Miguel
- **Sistema:** Arch Linux
- **Entorno:** Hyprland (Wayland)
- **Idioma:** Español (requiere acentos: á, é, í, ó, ú, ñ)

### Hardware
- **Teclado:** Lily58 (split keyboard, 58 teclas)
- **Trackpad:** Cirque Pinnacle 40mm (overlay rígido cóncavo)
- **Master side:** **Izquierdo** (el cable USB va a la mitad izquierda)
- **Trackpad side:** Derecho — o sea, en la mitad **esclava**. Por eso `SPLIT_POINTING_ENABLE` + `POINTING_DEVICE_RIGHT` son obligatorios.
- **Conexión:** TRRS cable entre ambos lados (transporte serial en D2; el bus I²C queda libre para el Cirque)

## 📁 Estructura del Proyecto

```
~/lily58/                          # Este repositorio (backup/documentación)
├── CLAUDE.md                      # Este archivo
├── README.md                      # Documentación completa para el usuario
├── sync.sh                        # Script de sincronización QMK → repo
├── lily58_cirque_configuracion_reporte.md  # Guía técnica del trackpad
└── keymap/                        # Backup de la configuración
    ├── keymap.c                   # Layout y funciones
    ├── config.h                   # Configuración de hardware
    ├── rules.mk                   # Features habilitadas
    └── lib/                       # Librerías OLED

~/qmk_firmware/keyboards/lily58/keymaps/miguel/  # Configuración activa en QMK
├── keymap.c                       # ← Editar aquí
├── config.h                       # ← Editar aquí
├── rules.mk                       # ← Editar aquí
└── lib/                           # Librerías OLED
```

## ⚙️ Configuración Actual

### Características del Teclado

1. **Home Row Mods** (MUY IMPORTANTE)
   - Mano izquierda: A/Shift, S/Ctrl, D/Alt, F/GUI
   - Mano derecha: J/GUI, K/Alt, L/Ctrl, ;/Shift
   - Tap = letra, Hold = modificador
   - TAPPING_TERM: 200ms base (Shift: **180ms**, GUI: 230ms)
   - PERMISSIVE_HOLD habilitado
   - `get_hold_on_other_key_press()` devuelve `true` **solo** para los Shift (A y `;`): hold inmediato al presionar otra tecla, para mayúsculas rápidas

2. **Layout personalizado**
   - Space y Enter **intercambiados** en los pulgares
   - Enter a la izquierda, Space a la derecha

3. **Acentos españoles**
   - Triple tap en vocales: aaa → á, eee → é, iii → í, ooo → ó, uuu → ú
   - Triple tap en N: nnn → ñ
   - Funciona con Shift para mayúsculas (AAA → Á)
   - Implementado con Tap Dance + Compose Key

4. **Compose Key**
   - RCtrl = Compose Key
   - Compose + ' + vocal = vocal con acento
   - Compose + ~ + n = ñ
   - Para ¿ y ¡ también

5. **Caps Lock**
   - Tecla dedicada en fila home (KC_CAPS)
   - **NO** es doble tap en Shift (eso se removió porque era problemático)

6. **Multimedia** (en capa LOWER)
   - Brillo: LOWER + 4/5
   - Volumen: LOWER + 9/0
   - Reproducción: LOWER + 6/7/8

### Trackpad Cirque Pinnacle

```c
#define SPLIT_POINTING_ENABLE   // trackpad en la mitad esclava (derecha)
#define POINTING_DEVICE_RIGHT
#define CIRQUE_PINNACLE_ADDR 0x2A
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
// POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE está DESACTIVADO (comentado)
```

- **Sensibilidad:** 2X attenuation (optimizada para overlay rígido)
- **Tap to click:** Habilitado
- **Scroll circular:** Habilitado (movimiento circular en bordes)
- **Cursor glide:** Desactivado (el usuario lo encontró incómodo)

**Problema conocido:**
- Detección del inicio del gesto de scroll a veces es inconsistente
- Usuario está probando la configuración 2X durante varios días

## 🔧 Workflow de Desarrollo

### Cuando el usuario quiere hacer cambios:

1. **Editar archivos en QMK:**
   ```bash
   nano ~/qmk_firmware/keyboards/lily58/keymaps/miguel/keymap.c
   # o config.h, rules.mk
   ```

2. **Compilar:**
   ```bash
   qmk compile -kb lily58/rev1 -km miguel
   ```

3. **Flashear:**
   ```bash
   qmk flash -kb lily58/rev1 -km miguel
   ```
   - **IMPORTANTE:** Hay que flashear **AMBOS lados** del teclado
   - El trackpad está en el lado derecho (master)

4. **Sincronizar al repositorio:**
   ```bash
   ~/lily58/sync.sh
   ```

### Si hay problemas de compilación:

```bash
qmk clean -a
qmk compile -kb lily58/rev1 -km miguel
```

## 🚨 Reglas Importantes

### LO QUE NUNCA DEBES HACER:

1. ❌ **NO eliminar Home Row Mods** - Es una característica fundamental
2. ❌ **NO cambiar el orden Space/Enter** sin confirmar - Está personalizado
3. ❌ **NO habilitar POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE** - Usuario lo desactivó expresamente
4. ❌ **NO sugerir doble tap en Shift para Caps Lock** - Se removió porque era problemático
5. ❌ **NO usar macros de Unicode** - Fallaron con ibus, usar Compose Key en su lugar
6. ❌ **NO quitar `SPLIT_POINTING_ENABLE` ni `POINTING_DEVICE_RIGHT`** - El trackpad está en la mitad esclava; sin esos defines deja de funcionar por completo
7. ❌ **NO anclar la rotación del OLED a `is_keyboard_master()`** - Va anclada a `is_keyboard_left()`, porque la orientación depende de cómo está montada físicamente cada pantalla

### ⚠️ ESPACIO EN FLASH

El firmware está al **94% (27114/28672 bytes, ~1.5 KB libres)** en el atmega32u4. Antes de agregar
cualquier feature, considera que cada bitmap OLED cuesta **512 bytes**. Si no cabe, hay margen fácil en:
- `TD_A_ACUTE` está definido pero nunca se usa en el keymap (la `A` es `LSFT_T(KC_A)`) — es código muerto
- `rgb_state_reader.c` y `logo_reader.c` siguen en `SRC` sin usarse

### LO QUE SIEMPRE DEBES HACER:

1. ✅ **Siempre editar archivos en `~/qmk_firmware/keyboards/lily58/keymaps/miguel/`**
2. ✅ **Después de cambios exitosos, recordar sincronizar con `~/lily58/sync.sh`**
3. ✅ **Actualizar README.md si cambias funcionalidad importante**
4. ✅ **Recordar que hay que flashear AMBOS lados del teclado**
5. ✅ **Si cambias config.h o rules.mk, hacer `qmk clean -a` antes de compilar**

## 📝 Archivos Clave

### keymap.c
- Contiene los layouts de las 4 capas: QWERTY, LOWER, RAISE, ADJUST
- Define los Tap Dance para acentos españoles
- Implementa las funciones de Home Row Mods (get_tapping_term, get_quick_tap_term)
- **Código OLED** (`oled_task_user()`, `oled_init_user()`)
- **4 bitmaps PROGMEM** (`byakko_logo[]`, `seiryu_logo[]`, `suzaku_logo[]`, `genbu_logo[]`)
- Lógica del trackpad (`pointing_device_task_user()`)

**Líneas importantes** (aproximadas — verificar con `grep` antes de confiar):
- Línea 11-18: Enum de Tap Dance (solo vocales y ñ, NO hay TD_LSHIFT_CAPS)
- Línea 95-102: Definiciones de Tap Dance
- Línea 121-127: QWERTY layer con Home Row Mods
- Línea 195-243: Timing de Home Row Mods (`get_tapping_term`, `get_quick_tap_term`, `get_hold_on_other_key_press`)
- Línea 251-392: Bitmaps OLED de las 4 bestias divinas (512 bytes cada uno)
- Línea 398-428: Lógica del trackpad (`pointing_device_task_user`) — Shift+tap = clic derecho, Shift+mover = drag
- Línea 433-439: `oled_init_user()` — rotación anclada a `is_keyboard_left()`, NO a `is_keyboard_master()`
- Línea 451-480: Código OLED con switch por capa (`oled_task_user()`)

### lib/ (Librerías OLED)

> ⚠️ **OJO con la ubicación.** `lib/` **NO** vive en el directorio del keymap. Los archivos reales están en
> `~/qmk_firmware/keyboards/lily58/lib/` (nivel teclado); el `SRC += ./lib/...` de `rules.mk` se resuelve ahí.
> La copia en `~/lily58/keymap/lib/` es solo un respaldo, y **`sync.sh` no la actualiza** (solo copia
> del keymap al repo). Si editas un reader, hazlo en QMK y copia a mano al repo.

Funciones disponibles para la pantalla OLED:
- `layer_state_reader.c` — Nombre de la capa activa (**en uso**, pantalla derecha/offhand)
- `keylogger.c` — Última tecla + historial de 20 teclas (**desactivado**: solo funciona en el master, y el master ahora muestra las bestias)
- `logo_reader.c` — Logo QMK (respaldo, no usado actualmente)
- `host_led_state_reader.c` — Estado de Caps/Num/Scroll Lock (no usado)
- `mode_icon_reader.c` — Icono de modo Mac/Windows (no usado)
- `rgb_state_reader.c` — Estado del RGB (requiere RGBLIGHT_ENABLE)
- `timelogger.c` — Tiempo entre pulsaciones (no usado)

**Nota:** Las imágenes actuales (bestias divinas) no usan `lib/`. Son arrays de bytes `PROGMEM` embebidos directamente en `keymap.c` y se dibujan con `oled_write_raw_P()`.

### config.h
- Configuración de Home Row Mods (líneas 23-28)
- `MASTER_LEFT` (línea 47) — el USB va en la mitad izquierda
- `SPLIT_LAYER_STATE_ENABLE` (línea 51) — **Sincroniza estado de capa al lado offhand (derecho)**
- `SPLIT_POINTING_ENABLE` + `POINTING_DEVICE_RIGHT` (líneas 57-58) — **el trackpad está en la mitad esclava; sin esto no funciona**
- Configuración del trackpad Cirque (líneas 60-65)
- RGB lighting (líneas 30-45) — nota: `RGBLIGHT_ENABLE = no` en rules.mk, así que esto no hace nada

### rules.mk
- Features habilitadas:
  - POINTING_DEVICE_ENABLE = yes
  - POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
  - TAP_DANCE_ENABLE = yes
  - EXTRAKEY_ENABLE = yes (para multimedia)
  - OLED_ENABLE = yes

## 🎯 Tareas Comunes

### Si el usuario quiere agregar una nueva tecla/función:
1. Lee `~/qmk_firmware/keyboards/lily58/keymaps/miguel/keymap.c`
2. Identifica la capa apropiada (QWERTY, LOWER, RAISE, ADJUST)
3. Haz el cambio manteniendo la estructura
4. Compila y prueba
5. Sincroniza con `~/lily58/sync.sh`
6. Actualiza README.md si es necesario

### Si el usuario quiere ajustar el trackpad:
1. Lee `~/qmk_firmware/keyboards/lily58/keymaps/miguel/config.h`
2. Modifica las defines de CIRQUE_PINNACLE_*
3. Consulta `lily58_cirque_configuracion_reporte.md` para opciones disponibles
4. **Siempre hacer `qmk clean -a`** antes de compilar cambios en config.h
5. Flashea AMBOS lados
6. Sincroniza y documenta en README.md

### Si el usuario quiere ajustar timing de Home Row Mods:
1. Para timing global: edita TAPPING_TERM en config.h (línea 24)
2. Para timing por tecla: edita get_tapping_term() en keymap.c (línea 195-211)
3. QUICK_TAP_TERM en config.h (línea 27) controla repetición rápida

### Si el usuario quiere modificar la pantalla OLED:

#### Opción A: Cambiar las bestias divinas por otras imágenes
1. Prepara una imagen de 320×427 (o similar) en `~/Pictures/nombre.jpg`
2. Usa el script de conversión (ver `scripts/` o pedir ayuda) para generar el array OLED
3. Reemplaza el array correspondiente en `keymap.c` (`byakko_logo[]`, `seiryu_logo[]`, etc.)
4. Asegúrate de usar `oled_write_raw_P(array, sizeof(array))` en `oled_task_user()`

#### Opción B: Usar las librerías de texto en `lib/`
1. Edita `oled_task_user()` en `keymap.c` (líneas 470–485)
2. Funciones disponibles:
   - `read_layer_state()` — capa activa
   - `read_keylog()` / `read_keylogs()` — última tecla e historial (**solo sirven en el master**; hay que reactivar `keylogger.c` en `SRC` y volver a llamar `set_keylog()` desde `process_record_user()`)
   - `read_logo()` — logo QMK
   - `read_host_led_state()` — estado Caps/Num/Scroll Lock
   - `read_mode_icon(swap)` — icono Mac/Windows
   - `read_timelog()` — timing entre teclas
3. Para agregar nuevas funciones: crea archivo en `lib/` y agrégalo a `SRC` en `rules.mk`

#### Configuraciones útiles en `config.h`:
- `SPLIT_LAYER_STATE_ENABLE` — sincroniza capa al lado offhand (ya activo)
- `#define OLED_TIMEOUT 30000` — apaga OLED tras 30 segundos de inactividad
- `#define OLED_BRIGHTNESS 128` — ajusta brillo (0–255)

## 🔍 Debugging

### El teclado no responde:
- Verifica cable TRRS conectado
- Verifica que ambos lados estén flasheados
- Reconecta USB

### Cambios no se aplican:
- `qmk clean -a` y recompila
- Verifica que flasheaste el lado correcto (trackpad = derecho = master)

### Trackpad no funciona:
- Verifica que `MASTER_LEFT`, `SPLIT_POINTING_ENABLE` y `POINTING_DEVICE_RIGHT` estén en config.h
- Verifica que ambos lados estén flasheados (el trackpad es esclavo: si la mitad derecha tiene firmware viejo, no manda nada)
- Verifica que el cable TRRS esté bien conectado — el reporte del trackpad viaja por ahí
- Revisa que el cable I2C del trackpad esté bien conectado

### Home Row Mods se activan por error:
- Aumenta TAPPING_TERM en config.h
- Ajusta tiempos específicos en get_tapping_term()

### OLED no cambia de bestia al cambiar de capa:
- Verifica que `SPLIT_LAYER_STATE_ENABLE` esté definido en `config.h`
- Si cambiaste `config.h`, haz `qmk clean -a` antes de compilar
- Asegúrate de flashear **ambos lados** del teclado
- Verifica que el switch en `oled_task_user()` use `layer_state` (no `get_highest_layer()`)

### OLED se ve distorsionado o incompleto:
- El array debe tener exactamente **512 bytes** (128×32 / 8)
- El formato debe ser **vertical SSD1306** (page addressing), no horizontal
- Usa `oled_write_raw_P(array, sizeof(array))`, no `oled_write()`

## 📚 Referencias

- **QMK Docs:** https://docs.qmk.fm/
- **QMK OLED Driver:** https://docs.qmk.fm/features/oled_driver
- **Cirque Pinnacle:** https://docs.qmk.fm/features/pointing_device
- **Tap Dance:** https://docs.qmk.fm/features/tap_dance
- **Home Row Mods:** https://precondition.github.io/home-row-mods

## 💡 Filosofía del Usuario

Miguel prefiere:
- Ergonomía sobre velocidad inicial (Home Row Mods, split keyboard)
- Soluciones nativas de QMK sobre dependencias externas
- Documentación completa y clara
- Workflow simple y reproducible

---

**Última actualización:** 2026-07-30

**Estado actual:** El cable USB se movió de la mitad derecha a la **izquierda** (`MASTER_LEFT`). El trackpad
sigue físicamente en la derecha, ahora esclava, y transmite por TRRS vía `SPLIT_POINTING_ENABLE` +
`POINTING_DEVICE_RIGHT`. Las 4 bestias divinas (白虎/青龍/朱雀/玄武) se muestran ahora en el OLED
**izquierdo** (master) y el nombre de la capa en el **derecho**; el keylogger quedó desactivado.
Trackpad con sensibilidad 2X. Firmware al 94% de flash.
