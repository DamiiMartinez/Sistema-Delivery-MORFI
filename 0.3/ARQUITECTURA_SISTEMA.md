# 🏗️ ARQUITECTURA DEL SISTEMA DE DELIVERY - ANÁLISIS INTEGRAL

**Versión**: 0.4  
**Última Actualización**: 2026-06-21  
**Estado**: En Desarrollo - Fase 2 (Gestión de Pedidos, Pagos, Menú)

---

## 📋 ÍNDICE DE CONTENIDOS

1. [Correlación de Usuarios](#correlación-de-usuarios)
2. [Flujo de Procesos](#flujo-de-procesos)
3. [Análisis de Deficiencias](#análisis-de-deficiencias)
4. [Plan de Implementación](#plan-de-implementación)
5. [Archivos y Estructuras](#archivos-y-estructuras)

---

## 1️⃣ CORRELACIÓN DE USUARIOS

### ROL: CLIENTE
**Acceso**: Basado en rol "Cliente" (id_usuario con registro en cliente.dat)

**Permisos**:
- ✅ Realizar pedidos (nuevo)
- ✅ Ver mis pedidos (nuevo)
- ✅ Ver historial de estados de mis pedidos (nuevo)
- ✅ Realizar pagos (nuevo)
- ✅ Ver recibos de pagos (nuevo)
- ✅ Realizar consultas/reclamos (no implementado aún)
- ✅ Ver mis datos de cuenta (no implementado)
- ✅ Eliminar mi cuenta (no implementado)

**Datos Requeridos**:
- `usuario.dat` - Autenticación
- `cliente.dat` - id_usuario + direccion
- `pedido.dat` (nuevo) - Pedidos del cliente
- `orden_preparacion.dat` (nuevo) - Estado de preparación
- `detalle_orden.dat` (nuevo) - Items del pedido
- `historial_estado.dat` (nuevo) - Timeline de estados
- `pago.dat` (nuevo) - Pagos realizados
- `transaccion.dat` (nuevo) - Detalles de transacciones

**Flujo Cliente**:
```
1. Cliente inicia sesión
2. Cliente selecciona restaurante (futuro - necesita menú)
3. Cliente selecciona productos
4. Cliente realiza pedido (NUEVO)
   ├─ Crear Pedido (pedido.dat)
   ├─ Crear Orden de Preparación (orden_preparacion.dat)
   └─ Crear Detalle de Orden (detalle_orden.dat)
5. Cliente realiza pago (NUEVO)
   ├─ Crear Pago (pago.dat)
   ├─ Crear Transacción (transaccion.dat)
   └─ Generar Recibo
6. Cliente ve mis pedidos
   └─ Lista pedidos de cliente actual
7. Cliente ve historial de estado (NUEVO)
   └─ Muestra timeline: Pendiente → Confirmado → Preparándose → En_Camino → Entregado
```

---

### ROL: ENCARGADO
**Acceso**: Basado en rol "Encargado" (id_usuario con registro en encargado.dat)  
**Restricción**: Solo puede acceder a su restaurante asignado (encargado.id_restaurante)

**Permisos**:
- ✅ Ver menú del restaurante (nuevo)
- ✅ Agregar platos/productos (nuevo)
- ✅ Modificar platos/productos (nuevo)
- ✅ Eliminar platos/productos (nuevo)
- ✅ Ver órdenes de preparación (nuevo)
- ✅ Actualizar estado de preparación (futuro)
- ✅ Ver datos de su turno (no implementado)
- ✅ Modificar sus datos (no implementado)

**Datos Requeridos**:
- `usuario.dat` - Autenticación
- `encargado.dat` - id_usuario + id_restaurante + turno
- `restaurante.dat` - Información del restaurante
- `producto.dat` (nuevo) - Platos del restaurante
- `menu.dat` (nuevo) - Menú del restaurante
- `categoria.dat` (nuevo) - Categorías de platos
- `orden_preparacion.dat` (nuevo) - Órdenes asignadas al restaurante
- `detalle_orden.dat` (nuevo) - Detalles de órdenes

**Validaciones**:
- Encargado solo ve platos de su restaurante
- Encargado solo ve órdenes de su restaurante
- No puede agregar platos si el restaurante está "inactivo"

**Flujo Encargado**:
```
1. Encargado inicia sesión
2. Sistema obtiene: id_usuario → busca en encargado.dat → obtiene id_restaurante
3. Encargado accede a "Gestionar Menú"
   ├─ Ver menú actual (filtrado por id_restaurante)
   ├─ Agregar plato (NUEVO)
   │  ├─ Nombre, descripción, precio, categoría
   │  └─ Guardar en producto.dat con id_restaurante
   ├─ Modificar plato (NUEVO)
   │  └─ Solo platos de su restaurante
   └─ Eliminar plato (NUEVO)
      └─ Cambiar disponibilidad a "inactivo"
4. Encargado ve "Órdenes Pendientes" (NUEVO)
   ├─ Filtrar orden_preparacion.dat por id_restaurante
   ├─ Mostrar estado: Pendiente → Confirmado → Preparándose
   └─ Actualizar estado (futuro)
5. Encargado modifica su turno (no implementado)
```

---

### ROL: REPARTIDOR
**Acceso**: Basado en rol "Repartidor" (id_usuario con registro en repartidor.dat)

**Permisos**:
- ✅ Ver entregas asignadas (futuro)
- ✅ Actualizar ubicación (futuro)
- ✅ Cambiar estado de disponibilidad (futuro)
- ✅ Ver mis datos (no implementado)

**Datos Requeridos**:
- `usuario.dat` - Autenticación
- `repartidor.dat` - id_usuario + vehiculo + estado_disponibilidad
- `pedido.dat` - Pedidos asignados (id_repartidor)

**Flujo Repartidor**:
```
1. Repartidor inicia sesión
2. Repartidor ve "Entregas Disponibles" (FUTURO)
   ├─ Filtrar pedido.dat por estado="En_Camino"
   ├─ Mostrar ubicación + destino
   └─ Aceptar entrega
3. Repartidor actualiza "He Llegado" (FUTURO)
   └─ Cambiar estado a "Entregado" en historial_estado.dat
```

---

### ROL: ADMINISTRADOR
**Acceso**: Basado en rol "Administrador" (id_usuario con registro en administrador.dat)

**Permisos**: ✅ IMPLEMENTADO
- ✅ Listar usuarios
- ✅ Listar restaurantes
- ✅ Agregar restaurante (con validación)
- ✅ Eliminar usuario (con confirmación)
- ✅ Eliminar restaurante (con confirmación)
- ✅ Ver finanzas (no implementado aún)
- ✅ Generar informes (no implementado)

**Datos Requeridos**:
- `usuario.dat` - Todos los usuarios
- `restaurante.dat` - Todos los restaurantes
- `cliente.dat`, `repartidor.dat`, `encargado.dat` - Roles para eliminar en cascada

**Flujo Administrador**: ✅ YA IMPLEMENTADO
```
1. Administrador inicia sesión
2. [1] Ver Cuentas → lista usuarios
3. [2] Ver Restaurantes → lista restaurantes
4. [3] Ver Finanzas (no implementado)
5. [4] Eliminar Usuario
   ├─ Pide ID
   ├─ Muestra datos
   ├─ Pide confirmación
   └─ Elimina de usuario.dat + todos sus roles
6. [5] Agregar Restaurante
   ├─ Validación de nombre (1-100 chars)
   ├─ Validación de teléfono (7-20 chars)
   ├─ Validación de horarios (HH:MM)
   ├─ Validación de estado (activo/inactivo/mantenimiento)
   └─ Guarda en restaurante.dat + ubicacion_restaurante.dat
7. [6] Eliminar Restaurante
   ├─ Pide ID
   ├─ Muestra datos
   ├─ Pide confirmación
   └─ Elimina de restaurante.dat
```

---

## 2️⃣ FLUJO DE PROCESOS

### FLUJO 1: CLIENTE REALIZA PEDIDO
```
┌─────────────────────────────────────────────────────────────────┐
│ 1. Cliente selecciona restaurante y productos (FUTURO)          │
│    └─ Necesita: Ver menú del restaurante                        │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 2. Cliente confirma pedido (NUEVO - IMPLEMENTAR)                │
│    Genera:                                                      │
│    ├─ Pedido (id_pedido, id_cliente, total, estado=Pendiente) │
│    ├─ OrdenPreparacion (id_orden, id_pedido, estado=Pendiente)│
│    └─ DetalleOrden (id_producto, cantidad para cada item)     │
│    Archivos: pedido.dat, orden_preparacion.dat, detalle_orden │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 3. Encargado ve orden (NUEVO - IMPLEMENTAR)                     │
│    └─ Actualiza estado: Pendiente → Confirmado → Preparándose  │
│    Archivo: orden_preparacion.dat                               │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 4. Pedido está listo (NUEVO - IMPLEMENTAR)                      │
│    └─ Estado: Preparándose → Listo                              │
│    Notifica a Repartidor disponible                             │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 5. Repartidor recoge pedido (FUTURO)                            │
│    └─ Estado: Listo → En_Camino                                │
│    Actualiza historial_estado.dat                               │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 6. Repartidor entrega (FUTURO)                                  │
│    └─ Estado: En_Camino → Entregado                            │
│    Actualiza historial_estado.dat                               │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 7. Cliente ve estado del pedido (NUEVO - IMPLEMENTAR)           │
│    └─ Lee historial_estado.dat filtrado por su id_cliente      │
└─────────────────────────────────────────────────────────────────┘
```

### FLUJO 2: CLIENTE REALIZA PAGO
```
┌─────────────────────────────────────────────────────────────────┐
│ 1. Cliente selecciona método de pago (NUEVO - IMPLEMENTAR)      │
│    Opciones: Efectivo, Tarjeta Débito, Tarjeta Crédito        │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 2. Sistema crea Pago (NUEVO - IMPLEMENTAR)                      │
│    ├─ id_pago (autoincrementado)                                │
│    ├─ id_pedido (vinculado al pedido)                          │
│    ├─ fecha_pago                                                │
│    ├─ monto_total (del pedido)                                 │
│    └─ estado_pago = "Pendiente"                                │
│    Archivo: pago.dat                                            │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 3. Sistema procesa método de pago (NUEVO - IMPLEMENTAR)         │
│    ├─ SI Efectivo → estado_pago = "Confirmado"                │
│    └─ SI Tarjeta → Crear Transacción                          │
│       ├─ id_transaccion                                         │
│       ├─ codigo_autorizacion (simulado)                        │
│       ├─ entidad_bancaria                                       │
│       ├─ fecha_transaccion                                      │
│       └─ estado_transaccion = "Autorizado"/"Rechazado"         │
│       Archivo: transaccion.dat                                  │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 4. Sistema genera Recibo (NUEVO - IMPLEMENTAR)                  │
│    ├─ id_recibo                                                 │
│    ├─ numero_comprobante (formato: AAAA-XXXXX)                │
│    ├─ tipo_comprobante = "Factura"/"Recibo"                   │
│    ├─ fecha_emision                                             │
│    └─ Mostrar al cliente                                        │
│    Archivo: recibo.dat                                          │
└─────────────────────────────────────────────────────────────────┘
```

### FLUJO 3: ENCARGADO GESTIONA MENÚ
```
┌─────────────────────────────────────────────────────────────────┐
│ 1. Encargado inicia sesión (YA EXISTE)                          │
│    └─ Sistema obtiene: id_restaurante desde encargado.dat       │
└─────────────────────────────────────────────────────────────────┘
                            ↓
┌─────────────────────────────────────────────────────────────────┐
│ 2. Encargado accede a "Gestionar Menú" (NUEVO - IMPLEMENTAR)    │
│    ├─ Ver menú actual                                           │
│    │  └─ Lista productos.dat donde id_restaurante = su resto   │
│    ├─ Agregar plato                                            │
│    │  ├─ Nombre (validar 1-100 chars)                          │
│    │  ├─ Descripción (max 500 chars)                           │
│    │  ├─ Precio (validar > 0)                                  │
│    │  ├─ Categoría (ver categorias.dat)                        │
│    │  └─ Disponibilidad = "disponible"                         │
│    ├─ Modificar plato                                          │
│    │  └─ Cambiar precio, descripción, disponibilidad           │
│    └─ Eliminar plato                                           │
│       └─ Cambiar disponibilidad a "inactivo" (no borrar físico)│
└─────────────────────────────────────────────────────────────────┘
```

---

## 3️⃣ ANÁLISIS DE DEFICIENCIAS

### ❌ QUÉ FALTA

| Sistema | Estado | Problema | Solución |
|---------|--------|----------|----------|
| **Menú/Productos** | ❌ NO IMPLEMENTADO | Clientes no ven qué pedir | Implementar: `agregarProducto()`, `listarProductos()`, `modificarProducto()` |
| **Pedidos** | ❌ NO IMPLEMENTADO | Clientes no pueden realizar pedidos | Implementar: `agregarPedido()`, `listarPedidosCliente()`, `obtenerDetallePedido()` |
| **Orden de Preparación** | ❌ NO IMPLEMENTADO | Encargado no puede preparar | Implementar: `agregarOrdenPreparacion()`, `actualizarEstadoOrden()` |
| **Detalles de Orden** | ❌ NO IMPLEMENTADO | No se sabe qué items tiene c/pedido | Implementar: `agregarDetalleOrden()`, `listarDetallesOrden()` |
| **Historial de Estado** | ❌ NO IMPLEMENTADO | Cliente no ve progreso | Implementar: `registrarCambioEstado()`, `obtenerHistorialEstados()` |
| **Pagos** | ❌ NO IMPLEMENTADO | No hay forma de cobrar | Implementar: `realizarPago()`, `registrarTransaccion()`, `generarRecibo()` |
| **Entregas (Repartidor)** | ⏳ FUTURO | Repartidor no tiene funcionalidad | Implementar en FASE 3 |
| **Informes** | ⏳ FUTURO | Admin no ve reportes | Implementar en FASE 3+ |

### ⚠️ DEPENDENCIAS FALTANTES

```
Cliente realiza Pedido
    ├─ Necesita: VER MENÚ DISPONIBLE
    │    └─ Necesita: agregarProducto() del Encargado
    └─ Genera: Pedido + OrdenPreparacion + DetalleOrden

Cliente realiza Pago
    ├─ Necesita: Pedido existente
    └─ Genera: Pago + Transacción + Recibo

Encargado gestiona Menú
    ├─ Necesita: Restaurante activo (YA EXISTE)
    └─ Genera: Productos

Encargado prepara Pedido
    ├─ Necesita: Orden pendiente (del Cliente)
    ├─ Actualiza: orden_preparacion.estado
    └─ Notifica: Cliente (ver historial)

Repartidor entrega
    ├─ Necesita: Pedido en estado "Listo"
    ├─ Actualiza: pedido.estado = "En_Camino" → "Entregado"
    └─ Notifica: Cliente (ver historial)
```

---

## 4️⃣ PLAN DE IMPLEMENTACIÓN

### FASE 2A: MENÚ Y PRODUCTOS (ENCARGADO) - PRIORIDAD 1️⃣
**Dependencia**: Encargado ya existe, solo le falta funcionalidad

**Archivos a crear/modificar**:
- `BBD.h` - ✅ Estructuras ya existen: `Menu`, `Producto`, `Categoria`
- `crud.c` - CREAR: `agregarProducto()`, `modificarProducto()`, `listarProductos()`, `eliminarProducto()`, `agregarCategoria()`, etc.
- `crud.h` - AGREGAR: Prototipos de funciones de producto
- `BBD.c` - MODIFICAR: `panelEncargador()` para agregar menú

**Funciones a implementar**:
```c
// Menú
void agregarProducto(int id_restaurante);
void modificarProducto(int id_restaurante);
void eliminarProducto(int id_restaurante);
void listarProductos(int id_restaurante);
void listarProductosDisponibles(int id_restaurante);

// Categorías
void agregarCategoria();
void listarCategorias();
```

### FASE 2B: PEDIDOS, ÓRDENES, DETALLES Y HISTORIAL (CLIENTE + ENCARGADO) - PRIORIDAD 2️⃣
**Dependencia**: Requiere menú disponible

**Archivos a crear/modificar**:
- `BBD.h` - ✅ Estructuras ya existen: `Pedido`, `OrdenPreparacion`, `DetalleOrden`, `HistorialEstado`
- `crud.c` - CREAR: `agregarPedido()`, `agregarOrdenPreparacion()`, etc.
- `BBD.c` - MODIFICAR: `panelCliente()` y `panelEncargador()`

**Funciones a implementar**:
```c
// Cliente
void agregarPedido(Usuario usuario);
void listarMisPedidos(Usuario usuario);
void obtenerDetallePedido(int id_pedido);
void obtenerHistorialPedido(int id_pedido);

// Encargado
void listarOrdenesRestaurante(Usuario usuario);
void actualizarEstadoOrden(int id_orden);

// Sistema
void registrarCambioEstado(int id_pedido, const char* nuevo_estado);
void obtenerHistorialEstados(int id_pedido);
```

### FASE 2C: PAGOS - PRIORIDAD 3️⃣
**Dependencia**: Requiere pedidos existentes

**Archivos a crear/modificar**:
- `BBD.h` - ✅ Estructuras ya existen: `Pago`, `Transaccion`, `Comision`, `Recibo`
- `crud.c` - CREAR: `realizarPago()`, `registrarTransaccion()`, `generarRecibo()`
- `BBD.c` - MODIFICAR: `panelCliente()`

**Funciones a implementar**:
```c
// Cliente
void realizarPago(Usuario usuario, int id_pedido);
void seleccionarMetodoPago();
void verMisRecibos(Usuario usuario);

// Sistema
void procesarPago(int id_pedido, char* metodo_pago);
void generarRecibo(int id_pago);
void registrarTransaccion(int id_pago);
```

---

## 5️⃣ ARCHIVOS Y ESTRUCTURAS

### ARCHIVOS BINARIOS EXISTENTES
```
✅ usuario.dat          → Usuario (id_usuario, nombre, apellido, email, etc)
✅ cliente.dat          → Cliente (id_usuario, direccion)
✅ repartidor.dat       → Repartidor (id_usuario, vehiculo, estado)
✅ encargado.dat        → Encargado (id_usuario, id_restaurante, turno)
✅ administrador.dat    → Administrador (id_usuario, nivel_acceso)
✅ restaurante.dat      → Restaurante (id_restaurante, nombre, telefono, etc)
✅ ubicacion_restaurante.dat → UbicacionRestaurante
✅ producto.dat         → Producto (id_producto, id_menu, nombre, etc)
✅ pedido.dat           → Pedido (id_pedido, id_cliente, id_repartidor, etc)
⏳ pago.dat             → Pago (id_pago, id_pedido, monto, estado) [NUEVO]
```

### ARCHIVOS BINARIOS A CREAR
```
📝 NUEVA: orden_preparacion.dat     → OrdenPreparacion
📝 NUEVA: detalle_orden.dat         → DetalleOrden
📝 NUEVA: historial_estado.dat      → HistorialEstado
📝 NUEVA: transaccion.dat           → Transaccion
📝 NUEVA: recibo.dat                → Recibo
📝 NUEVA: categoria.dat             → Categoria
📝 NUEVA: menu.dat                  → Menu
```

### ESTRUCTURAS EN BBD.h ✅ YA EXISTEN
```c
✅ Usuario, Cliente, Repartidor, Encargado, Administrador
✅ Restaurante, UbicacionRestaurante
✅ Menu, Producto, Categoria
✅ Pedido, OrdenPreparacion, DetalleOrden, HistorialEstado
✅ Pago, Transaccion, Comision, Recibo
✅ Calificacion, Reclamo, Consulta
✅ SolicitudInforme
```

---

## 📊 MATRIZ DE ACCESO POR ROL

| Función | Cliente | Encargado | Repartidor | Admin |
|---------|---------|-----------|-----------|-------|
| Realizar Pedido | ✅ NUEVO | ❌ | ❌ | ❌ |
| Ver mis Pedidos | ✅ NUEVO | ❌ | ❌ | ❌ |
| Ver Menú | ✅ FUTURO | ✅ NUEVO | ❌ | ❌ |
| Agregar Producto | ❌ | ✅ NUEVO | ❌ | ❌ |
| Modificar Producto | ❌ | ✅ NUEVO | ❌ | ❌ |
| Ver Órdenes Pendientes | ❌ | ✅ NUEVO | ❌ | ❌ |
| Actualizar Estado Orden | ❌ | ✅ NUEVO | ❌ | ❌ |
| Realizar Pago | ✅ NUEVO | ❌ | ❌ | ❌ |
| Ver Historial Estado | ✅ NUEVO | ❌ | ❌ | ❌ |
| Ver Entregas | ❌ | ❌ | ✅ FUTURO | ❌ |
| Entregar Pedido | ❌ | ❌ | ✅ FUTURO | ❌ |
| Listar Usuarios | ❌ | ❌ | ❌ | ✅ HECHO |
| Agregar Restaurante | ❌ | ❌ | ❌ | ✅ HECHO |
| Eliminar Restaurante | ❌ | ❌ | ❌ | ✅ HECHO |

---

## 🔗 REFERENCIAS Y CONTEXTO

**Documentos de Contexto**:
- `RESUMEN_FASE1.md` - Resumen de problemas resueltos en Fase 1
- `INDEX.md` - Índice de archivos del proyecto
- `COMPILACION_Y_TESTING.md` - Guía de compilación y pruebas
- `avances.md` - Registro de avances históricos

**Última Actualización de Contexto**: 2026-06-21
**Próxima Revisión**: Después de implementar Fase 2A (Menú/Productos)

---

**Fin de Análisis Arquitectónico**
