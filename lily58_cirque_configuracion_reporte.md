# Reporte de Configuración - Lily58 con Cirque Trackpad

## 🔍 CONFIGURACIÓN ACTUAL VS DEFAULTS (CON EXPLICACIONES)

### **CONFIGURADO EXPLÍCITAMENTE (en tu config.h)**

---

✅ **`CIRQUE_PINNACLE_ADDR = 0x2A`**
- **Tu valor:** `0x2A`
- **Default QMK:** `0x2A`
- **Status:** Mismo que default
- **¿Qué hace?** Define la dirección I2C del trackpad en el bus de comunicación. Es como una "dirección postal" para que el teclado encuentre el trackpad. El valor 0x2A es estándar para Cirque Pinnacle.
- **¿Cuándo cambiarlo?** Solo si tienes múltiples dispositivos I2C con la misma dirección o si tu hardware usa una dirección diferente (raro).

---

✅ **`CIRQUE_PINNACLE_POSITION_MODE = CIRQUE_PINNACLE_ABSOLUTE_MODE`**
- **Tu valor:** `ABSOLUTE_MODE`
- **Default QMK:** `RELATIVE_MODE`
- **Status:** ✨ MODIFICADO - Modo absoluto activo
- **¿Qué hace?**
  - **ABSOLUTE_MODE:** El trackpad reporta la posición exacta de tu dedo (coordenadas X, Y fijas). Como tocar una pantalla táctil - el cursor va exactamente donde tocas. Mejor para gestos táctiles y scroll circular.
  - **RELATIVE_MODE:** El trackpad reporta cuánto se movió tu dedo (deltas). Como un mouse tradicional - el cursor se mueve relativamente desde donde estaba. Mejor para precisión tipo mouse.
- **¿Por qué lo cambiaste?** Para habilitar scroll circular y gestos táctiles avanzados.

---

✅ **`CIRQUE_PINNACLE_DIAMETER_MM = 40`**
- **Tu valor:** `40mm`
- **Default QMK:** `40mm`
- **Status:** Mismo que default
- **¿Qué hace?** Le dice al firmware el tamaño físico del trackpad circular. Esto es crucial para calcular correctamente:
  - La zona del borde para scroll circular
  - La sensibilidad del movimiento
  - La calibración de coordenadas
- **Valores comunes:** 35mm o 40mm (los dos tamaños estándar de Cirque)
- **¿Cuándo cambiarlo?** Si tienes un trackpad de 35mm, debes poner 35. Si está mal configurado, el scroll no funcionará correctamente porque el firmware calcula mal dónde está el "borde exterior".

---

✅ **`CIRQUE_PINNACLE_TAP_ENABLE`**
- **Tu valor:** Habilitado
- **Default QMK:** Deshabilitado
- **Status:** ✨ ACTIVADO - Tap to click funciona
- **¿Qué hace?** Permite hacer clic tocando el trackpad en lugar de presionarlo físicamente. Es la detección de "tap" que hace el hardware del Cirque.
  - Toque rápido = clic izquierdo
  - Dos toques rápidos + mantener = arrastrar (drag)
- **¿Por qué activarlo?** Más ergonómico y rápido que presionar. Es como los trackpads de laptops modernos.

---

✅ **`POINTING_DEVICE_GESTURES_SCROLL_ENABLE`**
- **Tu valor:** Habilitado
- **Default QMK:** Deshabilitado
- **Status:** ✨ ACTIVADO - Scroll circular disponible
- **¿Qué hace?** Habilita detección de gestos de scroll en modo absoluto:
  - **Scroll circular:** Mover el dedo en círculos alrededor del borde exterior del trackpad hace scroll
  - **Lado cercano:** Scroll vertical (arriba/abajo)
  - **Lado lejano:** Scroll horizontal (izquierda/derecha)
- **¿Por qué activarlo?** Permite hacer scroll sin necesidad de usar teclas o rueda de mouse. Muy útil para documentos largos, páginas web, etc.

---

✅ **`POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE`**
- **Tu valor:** Habilitado
- **Default QMK:** Deshabilitado
- **Status:** ✨ ACTIVADO - Cursor con inercia
- **¿Qué hace?** Añade física de inercia al cursor:
  - Si mueves el dedo rápido y lo levantas, el cursor continúa moviéndose un poco antes de detenerse (como si tuviera momentum)
  - La velocidad de desaceleración es configurable
- **¿Por qué activarlo?** Hace que el cursor se sienta más natural y fluido, como deslizar en una pantalla táctil. También reduce la necesidad de mover grandes distancias con el dedo.
- **¿Cuándo desactivarlo?** Si prefieres control preciso absoluto sin movimiento extra.

---

### **SIN CONFIGURAR (usando defaults de QMK)**

---

❌ **`CIRQUE_PINNACLE_ATTENUATION`**
- **Default QMK:** `EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_4X`
- **Status:** Sensibilidad estándar (menor sensibilidad)
- **¿Qué hace?** Controla la sensibilidad del sensor capacitivo del trackpad. Atenuación = cuánto reduce la señal analógica.
  - **1X:** Máxima sensibilidad - Detecta toques muy ligeros, pero puede ser errático
  - **2X:** Alta sensibilidad - Recomendado para overlays gruesos o curvos
  - **3X:** Media sensibilidad
  - **4X (DEFAULT):** Baja sensibilidad - Requiere más presión, mejor para overlays planos/delgados, menos falsos positivos
- **¿Cuándo cambiarlo?**
  - Si el trackpad no detecta bien tus toques → Bajar a 2X o 1X
  - Si detecta toques fantasma o es muy sensible → Mantener en 4X o subir a 3X
  - Si tienes overlay curvo → Usar 2X

---

❌ **`POINTING_DEVICE_ROTATION_XX`**
- **Default QMK:** Sin rotación (0°)
- **Status:** Sin rotación
- **¿Qué hace?** Rota virtualmente el trackpad:
  - **90°:** Lo que era derecha ahora es arriba, arriba es izquierda, etc.
  - **180°:** Invierte completamente (arriba↔abajo, izquierda↔derecha)
  - **270°:** Rotación anti-horario de 90°
- **¿Por qué usarlo?**
  - Si el trackpad está instalado físicamente rotado
  - Si el scroll funciona en dirección incorrecta (como tu caso - scroll horizontal en lugar de vertical)
  - Para adaptar la orientación del trackpad a cómo naturalmente mueves el dedo
- **Tu problema:** Probablemente necesitas 90° o 270° para que el scroll funcione verticalmente.

---

❌ **`POINTING_DEVICE_INVERT_X/Y`**
- **Default QMK:** Sin inversión
- **Status:** Ejes normales
- **¿Qué hace?**
  - **INVERT_X:** Invierte solo eje horizontal (izquierda↔derecha)
  - **INVERT_Y:** Invierte solo eje vertical (arriba↔abajo)
- **¿Por qué usarlo?**
  - Si el cursor se mueve en dirección opuesta a tu dedo
  - Combinado con rotación para ajuste fino de orientación
  - Si el trackpad está montado al revés
- **Diferencia vs rotación:** Inversión solo voltea un eje, rotación cambia ambos ejes simultáneamente.

---

❌ **`CIRQUE_PINNACLE_SECONDARY_TAP_ENABLE`**
- **Default QMK:** Deshabilitado
- **Status:** ❌ NO DISPONIBLE - Clic derecho por tap no funciona
- **¿Qué hace?** Habilita detección de clic derecho mediante tap en una zona específica:
  - En modo relativo: Tap en esquina superior derecha = clic derecho
  - Requiere `CIRQUE_PINNACLE_TAP_ENABLE` activado primero
- **¿Por qué activarlo?** Para tener clic derecho sin necesidad de asignar una tecla del teclado para esa función.
- **Limitaciones:** Solo funciona bien en modo RELATIVE. En modo ABSOLUTE (el que tienes) es menos confiable.

---

❌ **`CIRQUE_PINNACLE_SIDE_SCROLL_ENABLE`**
- **Default QMK:** Deshabilitado
- **Status:** ❌ NO DISPONIBLE
- **¿Qué hace?** Habilita scroll lateral (horizontal) detectando deslizamiento en el lado derecho del trackpad:
  - Mover dedo verticalmente en el lado derecho = scroll horizontal
  - Estilo trackpad IntelliSense
- **¿Por qué usarlo?** Si prefieres scroll tradicional tipo IntelliSense en lugar de circular.
- **Nota:** Probablemente funciona mejor en modo RELATIVE.

---

❌ **`CIRQUE_PINNACLE_CURVED_OVERLAY`**
- **Default QMK:** Deshabilitado
- **Status:** Optimizado para overlay plano
- **¿Qué hace?** Optimiza el trackpad para overlays curvos (como burbujas protectoras):
  - Ajusta sensibilidad en los bordes (donde el overlay es más grueso)
  - Automáticamente cambia atenuación a 2X
  - Mejora detección en toda la superficie curva
- **¿Cuándo activarlo?** Si tu trackpad tiene un overlay curvo o burbuja protectora encima.
- **¿Qué es overlay?** La cubierta protectora encima del sensor táctil (puede ser plana o curva).

---

❌ **`POINTING_DEVICE_TASK_THROTTLE_MS`**
- **Default QMK:** `10ms` (100Hz)
- **Status:** Actualización a 100Hz
- **¿Qué hace?** Controla cada cuánto tiempo el firmware lee datos del trackpad:
  - 10ms = 100 veces por segundo (100Hz)
  - Valor más bajo = cursor más responsive pero más uso de CPU
  - Valor más alto = menos CPU pero cursor puede sentirse "laggoso"
- **¿Cuándo cambiarlo?**
  - Si el cursor se siente lento o retrasado → Bajar a 5ms
  - Si quieres ahorrar batería (teclados wireless) → Subir a 20ms
- **Límite del hardware:** Cirque Pinnacle soporta máximo 100Hz, así que valores menores a 10ms no mejoran nada.

---

❌ **`POINTING_DEVICE_AUTO_MOUSE_ENABLE`**
- **Default QMK:** Deshabilitado
- **Status:** ❌ NO DISPONIBLE
- **¿Qué hace?** Automáticamente cambia a una "capa de mouse" cuando detecta que tocas el trackpad:
  - Teclado normal cuando no tocas el trackpad
  - Al tocar trackpad → activa capa con botones de clic, scroll, etc.
  - Al soltar → vuelve a capa normal
- **¿Por qué usarlo?** Puedes tener teclas que normalmente son letras, pero se convierten en botones de mouse cuando usas el trackpad.
- **Ejemplo:** La tecla "J" normalmente escribe "j", pero mientras usas trackpad se convierte en "clic izquierdo".

---

❌ **`CIRQUE_PINNACLE_REACHABLE_CALIBRATION`**
- **Default QMK:** Deshabilitado
- **Status:** Sin calibración dinámica
- **¿Qué hace?** Habilita calibración en tiempo real del trackpad:
  - El firmware aprende el rango real de coordenadas que tu trackpad puede alcanzar
  - Muestra información de debug en consola
  - Útil para diagnosticar problemas
- **¿Cuándo activarlo?**
  - Si el cursor no llega a las esquinas de la pantalla
  - Si el trackpad parece tener "zonas muertas"
  - Para debugging y diagnóstico

---

❌ **Calibración manual de coordenadas:**
```c
CIRQUE_PINNACLE_X_LOWER (default: 127)
CIRQUE_PINNACLE_X_UPPER (default: 1919)
CIRQUE_PINNACLE_Y_LOWER (default: 63)
CIRQUE_PINNACLE_Y_UPPER (default: 1471)
```
- **¿Qué hacen?** Definen el rango de coordenadas que el trackpad puede reportar:
  - LOWER = coordenada mínima (cuando tocas en el borde extremo)
  - UPPER = coordenada máxima (borde opuesto)
- **¿Por qué ajustarlos?**
  - Si el cursor no llega a ciertas áreas de la pantalla
  - Si hay zonas del trackpad que no responden
  - Para mapear perfectamente el trackpad al tamaño de tu pantalla
- **¿Cómo saber los valores correctos?** Usa `CIRQUE_PINNACLE_REACHABLE_CALIBRATION` para que el firmware los descubra automáticamente.

---

❌ **`CIRQUE_PINNACLE_SKIP_SENSOR_CHECK`**
- **Default QMK:** Deshabilitado (sí hace verificación)
- **Status:** Verifica sensor al iniciar
- **¿Qué hace?** Al iniciar el teclado, el firmware verifica que el trackpad esté conectado y respondiendo.
- **¿Por qué deshabilitarlo?**
  - Si el teclado tarda mucho en iniciar
  - Si tienes problemas de conexión intermitente del trackpad
  - Para debugging
- **Riesgo:** Si el trackpad no está conectado correctamente, el teclado puede congelarse intentando comunicarse con él.

---

## 📊 RESUMEN VISUAL DE FUNCIONALIDADES

### ✅ **ACTIVAS Y FUNCIONANDO:**
| Feature | Qué hace | Cómo lo usas |
|---------|----------|--------------|
| **Modo Absoluto** | Posición exacta del dedo | Mueves dedo = cursor va a esa posición |
| **Tap to Click** | Clic sin presionar | Toca rápido = clic izquierdo |
| **Cursor Glide** | Inercia del cursor | Desliza rápido = cursor continúa moviéndose |
| **Scroll Circular** | Scroll con gestos | Círculos en borde = scroll (⚠️ solo horizontal) |

### 🔲 **DISPONIBLES PERO DESACTIVADAS:**
| Feature | Qué haría | Por qué activarla |
|---------|-----------|-------------------|
| **Secondary Tap** | Clic derecho por tap | Clic derecho sin teclas |
| **Side Scroll** | Scroll IntelliSense | Scroll tradicional lateral |
| **Auto Mouse Layer** | Capa automática al tocar | Teclas cambian con trackpad |
| **Curved Overlay** | Optimización para overlay curvo | Si tienes burbuja protectora |
| **Atenuación 2X** | Más sensibilidad | Si no detecta bien los toques |

### ⚙️ **PARÁMETROS AJUSTABLES:**
| Parámetro | Default | Qué controla |
|-----------|---------|--------------|
| **Attenuation** | 4X | Sensibilidad del sensor |
| **Rotation** | 0° | Orientación del trackpad |
| **Invert X/Y** | No | Inversión de ejes |
| **Throttle** | 10ms | Velocidad de actualización |
| **Diameter** | 40mm | Tamaño del trackpad |

---

## 🎯 DIAGNÓSTICO DE TU PROBLEMA DE SCROLL

**Síntoma:** Scroll solo funciona horizontal, no vertical

**Causa probable:** Los ejes están rotados 90° respecto a la orientación esperada por el firmware.

**Soluciones posibles:**
1. Agregar `POINTING_DEVICE_ROTATION_90` o `POINTING_DEVICE_ROTATION_270`
2. Verificar que el diámetro sea correcto (35mm vs 40mm)
3. Probar con inversión de ejes `POINTING_DEVICE_INVERT_X` y/o `POINTING_DEVICE_INVERT_Y`

---

## 📁 UBICACIÓN DE ARCHIVOS DE CONFIGURACIÓN

- **Keymap:** `~/qmk_firmware/keyboards/lily58/keymaps/miguel/keymap.c`
- **Config:** `~/qmk_firmware/keyboards/lily58/keymaps/miguel/config.h`
- **Rules:** `~/qmk_firmware/keyboards/lily58/keymaps/miguel/rules.mk`

---

## 🔧 CONFIGURACIÓN ACTUAL COMPLETA

### En `config.h`:
```c
// Cirque Trackpad Configuration
#define CIRQUE_PINNACLE_ADDR 0x2A
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
// #define POINTING_DEVICE_ROTATION_90      // ← COMENTADO (sin rotación)
// #define POINTING_DEVICE_INVERT_X         // ← COMENTADO (sin inversión)
// #define POINTING_DEVICE_INVERT_Y         // ← COMENTADO (sin inversión)
```

### En `rules.mk`:
```make
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = cirque_pinnacle_i2c
TAP_DANCE_ENABLE = yes
EXTRAKEY_ENABLE = yes
```

---

## 📝 NOTAS ADICIONALES

### Funcionalidades del Teclado Lily58 (no trackpad):
- ✅ Space y Enter intercambiados
- ✅ Caps Lock con doble tap en Shift
- ✅ Triple tap en vocales para acentos españoles (aaa=á, eee=é, etc.)
- ✅ Teclas multimedia en LOWER layer
- ✅ Compose Key en Ctrl derecho

### Próximos pasos sugeridos:
1. Probar rotación de 90° para arreglar scroll vertical
2. Experimentar con sensibilidad (atenuación)
3. Considerar activar Auto Mouse Layer para integración teclado-trackpad
4. Probar diferentes configuraciones de scroll

---

*Documento generado: 2026-04-16*
*Configuración QMK: lily58/rev1/miguel*
