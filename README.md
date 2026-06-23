# MORFI — Sistema de Gestión de Delivery

Proyecto intercátedra desarrollado en lenguaje C para la materia Programación I de la Universidad Atlántida Argentina. El sistema simula la gestión operativa de una plataforma de delivery, integrando los contenidos de Programación I, Base de Datos I e Ingeniería de Software I.

---

## Integrantes — Grupo N° 2

- Damian Martinez
- Elian Rosito Sosa
- Nahuel Gonzalez

---

## Descripción

MORFI permite que cuatro tipos de usuarios interactúen con el sistema a través de menús propios:

- **Cliente** — realiza pedidos, efectúa pagos, consulta su historial y califica restaurantes
- **Repartidor** — visualiza los pedidos disponibles y acepta entregas
- **Encargado** — gestiona el menú del restaurante y actualiza el estado de las órdenes
- **Administrador** — gestiona usuarios, restaurantes y genera reportes

Toda la información se persiste en archivos binarios de registros de longitud fija (.dat), que representan las tablas del modelo relacional diseñado en Base de Datos I.

---

## Estructura del proyecto

```
0.5.1/
├── main.c                          # Menú principal y flujo del programa
├── BBD.h / BBD.c                   # Estructuras de datos y paneles por rol
├── crud.h / crud.c                 # Altas, bajas, modificaciones y consultas
├── filemanager.h / filemanager.c   # Manejo genérico de archivos
├── informes.h / informes.c         # Generación de reportes en texto
├── validaciones.h / validaciones.c # Validaciones de entrada de datos
├── ui.h / ui.c                     # Interfaz visual (colores ANSI, menús)
└── *.dat                           # Archivos binarios de datos
```

---

## Requisitos

- Sistema operativo: Windows
- IDE: [Code::Blocks](https://www.codeblocks.org/) con compilador MinGW (GCC)
- No requiere librerías externas

---

## Compilación y ejecución

### Con Code::Blocks

1. Clonar o descargar el repositorio
2. Abrir el archivo TP-Integrador.cbp ubicado dentro de la carpeta 0.5.1/
3. Compilar con Build > Build* (F9)
4. Ejecutar con Build > Run (Ctrl+F10)

El programa debe ejecutarse desde dentro de la carpeta 0.5.1/ para que los archivos .dat se lean y generen correctamente.

### Con gcc desde la terminal

Desde la carpeta 0.5.1/:


gcc main.c BBD.c crud.c filemanager.c informes.c validaciones.c ui.c -o morfi.exe
morfi.exe


---

## Archivos de datos

Al ejecutar el sistema por primera vez se crean automáticamente todos los archivos .dat necesarios. La carpeta 0.5.1/ ya incluye archivos de ejemplo con al menos 3 registros por tabla para facilitar las pruebas.

| Archivo | Contenido |
|---------|-----------|
| `usuario.dat` | Usuarios registrados |
| `cliente.dat` | Datos de clientes |
| `repartidor.dat` | Datos de repartidores |
| `encargado.dat` | Datos de encargados |
| `administrador.dat` | Datos de administradores |
| `restaurante.dat` | Restaurantes del sistema |
| `ubicacion_restaurante.dat` | Ubicaciones de restaurantes |
| `producto.dat` | Productos del menú |
| `pedido.dat` | Pedidos realizados |
| `orden_preparacion.dat` | Órdenes de preparación |
| `detalle_orden.dat` | Detalle de productos por orden |
| `historial_estado.dat` | Historial de estados de pedidos |
| `calificacion.dat` | Calificaciones de clientes |
| `pago.dat` | Pagos registrados |
| `comision.dat` | Comisiones calculadas |

---

## Informes generados

El sistema genera los siguientes reportes en archivos de texto plano:

| Reporte | Archivo de salida | Descripción |
|---------|------------------|-------------|
| Restaurantes top | `restaurantes_top.txt` | Restaurantes con calificación promedio mayor a 4.0 |
| Pedidos por usuario | `reporte_pedidos_usuario.txt` | Historial de pedidos de un usuario específico |
| Top 5 platos | `top_platos.txt` | Los 5 productos más pedidos del sistema |
| Factura | `factura_pedido.txt` | Detalle y total de un pedido |

---

## Información académica

| | |
|-|-|
| Universidad | Universidad Atlántida Argentina |
| Facultad | Ingeniería |
| Materia | Programación I |
| Año | 2026 |
| Profesores | David A. Fernández, Mauro E. Pavesse |
