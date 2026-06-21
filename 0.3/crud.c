#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crud.h"

/** direccion de las estructuras*/
#include "BBD.h"

/** funciones de alta, baja, modificaci�n, */
/** listado para cada tabla. */

void abrirBDD(){
    FILE *archivo;

    archivo = fopen("usuario.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("cliente.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("repartidor.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("encargado.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("administrador.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("restaurante.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("producto.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("pedido.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("pago.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("orden_preparacion.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("detalle_orden.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("historial_estado.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("categoria.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("menu.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("transaccion.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("recibo.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    printf("\nBase de datos inicializada correctamente.\n");
}

/** Agregar Usuarios*/
void agregarUsuario(){
    int rol;
    Usuario usuario;
    int id_usuario_existente;
    int opcion_menu = 0;

    char roles[4][50]={
        "\n[1] Cliente\n",
        "[2] Encargado\n",
        "[3] Repartidor\n",
        "[4] Administrador\n",
    };

    printf("\n===============================\n");
    printf("\n        INGRESAR USUARIO\n");
    printf("\n===============================\n");

    // Validar Email PRIMERO para ver si existe
    do {
        printf("\nIngrese Correo: ");
        scanf(" %[^\n]", usuario.email);
        convertirEspaciosAGuiones(usuario.email);
        if (!validarEmail(usuario.email)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Verificar si el email ya existe
    id_usuario_existente = obtenerIdPorEmail(usuario.email);

    if(id_usuario_existente != -1){
        // El email ya existe - usuario registrado previamente
        printf("\n===============================\n");
        printf("\n  CORREO YA REGISTRADO\n");
        printf("\n===============================\n");
        printf("\nEsta cuenta ya existe en el sistema.");
        printf("\n¿Qué desea hacer?\n");
        printf("[1] Agregar otro rol a esta cuenta\n");
        printf("[2] Cancelar\n");
        printf("Opción: ");

        if(scanf("%d", &opcion_menu) != 1){
            while (getchar() != '\n');
            opcion_menu = -1;
        }

        if(opcion_menu == 1){
            agregarRolExistente(id_usuario_existente);
            return;
        } else {
            printf("\nOperación cancelada.\n");
            return;
        }
    }

    // El email NO existe - crear nuevo usuario

    // Validar Contraseña
    do {
        printf("\nIngrese Contraseña: ");
        scanf(" %[^\n]", usuario.contrasena);
        convertirEspaciosAGuiones(usuario.contrasena);
        if (!validarContrasena(usuario.contrasena)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Nombre
    do {
        printf("\nIngrese Nombre: ");
        scanf(" %[^\n]", usuario.nombre);
        convertirEspaciosAGuiones(usuario.nombre);
        if (!validarNombre(usuario.nombre)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Apellido
    do {
        printf("\nIngrese Apellido: ");
        scanf(" %[^\n]", usuario.apellido);
        convertirEspaciosAGuiones(usuario.apellido);
        if (!validarNombre(usuario.apellido)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Teléfono
    do {
        printf("\nIngrese Telefono: ");
        scanf(" %[^\n]", usuario.telefono);
        convertirEspaciosAGuiones(usuario.telefono);
        if (!validarTelefono(usuario.telefono)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Inicializar campos de fecha y estado
    strcpy(usuario.fecha_registro, "2024-06-21");  // Pendiente de mejorar con función de fecha real
    strcpy(usuario.estado_cuenta, "activa");

    // Seleccionar Rol (ÚNICO)
    do {
        generarMenu(roles, 4);
        printf("\nIngrese Rol: ");

        if(scanf("%d", &rol) != 1){
            while (getchar() != '\n'); //Limpiamos el buffer para que no quede el caracter dando error
            rol = -1;
        }

        if (rol < 1 || rol > 4) {
            printf("\n[ERROR] Opción inválida. Ingrese entre 1 y 4.\n");
            continue;
        }

        // Hacer el switch con el rol seleccionado
        switch(rol){
            case 1:{
                agregarCliente(usuario);
                break;
            }
            case 2:{
                agregarEncargado(usuario);
                break;
            }
            case 3:{
                agregarRepartidor(usuario);
                break;
            }
            case 4:{
                agregarAdministrador(usuario);
                break;
            }
        }
        break;  // Salir del loop después de procesar
    } while(0);
}
void agregarCliente(Usuario usuario){
    FILE *archivoUsuario;
    FILE *archivoCliente;

    archivoUsuario = fopen("usuario.dat", "rb");

    Usuario auxUsuario;
    Cliente cliente;

    int ultimoId = 0;

    if(archivoUsuario != NULL){
        while( fread(&auxUsuario, sizeof(Usuario), 1, archivoUsuario) == 1 ){
            if(auxUsuario.id_usuario > ultimoId){ ultimoId = auxUsuario.id_usuario; }
        } fclose(archivoUsuario);
    }

    usuario.id_usuario = ultimoId + 1;
    cliente.id_usuario = usuario.id_usuario;

    printf("\nIngrese Direccion: ");
    scanf(" %[^\n]", cliente.direccion);
    convertirEspaciosAGuiones(cliente.direccion);

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoCliente = fopen("cliente.dat", "ab");

    if(archivoUsuario != NULL && archivoCliente != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_cliente = fwrite(&cliente, sizeof(Cliente), 1, archivoCliente);

        fflush(archivoUsuario);
        fflush(archivoCliente);

        fclose(archivoUsuario);
        fclose(archivoCliente);

        if(resultado_usuario == 1 && resultado_cliente == 1){
            printf("\n✓ Cliente agregado correctamente.");
            printf("\n  ID asignado: %d\n", usuario.id_usuario);
        } else {
            printf("\n[ERROR] Fallo al escribir en los archivos.\n");
            printf("  Usuario escrito: %d, Cliente escrito: %d\n", resultado_usuario, resultado_cliente);
        }
    }
    else{
        printf("\n[ERROR] No se pudo abrir los archivos.\n");

        if(archivoUsuario != NULL)
            fclose(archivoUsuario);

        if(archivoCliente != NULL)
            fclose(archivoCliente);
    }
}
void agregarRepartidor(Usuario usuario){
    FILE *archivoUsuario;
    FILE *archivoRepartidor;

    archivoUsuario = fopen("usuario.dat", "rb");

    Usuario auxUsuario;
    Repartidor repartidor;

    int ultimoId = 0;

    if(archivoUsuario != NULL){
        while(fread(&auxUsuario, sizeof(Usuario), 1, archivoUsuario) == 1){
            if(auxUsuario.id_usuario > ultimoId){
                ultimoId = auxUsuario.id_usuario;
            }
        } fclose(archivoUsuario);
    }

    usuario.id_usuario = ultimoId + 1;

    repartidor.id_usuario = usuario.id_usuario;

    printf("\nIngrese Vehiculo: ");
    scanf(" %[^\n]", repartidor.vehiculo);
    convertirEspaciosAGuiones(repartidor.vehiculo);

    printf("\nIngrese Estado de Disponibilidad: ");
    scanf(" %[^\n]", repartidor.estado_disponibilidad);
    convertirEspaciosAGuiones(repartidor.estado_disponibilidad);

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoRepartidor = fopen("repartidor.dat", "ab");

    if(archivoUsuario != NULL && archivoRepartidor != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_repartidor = fwrite(&repartidor, sizeof(Repartidor), 1, archivoRepartidor);

        fflush(archivoUsuario);
        fflush(archivoRepartidor);

        fclose(archivoUsuario);
        fclose(archivoRepartidor);

        if(resultado_usuario == 1 && resultado_repartidor == 1){
            printf("\nRepartidor agregado correctamente.");
            printf("\n  ID asignado: %d\n", usuario.id_usuario);
        } else {
            printf("\n[ERROR] Fallo al escribir en los archivos.\n");
            printf("  Usuario escrito: %d, Repartidor escrito: %d\n", resultado_usuario, resultado_repartidor);
        }
    }
    else{
        printf("\n[ERROR] No se pudo abrir los archivos.\n");

        if(archivoUsuario != NULL)
            fclose(archivoUsuario);

        if(archivoRepartidor != NULL)
            fclose(archivoRepartidor);
    }
}
void agregarEncargado(Usuario usuario){
    FILE *archivoUsuario;
    FILE *archivoEncargado;

    archivoUsuario = fopen("usuario.dat", "rb");

    Usuario auxUsuario;
    Encargado encargado;

    int ultimoId = 0;

    if(archivoUsuario != NULL){
        while(fread(&auxUsuario, sizeof(Usuario), 1, archivoUsuario) == 1){
            if(auxUsuario.id_usuario > ultimoId){
                ultimoId = auxUsuario.id_usuario;
            }
        } fclose(archivoUsuario);
    }

    usuario.id_usuario = ultimoId + 1;
    encargado.id_usuario = usuario.id_usuario;

    printf("\nIngrese ID del Restaurante: ");
    scanf("%d", &encargado.id_restaurante);

    printf("\nIngrese Turno: ");
    scanf(" %[^\n]", encargado.turno);
    convertirEspaciosAGuiones(encargado.turno);

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoEncargado = fopen("encargado.dat", "ab");

    if(archivoUsuario != NULL && archivoEncargado != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_encargado = fwrite(&encargado, sizeof(Encargado), 1, archivoEncargado);

        fflush(archivoUsuario);
        fflush(archivoEncargado);

        fclose(archivoUsuario);
        fclose(archivoEncargado);

        if(resultado_usuario == 1 && resultado_encargado == 1){
            printf("\nEncargado agregado correctamente.");
            printf("\n  ID asignado: %d\n", usuario.id_usuario);
        } else {
            printf("\n[ERROR] Fallo al escribir en los archivos.\n");
            printf("  Usuario escrito: %d, Encargado escrito: %d\n", resultado_usuario, resultado_encargado);
        }
    }
    else{
        printf("\n[ERROR] No se pudo abrir los archivos.\n");

        if(archivoUsuario != NULL)
            fclose(archivoUsuario);

        if(archivoEncargado != NULL)
            fclose(archivoEncargado);
    }
}
void agregarAdministrador(Usuario usuario){
    FILE *archivoUsuario;
    FILE *archivoAdministrador;
    archivoUsuario = fopen("usuario.dat", "rb");

    Usuario auxUsuario;
    Administrador administrador;

    int ultimoId = 0;

    if(archivoUsuario != NULL){
        while(fread(&auxUsuario, sizeof(Usuario), 1, archivoUsuario) == 1){
            if(auxUsuario.id_usuario > ultimoId){
                ultimoId = auxUsuario.id_usuario;
            }
        } fclose(archivoUsuario);
    }

    usuario.id_usuario = ultimoId + 1;
    administrador.id_usuario = usuario.id_usuario;

    printf("\nIngrese Nivel de Acceso (superadmin, admin, supervisor) : ");
    scanf(" %[^\n]", administrador.nivel_acceso);
    convertirEspaciosAGuiones(administrador.nivel_acceso);

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoAdministrador = fopen("administrador.dat", "ab");

    if(archivoUsuario != NULL && archivoAdministrador != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_admin = fwrite(&administrador, sizeof(Administrador), 1, archivoAdministrador);

        fflush(archivoUsuario);
        fflush(archivoAdministrador);

        fclose(archivoUsuario);
        fclose(archivoAdministrador);

        if(resultado_usuario == 1 && resultado_admin == 1){
            printf("\nAdministrador agregado correctamente.");
            printf("\n  ID asignado: %d\n", usuario.id_usuario);
        } else {
            printf("\n[ERROR] Fallo al escribir en los archivos.\n");
            printf("  Usuario escrito: %d, Administrador escrito: %d\n", resultado_usuario, resultado_admin);
        }
    }
    else{
        printf("\n[ERROR] No se pudo abrir los archivos.\n");

        if(archivoUsuario != NULL)
            fclose(archivoUsuario);

        if(archivoAdministrador != NULL)
            fclose(archivoAdministrador);
    }
}

/**Eliminar Cuenta*/
void eliminarUsuario(Usuario usuario){
    FILE *archivo;
    FILE *auxiliar;

    Usuario reg;

    int encontrado = 0;

    archivo = fopen("usuario.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");

        if(archivo != NULL){ fclose(archivo); }
        if(auxiliar != NULL){fclose(auxiliar);}

        return;
    }

    while(fread(&reg, sizeof(Usuario), 1, archivo) == 1){
        if( strcmp(reg.email, usuario.email) == 0 &&
            strcmp(reg.contrasena, usuario.contrasena) == 0){

            eliminarCliente( usuario.id_usuario );
            eliminarEncargado( usuario.id_usuario );
            eliminarRepartidor( usuario.id_usuario );
            eliminarAdministrador( usuario.id_usuario );

            encontrado = 1;
        }
        else{
            fwrite(&reg, sizeof(Usuario), 1, auxiliar);
        }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("usuario.dat");
    rename("auxiliar.dat", "usuario.dat");

    if(encontrado){ printf("\nUsuario eliminado correctamente."); }
    else{ printf("\nCorreo o contrase�a incorrectos."); }
}
void eliminarCliente(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Cliente cliente;

    archivo = fopen("cliente.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&cliente, sizeof(Cliente), 1, archivo) == 1){
        if(cliente.id_usuario != id_usuario){ fwrite(&cliente, sizeof(Cliente), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("cliente.dat");
    rename("auxiliar.dat", "cliente.dat");
}
void eliminarRepartidor(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Repartidor repartidor;

    archivo = fopen("repartidor.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&repartidor, sizeof(Repartidor), 1, archivo) == 1){
        if(repartidor.id_usuario != id_usuario){ fwrite(&repartidor, sizeof(Repartidor), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("repartidor.dat");
    rename("auxiliar.dat", "repartidor.dat");
}
void eliminarEncargado(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Encargado encargado;

    archivo = fopen("encargado.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&encargado, sizeof(Encargado), 1, archivo) == 1){
        if(encargado.id_usuario != id_usuario){ fwrite(&encargado, sizeof(Encargado), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("encargado.dat");
    rename("auxiliar.dat", "encargado.dat");
}
void eliminarAdministrador(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Administrador administrador;

    archivo = fopen("administrador.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&administrador, sizeof(Administrador), 1, archivo) == 1){
        if(administrador.id_usuario != id_usuario){ fwrite(&administrador, sizeof(Administrador), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("administrador.dat");
    rename("auxiliar.dat", "administrador.dat");
}


/**Actualizar Datos*/
void actualizarUsuarioXid(Usuario usuario){
    FILE *archivo;
    Usuario reg;
    archivo = fopen("usuario.dat", "rb+");

    int rol;

    if(archivo == NULL){
        printf("\nError al abrir archivo.");
        return;
    }

    while(fread(&reg, sizeof(Usuario), 1, archivo) == 1){
        if(reg.email == usuario.email && reg.contrasena == usuario.email){
            printf("\nIngrese Nombre: ");
            scanf(" %[^\n]", reg.nombre);
            convertirEspaciosAGuiones(reg.nombre);

            printf("\nIngrese Apellido: ");
            scanf(" %[^\n]", reg.apellido);
            convertirEspaciosAGuiones(reg.apellido);

            printf("\nIngrese Correo: ");
            scanf(" %[^\n]", reg.email);
            convertirEspaciosAGuiones(reg.email);

            printf("\nIngrese Contraseña: ");
            scanf(" %[^\n]", reg.contrasena);
            convertirEspaciosAGuiones(reg.contrasena);

            printf("\nIngrese Telefono: ");
            scanf(" %[^\n]", reg.telefono);
            convertirEspaciosAGuiones(reg.telefono);

            printf("\nSeleccione Rol:");
            printf("\n[1] Cliente");
            printf("\n[2] Encargado");
            printf("\n[3] Repartidor");
            printf("\n[4] Administrador");
            printf("\nOpcion: ");

            if(scanf("%d", &rol) != 1){
                while (getchar() != '\n'); //Limpiamos el buffer para que no quede el caracter dando error
                rol = -1;
            }

            switch(rol){
                case 1:{
                    actualizarClienteXid(usuario.id_usuario);

                    fseek(archivo, -(long)sizeof(Usuario), SEEK_CUR);
                    fwrite(&reg, sizeof(Usuario), 1, archivo);

                    fclose(archivo);

                    printf("\nDatos generales actualizados.\n");

                    break;
                }
                case 2:{
                    actualizarEncargadoXid(usuario.id_usuario);

                    fseek(archivo, -(long)sizeof(Usuario), SEEK_CUR);
                    fwrite(&reg, sizeof(Usuario), 1, archivo);

                    fclose(archivo);

                    printf("\nDatos generales actualizados.\n");

                    break;
                }
                case 3:{
                    actualizarRepartidorXid(usuario.id_usuario);

                    fseek(archivo, -(long)sizeof(Usuario), SEEK_CUR);
                    fwrite(&reg, sizeof(Usuario), 1, archivo);

                    fclose(archivo);

                    printf("\nDatos generales actualizados.\n");

                    break;
                }
                case 4:{
                    actualizarAdministradorXid(usuario.id_usuario);

                    fseek(archivo, -(long)sizeof(Usuario), SEEK_CUR);
                    fwrite(&reg, sizeof(Usuario), 1, archivo);

                    fclose(archivo);

                    printf("\nDatos generales actualizados.\n");

                    break;
                }
                default:{
                    printf("\nRol invalido.");
                    break;
                }
            }

            return;
        }
    }

    printf("\nUsuario no encontrado.");
    fclose(archivo);
}
void actualizarClienteXid(int id_usuario){
    FILE *archivo;
    Cliente cliente;

    archivo = fopen("cliente.dat", "rb");

    if(archivo == NULL){
        printf("\nError al abrir archivo.");
        return;
    }

    while(fread(&cliente, sizeof(Cliente), 1, archivo) == 1){

        if(cliente.id_usuario == id_usuario){

            printf("\nNueva Direccion: ");
            scanf(" %[^\n]", cliente.direccion);
            convertirEspaciosAGuiones(cliente.direccion);

            fseek(archivo, -(long)sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, archivo);

            printf("\nCliente actualizado.");
            fclose(archivo);
            return;
        }
    }

    printf("\nCliente no encontrado.");
    fclose(archivo);
}
void actualizarRepartidorXid(int id_usuario){
    FILE *archivo;
    Repartidor repartidor;

    archivo = fopen("repartidor.dat", "rb");

    if(archivo == NULL){
        printf("\nError al abrir archivo.");
        return;
    }

    while(fread(&repartidor, sizeof(Repartidor), 1, archivo) == 1){
        if(repartidor.id_usuario == id_usuario){
            printf("\nNuevo Vehiculo: ");
            scanf(" %[^\n]", repartidor.vehiculo);
            convertirEspaciosAGuiones(repartidor.vehiculo);

            printf("\nNuevo Estado: ");
            scanf(" %[^\n]", repartidor.estado_disponibilidad);
            convertirEspaciosAGuiones(repartidor.estado_disponibilidad);

            fseek(archivo, -(long)sizeof(Repartidor), SEEK_CUR);
            fwrite(&repartidor, sizeof(Repartidor), 1, archivo);

            printf("\nRepartidor actualizado.");
            fclose(archivo);
            return;
        }
    }

    printf("\nRepartidor no encontrado.");
    fclose(archivo);
}
void actualizarEncargadoXid(int id_usuario){
    FILE *archivo;
    Encargado encargado;

    archivo = fopen("encargado.dat", "rb");

    if(archivo == NULL){
        printf("\nError al abrir archivo.");
        return;
    }

    while(fread(&encargado, sizeof(Encargado), 1, archivo) == 1){
        if(encargado.id_usuario == id_usuario){

            printf("\nNuevo ID Restaurante: ");
            scanf("%d", &encargado.id_restaurante);

            printf("\nNuevo Turno: ");
            scanf(" %[^\n]", encargado.turno);
            convertirEspaciosAGuiones(encargado.turno);

            fseek(archivo, -(long)sizeof(Encargado), SEEK_CUR);
            fwrite(&encargado, sizeof(Encargado), 1, archivo);

            printf("\nEncargado actualizado.");
            fclose(archivo);
            return;
        }
    }

    printf("\nEncargado no encontrado.");
    fclose(archivo);
}
void actualizarAdministradorXid(int id_usuario){
    FILE *archivo;
    Administrador administrador;

    archivo = fopen("administrador.dat", "rb");

    if(archivo == NULL){
        printf("\nError al abrir archivo.");
        return;
    }

    while(fread(&administrador, sizeof(Administrador), 1, archivo) == 1){
        if(administrador.id_usuario == id_usuario){
            printf("\nNuevo Nivel de Acceso: ");
            scanf(" %[^\n]", administrador.nivel_acceso);
            convertirEspaciosAGuiones(administrador.nivel_acceso);

            fseek(archivo, -(long)sizeof(Administrador), SEEK_CUR);
            fwrite(&administrador, sizeof(Administrador), 1, archivo);

            printf("\nAdministrador actualizado.");
            fclose(archivo);
            return;
        }
    }

    printf("\nAdministrador no encontrado.");
    fclose(archivo);
}

/**Mostrar Cuentas*/
void listarUsuarios(){
    FILE *archivo;
    Usuario usuario;
    archivo = fopen("usuario.dat", "rb");

    if(archivo == NULL){
        printf("\nNo se pudo abrir usuario.dat\n");
        return;
    }
    printf("\n========== LISTADO DE USUARIOS ==========\n");

    while(fread(&usuario, sizeof(Usuario), 1, archivo) == 1){
        printf("ID: %d", usuario.id_usuario);
        printf("\nNombre: %s", usuario.nombre);
        printf("\nApellido: %s", usuario.apellido);
        printf("\nEmail: %s", usuario.email);
        printf("\nTelefono: %s", usuario.telefono);
        printf("\n----------------------------------\n");
    }

    fclose(archivo);
}

void seleccionarCuenta(Usuario usuario){
    FILE *archivo;
    archivo = fopen("usuario.dat", "rb");

    Usuario reg;
    int encontrado = 0;

    if(archivo == NULL){ printf("\nError al abrir archivo.\n"); }

    while(fread(&reg, sizeof(Usuario), 1, archivo) == 1){
        if( strcmp(reg.email, usuario.email) == 0 &&
            strcmp(reg.contrasena, usuario.contrasena) == 0){

            encontrado = 1;
            usuario = reg;
            break;
        }
    }
    fclose(archivo);

    if(!encontrado){
        printf("\nCorreo o contrasena incorrectos.\n");
        return;
    }
    else{
        printf("\nBienvenido %s %s\n", usuario.nombre, usuario.apellido);
    }

    system("Pause");
    system("cls");

    // Contar roles del usuario
    int cantidad_roles = contarRolesDelUsuario(usuario.id_usuario);
    int roles_actuales[4] = {0};
    obtenerRolesDelUsuario(usuario.id_usuario, roles_actuales);

    // Si tiene solo 1 rol, ir directamente a ese panel
    if(cantidad_roles == 1){
        if(roles_actuales[0]){ panelCliente(usuario); }
        else if(roles_actuales[1]){ panelEncargador(usuario); }
        else if(roles_actuales[2]){ panelRepartidor(usuario); }
        else if(roles_actuales[3]){ panelAdministrador(usuario); }
    }
    // Si tiene múltiples roles, mostrar menú de selección
    else if(cantidad_roles > 1){
        int rol_seleccionado = 0;

        printf("\n===============================\n");
        printf("\n  SELECCIONE SU ROL\n");
        printf("\n===============================\n");
        printf("\nTiene múltiples roles disponibles:\n\n");

        int contador = 1;
        if(roles_actuales[0]){ printf("[%d] Cliente\n", contador++); }
        if(roles_actuales[1]){ printf("[%d] Encargado\n", contador++); }
        if(roles_actuales[2]){ printf("[%d] Repartidor\n", contador++); }
        if(roles_actuales[3]){ printf("[%d] Administrador\n", contador++); }

        printf("\nIngrese el rol con el que desea iniciar sesión: ");

        if(scanf("%d", &rol_seleccionado) != 1){
            while (getchar() != '\n');
            rol_seleccionado = -1;
        }

        // Mapear la selección al rol correcto
        int rol_actual = 0;
        contador = 1;

        if(roles_actuales[0]){
            if(contador == rol_seleccionado){ rol_actual = 1; }
            contador++;
        }
        if(roles_actuales[1]){
            if(contador == rol_seleccionado){ rol_actual = 2; }
            contador++;
        }
        if(roles_actuales[2]){
            if(contador == rol_seleccionado){ rol_actual = 3; }
            contador++;
        }
        if(roles_actuales[3]){
            if(contador == rol_seleccionado){ rol_actual = 4; }
            contador++;
        }

        system("cls");

        if(rol_actual == 0){
            printf("\n[ERROR] Opción inválida.\n");
            system("Pause");
            return;
        }

        // Ir al panel del rol seleccionado
        switch(rol_actual){
            case 1:
                //printf("\nIngresando como Cliente...\n"); system("Pause"); system("cls");
                panelCliente(usuario);
                break;
            case 2:
                //printf("\nIngresando como Encargado...\n"); system("Pause"); system("cls");
                panelEncargador(usuario);
                break;
            case 3:
                //printf("\nIngresando como Repartidor...\n"); system("Pause"); system("cls");
                panelRepartidor(usuario);
                break;
            case 4:
                //printf("\nIngresando como Administrador...\n"); system("Pause"); system("cls");
                panelAdministrador(usuario);
                break;
        }
    }
    else{
        printf("\nAdvertencia: No se encontró rol asociado a esta cuenta.\n");
        system("Pause");
    }
}
int esCliente(int id_usuario){
    FILE *archivo;
    archivo = fopen("cliente.dat", "rb");

    Cliente cliente;

    if(archivo == NULL){
        return 0;
    }

    while(fread(&cliente, sizeof(Cliente), 1, archivo) == 1){
        if(cliente.id_usuario == id_usuario){
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}
int esEncargado(int id_usuario){
    FILE *archivo;
    archivo = fopen("encargado.dat", "rb");

    Encargado encargado;

    if(archivo == NULL){ return 0; }

    while(fread(&encargado, sizeof(Encargado), 1, archivo) == 1){
        if(encargado.id_usuario == id_usuario){
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}
int esRepartidor(int id_usuario){
    FILE *archivo;
    archivo = fopen("repartidor.dat", "rb");

    Repartidor repartidor;

    if(archivo == NULL){ return 0; }

    while(fread(&repartidor, sizeof(Repartidor), 1, archivo) == 1){
        if(repartidor.id_usuario == id_usuario){
            fclose(archivo);
            return 1;
        }
    }
    fclose(archivo);
    return 0;
}
int esAdministrador(int id_usuario){
    FILE *archivo;
    archivo = fopen("administrador.dat", "rb");

    Administrador administrador;

    if(archivo == NULL){ return 0; }

    while(fread(&administrador, sizeof(Administrador), 1, archivo) == 1){
        if(administrador.id_usuario == id_usuario){
            fclose(archivo);
            return 1;
        }
    }

    fclose(archivo);
    return 0;
}

// =========================
// FUNCIONES AUXILIARES PARA GESTIÓN DE ROLES
// =========================

int obtenerIdPorEmail(const char email[]){
    FILE *archivo;
    archivo = fopen("usuario.dat", "rb");

    Usuario usuario;

    if(archivo == NULL){ return -1; }

    while(fread(&usuario, sizeof(Usuario), 1, archivo) == 1){
        if(strcmp(usuario.email, email) == 0){
            fclose(archivo);
            return usuario.id_usuario;
        }
    }
    fclose(archivo);
    return -1;
}

int contarRolesDelUsuario(int id_usuario){
    int cantidad = 0;

    if(esCliente(id_usuario) == 1) cantidad++;
    if(esEncargado(id_usuario) == 1) cantidad++;
    if(esRepartidor(id_usuario) == 1) cantidad++;
    if(esAdministrador(id_usuario) == 1) cantidad++;

    return cantidad;
}

int tieneRol(int id_usuario, int rol){
    switch(rol){
        case 1: return esCliente(id_usuario);
        case 2: return esEncargado(id_usuario);
        case 3: return esRepartidor(id_usuario);
        case 4: return esAdministrador(id_usuario);
        default: return 0;
    }
}

void obtenerRolesDelUsuario(int id_usuario, int roles[4]){
    roles[0] = esCliente(id_usuario);      // rol 1
    roles[1] = esEncargado(id_usuario);    // rol 2
    roles[2] = esRepartidor(id_usuario);   // rol 3
    roles[3] = esAdministrador(id_usuario); // rol 4
}

void agregarRolExistente(int id_usuario){
    FILE *archivoUsuario = fopen("usuario.dat", "rb");
    Usuario usuario;
    int encontrado = 0;
    int rol;
    int roles_actuales[4] = {0};

    // Obtener datos del usuario
    if(archivoUsuario != NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archivoUsuario) == 1){
            if(usuario.id_usuario == id_usuario){
                encontrado = 1;
                break;
            }
        }
        fclose(archivoUsuario);
    }

    if(!encontrado){
        printf("\n[ERROR] No se encontró el usuario.\n");
        return;
    }

    // Obtener roles actuales
    obtenerRolesDelUsuario(id_usuario, roles_actuales);

    printf("\n===============================\n");
    printf("\n   AGREGAR NUEVO ROL\n");
    printf("\n===============================\n");
    printf("\nUsuario: %s %s\n", usuario.nombre, usuario.apellido);
    printf("Email: %s\n", usuario.email);
    printf("\nRoles actuales:\n");

    if(roles_actuales[0]) printf("  Cliente\n");
    if(roles_actuales[1]) printf("  Encargado\n");
    if(roles_actuales[2]) printf("  Repartidor\n");
    if(roles_actuales[3]) printf("  Administrador\n");

    printf("\nRoles disponibles:\n");

    if(!roles_actuales[0]) printf("[1] Cliente\n");
    if(!roles_actuales[1]) printf("[2] Encargado\n");
    if(!roles_actuales[2]) printf("[3] Repartidor\n");
    if(!roles_actuales[3]) printf("[4] Administrador\n");

    printf("\nIngrese el rol a agregar: ");

    if(scanf("%d", &rol) != 1){
        while (getchar() != '\n');
        rol = -1;
    }

    if (rol < 1 || rol > 4) {
        printf("\n[ERROR] Opción inválida.\n");
        return;
    }

    // Verificar que no tenga ya ese rol
    if(tieneRol(id_usuario, rol)){
        printf("\n[ERROR] Este usuario ya tiene este rol.\n");
        return;
    }

    // Agregar el nuevo rol
    usuario.id_usuario = id_usuario;

    switch(rol){
        case 1:{
            FILE *archivoCliente = fopen("cliente.dat", "ab");
            if(archivoCliente != NULL){
                Cliente cliente;
                cliente.id_usuario = id_usuario;
                printf("\nIngrese Direccion: ");
                scanf(" %[^\n]", cliente.direccion);
                convertirEspaciosAGuiones(cliente.direccion);
                int resultado = fwrite(&cliente, sizeof(Cliente), 1, archivoCliente);
                fflush(archivoCliente);
                fclose(archivoCliente);
                if(resultado == 1){
                    printf("\nRol Cliente agregado exitosamente.\n");
                } else {
                    printf("\n[ERROR] Fallo al escribir rol de cliente.\n");
                }
            } else {
                printf("\n[ERROR] No se pudo abrir archivo de clientes.\n");
            }
            break;
        }
        case 2:{
            FILE *archivoEncargado = fopen("encargado.dat", "ab");
            if(archivoEncargado != NULL){
                Encargado encargado;
                encargado.id_usuario = id_usuario;
                printf("\nIngrese ID del Restaurante: ");
                scanf("%d", &encargado.id_restaurante);
                printf("Ingrese Turno: ");
                scanf(" %[^\n]", encargado.turno);
                convertirEspaciosAGuiones(encargado.turno);
                int resultado = fwrite(&encargado, sizeof(Encargado), 1, archivoEncargado);
                fflush(archivoEncargado);
                fclose(archivoEncargado);
                if(resultado == 1){
                    printf("\nRol Encargado agregado exitosamente.\n");
                } else {
                    printf("\n[ERROR] Fallo al escribir rol de encargado.\n");
                }
            } else {
                printf("\n[ERROR] No se pudo abrir archivo de encargados.\n");
            }
            break;
        }
        case 3:{
            FILE *archivoRepartidor = fopen("repartidor.dat", "ab");
            if(archivoRepartidor != NULL){
                Repartidor repartidor;
                repartidor.id_usuario = id_usuario;
                printf("\nIngrese Vehiculo: ");
                scanf(" %[^\n]", repartidor.vehiculo);
                convertirEspaciosAGuiones(repartidor.vehiculo);
                printf("Ingrese Estado de Disponibilidad: ");
                scanf(" %[^\n]", repartidor.estado_disponibilidad);
                convertirEspaciosAGuiones(repartidor.estado_disponibilidad);
                int resultado = fwrite(&repartidor, sizeof(Repartidor), 1, archivoRepartidor);
                fflush(archivoRepartidor);
                fclose(archivoRepartidor);
                if(resultado == 1){
                    printf("\nRol Repartidor agregado exitosamente.\n");
                } else {
                    printf("\n[ERROR] Fallo al escribir rol de repartidor.\n");
                }
            } else {
                printf("\n[ERROR] No se pudo abrir archivo de repartidores.\n");
            }
            break;
        }
        case 4:{
            FILE *archivoAdministrador = fopen("administrador.dat", "ab");
            if(archivoAdministrador != NULL){
                Administrador administrador;
                administrador.id_usuario = id_usuario;
                printf("\nIngrese Nivel de Acceso (superadmin, admin, supervisor): ");
                scanf(" %[^\n]", administrador.nivel_acceso);
                convertirEspaciosAGuiones(administrador.nivel_acceso);
                int resultado = fwrite(&administrador, sizeof(Administrador), 1, archivoAdministrador);
                fflush(archivoAdministrador);
                fclose(archivoAdministrador);
                if(resultado == 1){
                    printf("\nRol Administrador agregado exitosamente.\n");
                } else {
                    printf("\n[ERROR] Fallo al escribir rol de administrador.\n");
                }
            } else {
                printf("\n[ERROR] No se pudo abrir archivo de administradores.\n");
            }
            break;
        }
    }
}

// =========================
// ELIMINACIÓN CON CONFIRMACIÓN (PARA ADMINISTRADOR)
// =========================

void eliminarUsuarioPorId(Usuario usuario_actual){
    int id_a_eliminar;
    int confirmacion;
    FILE *archivo;
    Usuario usuario;
    int encontrado = 0;

    printf("\n===============================\n");
    printf("\n   ELIMINAR USUARIO\n");
    printf("\n===============================\n");

    printf("\nIngrese el ID del usuario a eliminar: ");
    scanf("%d", &id_a_eliminar);

    // Buscar el usuario
    archivo = fopen("usuario.dat", "rb");
    if(archivo == NULL){
        printf("\n[ERROR] No se puede abrir archivo de usuarios.\n");
        return;
    }

    while(fread(&usuario, sizeof(Usuario), 1, archivo) == 1){
        if(usuario.id_usuario == id_a_eliminar){
            encontrado = 1;
            break;
        }
    }
    fclose(archivo);

    if(!encontrado){
        printf("\n[ERROR] Usuario con ID %d no encontrado.\n", id_a_eliminar);
        return;
    }

    // Prevenir auto-eliminación
    if(usuario.id_usuario == usuario_actual.id_usuario){
        printf("\n[ERROR] No puedes eliminar tu propio usuario.\n");
        system("pause");
        return;
    }

    // Mostrar datos y pedir confirmación
    printf("\n====== CONFIRMAR ELIMINACIÓN ======\n");
    printf("\n¿Desea eliminar este usuario?\n");
    printf("  Nombre: %s %s\n", usuario.nombre, usuario.apellido);
    printf("  Email: %s\n", usuario.email);
    printf("  ID: %d\n", usuario.id_usuario);
    printf("\nEsta acción NO se puede deshacer.\n");
    printf("\n[1] SÍ, eliminar usuario\n");
    printf("[2] NO, cancelar\n");
    printf("\nOpción: ");
    
    scanf("%d", &confirmacion);

    if(confirmacion != 1){
        printf("\n✓ Operación cancelada.\n");
        system("pause");
        return;
    }

    // Eliminar el usuario
    FILE *auxiliar;
    Usuario reg;
    int eliminado = 0;

    archivo = fopen("usuario.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\n[ERROR] No se pueden abrir los archivos.\n");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&reg, sizeof(Usuario), 1, archivo) == 1){
        if(reg.id_usuario == id_a_eliminar){
            // Eliminar también de los archivos de roles
            eliminarCliente(reg.id_usuario);
            eliminarEncargado(reg.id_usuario);
            eliminarRepartidor(reg.id_usuario);
            eliminarAdministrador(reg.id_usuario);
            eliminado = 1;
        }
        else{
            fwrite(&reg, sizeof(Usuario), 1, auxiliar);
        }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("usuario.dat");
    rename("auxiliar.dat", "usuario.dat");

    if(eliminado){
        printf("\n✓ Usuario eliminado correctamente.\n");
    } else {
        printf("\n[ERROR] No se pudo eliminar el usuario.\n");
    }
    
    system("pause");
}

void eliminarRestaurantePorId(){
    int id_a_eliminar;
    int confirmacion;
    FILE *archivo;
    Restaurante restaurante;
    int encontrado = 0;

    printf("\n===============================\n");
    printf("\n   ELIMINAR RESTAURANTE\n");
    printf("\n===============================\n");

    printf("\nIngrese el ID del restaurante a eliminar: ");
    scanf("%d", &id_a_eliminar);

    // Buscar el restaurante
    archivo = fopen("restaurante.dat", "rb");
    if(archivo == NULL){
        printf("\n[ERROR] No se puede abrir archivo de restaurantes.\n");
        return;
    }

    while(fread(&restaurante, sizeof(Restaurante), 1, archivo) == 1){
        if(restaurante.id_restaurante == id_a_eliminar){
            encontrado = 1;
            break;
        }
    }
    fclose(archivo);

    if(!encontrado){
        printf("\n[ERROR] Restaurante con ID %d no encontrado.\n", id_a_eliminar);
        return;
    }

    // Mostrar datos y pedir confirmación
    printf("\n====== CONFIRMAR ELIMINACIÓN ======\n");
    printf("\n¿Desea eliminar este restaurante?\n");
    printf("  Nombre: %s\n", restaurante.nombre);
    printf("  Teléfono: %s\n", restaurante.telefono);
    printf("  Estado: %s\n", restaurante.estado);
    printf("  ID: %d\n", restaurante.id_restaurante);
    printf("\nEsta acción NO se puede deshacer.\n");
    printf("\n[1] SÍ, eliminar restaurante\n");
    printf("[2] NO, cancelar\n");
    printf("\nOpción: ");
    
    scanf("%d", &confirmacion);

    if(confirmacion != 1){
        printf("\n✓ Operación cancelada.\n");
        system("pause");
        return;
    }

    // Eliminar el restaurante
    FILE *auxiliar;
    Restaurante reg;
    int eliminado = 0;

    archivo = fopen("restaurante.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\n[ERROR] No se pueden abrir los archivos.\n");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&reg, sizeof(Restaurante), 1, archivo) == 1){
        if(reg.id_restaurante == id_a_eliminar){
            eliminado = 1;
            // También se podría eliminar ubicación asociada
        }
        else{
            fwrite(&reg, sizeof(Restaurante), 1, auxiliar);
        }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("restaurante.dat");
    rename("auxiliar.dat", "restaurante.dat");

    if(eliminado){
        printf("\n✓ Restaurante eliminado correctamente.\n");
    } else {
        printf("\n[ERROR] No se pudo eliminar el restaurante.\n");
    }
    
    system("pause");
}

// =========================
// RESTAURANTES Y PRODUCTOS
// =========================

//PANEL PARA ADMINISTRADOR
//Agregar
void agregarRestaurante(){
    Restaurante restaurante;

    printf("\n===============================\n");
    printf("\n     INGRESAR RESTAURANTES\n");
    printf("\n===============================\n");

    // Validar Nombre del Restaurante
    do {
        printf("\nIngrese Nombre: ");
        scanf(" %[^\n]", restaurante.nombre);
        convertirEspaciosAGuiones(restaurante.nombre);
        if (!validarNombre(restaurante.nombre)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Teléfono
    do {
        printf("\nIngrese Telefono: ");
        scanf(" %[^\n]", restaurante.telefono);
        convertirEspaciosAGuiones(restaurante.telefono);
        if (!validarTelefono(restaurante.telefono)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Horario de Apertura
    do {
        printf("\nIngrese Horario de Apertura (HH:MM): ");
        scanf(" %[^\n]", restaurante.horario_apertura);
        convertirEspaciosAGuiones(restaurante.horario_apertura);
        if (!validarHorario(restaurante.horario_apertura)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Horario de Cierre
    do {
        printf("\nIngrese Horario de Cierre (HH:MM): ");
        scanf(" %[^\n]", restaurante.horario_cierre);
        convertirEspaciosAGuiones(restaurante.horario_cierre);
        if (!validarHorario(restaurante.horario_cierre)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Estado
    do {
        printf("\nIngrese Estado (activo/inactivo/mantenimiento): ");
        scanf(" %[^\n]", restaurante.estado);
        convertirEspaciosAGuiones(restaurante.estado);
        if (!validarEstadoRestaurante(restaurante.estado)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    agregarUbicacionRestaurante(restaurante);
}
void agregarUbicacionRestaurante(Restaurante restaurante){
    FILE *archivoRestaurante;
    FILE *archivoUbicacion;

    Restaurante auxRestaurante;
    UbicacionRestaurante ubicacion;

    int ultimoId = 0;

    archivoRestaurante = fopen("restaurante.dat", "rb");

    if(archivoRestaurante != NULL){
        while(fread(&auxRestaurante, sizeof(Restaurante), 1, archivoRestaurante) == 1){
            if(auxRestaurante.id_restaurante > ultimoId){
                ultimoId = auxRestaurante.id_restaurante;
            }
        } fclose(archivoRestaurante);
    }

    restaurante.id_restaurante = ultimoId + 1;

    ubicacion.id_ubicacion = restaurante.id_restaurante;
    ubicacion.id_restaurante = restaurante.id_restaurante;

    printf("\n===============================\n");
    printf("\nINGRESAR UBICACION: %s\n", restaurante.nombre);
    printf("\n===============================\n");

    printf("\nIngrese Direccion: ");
    scanf(" %[^\n]", ubicacion.direccion);
    convertirEspaciosAGuiones(ubicacion.direccion);

    printf("\nIngrese Numero: ");
    scanf("%d", &ubicacion.numero);

    printf("\nIngrese Ciudad: ");
    scanf(" %[^\n]", ubicacion.ciudad);
    convertirEspaciosAGuiones(ubicacion.ciudad);

    printf("\nIngrese Provincia: ");
    scanf(" %[^\n]", ubicacion.provincia);
    convertirEspaciosAGuiones(ubicacion.provincia);

    printf("\nIngrese Codigo Postal: ");
    scanf(" %[^\n]", ubicacion.codigo_postal);
    convertirEspaciosAGuiones(ubicacion.codigo_postal);

    archivoRestaurante = fopen("restaurante.dat", "ab");
    archivoUbicacion = fopen("ubicacion_restaurante.dat", "ab");

    if(archivoRestaurante != NULL && archivoUbicacion != NULL){
        fwrite(&restaurante, sizeof(Restaurante), 1, archivoRestaurante);
        fwrite(&ubicacion, sizeof(UbicacionRestaurante), 1, archivoUbicacion);

        fclose(archivoRestaurante);
        fclose(archivoUbicacion);

        printf("\nRestaurante agregado correctamente.");
        printf("\nID asignado: %d\n", restaurante.id_restaurante);
    } else{
        printf("\nError al abrir archivos.");

        if(archivoRestaurante != NULL)
            fclose(archivoRestaurante);

        if(archivoUbicacion != NULL)
            fclose(archivoUbicacion);
    }
}
//Eliminar
void eliminarRestaurante(Restaurante restaurante);
void eliminarUbicacionRestaurante(int id_ubicacion);
//Actualizar
void actualizarRestauranteXid(Restaurante restaurante);
void actualizarUbicacionRestauranteXid(int id_ubicacion);
//Mostrar - Listar
void listarRestaurantes(){
    FILE *archivo;
    Restaurante restaurante;

    archivo = fopen("restaurante.dat", "rb");

    if(archivo == NULL){
        printf("\nNo se pudo abrir restaurante.dat\n");
        return;
    }

    printf("\n========== LISTADO DE RESTAURANTES ==========\n");

    while(fread(&restaurante, sizeof(Restaurante), 1, archivo) == 1){

        printf("ID Restaurante: %d", restaurante.id_restaurante);
        printf("\nNombre: %s", restaurante.nombre);
        printf("\nTelefono: %s", restaurante.telefono);
        printf("\nHorario Apertura: %s", restaurante.horario_apertura);
        printf("\nHorario Cierre: %s", restaurante.horario_cierre);
        printf("\nEstado: %s\n", restaurante.estado);

        //printf("\n----------------------------------");
        listarUbicacionesRestaurante(restaurante.id_restaurante);
        printf("\n----------------------------------\n");
    }

    fclose(archivo);
}
void listarUbicacionesRestaurante(int id_restaurante){
    FILE *archivo;
    UbicacionRestaurante ubicacion;

    archivo = fopen("ubicacion_restaurante.dat", "rb");

    if(archivo == NULL){
        printf("\nNo se pudo abrir ubicacion_restaurante.dat\n");
        return;
    }

    while(fread(&ubicacion, sizeof(UbicacionRestaurante), 1, archivo) == 1){

        if(ubicacion.id_restaurante == id_restaurante){

            printf("\n--- Ubicacion ---");
            printf("\nID Ubicacion: %d", ubicacion.id_ubicacion);
            printf("\nDireccion: %s", ubicacion.direccion);
            printf("\nNumero: %d", ubicacion.numero);
            printf("\nCiudad: %s", ubicacion.ciudad);
            printf("\nProvincia: %s", ubicacion.provincia);
            printf("\nCodigo Postal: %s", ubicacion.codigo_postal);
            break;
        }
    }

    fclose(archivo);
}

// =========================
// MENÚ Y PRODUCTOS (ENCARGADO)
// =========================

void agregarProducto(int id_restaurante){
    FILE *archivoProducto;
    Producto producto;
    int ultimoId = 0;

    printf("\n===============================\n");
    printf("\n     AGREGAR PRODUCTO\n");
    printf("\n===============================\n");

    // Validar nombre del producto
    do {
        printf("\nIngrese Nombre del Producto: ");
        scanf(" %[^\n]", producto.nombre_producto);
        convertirEspaciosAGuiones(producto.nombre_producto);
        if (!validarNombre(producto.nombre_producto)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar descripción
    printf("\nIngrese Descripción (max 500 caracteres): ");
    scanf(" %[^\n]", producto.descripcion);
    convertirEspaciosAGuiones(producto.descripcion);

    // Validar precio
    do {
        printf("\nIngrese Precio: $");
        if(scanf("%lf", &producto.precio) != 1 || producto.precio <= 0) {
            while(getchar() != '\n');
            printf("[ERROR] Precio debe ser mayor a 0. [REINTENTE] ");
        } else {
            while(getchar() != '\n');
            break;
        }
    } while(1);

    // Validar categoría
    printf("\nIngrese Categoría: ");
    scanf(" %[^\n]", producto.categoria);
    convertirEspaciosAGuiones(producto.categoria);

    // Obtener próximo ID
    archivoProducto = fopen("producto.dat", "rb");
    if(archivoProducto != NULL){
        Producto auxProducto;
        while(fread(&auxProducto, sizeof(Producto), 1, archivoProducto) == 1){
            if(auxProducto.id_producto > ultimoId){
                ultimoId = auxProducto.id_producto;
            }
        }
        fclose(archivoProducto);
    }

    producto.id_producto = ultimoId + 1;
    producto.id_menu = id_restaurante;
    strcpy(producto.disponibilidad, "disponible");

    // Guardar producto
    archivoProducto = fopen("producto.dat", "ab");
    if(archivoProducto != NULL){
        int resultado = fwrite(&producto, sizeof(Producto), 1, archivoProducto);
        fflush(archivoProducto);
        fclose(archivoProducto);
        if(resultado == 1){
            printf("\n✓ Producto agregado exitosamente.\n");
            printf("  ID: %d\n", producto.id_producto);
        } else {
            printf("\n[ERROR] Fallo al guardar producto.\n");
        }
    } else {
        printf("\n[ERROR] No se pudo abrir archivo de productos.\n");
    }
}

void listarProductosRestaurante(int id_restaurante){
    FILE *archivo;
    Producto producto;
    int cantidad = 0;

    printf("\n===============================\n");
    printf("\n   MENÚ DEL RESTAURANTE\n");
    printf("\n===============================\n");

    archivo = fopen("producto.dat", "rb");
    if(archivo == NULL){
        printf("\nNo hay productos disponibles aún.\n");
        return;
    }

    while(fread(&producto, sizeof(Producto), 1, archivo) == 1){
        if(producto.id_menu == id_restaurante && strcmp(producto.disponibilidad, "disponible") == 0){
            cantidad++;
            printf("\n[%d] %s", producto.id_producto, producto.nombre_producto);
            printf("\n    Descripción: %s", producto.descripcion);
            printf("\n    Precio: $%.2f", producto.precio);
            printf("\n    Categoría: %s", producto.categoria);
            printf("\n    Estado: %s", producto.disponibilidad);
        }
    }

    if(cantidad == 0){
        printf("\nNo hay productos disponibles.\n");
    } else {
        printf("\n\nTotal de productos: %d\n", cantidad);
    }

    fclose(archivo);
}

void modificarProducto(int id_restaurante){
    FILE *archivo;
    FILE *auxiliar;
    Producto producto;
    int id_buscar;
    int encontrado = 0;
    int opcion;

    printf("\n===============================\n");
    printf("\n   MODIFICAR PRODUCTO\n");
    printf("\n===============================\n");

    printf("\nIngrese ID del producto a modificar: ");
    scanf("%d", &id_buscar);

    archivo = fopen("producto.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\n[ERROR] No se pueden abrir los archivos.\n");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&producto, sizeof(Producto), 1, archivo) == 1){
        if(producto.id_producto == id_buscar && producto.id_menu == id_restaurante){
            encontrado = 1;
            printf("\n✓ Producto encontrado: %s\n", producto.nombre_producto);
            printf("\n¿Qué deseas modificar?\n");
            printf("[1] Nombre\n");
            printf("[2] Descripción\n");
            printf("[3] Precio\n");
            printf("[4] Categoría\n");
            printf("[5] Disponibilidad\n");
            printf("[6] Cancelar\n");
            printf("Opción: ");
            scanf("%d", &opcion);

            switch(opcion){
                case 1:
                    printf("\nNuevo nombre: ");
                    scanf(" %[^\n]", producto.nombre_producto);
                    convertirEspaciosAGuiones(producto.nombre_producto);
                    break;
                case 2:
                    printf("\nNueva descripción: ");
                    scanf(" %[^\n]", producto.descripcion);
                    convertirEspaciosAGuiones(producto.descripcion);
                    break;
                case 3:
                    printf("\nNuevo precio: $");
                    scanf("%lf", &producto.precio);
                    break;
                case 4:
                    printf("\nNueva categoría: ");
                    scanf(" %[^\n]", producto.categoria);
                    convertirEspaciosAGuiones(producto.categoria);
                    break;
                case 5:
                    printf("\nNuevo estado (disponible/inactivo): ");
                    scanf(" %[^\n]", producto.disponibilidad);
                    convertirEspaciosAGuiones(producto.disponibilidad);
                    break;
                case 6:
                    printf("\nOperación cancelada.\n");
                    break;
            }
        }

        fwrite(&producto, sizeof(Producto), 1, auxiliar);
    }

    fclose(archivo);
    fclose(auxiliar);

    if(encontrado){
        remove("producto.dat");
        rename("auxiliar.dat", "producto.dat");
        printf("\n✓ Producto modificado exitosamente.\n");
    } else {
        remove("auxiliar.dat");
        printf("\n[ERROR] Producto no encontrado.\n");
    }
}

void listarProductos(){
    FILE *archivo;
    Producto producto;

    printf("\n========== LISTADO DE TODOS LOS PRODUCTOS ==========\n");

    archivo = fopen("producto.dat", "rb");
    if(archivo == NULL){
        printf("\nNo hay productos en el sistema.\n");
        return;
    }

    while(fread(&producto, sizeof(Producto), 1, archivo) == 1){
        printf("\n[%d] %s (Menu ID: %d)", producto.id_producto, producto.nombre_producto, producto.id_menu);
        printf("\n    Descripción: %s", producto.descripcion);
        printf("\n    Precio: $%.2f", producto.precio);
        printf("\n    Categoría: %s | Estado: %s\n", producto.categoria, producto.disponibilidad);
    }

    fclose(archivo);
}

//PANEL PARA ENCARGADO
//Stub functions (now implemented above)
void agregarMenu(Menu menu);
void eliminarMenu();
void actualizarMenuXid();
void listarMenus();

// =========================
// PEDIDOS Y ENTREGAS
// =========================

// Función auxiliar para obtener siguiente ID
int obtenerSiguientePedidoId(){
    FILE *archivo = fopen("pedido.dat", "rb");
    Pedido pedido;
    int maxId = 0;
    
    if(archivo != NULL){
        while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
            if(pedido.id_pedido > maxId){
                maxId = pedido.id_pedido;
            }
        }
        fclose(archivo);
    }
    return maxId + 1;
}

// CLIENTE: Realizar Pedido
void agregarPedido(Usuario usuario){
    Pedido pedido;
    Restaurante restaurante;
    FILE *archivoRestaurante, *archivoPedido, *archivoOrden, *archivoHistorial;
    int id_restaurante = -1;
    int cantidad_restaurantes = 0;
    int seleccion = 0;

    printf("\n===============================\n");
    printf("\n     REALIZAR PEDIDO\n");
    printf("\n===============================\n");

    // Listar restaurantes disponibles
    archivoRestaurante = fopen("restaurante.dat", "rb");
    if(archivoRestaurante == NULL || (fseek(archivoRestaurante, 0, SEEK_END) == 0 && ftell(archivoRestaurante) == 0)){
        printf("\n[ERROR] No hay restaurantes disponibles.\n");
        if(archivoRestaurante != NULL) fclose(archivoRestaurante);
        return;
    }

    printf("\nRestaurantes disponibles:\n");
    fseek(archivoRestaurante, 0, SEEK_SET);
    
    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurante) == 1){
        cantidad_restaurantes++;
        printf("[%d] %s - %s\n", restaurante.id_restaurante, restaurante.nombre, restaurante.estado);
    }
    fclose(archivoRestaurante);

    if(cantidad_restaurantes == 0){
        printf("\n[ERROR] No hay restaurantes disponibles.\n");
        return;
    }

    printf("\nSeleccione ID de restaurante: ");
    scanf("%d", &seleccion);

    // Verificar que exista el restaurante
    archivoRestaurante = fopen("restaurante.dat", "rb");
    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurante) == 1){
        if(restaurante.id_restaurante == seleccion){
            id_restaurante = restaurante.id_restaurante;
            break;
        }
    }
    fclose(archivoRestaurante);

    if(id_restaurante == -1){
        printf("\n[ERROR] Restaurante no encontrado.\n");
        return;
    }

    // Mostrar menú del restaurante
    printf("\n--- Productos Disponibles ---\n");
    FILE *archivoProducto = fopen("producto.dat", "rb");
    Producto producto;

    while(fread(&producto, sizeof(Producto), 1, archivoProducto) == 1){
        if(producto.id_menu == id_restaurante && strcmp(producto.disponibilidad, "disponible") == 0){
            printf("\n[%d] %s - $%.2f", producto.id_producto, producto.nombre_producto, producto.precio);
        }
    }
    fclose(archivoProducto);

    // Crear nuevo Pedido
    pedido.id_pedido = obtenerSiguientePedidoId();
    pedido.id_cliente = usuario.id_usuario;
    pedido.id_repartidor = -1;  // Se asignará después
    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    strftime(pedido.fecha_pedido, 20, "%Y-%m-%d", info);
    strcpy(pedido.estado, "Pendiente");

    // Ingresar datos de entrega
    printf("\n\n--- DATOS DE ENTREGA ---\n");
    printf("Dirección: ");
    scanf(" %[^\n]", pedido.direccion_entrega);
    convertirEspaciosAGuiones(pedido.direccion_entrega);

    printf("Observaciones: ");
    scanf(" %[^\n]", pedido.observaciones);
    convertirEspaciosAGuiones(pedido.observaciones);

    // Guardar Pedido
    archivoPedido = fopen("pedido.dat", "ab");
    if(archivoPedido != NULL){
        fwrite(&pedido, sizeof(Pedido), 1, archivoPedido);
        fflush(archivoPedido);
        fclose(archivoPedido);
    }

    // Crear Orden de Preparación
    OrdenPreparacion orden;
    orden.id_orden = pedido.id_pedido;  // Mismo ID del pedido
    orden.id_pedido = pedido.id_pedido;
    strcpy(orden.fecha_creacion, pedido.fecha_pedido);
    strcpy(orden.estado_preparacion, "Pendiente");

    archivoOrden = fopen("orden_preparacion.dat", "ab");
    if(archivoOrden != NULL){
        fwrite(&orden, sizeof(OrdenPreparacion), 1, archivoOrden);
        fflush(archivoOrden);
        fclose(archivoOrden);
    }

    // Crear Historial de Estado inicial
    HistorialEstado historial;
    historial.id_historial = pedido.id_pedido;
    historial.id_pedido = pedido.id_pedido;
    strcpy(historial.estado, "Pendiente");
    strcpy(historial.fecha_actualizacion, pedido.fecha_pedido);

    archivoHistorial = fopen("historial_estado.dat", "ab");
    if(archivoHistorial != NULL){
        fwrite(&historial, sizeof(HistorialEstado), 1, archivoHistorial);
        fflush(archivoHistorial);
        fclose(archivoHistorial);
    }

    printf("\n✓ Pedido creado exitosamente.\n");
    printf("  ID Pedido: %d\n", pedido.id_pedido);
    printf("  Estado: %s\n", pedido.estado);
}

// CLIENTE: Ver mis pedidos
void listarMisPedidos(Usuario usuario){
    FILE *archivo;
    Pedido pedido;
    int cantidad = 0;

    printf("\n===============================\n");
    printf("\n      MIS PEDIDOS\n");
    printf("\n===============================\n");

    archivo = fopen("pedido.dat", "rb");
    if(archivo == NULL){
        printf("\nNo tienes pedidos.\n");
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
        if(pedido.id_cliente == usuario.id_usuario){
            cantidad++;
            printf("\n[%d] Fecha: %s", pedido.id_pedido, pedido.fecha_pedido);
            printf("\n    Estado: %s", pedido.estado);
            printf("\n    Dirección: %s\n", pedido.direccion_entrega);
        }
    }

    if(cantidad == 0){
        printf("\nNo tienes pedidos registrados.\n");
    } else {
        printf("\nTotal de pedidos: %d\n", cantidad);
    }

    fclose(archivo);
}

// Ver historial de estados de un pedido
void obtenerHistorialEstados(int id_pedido){
    FILE *archivo;
    HistorialEstado historial;

    printf("\n--- Historial de Estados (Pedido #%d) ---\n", id_pedido);

    archivo = fopen("historial_estado.dat", "rb");
    if(archivo == NULL){
        printf("\nNo hay historial disponible.\n");
        return;
    }

    while(fread(&historial, sizeof(HistorialEstado), 1, archivo) == 1){
        if(historial.id_pedido == id_pedido){
            printf("\n→ %s (%s %s)", historial.estado, historial.fecha_actualizacion, historial.hora_actualizacion);
        }
    }

    fclose(archivo);
}

// =====================================
// PAGOS
// =====================================

int obtenerSiguientePagoId(){
    FILE *archivo = fopen("pago.dat", "rb");
    Pago pago;
    int maxId = 0;
    
    if(archivo != NULL){
        while(fread(&pago, sizeof(Pago), 1, archivo) == 1){
            if(pago.id_pago > maxId){
                maxId = pago.id_pago;
            }
        }
        fclose(archivo);
    }
    return maxId + 1;
}

// CLIENTE: Realizar Pago
void realizarPago(Usuario usuario, int id_pedido){
    Pago pago;
    Pedido pedido;
    FILE *archivoPago, *archivoPedido;
    int metodo_pago = 0;
    int encontrado = 0;

    printf("\n===============================\n");
    printf("\n     REALIZAR PAGO\n");
    printf("\n===============================\n");

    // Verificar que el pedido pertenezca al usuario
    archivoPedido = fopen("pedido.dat", "rb");
    if(archivoPedido == NULL){
        printf("\n[ERROR] No se encontraron pedidos.\n");
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivoPedido) == 1){
        if(pedido.id_pedido == id_pedido && pedido.id_cliente == usuario.id_usuario){
            encontrado = 1;
            break;
        }
    }
    fclose(archivoPedido);

    if(!encontrado){
        printf("\n[ERROR] Pedido no encontrado o no pertenece a tu cuenta.\n");
        return;
    }

    printf("\nSelecciona método de pago:");
    printf("\n[1] Efectivo");
    printf("\n[2] Tarjeta de Débito");
    printf("\n[3] Tarjeta de Crédito");
    printf("\n[4] Billetera Digital");
    printf("\nOpción: ");
    scanf("%d", &metodo_pago);

    // Crear registro de pago
    pago.id_pago = obtenerSiguientePagoId();
    pago.id_pedido = id_pedido;
    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    strftime(pago.fecha_pago, 20, "%Y-%m-%d", info);
    pago.monto_total = pedido.total > 0 ? pedido.total : 0.0;
    strcpy(pago.estado_pago, "Pendiente");

    switch(metodo_pago){
        case 1:
            strcpy(pago.metodo_pago, "Efectivo");
            strcpy(pago.estado_pago, "Pendiente");
            break;
        case 2:
            strcpy(pago.metodo_pago, "Tarjeta_Débito");
            strcpy(pago.estado_pago, "Procesando");
            break;
        case 3:
            strcpy(pago.metodo_pago, "Tarjeta_Crédito");
            strcpy(pago.estado_pago, "Procesando");
            break;
        case 4:
            strcpy(pago.metodo_pago, "Billetera_Digital");
            strcpy(pago.estado_pago, "Procesando");
            break;
        default:
            printf("\n[ERROR] Opción no válida.\n");
            return;
    }

    // Guardar pago
    archivoPago = fopen("pago.dat", "ab");
    if(archivoPago != NULL){
        fwrite(&pago, sizeof(Pago), 1, archivoPago);
        fflush(archivoPago);
        fclose(archivoPago);

        printf("\n✓ Pago registrado exitosamente.\n");
        printf("  ID Pago: %d\n", pago.id_pago);
        printf("  Método: %s\n", pago.metodo_pago);
        printf("  Estado: %s\n", pago.estado_pago);
        printf("  Monto: $%.2f\n", pago.monto_total);
    } else {
        printf("\n[ERROR] No se pudo guardar el pago.\n");
    }
}

//Placeholder stubs for remaining functions
void listarPedidos();
void listarHistorialEstados();
void listarOrdenesPreparacion();
void listarDetallesOrden();

// =========================
// ATENCION AL CLIENTE - Esto dejamos al ultimo
// =========================

void agregarCalificacion(Usuario usuario);
void agregarReclamo(Usuario usuario);
void agregarConsulta(Usuario usuario);

void eliminarCalificacion(int id_calificacion);
void eliminarReclamo(int id_reclamo);
void eliminarConsulta(int id_consulta);

void actualizarCalificacionXid(int id_calificacion);
void actualizarReclamoXid(int id_reclamo);
void actualizarConsultaXid(int id_consulta);

void listarCalificaciones();
void listarReclamos();
void listarConsultas();

// =========================
// PAGOS Y FACTURACION
// =========================

void agregarPago(Pedido pedido);
void agregarTransaccion(Pago pago);
void agregarComision(Pago pago);
void agregarRecibo(Pago pago);

void eliminarPago(int id_pago);
void eliminarTransaccion(int id_transaccion);
void eliminarComision(int id_comision);
void eliminarRecibo(int id_recibo);

void actualizarPagoXid(int id_pago);
void actualizarTransaccionXid(int id_transaccion);
void actualizarComisionXid(int id_comision);
void actualizarReciboXid(int id_recibo);

void listarPagos();
void listarTransacciones();
void listarComisiones();
void listarRecibos();

// =========================
// ADMINISTRACION
// =========================

void agregarSolicitudInforme(Usuario usuario);
void eliminarSolicitudInforme(int id_solicitud);
void actualizarSolicitudInformeXid(int id_solicitud);
void listarSolicitudesInforme();
