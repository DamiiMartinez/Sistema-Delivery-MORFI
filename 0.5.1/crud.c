#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "crud.h"
#include "BBD.h"

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

    archivo = fopen("comision.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("pago_restaurante.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("ingreso_repartidor.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("calificacion.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    printf("\nBase de datos inicializada correctamente.\n");
}

/** Agregar Usuarios*/
void agregarUsuario(Usuario usuario, int opcion_app){
    int rol;
    int id_usuario_existente;

    char roles[4][50]={
        "\n[1] Cliente\n",
        "[2] Encargado\n",
        "[3] Repartidor\n",
        "[4] Administrador\n",
    };
    int opcion_menu = 0;
    int rol_asignar = 0;

    // Mapeo de opción a rol
    if(opcion_app == 1) rol_asignar = 0;      // Cliente
    else if(opcion_app == 2) rol_asignar = 2; // Repartidor
    else if(opcion_app == 3) rol_asignar = 1; // Encargado
    else if(opcion_app == 4) rol_asignar = 3; // Admin

    char nombre_rol[20];
    switch(opcion_app){
        case 1: strcpy(nombre_rol, "Cliente"); break;
        case 2: strcpy(nombre_rol, "Repartidor"); break;
        case 3: strcpy(nombre_rol, "Encargado"); break;
        case 4: strcpy(nombre_rol, "Administrador"); break;
    }
    printf("\n===============================\n");
    printf("\n   REGISTRAR USUARIO\n");
    printf("\n===============================\n");
    // Validar Email PRIMERO
    do {
        printf("\nIngrese Correo: ");
        scanf(" %[^\n]", usuario.email);
        if (!validarEmail(usuario.email)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Verificar si el email ya existe
    id_usuario_existente = obtenerIdPorEmail(usuario.email);

    if(id_usuario_existente != -1){
        // El email ya existe - verificar si ya tiene este rol
        int roles_actuales[4] = {0};
        obtenerRolesDelUsuario(id_usuario_existente, roles_actuales);

        if(roles_actuales[rol_asignar]){
            // Ya tiene este rol
            printf("\n===============================\n");
            printf("\n    USUARIO YA EXISTE\n");
            printf("\n===============================\n");
            printf("\nEsta cuenta ya tiene el rol de %s.\n", nombre_rol);
            printf("No se puede registrar nuevamente.\n");
            return;
        } else {
            // Tiene usuario pero no este rol - agregar rol
            printf("\n===============================\n");
            printf("\n  USUARIO EXISTENTE - AGREGAR ROL\n");
            printf("\n===============================\n");
            printf("\nEsta cuenta ya existe con otros roles.\n");
            printf("¿Desea agregar el rol de %s? [1] SÍ [2] NO: ", nombre_rol);

            if(scanf("%d", &opcion_menu) != 1){
                while (getchar() != '\n');
                opcion_menu = 0;
            }

            if(opcion_menu == 1){
                agregarRolEspecifico(id_usuario_existente, opcion_app);
                printf("\n✓ Rol de %s agregado exitosamente.\n", nombre_rol);
                return;
            } else {
                printf("\nOperación cancelada.\n");
                return;
            }
        }
    }

    // El email NO existe - crear nuevo usuario

    // Validar Contraseña
    do {
        printf("\nIngrese Contraseña: ");
        scanf(" %[^\n]", usuario.contrasena);
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
        if (!validarTelefono(usuario.telefono)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    strcpy(usuario.fecha_registro, "2024-06-21");
    strcpy(usuario.estado_cuenta, "activa");
    // Asignar rol automáticamente según la app
    if(opcion_app == 1){
        // Cliente
        agregarCliente(usuario);
    }
    else if(opcion_app == 2){
        // Repartidor
        agregarRepartidor(usuario);
    }
    else if(opcion_app == 3){
        // Encargado
        agregarEncargado(usuario);
    }
    else if(opcion_app == 4){
        // Administrador
        agregarAdministrador(usuario);
    }
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

    printf("\nIngrese Direccion Completa: ");
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

    int opcion =0;
    char menuDisponibilidad[2][50]={
        "[1] Activo",
        "[2] Inactivo",
    };

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

    printf("\nIngrese Patente de Vehiculo: ");
    scanf(" %[^\n]", repartidor.vehiculo);
    convertirEspaciosAGuiones(repartidor.vehiculo);

    generarMenu(menuDisponibilidad, 2);
    printf("\nIngrese Estado de Disponibilidad: ");
    scanf("%d", &opcion);
    if(opcion == 1){
        strcpy(repartidor.estado_disponibilidad, "Activo");
    }else if(opcion == 2){
        strcpy(repartidor.estado_disponibilidad, "Inactivo");
    }

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

    int opcion = 0;
    char menuTurno[3][50]={
    "\n[1] Mañana\n",
    "\n[2] Tarde\n",
    "\n[3] Noche\n",
    };

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
    listarRestaurantes();

    printf("\nIngrese ID del Restaurante: ");
    scanf("%d", &encargado.id_restaurante);

    generarMenu(menuTurno, 3);
    printf("\nIngrese Turno: ");
    scanf("%d", &opcion);
    if(opcion == 1){
        strcpy(encargado.turno, "Mañana");
    }else if(opcion == 2){
        strcpy(encargado.turno, "Tarde");
    }else if(opcion == 3){
        strcpy(encargado.turno, "Noche");
    }


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

    int opcion = 0;
    char menuAdministrador[3][50]={
    "\n[1] Superadmin\n",
    "\n[2] Admin\n",
    "\n[3] Supervisor\n",
    };

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

    generarMenu(menuAdministrador, 3);

    printf("\nIngrese Nivel de Acceso: ");
    scanf("%d", &opcion);
    if(opcion == 1){
        strcpy(administrador.nivel_acceso, "superadmin");
    }else if(opcion == 2){
        strcpy(administrador.nivel_acceso, "admin");
    }else if(opcion == 3){
        strcpy(administrador.nivel_acceso, "supervisor");
    }

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
        if( strcasecmp(reg.email, usuario.email) == 0 &&
            strcmp(reg.contrasena, usuario.contrasena) == 0){
            usuario = reg;

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
    auxiliar = fopen("auxiliar_cliente.dat", "wb");

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
    rename("auxiliar_cliente.dat", "cliente.dat");
}
void eliminarRepartidor(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Repartidor repartidor;

    archivo = fopen("repartidor.dat", "rb");
    auxiliar = fopen("auxiliar_repartidor.dat", "wb");

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
    rename("auxiliar_repartidor.dat", "repartidor.dat");
}
void eliminarEncargado(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Encargado encargado;

    archivo = fopen("encargado.dat", "rb");
    auxiliar = fopen("auxiliar_encargado.dat", "wb");

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
    rename("auxiliar_encargado.dat", "encargado.dat");
}
void eliminarAdministrador(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Administrador administrador;

    archivo = fopen("administrador.dat", "rb");
    auxiliar = fopen("auxiliar_administrador.dat", "wb");

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
    rename("auxiliar_administrador.dat", "administrador.dat");
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

void listarRepartidores(){
    FILE *archivo;
    Usuario usuario;
    archivo = fopen("usuario.dat", "rb");

    if(archivo == NULL){
        printf("\nNo se pudo abrir usuario.dat\n");
        return;
    }
    printf("\n========== LISTADO DE USUARIOS ==========\n");

    while(fread(&usuario, sizeof(Usuario), 1, archivo) == 1){
        if( esRepartidor(usuario.id_usuario) ){
            printf("ID: %d", usuario.id_usuario);
            printf("\nNombre: %s", usuario.nombre);
            printf("\nApellido: %s", usuario.apellido);
            printf("\nEmail: %s", usuario.email);
            printf("\nTelefono: %s", usuario.telefono);
            printf("\n----------------------------------\n");
        }
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
        if( strcasecmp(reg.email, usuario.email) == 0 &&
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

    int cantidad_roles = contarRolesDelUsuario(usuario.id_usuario);
    int roles_actuales[4] = {0};
    obtenerRolesDelUsuario(usuario.id_usuario, roles_actuales);

    if(cantidad_roles == 1){
        if(roles_actuales[0]){ panelCliente(usuario); }
        else if(roles_actuales[1]){ panelEncargador(usuario); }
        else if(roles_actuales[2]){ panelRepartidor(usuario); }
        else if(roles_actuales[3]){ panelAdministrador(usuario); }
    }
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
        if(strcasecmp(usuario.email, email) == 0){
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
    roles[3] = esAdministrador(id_usuario);
}

void agregarRolExistente(int id_usuario){
    FILE *archivoUsuario = fopen("usuario.dat", "rb");
    Usuario usuario;
    int encontrado = 0;
    int rol;
    int roles_actuales[4] = {0};

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

    if(tieneRol(id_usuario, rol)){
        printf("\n[ERROR] Este usuario ya tiene este rol.\n");
        return;
    }

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
    listarUsuarios();

    printf("\nIngrese el ID del usuario a eliminar: ");
    scanf("%d", &id_a_eliminar);

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
    listarRestaurantes();

    printf("\nIngrese el ID del restaurante a eliminar: ");
    scanf("%d", &id_a_eliminar);

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
        if (!validarNombre(restaurante.nombre)) {
            printf("[REINTENTE] ");
        } else {
            convertirEspaciosAGuiones(restaurante.nombre);
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

    printf("\nIngrese Nombre de Direccion: ");
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
    char tipoProducto[4][50]={
    "\n[1] Desayuno\n",
    "\n[2] Comida\n",
    "\n[3] Postre\n",
    "\n[4] Guarnicion\n",
    };
    int categoria;

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
    generarMenu(tipoProducto, 4);
    printf("\nIngrese Categoría: ");
    scanf("%d", &categoria);
    if(categoria == 1){
        strcpy(producto.categoria, "Desayuno");
    }else if(categoria == 2){
        strcpy(producto.categoria, "Comida");
    }else if(categoria == 3){
        strcpy(producto.categoria, "Postre");
    }else if(categoria == 4){
        strcpy(producto.categoria, "Guarnicion");
    }

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

// =========================
// PEDIDOS Y ENTREGAS
// =========================

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
    FILE *archivoRestaurante, *archivoPedido, *archivoOrden, *archivoHistorial, *archivoProducto, *archivoDetalle;
    int id_restaurante = -1;
    int cantidad_restaurantes = 0;
    int seleccion = 0;
    int producto_id = 0;
    int cantidad_producto = 0;
    double total_pedido = 0;

    Producto producto;
    DetalleOrden detalle;

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

    // Crear nuevo Pedido
    pedido.id_pedido = obtenerSiguientePedidoId();
    pedido.id_cliente = usuario.id_usuario;
    pedido.id_restaurante = id_restaurante;
    pedido.id_repartidor = -1;  // Se asignará después
    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    strftime(pedido.fecha_pedido, 20, "%Y-%m-%d", info);
    strcpy(pedido.estado, "Pendiente");
    pedido.total = 0;

    int seguir = 1;
    while(seguir){
        system("cls");
        printf("\n===============================\n");
        printf("\n   SELECCIONAR PRODUCTOS\n");
        printf("\n===============================\n");
        printf("\nRestaurante seleccionado: %d\n", id_restaurante);
        printf("Total actual: $%.2f\n", total_pedido);
        printf("\n--- Productos Disponibles ---\n");

        archivoProducto = fopen("producto.dat", "rb");
        if(archivoProducto != NULL){
            while(fread(&producto, sizeof(Producto), 1, archivoProducto) == 1){
                if(producto.id_menu == id_restaurante && strcmp(producto.disponibilidad, "disponible") == 0){
                    printf("[%d] %s - $%.2f\n", producto.id_producto, producto.nombre_producto, producto.precio);
                }
            }
            fclose(archivoProducto);
        }

        printf("\n[0] Terminar selección\n");
        printf("\nIngrese ID de producto (o 0 para terminar): ");
        scanf("%d", &producto_id);

        if(producto_id == 0){
            seguir = 0;
            break;
        }

        archivoProducto = fopen("producto.dat", "rb");
        int encontrado = 0;
        double precio_producto = 0;

        while(fread(&producto, sizeof(Producto), 1, archivoProducto) == 1){
            if(producto.id_producto == producto_id && producto.id_menu == id_restaurante && strcmp(producto.disponibilidad, "disponible") == 0){
                encontrado = 1;
                precio_producto = producto.precio;
                break;
            }
        }
        fclose(archivoProducto);

        if(!encontrado){
            printf("\n[ERROR] Producto no encontrado o no disponible.\n");
            system("pause");
            continue;
        }

        printf("Ingrese cantidad: ");
        scanf("%d", &cantidad_producto);

        if(cantidad_producto <= 0){
            printf("[ERROR] La cantidad debe ser mayor a 0.\n");
            system("pause");
            continue;
        }

        detalle.id_orden = pedido.id_pedido;
        detalle.id_producto = producto_id;
        detalle.cantidad = cantidad_producto;
        strcpy(detalle.estado_item, "Pendiente");
        strcpy(detalle.observaciones, "");

        archivoDetalle = fopen("detalle_orden.dat", "ab");
        if(archivoDetalle != NULL){
            fwrite(&detalle, sizeof(DetalleOrden), 1, archivoDetalle);
            fflush(archivoDetalle);
            fclose(archivoDetalle);
        }

        total_pedido += precio_producto * cantidad_producto;
        printf("\n✓ Producto agregado. Subtotal: $%.2f\n", total_pedido);
        system("pause");
    }

    if(total_pedido == 0){
        printf("\n[ERROR] El pedido debe tener al menos un producto.\n");
        return;
    }

    // Ingresar datos de entrega
    system("cls");
    printf("\n--- DATOS DE ENTREGA ---\n");
    printf("Dirección: ");
    scanf(" %[^\n]", pedido.direccion_entrega);

    printf("Observaciones: ");
    scanf(" %[^\n]", pedido.observaciones);

    pedido.total = total_pedido;

    archivoPedido = fopen("pedido.dat", "ab");
    if(archivoPedido != NULL){
        fwrite(&pedido, sizeof(Pedido), 1, archivoPedido);
        fflush(archivoPedido);
        fclose(archivoPedido);
    }

    OrdenPreparacion orden;
    orden.id_orden = pedido.id_pedido;
    orden.id_pedido = pedido.id_pedido;
    strcpy(orden.fecha_creacion, pedido.fecha_pedido);
    strcpy(orden.estado_preparacion, "Pendiente");

    archivoOrden = fopen("orden_preparacion.dat", "ab");
    if(archivoOrden != NULL){
        fwrite(&orden, sizeof(OrdenPreparacion), 1, archivoOrden);
        fflush(archivoOrden);
        fclose(archivoOrden);
    }

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

    realizarPago(usuario, pedido.id_pedido);


    printf("\n✓ Pedido creado exitosamente.\n");
    printf("  ID Pedido: %d\n", pedido.id_pedido);
    printf("  Total: $%.2f\n", pedido.total);
    printf("  Estado: %s\n", pedido.estado);
    system("pause");
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

        calcularComisionPedido(id_pedido, pago.id_pago, pedido.id_restaurante, pago.monto_total);
    } else {
        printf("\n[ERROR] No se pudo guardar el pago.\n");
    }
}

// =========================
// ÓRDENES DE PREPARACIÓN (ENCARGADO)
// =========================

// ENCARGADO: Ver órdenes pendientes
void listarOrdenesRestaurante(int id_restaurante){
    FILE *archivoOrdenes, *archivoPedidos;
    OrdenPreparacion orden;
    Pedido pedido;
    int cantidad = 0;

    printf("\n===============================\n");
    printf("\n   ÓRDENES PENDIENTES\n");
    printf("\n===============================\n");

    archivoOrdenes = fopen("orden_preparacion.dat", "rb");
    if(archivoOrdenes == NULL){
        printf("\nNo hay órdenes disponibles.\n");
        return;
    }

    archivoPedidos = fopen("pedido.dat", "rb");
    if(archivoPedidos == NULL){
        printf("\n[ERROR] No se pudo acceder a pedidos.\n");
        fclose(archivoOrdenes);
        return;
    }

    while(fread(&orden, sizeof(OrdenPreparacion), 1, archivoOrdenes) == 1){
        fseek(archivoPedidos, 0, SEEK_SET);

        while(fread(&pedido, sizeof(Pedido), 1, archivoPedidos) == 1){
            if(pedido.id_pedido == orden.id_pedido){
                if(strcmp(orden.estado_preparacion, "Pendiente") == 0 ||
                   strcmp(orden.estado_preparacion, "Confirmado") == 0 ||
                   strcmp(orden.estado_preparacion, "Preparandose") == 0){
                    cantidad++;
                    printf("\n[%d] Pedido ID: %d", orden.id_orden, orden.id_pedido);
                    printf("\n    Fecha: %s", orden.fecha_creacion);
                    printf("\n    Estado: %s", orden.estado_preparacion);
                    printf("\n    Dirección Entrega: %s\n", pedido.direccion_entrega);
                }
                break;
            }
        }
    }

    if(cantidad == 0){
        printf("\nNo hay órdenes pendientes en este momento.\n");
    } else {
        printf("\nTotal de órdenes pendientes: %d\n", cantidad);
    }

    fclose(archivoOrdenes);
    fclose(archivoPedidos);
}

//Para el Repartidor
void listarPedidoDisponibles(Usuario usuario){
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
        if(strcmp(pedido.estado, "Preparado") == 0){
            printf("\n[%d] Fecha: %s", pedido.id_pedido, pedido.fecha_pedido);
            printf("\n    Dirección: %s\n", pedido.direccion_entrega);
            cantidad = 1;
        }
    } fclose(archivo);
    if(cantidad){
        aceptarPedido(usuario);
    }
}

void aceptarPedido(Usuario usuario){
    FILE *archivo;
    FILE *auxiliar;

    Pedido pedido;

    int id_buscar;
    int encontrado = 0;

    printf("\nIngrese ID del pedido: ");
    scanf("%d", &id_buscar);

    archivo = fopen("pedido.dat", "rb");
    auxiliar = fopen("auxiliar_pedido.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
        if(pedido.id_pedido == id_buscar){
            encontrado = 1;
            pedido.id_repartidor = usuario.id_usuario;
            strcpy(pedido.estado, "En_Camino");
        }
        fwrite(&pedido, sizeof(Pedido), 1, auxiliar);
    }
    fclose(archivo);
    fclose(auxiliar);

    if(encontrado){
        remove("pedido.dat");
        rename("auxiliar_pedido.dat", "pedido.dat");
        printf("\nPedido aceptado correctamente.");
    }
    else{
        remove("auxiliar_pedido.dat");
        printf("\nPedido no encontrado.");
    }
}

void listarPedidosAceptados(int id_usuario){
    FILE *archivo;
    Pedido pedido;
    int cantidad = 0;

    archivo = fopen("pedido.dat", "rb");

    if(archivo == NULL){
        printf("\nNo se pudo abrir pedido.dat\n");
        return;
    }

    printf("\n========== PEDIDOS EN CAMINO ==========\n");

    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){

        if(pedido.id_repartidor == id_usuario &&
           strcmp(pedido.estado, "En_Camino") == 0){

            cantidad++;

            printf("\nID Pedido: %d", pedido.id_pedido);
            printf("\nDireccion: %s", pedido.direccion_entrega);
            printf("\nObservaciones: %s", pedido.observaciones);
            printf("\nEstado: %s", pedido.estado);
            printf("\n----------------------------------\n");
        }
    }
    if(cantidad == 0){
        printf("\nNo tienes pedidos en camino.\n");
    }
    fclose(archivo);
}

// ENCARGADO: Actualizar estado de orden
void actualizarEstadoOrden(int id_restaurante){
    FILE *archivo;
    FILE *auxiliar;

    OrdenPreparacion orden;

    int id_orden_buscar;
    int encontrado = 0;
    int opcion_estado;

    char menuUsuario[5][50]={
        "\n[1] Cancelar Pedido\n",
        "[2] Preparado\n",
        "[3] Finalizado - En Camino\n",
        "[4] Finalizado - Entregado\n",
        "Opcion: "
    };

    printf("\n===============================\n");
    printf("\n   ACTUALIZAR ESTADO DE ORDEN\n");
    printf("\n===============================\n");

    printf("\nIngrese ID de la orden a actualizar: ");
    scanf("%d", &id_orden_buscar);

    archivo = fopen("orden_preparacion.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\n[ERROR] No se pueden abrir los archivos.\n");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&orden, sizeof(OrdenPreparacion), 1, archivo) == 1){
        if(orden.id_orden == id_orden_buscar){
            encontrado = 1;
            printf("\n✓ Orden encontrada.\n");
            printf("ID Orden: %d\n", orden.id_orden);
            printf("Estado Actual: %s\n", orden.estado_preparacion);

            generarMenu(menuUsuario, 5);
            scanf("%d", &opcion_estado);
            switch(opcion_estado){
                case 1:{
                    strcpy(orden.estado_preparacion, "Cancelado");
                    actualizarPedidoXid(orden.id_pedido, "Cancelado");
                    break;
                }
                case 2:{
                    strcpy(orden.estado_preparacion, "Preparado");
                    actualizarPedidoXid(orden.id_pedido, "Preparado");
                    break;
                }
                case 3:{
                    strcpy(orden.estado_preparacion, "Listo_Entrega");
                    actualizarPedidoXid(orden.id_pedido, "En_Camino");
                    break;
                }
                case 4:{
                    strcpy(orden.estado_preparacion, "Entregado");
                    actualizarPedidoXid(orden.id_pedido, "Finalizado");
                    break;
                }
                default:{
                    printf("\n[ERROR] Opcion invalida.\n");
                    break;
                }
            }
            printf("\nNuevo Estado: %s\n",
                   orden.estado_preparacion);
            /* Si el ID es único no hace falta seguir buscando */
            fwrite(&orden, sizeof(OrdenPreparacion), 1, auxiliar);
            while(fread(&orden, sizeof(OrdenPreparacion), 1, archivo) == 1){
                fwrite(&orden, sizeof(OrdenPreparacion), 1, auxiliar);
            }
            break;
        }
        fwrite(&orden, sizeof(OrdenPreparacion), 1, auxiliar);
    }

    fclose(archivo);
    fclose(auxiliar);

    if(encontrado){
        remove("orden_preparacion.dat");
        rename("auxiliar.dat", "orden_preparacion.dat");
        printf("\n✓ Estado de la orden actualizado correctamente.\n");
    }else{
        remove("auxiliar.dat");
        printf("\n[ERROR] Orden no encontrada.\n");
    }
}

void actualizarPedidoXid(int id_pedido, char nuevoEstado[]){
    FILE *archivo;
    FILE *auxiliar;
    Pedido pedido;
    int encontrado = 0;
    archivo = fopen("pedido.dat", "rb");
    auxiliar = fopen("auxiliar_pedido.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
        if(pedido.id_pedido == id_pedido){
            encontrado = 1;
            strcpy(pedido.estado, nuevoEstado);

            HistorialEstado historial;
            historial.id_historial = pedido.id_pedido;
            historial.id_pedido = pedido.id_pedido;
            strcpy(historial.estado, nuevoEstado);
            strcpy(historial.fecha_actualizacion, pedido.fecha_pedido);
        }
        fwrite(&pedido, sizeof(Pedido), 1, auxiliar);
    }

    fclose(archivo);
    fclose(auxiliar);

    if(encontrado){
        remove("pedido.dat");
        rename("auxiliar_pedido.dat", "pedido.dat");
        printf("\nEstado actualizado correctamente.");
    }
    else{
        remove("auxiliar_pedido.dat");
        printf("\nPedido no encontrado.");
    }
}

// =========================
// FINANZAS - COMISIONES Y PAGOS
// =========================

void calcularComisionPedido(int id_pedido, int id_pago, int id_restaurante, double monto_total){
    FILE *archivo;
    ComisionDetalle comision;
    int ultimoId = 0;

    archivo = fopen("comision.dat", "rb");
    if(archivo != NULL){
        ComisionDetalle auxComision;
        while(fread(&auxComision, sizeof(ComisionDetalle), 1, archivo) == 1){
            if(auxComision.id_comision_detalle > ultimoId){
                ultimoId = auxComision.id_comision_detalle;
            }
        }
        fclose(archivo);
    }

    comision.id_comision_detalle = ultimoId + 1;
    comision.id_pedido = id_pedido;
    comision.id_restaurante = id_restaurante;
    comision.id_pago = id_pago;
    comision.monto_pedido = monto_total;
    comision.porcentaje_comision = 15.0;
    comision.monto_comision = monto_total * 0.15;
    comision.monto_neto = monto_total * 0.85;
    strcpy(comision.estado, "Pendiente");

    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    strftime(comision.fecha_comision, 11, "%d/%m/%Y", info);

    archivo = fopen("comision.dat", "ab");
    if(archivo != NULL){
        fwrite(&comision, sizeof(ComisionDetalle), 1, archivo);
        fflush(archivo);
        fclose(archivo);
    }
}

void verIngresosRestaurante(int id_restaurante){
    FILE *archivo;
    ComisionDetalle comision;
    double total_pendiente = 0, total_pagado = 0;
    int cantidad_pendiente = 0, cantidad_pagado = 0;

    printf("\n===============================\n");
    printf("\n   MIS INGRESOS\n");
    printf("\n===============================\n");

    archivo = fopen("comision.dat", "rb");
    if(archivo == NULL){
        printf("\nNo hay ingresos registrados.\n");
        return;
    }

    while(fread(&comision, sizeof(ComisionDetalle), 1, archivo) == 1){
        if(comision.id_restaurante == id_restaurante){
            if(strcmp(comision.estado, "Pendiente") == 0){
                total_pendiente += comision.monto_neto;
                cantidad_pendiente++;
            } else if(strcmp(comision.estado, "Pagado") == 0){
                total_pagado += comision.monto_neto;
                cantidad_pagado++;
            }
        }
    }
    fclose(archivo);

    printf("\n--- COMISIONES PENDIENTES DE PAGO ---\n");
    printf("Total pendiente: $%.2f (%d pedidos)\n", total_pendiente, cantidad_pendiente);
    printf("\n--- COMISIONES PAGADAS ---\n");
    printf("Total pagado: $%.2f (%d pedidos)\n", total_pagado, cantidad_pagado);
    printf("\n--- RESUMEN TOTAL ---\n");
    printf("Ingresos totales: $%.2f\n", total_pendiente + total_pagado);
}

void realizarPagoRestaurante(){
    FILE *archivoRestaurantes, *archivoComisiones, *archivoPagos;
    Restaurante restaurante;
    ComisionDetalle comision;
    PagoRestaurante pago;
    int id_restaurante, ultimoId = 0;
    double total_pagar = 0;
    int cantidad_pedidos = 0;

    printf("\n===============================\n");
    printf("\n   REALIZAR PAGO A RESTAURANTE\n");
    printf("\n===============================\n");

    // Listar restaurantes
    archivoRestaurantes = fopen("restaurante.dat", "rb");
    if(archivoRestaurantes == NULL){
        printf("\n[ERROR] No hay restaurantes.\n");
        return;
    }

    printf("\nRestaurantes disponibles:\n");
    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurantes) == 1){
        printf("[%d] %s\n", restaurante.id_restaurante, restaurante.nombre);
    }
    fclose(archivoRestaurantes);

    printf("\nIngrese ID del restaurante: ");
    scanf("%d", &id_restaurante);

    // Calcular total a pagar
    archivoComisiones = fopen("comision.dat", "rb");
    if(archivoComisiones == NULL){
        printf("\n[ERROR] No hay comisiones registradas.\n");
        return;
    }

    while(fread(&comision, sizeof(ComisionDetalle), 1, archivoComisiones) == 1){
        if(comision.id_restaurante == id_restaurante && strcmp(comision.estado, "Pendiente") == 0){
            total_pagar += comision.monto_neto;
            cantidad_pedidos++;
        }
    }
    fclose(archivoComisiones);

    if(total_pagar == 0){
        printf("\n[INFO] No hay pagos pendientes para este restaurante.\n");
        return;
    }

    printf("\n--- CONFIRMACIÓN DE PAGO ---\n");
    printf("Restaurante ID: %d\n", id_restaurante);
    printf("Total a pagar: $%.2f\n", total_pagar);
    printf("Cantidad de pedidos: %d\n", cantidad_pedidos);
    printf("\n¿Confirmar pago? [1] SÍ [2] NO: ");

    int confirmacion;
    scanf("%d", &confirmacion);

    if(confirmacion != 1){
        printf("\n✓ Pago cancelado.\n");
        return;
    }

    // Obtener próximo ID
    archivoPagos = fopen("pago_restaurante.dat", "rb");
    if(archivoPagos != NULL){
        PagoRestaurante auxPago;
        while(fread(&auxPago, sizeof(PagoRestaurante), 1, archivoPagos) == 1){
            if(auxPago.id_pago_restaurante > ultimoId){
                ultimoId = auxPago.id_pago_restaurante;
            }
        }
        fclose(archivoPagos);
    }

    // Crear pago
    pago.id_pago_restaurante = ultimoId + 1;
    pago.id_restaurante = id_restaurante;
    pago.monto_total = total_pagar;
    pago.cantidad_pedidos = cantidad_pedidos;
    strcpy(pago.metodo_pago, "Transferencia");
    strcpy(pago.estado, "Completado");

    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    strftime(pago.fecha_pago, 11, "%d/%m/%Y", info);

    archivoPagos = fopen("pago_restaurante.dat", "ab");
    if(archivoPagos != NULL){
        fwrite(&pago, sizeof(PagoRestaurante), 1, archivoPagos);
        fflush(archivoPagos);
        fclose(archivoPagos);
    }

    // Marcar comisiones como pagadas
    marcarComisionsComoPagadas(id_restaurante);

    printf("\n✓ Pago registrado exitosamente.\n");
    printf("  ID Pago: %d\n", pago.id_pago_restaurante);
    printf("  Monto: $%.2f\n", pago.monto_total);
}

void marcarComisionsComoPagadas(int id_restaurante){
    FILE *archivo, *auxiliar;
    ComisionDetalle comision;

    archivo = fopen("comision.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&comision, sizeof(ComisionDetalle), 1, archivo) == 1){
        if(comision.id_restaurante == id_restaurante && strcmp(comision.estado, "Pendiente") == 0){
            strcpy(comision.estado, "Pagado");
        }
        fwrite(&comision, sizeof(ComisionDetalle), 1, auxiliar);
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("comision.dat");
    rename("auxiliar.dat", "comision.dat");
}

void verIngresoRepartidor(int id_repartidor){
    FILE *archivo;
    IngresoRepartidor ingreso;
    double total_propina = 0, total_bonus = 0;
    int cantidad_entregas = 0;

    printf("\n===============================\n");
    printf("\n   MIS INGRESOS\n");
    printf("\n===============================\n");

    archivo = fopen("ingreso_repartidor.dat", "rb");
    if(archivo == NULL){
        printf("\nNo hay ingresos registrados.\n");
        return;
    }

    while(fread(&ingreso, sizeof(IngresoRepartidor), 1, archivo) == 1){
        if(ingreso.id_repartidor == id_repartidor){
            total_propina += ingreso.propina;
            total_bonus += ingreso.bonus;
            cantidad_entregas++;
        }
    }
    fclose(archivo);

    printf("\nTotal de entregas: %d\n", cantidad_entregas);
    printf("Total en propinas: $%.2f\n", total_propina);
    printf("Total en bonos: $%.2f\n", total_bonus);
    printf("Ingreso total: $%.2f\n", total_propina + total_bonus);
}

void verFinanzasTotales(){
    FILE *archComisiones, *archPagos;
    ComisionDetalle comision;
    PagoRestaurante pago;
    double ingresos_sistema = 0, monto_pagado = 0;
    int pedidos_totales = 0;

    printf("\n===============================\n");
    printf("\n   FINANZAS GENERALES DEL SISTEMA\n");
    printf("\n===============================\n");

    printf("\n--- INGRESOS DEL SISTEMA ---\n");
    printf("Comisiones totales: $%.2f\n", ingresos_sistema);
    printf("Pedidos procesados: %d\n", pedidos_totales);

    printf("\n--- PAGOS A RESTAURANTES ---\n");
    printf("Total pagado: $%.2f\n", monto_pagado);
    printf("Diferencia (comisiones retomadas): $%.2f\n", ingresos_sistema - monto_pagado);

    printf("\n--- PROMEDIO POR PEDIDO ---\n");
    if(pedidos_totales > 0){
        printf("Comisión promedio: $%.2f\n", ingresos_sistema / pedidos_totales);
    }
}

// =========================
// CALIFICACIONES Y RESEÑAS
// =========================

void calificarPedido(Usuario usuario){
    FILE *archivoPedidos, *archivoCalificaciones;
    Pedido pedido;
    Calificacion calificacion;
    int id_pedido, ultimoId = 0;
    int encontrado = 0;

    printf("\n===============================\n");
    printf("\n     CALIFICAR PEDIDO\n");
    printf("\n===============================\n");

    archivoPedidos = fopen("pedido.dat", "rb");
    if(archivoPedidos == NULL){
        printf("\nNo tienes pedidos.\n");
        return;
    }

    printf("\nTus pedidos:\n");
    while(fread(&pedido, sizeof(Pedido), 1, archivoPedidos) == 1){
        if(pedido.id_cliente == usuario.id_usuario && strcmp(pedido.estado, "Entregado") == 0){
            printf("[%d] Fecha: %s - Estado: %s\n", pedido.id_pedido, pedido.fecha_pedido, pedido.estado);
        }
    }
    fclose(archivoPedidos);

    printf("\nIngrese ID del pedido a calificar: ");
    scanf("%d", &id_pedido);

    archivoPedidos = fopen("pedido.dat", "rb");
    while(fread(&pedido, sizeof(Pedido), 1, archivoPedidos) == 1){
        if(pedido.id_pedido == id_pedido && pedido.id_cliente == usuario.id_usuario){
            encontrado = 1;
            break;
        }
    }
    fclose(archivoPedidos);

    if(!encontrado){
        printf("\n[ERROR] Pedido no encontrado.\n");
        return;
    }

    archivoCalificaciones = fopen("calificacion.dat", "rb");
    if(archivoCalificaciones != NULL){
        Calificacion auxCal;
        while(fread(&auxCal, sizeof(Calificacion), 1, archivoCalificaciones) == 1){
            if(auxCal.id_calificacion > ultimoId){
                ultimoId = auxCal.id_calificacion;
            }
        }
        fclose(archivoCalificaciones);
    }

    calificacion.id_calificacion = ultimoId + 1;
    calificacion.id_pedido = id_pedido;
    calificacion.id_cliente = usuario.id_usuario;
    calificacion.id_restaurante = pedido.id_restaurante;

    printf("\n--- CALIFICAR ---\n");
    printf("Puntuación comida (1-5): ");
    scanf("%d", &calificacion.puntuacion_comida);

    printf("Puntuación repartidor (1-5): ");
    scanf("%d", &calificacion.puntuacion_repartidor);

    printf("Puntuación entrega (1-5): ");
    scanf("%d", &calificacion.puntuacion_entrega);

    printf("¿Recomendarías este restaurante? [1] SÍ [2] NO: ");
    scanf("%d", &calificacion.fue_recomendado);

    printf("Comentario (opcional): ");
    scanf(" %[^\n]", calificacion.comentario);
    convertirEspaciosAGuiones(calificacion.comentario);

    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    strftime(calificacion.fecha_calificacion, 11, "%d/%m/%Y", info);
    strcpy(calificacion.estado_resenia, "Visible");

    archivoCalificaciones = fopen("calificacion.dat", "ab");
    if(archivoCalificaciones != NULL){
        fwrite(&calificacion, sizeof(Calificacion), 1, archivoCalificaciones);
        fflush(archivoCalificaciones);
        fclose(archivoCalificaciones);
    }

    actualizarPromedioRestaurante(calificacion.id_restaurante);

    printf("\n✓ Calificación registrada exitosamente.\n");
}

void verCalificacionesRestaurante(int id_restaurante){
    FILE *archivo;
    Calificacion calificacion;
    int cantidad = 0;
    double promedio_comida = 0, promedio_repartidor = 0, promedio_entrega = 0;

    printf("\n===============================\n");
    printf("\n   CALIFICACIONES DEL RESTAURANTE\n");
    printf("\n===============================\n");

    archivo = fopen("calificacion.dat", "rb");
    if(archivo == NULL){
        printf("\nNo hay calificaciones aún.\n");
        return;
    }

    while(fread(&calificacion, sizeof(Calificacion), 1, archivo) == 1){
        if(calificacion.id_restaurante == id_restaurante && strcmp(calificacion.estado_resenia, "Visible") == 0){
            cantidad++;
            promedio_comida += calificacion.puntuacion_comida;
            promedio_repartidor += calificacion.puntuacion_repartidor;
            promedio_entrega += calificacion.puntuacion_entrega;

            printf("\n--- Reseña #%d ---\n", cantidad);
            printf("Fecha: %s\n", calificacion.fecha_calificacion);
            printf("Comida: %d/5 | Repartidor: %d/5 | Entrega: %d/5\n",
                   calificacion.puntuacion_comida, calificacion.puntuacion_repartidor,
                   calificacion.puntuacion_entrega);
            printf("Comentario: %s\n", calificacion.comentario);
            printf("Recomendado: %s\n", calificacion.fue_recomendado ? "SÍ" : "NO");
        }
    }
    fclose(archivo);

    if(cantidad > 0){
        printf("\n--- PROMEDIOS ---\n");
        printf("Comida: %.2f/5\n", promedio_comida / cantidad);
        printf("Repartidor: %.2f/5\n", promedio_repartidor / cantidad);
        printf("Entrega: %.2f/5\n", promedio_entrega / cantidad);
        printf("Total de reseñas: %d\n", cantidad);
    } else {
        printf("\nNo hay calificaciones visibles.\n");
    }
}

void verMisCalificaciones(Usuario usuario){
    FILE *archivo;
    Calificacion calificacion;

    printf("\n===============================\n");
    printf("\n   MIS CALIFICACIONES\n");
    printf("\n===============================\n");

    archivo = fopen("calificacion.dat", "rb");
    if(archivo == NULL){
        printf("\nNo has hecho calificaciones.\n");
        return;
    }

    while(fread(&calificacion, sizeof(Calificacion), 1, archivo) == 1){
        if(calificacion.id_cliente == usuario.id_usuario){
            printf("\n[Pedido #%d] Fecha: %s\n", calificacion.id_pedido, calificacion.fecha_calificacion);
            printf("Puntuaciones: Comida %d/5, Repartidor %d/5, Entrega %d/5\n",
                   calificacion.puntuacion_comida, calificacion.puntuacion_repartidor,
                   calificacion.puntuacion_entrega);
            printf("Comentario: %s\n", calificacion.comentario);
        }
    }
    fclose(archivo);
}

void reportarResenia(int id_calificacion){
    FILE *archivo, *auxiliar;
    Calificacion calificacion;
    int encontrado = 0;

    printf("\n===============================\n");
    printf("\n   REPORTAR RESEÑA\n");
    printf("\n===============================\n");

    archivo = fopen("calificacion.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&calificacion, sizeof(Calificacion), 1, archivo) == 1){
        if(calificacion.id_calificacion == id_calificacion){
            encontrado = 1;
            strcpy(calificacion.estado_resenia, "Reportada");
            printf("\n✓ Reseña reportada.\n");
        }
        fwrite(&calificacion, sizeof(Calificacion), 1, auxiliar);
    }

    fclose(archivo);
    fclose(auxiliar);

    if(encontrado){
        remove("calificacion.dat");
        rename("auxiliar.dat", "calificacion.dat");
    } else {
        remove("auxiliar.dat");
        printf("\n[ERROR] Reseña no encontrada.\n");
    }
}

void actualizarPromedioRestaurante(int id_restaurante){
    FILE *archivoCalificaciones, *archivoRestaurantes, *auxiliar;
    Calificacion calificacion;
    Restaurante restaurante;
    double suma_puntuaciones = 0;
    int total_puntuaciones = 0;
    int total_calificaciones = 0;

    // Calcular promedio
    archivoCalificaciones = fopen("calificacion.dat", "rb");
    if(archivoCalificaciones != NULL){
        while(fread(&calificacion, sizeof(Calificacion), 1, archivoCalificaciones) == 1){
            if(calificacion.id_restaurante == id_restaurante && strcmp(calificacion.estado_resenia, "Visible") == 0){
                suma_puntuaciones += calificacion.puntuacion_comida + calificacion.puntuacion_repartidor + calificacion.puntuacion_entrega;
                total_puntuaciones += 3;
                total_calificaciones++;
            }
        }
        fclose(archivoCalificaciones);
    }

    // Actualizar restaurante
    archivoRestaurantes = fopen("restaurante.dat", "rb");
    auxiliar = fopen("auxiliar.dat", "wb");

    if(archivoRestaurantes == NULL || auxiliar == NULL){
        if(archivoRestaurantes != NULL) fclose(archivoRestaurantes);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurantes) == 1){
        if(restaurante.id_restaurante == id_restaurante){
            restaurante.promedio_calificacion = total_puntuaciones > 0 ? suma_puntuaciones / total_puntuaciones : 0;
            restaurante.total_calificaciones = total_calificaciones;
        }
        fwrite(&restaurante, sizeof(Restaurante), 1, auxiliar);
    }

    fclose(archivoRestaurantes);
    fclose(auxiliar);

    remove("restaurante.dat");
    rename("auxiliar.dat", "restaurante.dat");
}

// =========================
// INFORMACIÓN DEL RESTAURANTE
// =========================

void mostrarInfoRestaurante(int id_restaurante){
    FILE *archivoRestaurantes, *archivoProductos, *archivoPedidos, *archivoMenu;
    Restaurante restaurante;
    Producto producto;
    Menu menu;
    Pedido pedido;
    int encontrado = 0;
    int cantidad_productos = 0;
    int cantidad_pedidos_totales = 0;
    double ingresos_totales = 0;

    printf("\n===============================\n");
    printf("\n  INFORMACIÓN DEL RESTAURANTE\n");
    printf("\n===============================\n");

    // Buscar restaurante
    archivoRestaurantes = fopen("restaurante.dat", "rb");
    if(archivoRestaurantes == NULL){
        printf("\n[ERROR] No se encontraron restaurantes.\n");
        return;
    }

    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurantes) == 1){
        if(restaurante.id_restaurante == id_restaurante){
            encontrado = 1;
            break;
        }
    }
    fclose(archivoRestaurantes);

    if(!encontrado){
        printf("\n[ERROR] Restaurante no encontrado.\n");
        return;
    }

    // Contar productos: primero leer menus, luego productos
    archivoMenu = fopen("menu.dat", "rb");
    if(archivoMenu != NULL){
        while(fread(&menu, sizeof(Menu), 1, archivoMenu) == 1){
            if(menu.id_restaurante == id_restaurante){
                // Para cada menu, contar productos
                archivoProductos = fopen("producto.dat", "rb");
                if(archivoProductos != NULL){
                    while(fread(&producto, sizeof(Producto), 1, archivoProductos) == 1){
                        if(producto.id_menu == menu.id_menu){
                            cantidad_productos++;
                        }
                    }
                    fclose(archivoProductos);
                }
            }
        }
        fclose(archivoMenu);
    }

    // Contar pedidos e ingresos
    archivoPedidos = fopen("pedido.dat", "rb");
    if(archivoPedidos != NULL){
        while(fread(&pedido, sizeof(Pedido), 1, archivoPedidos) == 1){
            if(pedido.id_restaurante == id_restaurante){
                cantidad_pedidos_totales++;
                ingresos_totales += pedido.total;
            }
        }
        fclose(archivoPedidos);
    }

    // Mostrar información
    printf("\n--- DATOS BÁSICOS ---\n");
    printf("ID: %d\n", restaurante.id_restaurante);
    printf("Nombre: %s\n", restaurante.nombre);
    printf("Teléfono: %s\n", restaurante.telefono);
    printf("Estado: %s\n", restaurante.estado);

    printf("\n--- HORARIOS ---\n");
    printf("Apertura: %s\n", restaurante.horario_apertura);
    printf("Cierre: %s\n", restaurante.horario_cierre);

    printf("\n--- CALIFICACIONES ---\n");
    printf("Promedio: %.2f/5.0\n", restaurante.promedio_calificacion);
    printf("Total de reseñas: %d\n", restaurante.total_calificaciones);

    printf("\n--- ESTADÍSTICAS DEL NEGOCIO ---\n");
    printf("Productos en menú: %d\n", cantidad_productos);
    printf("Pedidos totales: %d\n", cantidad_pedidos_totales);
    printf("Ingresos totales: $%.2f\n", ingresos_totales);

    if(cantidad_pedidos_totales > 0){
        printf("Ticket promedio: $%.2f\n", ingresos_totales / cantidad_pedidos_totales);
    }
}

// =========================
// LOGIN Y REGISTRO POR ROL
// =========================


void agregarRolEspecifico(int id_usuario, int opcion_app){
    FILE *archivo;
    Usuario usuario;
    int opcion = 0;

    char menuDisponibilidad[2][50]={
        "[1] Activo",
        "[2] Inactivo",
    };

    char menuTurno[3][50]={
    "\n[1] Mañana\n",
    "\n[2] Tarde\n",
    "\n[3] Noche\n",
    };

    char menuAdministrador[3][50]={
    "\n[1] Superadmin\n",
    "\n[2] Admin\n",
    "\n[3] Supervisor\n",
    };

    // Obtener datos del usuario
    archivo = fopen("usuario.dat", "rb");
    if(archivo != NULL){
        while(fread(&usuario, sizeof(Usuario), 1, archivo) == 1){
            if(usuario.id_usuario == id_usuario) break;
        }
        fclose(archivo);
    }

    if(opcion_app == 1){
        // Agregar Cliente
        Cliente cliente;
        cliente.id_usuario = id_usuario;
        printf("\nIngrese Dirección Completa: ");
        scanf(" %[^\n]", cliente.direccion);

        FILE *archivoCliente = fopen("cliente.dat", "ab");
        if(archivoCliente != NULL){
            fwrite(&cliente, sizeof(Cliente), 1, archivoCliente);
            fflush(archivoCliente);
            fclose(archivoCliente);
        }
    }
    else if(opcion_app == 2){
        // Agregar Repartidor
        Repartidor repartidor;
        repartidor.id_usuario = id_usuario;
        printf("\nIngrese Patente del Vehículo: ");
        scanf(" %[^\n]", repartidor.vehiculo);

        generarMenu(menuDisponibilidad, 2);
        printf("\nIngrese Estado de Disponibilidad: ");
        scanf("%d", &opcion);
        if(opcion == 1){
            strcpy(repartidor.estado_disponibilidad, "Activo");
        }else if(opcion == 2){
            strcpy(repartidor.estado_disponibilidad, "Inactivo");
        }

        FILE *archivoRepartidor = fopen("repartidor.dat", "ab");
        if(archivoRepartidor != NULL){
            fwrite(&repartidor, sizeof(Repartidor), 1, archivoRepartidor);
            fflush(archivoRepartidor);
            fclose(archivoRepartidor);
        }
    }
    else if(opcion_app == 3){
        // Agregar Encargado
        Encargado encargado;
        encargado.id_usuario = id_usuario;
        printf("\nIngrese ID del Restaurante: ");
        scanf("%d", &encargado.id_restaurante);

        generarMenu(menuTurno, 3);
        printf("\nIngrese Turno: ");
        scanf("%d", &opcion);
        if(opcion == 1){
            strcpy(encargado.turno, "Mañana");
        }else if(opcion == 2){
            strcpy(encargado.turno, "Tarde");
        }else if(opcion == 3){
            strcpy(encargado.turno, "Noche");
        }


        FILE *archivoEncargado = fopen("encargado.dat", "ab");
        if(archivoEncargado != NULL){
            fwrite(&encargado, sizeof(Encargado), 1, archivoEncargado);
            fflush(archivoEncargado);
            fclose(archivoEncargado);
        }
    }
    else if(opcion_app == 4){
        // Agregar Administrador
        Administrador administrador;
        administrador.id_usuario = id_usuario;

        generarMenu(menuAdministrador, 3);
        printf("\nIngrese Nivel de Acceso: ");
        scanf("%d", &opcion);
        if(opcion == 1){
            strcpy(administrador.nivel_acceso, "superadmin");
        }else if(opcion == 2){
            strcpy(administrador.nivel_acceso, "admin");
        }else if(opcion == 3){
            strcpy(administrador.nivel_acceso, "supervisor");
        }

        FILE *archivoAdministrador = fopen("administrador.dat", "ab");
        if(archivoAdministrador != NULL){
            fwrite(&administrador, sizeof(Administrador), 1, archivoAdministrador);
            fflush(archivoAdministrador);
            fclose(archivoAdministrador);
        }
    }
}

