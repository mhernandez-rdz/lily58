#!/bin/bash
# Script de sincronización - Lily58 Keymap
# Copia la configuración desde QMK al repositorio

set -e  # Salir si hay error

KEYMAP_SOURCE="$HOME/qmk_firmware/keyboards/lily58/keymaps/miguel"
KEYMAP_DEST="$HOME/lily58/keymap"

echo "🔄 Sincronizando keymap desde QMK..."

# Verificar que existan los directorios
if [ ! -d "$KEYMAP_SOURCE" ]; then
    echo "❌ Error: No se encuentra el keymap en QMK: $KEYMAP_SOURCE"
    exit 1
fi

if [ ! -d "$KEYMAP_DEST" ]; then
    echo "⚠️  Creando directorio destino: $KEYMAP_DEST"
    mkdir -p "$KEYMAP_DEST"
fi

# Copiar archivos
echo "📁 Copiando archivos..."
cp -r "$KEYMAP_SOURCE"/* "$KEYMAP_DEST"/

echo "✅ Sincronización completada"
echo ""
echo "📝 Archivos sincronizados:"
ls -lh "$KEYMAP_DEST"

# Opcional: Hacer commit automático si está en un repo git
if [ -d "$HOME/lily58/.git" ]; then
    echo ""
    read -p "¿Hacer commit de los cambios? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        cd "$HOME/lily58"
        git add keymap/
        read -p "Mensaje del commit (Enter para usar fecha): " COMMIT_MSG
        if [ -z "$COMMIT_MSG" ]; then
            COMMIT_MSG="Sync keymap: $(date '+%Y-%m-%d %H:%M:%S')"
        fi
        git commit -m "$COMMIT_MSG"
        echo "✅ Commit realizado"
    fi
fi
