# 🧪 PLAN DE TESTING - FASE 2

**Versión**: 0.4  
**Fecha de Pruebas**: 2026-06-21  
**Objetivo**: Validar funcionalidad de Menú, Pedidos y Pagos

---

## ✅ PRE-TESTING: VERIFICACIÓN DE COMPILACIÓN

### Paso 1: Verificar Compilación
**Ubicación**: CodeBlocks (TP-Integrador.cbp)
**Acción**: Abrir proyecto y compilar (Build → Rebuild)
**Resultado Esperado**: Sin errores (solo advertencias si las hay)

---

## 🧪 TEST 1: CREAR ENCARGADO

### Pre-requisitos:
- Ejecutable funcionando
- Al menos 1 Restaurante existente (creado por Admin)

### Pasos:
1. Ejecutar aplicación
2. Seleccionar [2] Crear Cuenta
3. Ingresar datos:
   ```
   Nombre: Carlos
   Apellido: Pérez
   Email: encargado_test@mail.com
   Contraseña: Pass123
   Teléfono: 3512345678
   ```
4. Seleccionar Rol: [2] Encargado
5. Ingresar ID Restaurante (ej: 1)
6. Ingresar Turno: matutino

### Validaciones:
- ✅ Archivo `encargado.dat` debe contener nuevo registro
- ✅ ID_usuario debe coincidir en `usuario.dat`
- ✅ Sistema no debe crear duplicado en siguiente intento

---

## 🧪 TEST 2: AGREGAR PRODUCTOS AL MENÚ

### Pre-requisitos:
- Encargado creado en TEST 1
- Iniciar sesión como Encargado

### Pasos:
1. Ingresar email: `encargado_test@mail.com`
2. Ingresar contraseña: `Pass123`
3. En menú principal, entrar a panelEncargador
4. Seleccionar [1] Agregar Producto
5. Ingresar datos:
   ```
   Nombre: Milanesa con Papas
   Descripción: Milanesa_de_ternera_con_papas_fritas_y_ensalada
   Precio: 450
   Categoría: Principales
   ```
6. Repetir TEST 2 agregando 3 productos más:
   - Hamburguesa Clásica (350)
   - Pizza Muzzarella (320)
   - Bebida Gaseosa 500ml (80)

### Validaciones:
- ✅ Cada producto debe tener ID único
- ✅ Archivo `producto.dat` debe contener 4 registros
- ✅ Id_menu debe ser el ID del restaurante del Encargado
- ✅ Disponibilidad debe ser "disponible"

---

## 🧪 TEST 3: LISTAR MENÚ DEL RESTAURANTE

### Pre-requisitos:
- TEST 2 completado (productos agregados)

### Pasos:
1. En panelEncargador, seleccionar [3] Ver Menú del Restaurante
2. Verificar que se muestren los 4 productos agregados

### Validaciones:
- ✅ Debe mostrar todos los productos disponibles
- ✅ Debe mostrar nombre, descripción, precio, categoría
- ✅ No debe mostrar productos de otros restaurantes

---

## 🧪 TEST 4: MODIFICAR PRODUCTO

### Pre-requisitos:
- TEST 2 completado

### Pasos:
1. En panelEncargador, seleccionar [2] Modificar Plato
2. Ingresar ID del producto: (uno de los agregados, ej: 1)
3. Seleccionar [3] Cambiar Precio
4. Ingresar nuevo precio: 500
5. Verificar cambio listando menú nuevamente

### Validaciones:
- ✅ Producto debe actualizarse en `producto.dat`
- ✅ El precio debe cambiar
- ✅ Otros datos del producto no deben alterarse

---

## 🧪 TEST 5: CLIENTE REALIZA PEDIDO

### Pre-requisitos:
- TEST 2 completado (menú disponible)
- Cliente existente

### Pasos:
1. Crear o iniciar sesión como Cliente
   - Email: `cliente_test@mail.com`
   - Contraseña: `Pass123`
2. En panelCliente, seleccionar [1] Realizar Pedido
3. Cuando pregunte por restaurante, ver lista:
   - Debe mostrar restaurante con productos
   - Seleccionar ID del restaurante (ej: 1)
4. Ver menú disponible (debe mostrar 4 productos)
5. Ingresar dirección de entrega:
   ```
   Direccion: Calle_Main_1234
   ```
6. Ingresar observaciones (opcional):
   ```
   Observaciones: Sin_cebolla
   ```

### Validaciones:
- ✅ Archivo `pedido.dat` debe contener nuevo Pedido
- ✅ Archivo `orden_preparacion.dat` debe contener OrdenPreparacion
- ✅ Archivo `historial_estado.dat` debe contener entrada con estado="Pendiente"
- ✅ Pedido.id_cliente debe ser el ID del Cliente
- ✅ Pedido.estado debe ser "Pendiente"
- ✅ Dirección se debe guardar correctamente (espacios → guiones)

---

## 🧪 TEST 6: CLIENTE VE SUS PEDIDOS

### Pre-requisitos:
- TEST 5 completado

### Pasos:
1. En panelCliente del mismo Usuario, seleccionar [2] Ver Mis Pedidos
2. Verificar que aparezca el pedido creado en TEST 5

### Validaciones:
- ✅ Debe mostrar solo pedidos del Cliente actual
- ✅ Debe mostrar ID, Fecha, Estado, Dirección
- ✅ Estado debe ser "Pendiente"

---

## 🧪 TEST 7: CLIENTE VE ESTADO DEL PEDIDO

### Pre-requisitos:
- TEST 6 completado

### Pasos:
1. En panelCliente, seleccionar [3] Ver Estado del Pedido
2. Ingresar ID del pedido (el del TEST 5)
3. Verificar historial

### Validaciones:
- ✅ Debe mostrar entrada inicial: Pendiente (fecha)
- ✅ Formato debe ser: → Estado (fecha hora)

---

## 🧪 TEST 8: CLIENTE REALIZA PAGO

### Pre-requisitos:
- TEST 7 completado
- Pedido existente

### Pasos:
1. En panelCliente, seleccionar [4] Realizar Pago
2. Ingresar ID del Pedido (del TEST 5)
3. Seleccionar método de pago: [1] Efectivo
4. Verificar confirmación

### Validaciones:
- ✅ Archivo `pago.dat` debe contener nuevo Pago
- ✅ Pago.id_pedido debe ser el del pedido
- ✅ Pago.metodo_pago debe ser "Efectivo"
- ✅ Pago.estado_pago debe ser "Pendiente"
- ✅ Debe mostrar: ID Pago, Método, Estado, Monto

---

## 🧪 TEST 9: PAGO CON TARJETA

### Pre-requisitos:
- Cliente y Pedido disponible

### Pasos:
1. Realizar TEST 8 pero seleccionar [2] Tarjeta de Débito
2. Verificar que estado sea "Procesando"

### Validaciones:
- ✅ Pago.estado_pago debe ser "Procesando"
- ✅ Pago.metodo_pago debe ser "Tarjeta_Débito"

---

## 🧪 TEST 10: VALIDACIONES DE ENTRADA

### Prueba 10A: Nombre inválido
**Pasos**: Intentar agregar producto sin nombre
**Resultado Esperado**: Mensaje de error, reintento

### Prueba 10B: Precio inválido
**Pasos**: Intentar agregar producto con precio = -50
**Resultado Esperado**: Mensaje de error, reintento

### Prueba 10C: Espacios en texto
**Pasos**: Agregar producto con nombre "Milanesa con Papas"
**Resultado Esperado**: Se guarda como "Milanesa_con_Papas"

---

## 📊 REPORTE DE TESTING

### Resumen de Pruebas:
| Test | Estado | Notas |
|------|--------|-------|
| TEST 1 | ⏳ | Crear Encargado |
| TEST 2 | ⏳ | Agregar Productos |
| TEST 3 | ⏳ | Listar Menú |
| TEST 4 | ⏳ | Modificar Producto |
| TEST 5 | ⏳ | Cliente Realiza Pedido |
| TEST 6 | ⏳ | Cliente Ve Pedidos |
| TEST 7 | ⏳ | Ver Estado Pedido |
| TEST 8 | ⏳ | Cliente Realiza Pago |
| TEST 9 | ⏳ | Pago con Tarjeta |
| TEST 10 | ⏳ | Validaciones |

### Criterios de Éxito:
- ✅ Mínimo 8/10 tests deben pasar
- ✅ Archivos .dat deben crearse correctamente
- ✅ No debe haber crashes o segmentation faults
- ✅ Datos deben persistir entre sesiones

---

**Fecha de Ejecución**: [Pendiente]  
**Ejecutor**: [Usuario]  
**Resultado**: [Pendiente]
