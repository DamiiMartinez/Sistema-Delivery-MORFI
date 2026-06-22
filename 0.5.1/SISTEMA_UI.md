# Sistema UI - Interfaz Visual Mejorada

## Descripción

Se ha creado un sistema de interfaz visual mejorado para que la consola de C se parezca más a una aplicación móvil moderna. Utiliza colores ANSI, bordes decorativos y símbolos Unicode para una mejor experiencia visual.

## Características

### 1. Colores ANSI
- **Textos:** Negro, Rojo, Verde, Amarillo, Azul, Magenta, Cian, Blanco, Gris
- **Fondos:** Negro, Rojo, Verde, Amarillo, Azul, Magenta, Cian, Blanco, Azul oscuro
- **Estilos:** Negrita, Atenuado, Reset

### 2. Símbolos Decorativos
```
╔═══════════════╗
║   TÍTULO      ║
╠═══════════════╣
║   CONTENIDO   ║
╚═══════════════╝
```

- Esquinas: `╔ ╗ ╚ ╝`
- Líneas horizontales: `═`
- Líneas verticales: `║`
- Intersecciones: `╠ ╣ ╤ ╥`

### 3. Indicadores
- Viñeta: `●`
- Flecha: `→`
- Checkmark: `✓`
- Error: `✗`

## Funciones Disponibles

### Inicialización
```c
void inicializarUI();
```
Configura la interfaz UI en Windows/Linux, habilita colores ANSI.

### Pantalla
```c
void limpiarPantalla();
```
Limpia la consola y prepara para nuevo contenido.

### Títulos
```c
void mostrarTitulo(const char *titulo);
void mostrarSubtitulo(const char *subtitulo);
```
Muestra títulos principales en cajas decoradas.

### Menús
```c
void mostrarOpcion(int numero, const char *texto);
void mostrarLinea();
```
Muestra opciones de menú con números en amarillo.

### Mensajes
```c
void mostrarError(const char *mensaje);
void mostrarExito(const char *mensaje);
void mostrarInfo(const char *mensaje);
```
Muestra mensajes con colores apropiados (rojo para error, verde para éxito, etc.).

### Cajas
```c
void mostrarCaja(const char *titulo);
void mostrarCajaFin();
```
Crea cajas decorativas para secciones.

### Entrada
```c
void mostrarInput(const char *prompt);
void pausar();
```
Solicita entrada con prompts formateados y pausas.

## Paleta de Colores

### Texto
- **Blanco (`WHITE`)**: Texto principal
- **Gris (`GRAY`)**: Texto secundario/dimmed
- **Amarillo (`YELLOW`)**: Números de opción
- **Cian (`CYAN`)**: Bordes decorativos
- **Verde (`GREEN`)**: Mensajes de éxito
- **Rojo (`RED`)**: Mensajes de error

### Fondo
- **Azul oscuro (`BG_DARK_BLUE`)**: Fondo de consola (ambiente general)

## Ejemplo de Uso

### Antes
```
===============================

    ¿QUÉ APP DESEAS ABRIR?

===============================

[1] Morfi - Cliente
[2] Morfi - Riders
[3] Morfi - Gestión
[4] Morfi - Admin
[5] Salir

Opción:
```

### Después
```
╔══════════════════════════════════════════════════════════════════════╗
║         MORFI - SISTEMA DE DELIVERY                                 ║
╠══════════════════════════════════════════════════════════════════════╣
║ ¿Qué aplicación deseas abrir?                                        ║
║ ────────────────────────────────────────────────────────────────────
║   [1] Morfi - Cliente
║   [2] Morfi - Riders (Repartidor)
║   [3] Morfi - Gestión (Encargado)
║   [4] Morfi - Admin
║   [5] Salir del Sistema
╚══════════════════════════════════════════════════════════════════════╝

║  Selecciona una opción: 
```

## Integración

### Archivos Incluidos
- `ui.h` - Definiciones de colores y funciones
- `ui.c` - Implementación de funciones UI

### Modificaciones a Archivos Existentes
- `main.c` - Incluye `ui.h` y usa funciones UI
- `BBD.c` - Incluye `ui.h` y actualiza paneles (Cliente, Repartidor, Encargado, Admin)

### Compilación
Asegúrate de compilar juntos:
```bash
gcc -o programa main.c BBD.c crud.c validaciones.c filemanager.c informes.c ui.c -Wall
```

## Soporte de Plataformas

### Windows 10+
- Requiere Windows 10 Build 16257 o superior
- Colores ANSI habilitados automáticamente
- Ajusta tamaño de consola a 80x30

### Linux/MacOS
- Colores ANSI nativos
- Terminal con soporte UTF-8

## Notas Técnicas

1. **Códigos ANSI**: Se utilizan códigos de escape ANSI estándar
2. **Windows**: Se habilita `ENABLE_VIRTUAL_TERMINAL_PROCESSING` automáticamente
3. **Unicode**: Se requiere terminal con soporte UTF-8 para símbolos decorativos
4. **Compatibilidad**: Backwards-compatible, puede funcionar sin colores en terminales antiguas

## Futuras Mejoras

- [ ] Animaciones de transición
- [ ] Barras de progreso
- [ ] Gráficos ASCII
- [ ] Modo oscuro/claro configurable
- [ ] Temas personalizables

---

**Fecha de Implementación:** 22/06/2026  
**Estado:** ✅ COMPLETADO Y INTEGRADO
