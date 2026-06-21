# 🔧 Instrucciones de Compilación y Testing - Fase 1

**Documento Creado**: 21 de Junio de 2026  
**Objetivo**: Compilar y testear los cambios de Fase 1 (bugs y validaciones)

---

## 📋 Cambios en el Código

### Archivos Creados:
1. **`validaciones.h`** - Header con declaraciones de 7 funciones de validación
2. **`validaciones.c`** - Implementación de validaciones

### Archivos Modificados:
1. **`crud.h`** - Agregado: `#include "validaciones.h"`
2. **`crud.c`** - Cambios principales en:
   - Función `agregarUsuario()` - Reescrita completamente con validaciones
   - Función `seleccionarCuenta()` - Mejorada manejo de errores
   - Agregado: `#include <string.h>` para strcpy()

---

## 🔨 Pasos para Compilar

### Opción 1: Code::Blocks (Recomendado)
1. Abrir `TP-Integrador.cbp` en Code::Blocks
2. Ir a **Build → Rebuild**
3. Si hay errores de compilación, revisar la sección "Errores Comunes" abajo

### Opción 2: Línea de Comandos (MinGW)
```bash
cd "c:\Users\Operador\Documents\Programación\morfi\0.2"
gcc -c validaciones.c -o obj/Debug/validaciones.o
gcc -c crud.c -o obj/Debug/crud.o
gcc -c main.c -o obj/Debug/main.o
gcc obj/Debug/*.o -o bin/Debug/TP-Integrador.exe
```

### Opción 3: Verificar sin Compilar
Si no tienes compilador disponible, haz una revisión estática:
- [ ] Verificar que `validaciones.h` existe en la raíz
- [ ] Verificar que `validaciones.c` existe en la raíz
- [ ] Verificar que `crud.h` incluye `#include "validaciones.h"`
- [ ] Revisar que `crud.c` incluye `#include <string.h>`

---

## ⚠️ Errores Comunes y Soluciones

### Error: "validaciones.h: No such file or directory"
**Causa**: El archivo no está en el lugar correcto
**Solución**: Asegúrate de que `validaciones.h` y `validaciones.c` están en la **raíz del proyecto** (mismo nivel que `main.c`)

### Error: "undefined reference to `validarEmail`"
**Causa**: Olvidaste compilar `validaciones.c`
**Solución**: 
- En Code::Blocks: Asegúrate de que `validaciones.c` está en el proyecto
- Haz Rebuild (no solo Build)

### Error: "redefinition of `struct Usuario`"
**Causa**: Inclusión múltiple de headers
**Solución**: Verifica que todos los `.h` tienen `#ifndef` guards (ya deberían tenerlos)

### Error: `isalpha`, `isdigit` no reconocidos
**Causa**: Falta `#include <ctype.h>` en `validaciones.c`
**Solución**: Ya está incluido en `validaciones.c`, si persiste el error, reconstruye limpiamente

---

## ✅ Plan de Testing

### Test 1: Validación de Teléfono
**Pasos**:
1. Ejecutar el programa
2. Seleccionar opción "2 - Crear Cuenta"
3. Ingrese datos válidos hasta llegar a Teléfono
4. **Test A** (debe aceptar):
   - Ingrese: `+34-123-4567`
   - Debe aceptar y continuar
5. **Test B** (debe rechazar):
   - Ingrese: `123` (muy corto)
   - Debe mostrar error y reintentar
6. **Test C** (debe rechazar):
   - Ingrese: `abc123def4567` (contiene letras)
   - Debe mostrar error y reintentar
7. **Test D** (debe aceptar):
   - Ingrese: `1234567890`
   - Debe aceptar y continuar

**Resultado Esperado**: Teléfono se guarda correctamente sin basura en archivo `usuario.dat`

---

### Test 2: Validación de Email
**Pasos**:
1. Ejecutar el programa
2. Seleccionar opción "2 - Crear Cuenta"
3. Ingrese nombre, apellido válidos
4. **Test A** (debe rechazar):
   - Ingrese: `usuarios.com` (sin @)
   - Debe mostrar error
5. **Test B** (debe rechazar):
   - Ingrese: `usuarios@` (sin dominio)
   - Debe mostrar error
6. **Test C** (debe aceptar):
   - Ingrese: `usuario@ejemplo.com`
   - Debe aceptar y continuar

**Resultado Esperado**: Solo acepta emails con @ y punto

---

### Test 3: Validación de Contraseña
**Pasos**:
1. Ejecutar el programa
2. Seleccionar opción "2 - Crear Cuenta"
3. Ingrese datos válidos hasta Contraseña
4. **Test A** (debe rechazar):
   - Ingrese: `123` (menos de 6)
   - Debe mostrar error
5. **Test B** (debe rechazar):
   - Ingrese: `pass 123` (contiene espacio)
   - Debe mostrar error
6. **Test C** (debe aceptar):
   - Ingrese: `password123`
   - Debe aceptar y continuar

**Resultado Esperado**: Solo acepta contraseñas válidas

---

### Test 4: Validación de Nombre/Apellido
**Pasos**:
1. Ejecutar el programa
2. Seleccionar opción "2 - Crear Cuenta"
3. En Nombre:
   - **Test A** (rechazar): Ingrese `Juan123` → debe mostrar error
   - **Test B** (aceptar): Ingrese `Juan` → debe continuar

**Resultado Esperado**: Solo acepta letras y espacios

---

### Test 5: Test de Rol Único
**Pasos**:
1. Crear un usuario como **Cliente**
2. Registrar el email usado
3. Ir a Login
4. Autenticarse con ese email
5. Verificar que va al **Panel Cliente** (no múltiples paneles)
6. Repetir proceso para cada rol (Encargado, Repartidor, Administrador)

**Resultado Esperado**: Cada usuario solo puede tener un rol y accede al correcto

---

### Test 6: Verificación de Archivos .dat
**Pasos**:
1. Crear 3 usuarios diferentes (uno cliente, uno repartidor, uno admin)
2. Revisar archivos generados (si tienes acceso):
   - `usuario.dat` debe contener 3 registros
   - `cliente.dat` debe contener 1 registro
   - `repartidor.dat` debe contener 1 registro
   - `administrador.dat` debe contener 1 registro
3. Verificar que teléfonos son legibles (no basura)

**Resultado Esperado**: Archivos sin corrupción de datos

---

## 📊 Checklist de Validación

Después de compilar y testear, marca lo completado:

- [ ] Código compila sin errores
- [ ] No hay advertencias graves (warnings)
- [ ] Test 1 de Teléfono: Pasa
- [ ] Test 2 de Email: Pasa
- [ ] Test 3 de Contraseña: Pasa
- [ ] Test 4 de Nombre: Pasa
- [ ] Test 5 de Rol Único: Pasa
- [ ] Test 6 de Archivos .dat: Pasa
- [ ] Sistema se puede usar normalmente
- [ ] Teléfonos se guardan y leen correctamente

---

## 🎯 Resultado Final

Si todos los tests pasan:
✅ **Fase 1 Completada Exitosamente**

Próximo paso: Proceder a **Fase 2 - Sistema de Pedidos**

---

## 📞 Si hay Problemas

1. Verifica que compilador está instalado:
   - En Code::Blocks: Tools → Compiler Settings
   - Busca MinGW GCC

2. Limpia proyecto antes de recompilar:
   - Code::Blocks: Build → Clean (or Rebuild)

3. Revisa include paths:
   - Code::Blocks: Project → Properties → Build Targets → Compiler Settings → Search Directories

4. Si persisten errores, comparte:
   - Mensaje de error exacto
   - Línea donde ocurre el error
   - Archivo donde ocurre

---

*Documento de Testing - Fase 1*  
*Última actualización: 21 de Junio de 2026*
