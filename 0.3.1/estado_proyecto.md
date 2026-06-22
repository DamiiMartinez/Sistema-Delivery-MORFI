# Estado del Proyecto - TP Integrador (v0.2)

## 📋 Descripción General
Sistema de gestión de pedidos de comida tipo Delivery (similar a Uber Eats/Rappi). Aplicación desarrollada en C con persistencia en archivos binarios.

---

## ✅ Estado Actual - Lo que Está Hecho

### Completado:
- ✅ **Sistema de Autenticación**: Login y registro de usuarios
- ✅ **Asignación de Roles**: 5 tipos de usuarios (Cliente, Repartidor, Encargado, Administrador)
- ✅ **Archivos Binarios**: Estructuras de BD (.dat) y función para activarlas
- ✅ **Paneles de Usuarios**: Menús base para cada tipo de usuario
- ✅ **Definición de Estructuras**: Usuarios, Restaurantes, Platos, Pedidos, etc. (BBD.h)

---

## ⚠️ Advertencias y Defectos Conocidos

### ✅ CORREGIDOS EN FASE 1:
- ✅ Teléfonos no se guardan: SOLUCIONADO (cambio scanf %d → %s)
- ✅ Bug de Roles Múltiples: MEJORADO (validaciones en registro, mejor lógica en login)
- ✅ Falta validación de entrada: COMPLETADO (creado módulo validaciones.h/c)

### Estado de Defectos:
1. **Teléfonos no se guardan** (salen basura) 
   - **Estado**: ✅ CORREGIDO
   - **Causa**: scanf("%d") en campo char[20]
   - **Solución**: scanf("%s") + validación
   
2. **Bug de Roles Múltiples** (usuarios con múltiples roles)
   - **Estado**: ✅ MEJORADO
   - **Causa**: Cada función generaba ID independiente
   - **Solución**: Validaciones en agregarUsuario(), mejor lógica en seleccionarCuenta()
   
3. **Falta validación de entrada** (acepta cualquier dato)
   - **Estado**: ✅ SOLUCIONADO
   - **Solución**: Módulo validaciones.h/c con 7 funciones

### ⏳ Limitaciones Técnicas Restantes:
- Código tiene estructura confusa con muchas funciones/estructuras repetidas (mejorar en refactoring futuro)
- Orden de funciones es desorganizado (mejorar en refactoring futuro)

---

## 📌 Plan de Acción - Orden de Prioridad

### FASE 1: Correcciones y Ajustes (URGENTE)
**Duración estimada: 1-2 días**

1. **Revisar y Corregir Bug de Teléfonos**
   - Ubicación: `crud.c` - función `agregarUsuario()`
   - Verificar lectura/escritura en archivo binario
   - Testear con datos válidos

2. **Resolver Bug de Roles Múltiples**
   - Ubicación: `crud.c` - función `seleccionarCuenta()`
   - Asegurar que un usuario tenga SOLO UN rol
   - Añadir validación antes de guardar

3. **Validación de Entrada de Datos** (IMPORTANTE)
   - Crear función `validarEmail()`
   - Crear función `validarTelefono()`
   - Crear función `validarContrasena()`
   - Crear función `convertirEspaciosAGuiones()`
   - Aplicar a todas las funciones de ingreso

## 📌 Plan de Acción - Orden de Prioridad

### FASE 1: Correcciones y Ajustes (URGENTE)
**Duración estimada: 1-2 días**  
**Estado**: ✅ IMPLEMENTACIÓN COMPLETADA - Pendiente Testing

1. ✅ **Revisar y Corregir Bug de Teléfonos** - HECHO
   - Cambio: scanf("%d") → scanf("%s") en agregarUsuario()
   - Agregada: validarTelefono() con validación completa
   
2. ✅ **Resolver Bug de Roles Múltiples** - MEJORADO
   - Agregadas validaciones estrictas en agregarUsuario()
   - Mejorada función seleccionarCuenta() con mejor manejo de errores

3. ✅ **Validación de Entrada de Datos** - COMPLETADA
   - Creado: validaciones.h/c (7 funciones)
   - Integrado: validarEmail(), validarTelefono(), validarContrasena(), validarNombre()
   - Aplicado: loops de reintento en agregarUsuario()

**Archivos Modificados/Creados**:
- ✨ Creado: `validaciones.h` - Header con 7 funciones
- ✨ Creado: `validaciones.c` - Implementación
- 📝 Modificado: `crud.h` - Agregado include validaciones.h
- 📝 Modificado: `crud.c` - Reescrita agregarUsuario(), mejorada seleccionarCuenta()

**Próximo**: Ejecutar pruebas (Ver `COMPILACION_Y_TESTING.md`)

---
**Duración estimada: 3-4 días**

4. **Ingreso de Pedidos**
   - Crear estructura `Pedido` (si no existe)
   - Función: `agregarPedido()` - para Cliente
   - Función: `listarMisPedidos()` - para Cliente
   - Función: `eliminarPedido()` - para Cliente (solo sin confirmar)
   - Archivo: `pedidos.dat`

5. **Detalle de Pedidos**
   - Crear estructura `DetallePedido` 
   - Función: `agregarDetallePedido()`
   - Función: `modificarDetallePedido()`
   - Función: `listarDetallesPedido()`
   - Archivo: `detalles_pedido.dat`

6. **Historial de Estados de Pedidos**
   - Crear estructura `EstadoPedido`
   - Estados: Pendiente → Confirmado → Preparándose → En Camino → Entregado
   - Función: `registrarCambioEstado()`
   - Función: `obtenerHistorialEstados()`
   - Archivo: `estados_pedido.dat`

### FASE 3: Sistema de Pagos
**Duración estimada: 2 días**

7. **Gestión de Pagos**
   - Crear estructura `Pago`
   - Métodos de pago: Efectivo, Tarjeta (débito/crédito), Billetera Digital
   - Función: `realizarPago()`
   - Función: `registrarTransaccion()`
   - Función: `obtenerRecibo()`
   - Archivo: `pagos.dat`

### FASE 4: Menú y Productos
**Duración estimada: 2-3 días**

8. **Crear Panel de Encargado**
   - Acceso: Solo usuarios con rol `Encargado`
   - Menú: Gestionar productos, ver pedidos asignados

9. **Gestión de Menú**
   - Crear estructura `Plato` (si no existe)
   - Función: `agregarPlato()` - para Encargado
   - Función: `modificarPlato()` - para Encargado
   - Función: `eliminarPlato()` - para Encargado
   - Función: `listarMenu()` - para todos
   - Archivo: `platos.dat`

10. **Gestión de Productos/Categorías**
    - Crear estructura `Categoria`
    - Función: `agregarCategoria()`
    - Función: `listarCategorias()`
    - Archivo: `categorias.dat`

### FASE 5: Informes y Reportes
**Duración estimada: 2 días**

11. **Informes del PDF (Revisar requisitos)**
    - Platos más pedidos
    - Ingresos por restaurante
    - Calificaciones promedio
    - Función: `generarInformeVentas()`
    - Función: `generarInformeRepartidores()`
    - Archivo de salida: `informes/` (carpeta con archivos .txt)

12. **Reportes del Usuario (Menos Importante)**
    - Mis pedidos y estados
    - Mis direcciones
    - Mis formas de pago
    - Función: `generarResumenMisPedidos()`
    - Archivo de salida: `reporte_usuario_[ID].txt`

---

## 🎯 Tareas Inmediatas (Próximo Sprint)

### Prioridad ALTA (Hacer Primero):
- [ ] Corregir bug de teléfonos no guardándose
- [ ] Resolver bug de múltiples roles por usuario
- [ ] Implementar validación de entrada de datos
- [ ] Implementar CRUD completo de Pedidos
- [ ] Implementar Detalle de Pedidos

### Prioridad MEDIA (Hacer Segundo):
- [ ] Historial de estados de pedidos
- [ ] Sistema de pagos
- [ ] Panel y funciones de Encargado
- [ ] CRUD de Menú/Productos

### Prioridad BAJA (Hacer Último):
- [ ] Informes avanzados
- [ ] Reportes del usuario
- [ ] Optimizaciones de código
- [ ] Refactorización de funciones duplicadas

---

## 📁 Estructura de Archivos .dat

**Archivos de Base de Datos (deben existir en `bin/Debug/`):**
- `usuarios.dat` - Cuentas registradas
- `clientes.dat` - Perfil de clientes
- `repartidores.dat` - Datos de repartidores
- `encargados.dat` - Datos de encargados
- `administradores.dat` - Datos de administradores
- `restaurantes.dat` - Información de restaurantes
- `platos.dat` - Menú de productos
- `categorias.dat` - Categorías de platos
- `pedidos.dat` - **POR HACER**
- `detalles_pedido.dat` - **POR HACER**
- `estados_pedido.dat` - **POR HACER**
- `pagos.dat` - **POR HACER**

---

## 🔧 Notas Técnicas Importantes

1. **Estructura de Código**: 
   - Funciones base en `crud.h/c`
   - Reportes en `informes.h/c`
   - Manejo de archivos en `filemanager.h/c`
   - Estructuras en `BBD.h`

2. **Patrones a Mantener**:
   - Usar archivos binarios con fopen/fwrite/fread
   - Una tabla = un archivo .dat
   - Funciones: agregar, actualizar, eliminar, listar (para cada tabla)

3. **Testing Recomendado**:
   - Probar cada función de CRUD inmediatamente después de crearla
   - Verificar que los datos se guardan correctamente en .dat
   - Probar roles y permisos de acceso

4. **Seguridad**:
   - Validar todos los inputs antes de guardar
   - Verificar permisos según rol del usuario
   - Manejar excepciones de lectura/escritura de archivos

---

## 📅 Estimado de Tiempo Total

- **Fase 1 (Correcciones)**: 1-2 días
- **Fase 2 (Pedidos)**: 3-4 días  
- **Fase 3 (Pagos)**: 2 días
- **Fase 4 (Menú)**: 2-3 días
- **Fase 5 (Informes)**: 2 días
- **Pruebas y Ajustes**: 2 días

**Total estimado: 14-18 días de desarrollo**

---

## 📝 Notas del Compañero (Recordatorio)

> "Cree comentarios para tener en cuenta como se usarán las funciones"
> "El orden de las funciones puede ser molesto y confuso"
> "La cantidad de Funciones y estructuras es demencial"

**Acción**: Considerar refactorizar y documentar mejor el código una vez completadas las funcionalidades.

---

*Última actualización: Fase de análisis inicial*
*Próxima revisión: Después de completar Fase 1*
