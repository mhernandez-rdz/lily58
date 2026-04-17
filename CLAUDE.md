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
- **Master side:** Derecho (trackpad está en el lado derecho)
- **Conexión:** TRRS cable entre ambos lados

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
   - TAPPING_TERM: 200ms base (Shift: 250ms, GUI: 230ms)
   - PERMISSIVE_HOLD habilitado

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
- Código OLED

**Líneas importantes:**
- Línea 11-18: Enum de Tap Dance (solo vocales y ñ, NO hay TD_LSHIFT_CAPS)
- Línea 95-102: Definiciones de Tap Dance
- Línea 121-127: QWERTY layer con Home Row Mods
- Línea 195-228: Funciones de timing para Home Row Mods

### config.h
- Configuración de Home Row Mods (líneas 23-28)
- Configuración del trackpad Cirque (líneas 48-58)
- MASTER_RIGHT (línea 46)
- RGB lighting (líneas 30-45)

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

## 🔍 Debugging

### El teclado no responde:
- Verifica cable TRRS conectado
- Verifica que ambos lados estén flasheados
- Reconecta USB

### Cambios no se aplican:
- `qmk clean -a` y recompila
- Verifica que flasheaste el lado correcto (trackpad = derecho = master)

### Trackpad no funciona:
- Verifica MASTER_RIGHT en config.h
- Verifica que ambos lados estén flasheados
- Revisa que el cable I2C del trackpad esté bien conectado

### Home Row Mods se activan por error:
- Aumenta TAPPING_TERM en config.h
- Ajusta tiempos específicos en get_tapping_term()

## 📚 Referencias

- **QMK Docs:** https://docs.qmk.fm/
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

**Última actualización:** 2026-04-17

**Estado actual:** Configuración estable. Usuario está probando sensibilidad 2X del trackpad durante varios días para evaluar detección de scroll.
