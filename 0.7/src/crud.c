#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#ifdef _WIN32
#include <direct.h>
#define CREAR_DIRECTORIO(path) _mkdir(path)
#else
#include <sys/stat.h>
#include <sys/types.h>
#define CREAR_DIRECTORIO(path) mkdir(path, 0777)
#endif
#include "crud.h"
#include "BBD.h"
#include "ui.h"

static void crearDirectorioAuxiliar(){
    if(CREAR_DIRECTORIO("data/auxiliar_data") == -1 && errno != EEXIST){
        perror("No se pudo crear data/auxiliar_data");
    }
}

void abrirBDD(){
    FILE *archivo;

    crearDirectorioAuxiliar();

    archivo = fopen("data/usuario.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/cliente.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/repartidor.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/encargado.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/administrador.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/restaurante.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/producto.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/pedido.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/pago.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/orden_preparacion.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/detalle_orden.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/historial_estado.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/categoria.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/menu.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/transaccion.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/recibo.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/comision.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/pago_data/restaurante.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/ingreso_data/repartidor.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    archivo = fopen("data/calificacion.dat", "ab");
    if(archivo != NULL)
        fclose(archivo);

    mostrarExito("Base de datos inicializada correctamente.");
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
    limpiarPantalla();
    mostrarCaja("REGISTRAR USUARIO");
    // Validar Email PRIMERO
    do {
        mostrarInput("Ingrese Correo");
        scanf(" %[^\n]", usuario.email);
        if (!validarEmail(usuario.email)) {
            mostrarError("Email inválido. Reintente");
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
            limpiarPantalla();
            mostrarCaja("USUARIO YA EXISTE");
            char msg[200];
            sprintf(msg, "Esta cuenta ya tiene el rol de %s.\\nNo se puede registrar nuevamente.", nombre_rol);
            mostrarInfo(msg);
            mostrarCajaFin();
            pausar();
            return;
        } else {
            // Tiene usuario pero no este rol - agregar rol
            limpiarPantalla();
            mostrarCaja("USUARIO EXISTENTE - AGREGAR ROL");
            mostrarInfo("Esta cuenta ya existe con otros roles.");
            char msg[200];
            sprintf(msg, "¿Desea agregar el rol de %s?", nombre_rol);
            mostrarInfo(msg);
            mostrarOpcion(1, "Sí");
            mostrarOpcion(2, "NO");
            mostrarInput("Seleccione una opción");

            if(scanf("%d", &opcion_menu) != 1){
                while (getchar() != '\n');
                opcion_menu = 0;
            }

            if(opcion_menu == 1){
                agregarRolEspecifico(id_usuario_existente, opcion_app);
                char msg3[150];
                sprintf(msg3, "Rol de %s agregado exitosamente", nombre_rol);
                mostrarExito(msg3);
                mostrarCajaFin();
                pausar();
                return;
            } else {
                mostrarError("Operación cancelada");
                mostrarCajaFin();
                pausar();
                return;
            }
        }
    }

    // El email NO existe - crear nuevo usuario

    // Validar Contraseña
    do {
        mostrarInput("Ingrese Contraseña");
        scanf(" %[^\n]", usuario.contrasena);
        if (!validarContrasena(usuario.contrasena)) {
            printf("[REINTENTE] ");
        } else {
            break;
        }
    } while(1);

    // Validar Nombre
    do {
        mostrarInput("Ingrese Nombre");
        scanf(" %[^\n]", usuario.nombre);
        if (!validarNombre(usuario.nombre)) {
            mostrarError("Nombre inválido. Reintente");
        } else {
            break;
        }
    } while(1);

    // Validar Apellido
    do {
        mostrarInput("Ingrese Apellido");
        scanf(" %[^\n]", usuario.apellido);
        if (!validarNombre(usuario.apellido)) {
            mostrarError("Apellido inválido. Reintente");
        } else {
            break;
        }
    } while(1);

    // Validar Teléfono
    do {
        mostrarInput("Ingrese Teléfono");
        scanf(" %[^\n]", usuario.telefono);
        if (!validarTelefono(usuario.telefono)) {
            mostrarError("Teléfono inválido. Reintente");
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

    archivoUsuario = fopen("data/usuario.dat", "rb");

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

    mostrarInput("Ingrese Dirección Completa");
    scanf(" %[^\n]", cliente.direccion);
    convertirEspaciosAGuiones(cliente.direccion);

    archivoUsuario = fopen("data/usuario.dat", "ab");
    archivoCliente = fopen("data/cliente.dat", "ab");

    if(archivoUsuario != NULL && archivoCliente != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_cliente = fwrite(&cliente, sizeof(Cliente), 1, archivoCliente);

        fflush(archivoUsuario);
        fflush(archivoCliente);

        fclose(archivoUsuario);
        fclose(archivoCliente);

        if(resultado_usuario == 1 && resultado_cliente == 1){
            mostrarExito("Cliente agregado correctamente.");
            char idMsg[100];
            sprintf(idMsg, "ID asignado: %d", usuario.id_usuario);
            mostrarInfo(idMsg);
        } else {
            mostrarError("Fallo al escribir en los archivos.");
            char detalleMsg[150];
            sprintf(detalleMsg, "Usuario escrito: %d | Cliente escrito: %d", resultado_usuario, resultado_cliente);
            mostrarInfo(detalleMsg);
        }
    }
    else{
        mostrarError("No se pudo abrir los archivos.");

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

    archivoUsuario = fopen("data/usuario.dat", "rb");

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

    
    mostrarInput("Ingrese Patente de Vehiculo");
    scanf(" %[^\n]", repartidor.vehiculo);
    convertirEspaciosAGuiones(repartidor.vehiculo);

    generarMenu(menuDisponibilidad, 2);
    mostrarInput("Ingrese Estado de Disponibilidad");
    scanf("%d", &opcion);
    if(opcion == 1){
        strcpy(repartidor.estado_disponibilidad, "Activo");
    }else if(opcion == 2){
        strcpy(repartidor.estado_disponibilidad, "Inactivo");
    }

    archivoUsuario = fopen("data/usuario.dat", "ab");
    archivoRepartidor = fopen("data/repartidor.dat", "ab");

    if(archivoUsuario != NULL && archivoRepartidor != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_repartidor = fwrite(&repartidor, sizeof(Repartidor), 1, archivoRepartidor);

        fflush(archivoUsuario);
        fflush(archivoRepartidor);

        fclose(archivoUsuario);
        fclose(archivoRepartidor);

        if(resultado_usuario == 1 && resultado_repartidor == 1){
            mostrarExito("Repartidor agregado correctamente.");
            char idMsg[100];
            sprintf(idMsg, "ID asignado: %d", usuario.id_usuario);
            mostrarInfo(idMsg);
        } else {
            mostrarError("Fallo al escribir en los archivos.");
            char detalleMsg[150];
            sprintf(detalleMsg, "Usuario escrito: %d | Repartidor escrito: %d", resultado_usuario, resultado_repartidor);
            mostrarInfo(detalleMsg);
        }
    }
    else{
        mostrarError("No se pudo abrir los archivos.");

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

    archivoUsuario = fopen("data/usuario.dat", "rb");

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

    mostrarInput("Ingrese ID del Restaurante");
    scanf("%d", &encargado.id_restaurante);

    generarMenu(menuTurno, 3);
    mostrarInput("Ingrese Turno");
    scanf("%d", &opcion);
    if(opcion == 1){
        strcpy(encargado.turno, "Mañana");
    }else if(opcion == 2){
        strcpy(encargado.turno, "Tarde");
    }else if(opcion == 3){
        strcpy(encargado.turno, "Noche");
    }


    archivoUsuario = fopen("data/usuario.dat", "ab");
    archivoEncargado = fopen("data/encargado.dat", "ab");

    if(archivoUsuario != NULL && archivoEncargado != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_encargado = fwrite(&encargado, sizeof(Encargado), 1, archivoEncargado);

        fflush(archivoUsuario);
        fflush(archivoEncargado);

        fclose(archivoUsuario);
        fclose(archivoEncargado);

        if(resultado_usuario == 1 && resultado_encargado == 1){
            mostrarExito("Encargado agregado correctamente.");
            char idMsg[100];
            sprintf(idMsg, "ID asignado: %d", usuario.id_usuario);
            mostrarInfo(idMsg);
        } else {
            mostrarError("Fallo al escribir en los archivos.");
            char detalleMsg[150];
            sprintf(detalleMsg, "Usuario escrito: %d | Encargado escrito: %d", resultado_usuario, resultado_encargado);
            mostrarInfo(detalleMsg);
        }
    }
    else{
        mostrarError("No se pudo abrir los archivos.");

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

    archivoUsuario = fopen("data/usuario.dat", "rb");

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

    mostrarInput("Ingrese Nivel de Acceso");
    scanf("%d", &opcion);
    if(opcion == 1){
        strcpy(administrador.nivel_acceso, "superadmin");
    }else if(opcion == 2){
        strcpy(administrador.nivel_acceso, "admin");
    }else if(opcion == 3){
        strcpy(administrador.nivel_acceso, "supervisor");
    }

    archivoUsuario = fopen("data/usuario.dat", "ab");
    archivoAdministrador = fopen("data/administrador.dat", "ab");

    if(archivoUsuario != NULL && archivoAdministrador != NULL){
        int resultado_usuario = fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        int resultado_admin = fwrite(&administrador, sizeof(Administrador), 1, archivoAdministrador);

        fflush(archivoUsuario);
        fflush(archivoAdministrador);

        fclose(archivoUsuario);
        fclose(archivoAdministrador);

        if(resultado_usuario == 1 && resultado_admin == 1){
            mostrarExito("Administrador agregado correctamente.");
            char idMsg[100];
            sprintf(idMsg, "ID asignado: %d", usuario.id_usuario);
            mostrarInfo(idMsg);
        } else {
            mostrarError("Fallo al escribir en los archivos.");
            char detalleMsg[150];
            sprintf(detalleMsg, "Usuario escrito: %d | Administrador escrito: %d", resultado_usuario, resultado_admin);
            mostrarInfo(detalleMsg);
        }
    }
    else{
        mostrarError("No se pudo abrir los archivos.");

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

    archivo = fopen("data/usuario.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

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

    remove("data/usuario.dat");
    rename("data/auxiliar.dat", "data/usuario.dat");

    if(encontrado){ mostrarExito("Usuario eliminado correctamente."); }
    else{ mostrarError("Correo o contraseña incorrectos."); }
}
void eliminarCliente(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Cliente cliente;

    archivo = fopen("data/cliente.dat", "rb");
    auxiliar = fopen("data/auxiliar_data/cliente.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&cliente, sizeof(Cliente), 1, archivo) == 1){
        if(cliente.id_usuario != id_usuario){ fwrite(&cliente, sizeof(Cliente), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("data/cliente.dat");
    rename("data/auxiliar_data/cliente.dat", "data/cliente.dat");
}
void eliminarRepartidor(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Repartidor repartidor;

    archivo = fopen("data/repartidor.dat", "rb");
    auxiliar = fopen("data/auxiliar_data/repartidor.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&repartidor, sizeof(Repartidor), 1, archivo) == 1){
        if(repartidor.id_usuario != id_usuario){ fwrite(&repartidor, sizeof(Repartidor), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("data/repartidor.dat");
    rename("data/auxiliar_data/repartidor.dat", "data/repartidor.dat");
}
void eliminarEncargado(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Encargado encargado;

    archivo = fopen("data/encargado.dat", "rb");
    auxiliar = fopen("data/auxiliar_data/encargado.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&encargado, sizeof(Encargado), 1, archivo) == 1){
        if(encargado.id_usuario != id_usuario){ fwrite(&encargado, sizeof(Encargado), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("data/encargado.dat");
    rename("data/auxiliar_data/encargado.dat", "data/encargado.dat");
}
void eliminarAdministrador(int id_usuario){
    FILE *archivo;
    FILE *auxiliar;
    Administrador administrador;

    archivo = fopen("data/administrador.dat", "rb");
    auxiliar = fopen("data/auxiliar_data/administrador.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&administrador, sizeof(Administrador), 1, archivo) == 1){
        if(administrador.id_usuario != id_usuario){ fwrite(&administrador, sizeof(Administrador), 1, auxiliar); }
    }

    fclose(archivo);
    fclose(auxiliar);

    remove("data/administrador.dat");
    rename("data/auxiliar_data/administrador.dat", "data/administrador.dat");
}


/**Actualizar Datos*/
void actualizarUsuarioXid(Usuario usuario){
    FILE *archivo;
    Usuario reg;
    archivo = fopen("data/usuario.dat", "rb+");

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

            mostrarInfo("Seleccione Rol:");
            mostrarOpcion(1, "Cliente");
            mostrarOpcion(2, "Encargado");
            mostrarOpcion(3, "Repartidor");
            mostrarOpcion(4, "Administrador");
            mostrarInput("Opción");

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
                    mostrarError("Rol inválido.");
                    break;
                }
            }

            return;
        }
    }

    mostrarError("Usuario no encontrado.");
    fclose(archivo);
}
void actualizarClienteXid(int id_usuario){
    FILE *archivo;
    Cliente cliente;

    archivo = fopen("data/cliente.dat", "rb");

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

            mostrarExito("Cliente actualizado.");
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

    archivo = fopen("data/repartidor.dat", "rb");

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

            mostrarExito("Repartidor actualizado.");
            fclose(archivo);
            return;
        }
    }

    mostrarError("Repartidor no encontrado.");
    fclose(archivo);
}
void actualizarEncargadoXid(int id_usuario){
    FILE *archivo;
    Encargado encargado;

    archivo = fopen("data/encargado.dat", "rb");

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

            mostrarExito("Encargado actualizado.");
            fclose(archivo);
            return;
        }
    }

    mostrarError("Encargado no encontrado.");
    fclose(archivo);
}
void actualizarAdministradorXid(int id_usuario){
    FILE *archivo;
    Administrador administrador;

    archivo = fopen("data/administrador.dat", "rb");

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

            mostrarExito("Administrador actualizado.");
            fclose(archivo);
            return;
        }
    }

    mostrarError("Administrador no encontrado.");
    fclose(archivo);
}

static void obtenerTextoRolesUsuario(int id_usuario, char *buffer, size_t size){
    int roles[4] = {0};
    int offset = 0;

    obtenerRolesDelUsuario(id_usuario, roles);

    if(roles[0]) offset += snprintf(buffer + offset, size - offset, "%sCliente", offset > 0 ? ", " : "");
    if(roles[1]) offset += snprintf(buffer + offset, size - offset, "%sEncargado", offset > 0 ? ", " : "");
    if(roles[2]) offset += snprintf(buffer + offset, size - offset, "%sRepartidor", offset > 0 ? ", " : "");
    if(roles[3]) offset += snprintf(buffer + offset, size - offset, "%sAdmin", offset > 0 ? ", " : "");

    if(offset == 0){
        snprintf(buffer, size, "Sin roles");
    }
}

/**Mostrar Cuentas*/
void listarUsuarios(){
    FILE *archivo;
    Usuario usuario;
    archivo = fopen("data/usuario.dat", "rb");

    if(archivo == NULL){
        printf("\nNo se pudo abrir data/usuario.dat\n");
        return;
    }
    limpiarPantalla();
    mostrarCaja("LISTADO DE USUARIOS");
    
    while(fread(&usuario, sizeof(Usuario), 1, archivo) == 1){
        char rolesTexto[120];
        char detalle[320];
        obtenerTextoRolesUsuario(usuario.id_usuario, rolesTexto, sizeof(rolesTexto));
        snprintf(detalle, sizeof(detalle), "ID: %d | Nombre: %s %s | Email: %s | Teléfono: %s | Roles: %s", usuario.id_usuario, usuario.nombre, usuario.apellido, usuario.email, usuario.telefono, rolesTexto);
        mostrarInfo(detalle);
        mostrarLinea();
    }
    mostrarCajaFin();
    fclose(archivo);
}

void listarRepartidores(){
    FILE *archivo;
    Usuario usuario;
    archivo = fopen("data/usuario.dat", "rb");

    if(archivo == NULL){
        printf("\nNo se pudo abrir data/usuario.dat\n");
        return;
    }
    limpiarPantalla();
    mostrarCaja("LISTADO DE REPARTIDORES");
    
    while(fread(&usuario, sizeof(Usuario), 1, archivo) == 1){
        if( esRepartidor(usuario.id_usuario) ){
            char detalle[250];
            sprintf(detalle, "ID: %d | Nombre: %s %s | Email: %s | Teléfono: %s", usuario.id_usuario, usuario.nombre, usuario.apellido, usuario.email, usuario.telefono);
            mostrarInfo(detalle);
            mostrarLinea();
        }
    }
    mostrarCajaFin();
    fclose(archivo);
}

void seleccionarCuenta(Usuario usuario){
    FILE *archivo;
    archivo = fopen("data/usuario.dat", "rb");

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
        mostrarExito("Inicio de sesión correcto.");
        char bienvenida[120];
        sprintf(bienvenida, "Bienvenido %s %s", usuario.nombre, usuario.apellido);
        mostrarInfo(bienvenida);
    }

    pausar();
    limpiarPantalla();

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

        limpiarPantalla();
        mostrarCaja("SELECCIONE SU ROL");
        mostrarInfo("Tiene múltiples roles disponibles:");

        int contador = 1;
        if(roles_actuales[0]){ mostrarOpcion(contador++, "Cliente"); }
        if(roles_actuales[1]){ mostrarOpcion(contador++, "Encargado"); }
        if(roles_actuales[2]){ mostrarOpcion(contador++, "Repartidor"); }
        if(roles_actuales[3]){ mostrarOpcion(contador++, "Administrador"); }

        mostrarInput("Ingrese el rol con el que desea iniciar sesión");

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

        limpiarPantalla();

        if(rol_actual == 0){
            mostrarError("Opción inválida.");
            pausar();
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
        mostrarError("No se encontró rol asociado a esta cuenta.");
        pausar();
    }
}
int esCliente(int id_usuario){
    FILE *archivo;
    archivo = fopen("data/cliente.dat", "rb");

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
    archivo = fopen("data/encargado.dat", "rb");

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
    archivo = fopen("data/repartidor.dat", "rb");

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
    archivo = fopen("data/administrador.dat", "rb");

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
    archivo = fopen("data/usuario.dat", "rb");

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
    FILE *archivoUsuario = fopen("data/usuario.dat", "rb");
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
        mostrarError("No se encontró el usuario.");
        pausar();
        return;
    }

    obtenerRolesDelUsuario(id_usuario, roles_actuales);

    limpiarPantalla();
    mostrarCaja("AGREGAR NUEVO ROL");
    char userInfo[200];
    sprintf(userInfo, "Usuario: %s %s | Email: %s", usuario.nombre, usuario.apellido, usuario.email);
    mostrarInfo(userInfo);
    
    mostrarInfo("Roles actuales:");
    if(roles_actuales[0]) mostrarInfo("Cliente");
    if(roles_actuales[1]) mostrarInfo("Encargado");
    if(roles_actuales[2]) mostrarInfo("Repartidor");
    if(roles_actuales[3]) mostrarInfo("Administrador");

    mostrarInfo("Roles disponibles:");
    if(!roles_actuales[0]) mostrarOpcion(1, "Cliente");
    if(!roles_actuales[1]) mostrarOpcion(2, "Encargado");
    if(!roles_actuales[2]) mostrarOpcion(3, "Repartidor");
    if(!roles_actuales[3]) mostrarOpcion(4, "Administrador");

    mostrarInput("Ingrese el rol a agregar");

    if(scanf("%d", &rol) != 1){
        while (getchar() != '\n');
        rol = -1;
    }

    if (rol < 1 || rol > 4) {
        mostrarError("Opción inválida.");
        pausar();
        return;
    }

    if(tieneRol(id_usuario, rol)){
        mostrarError("Este usuario ya tiene este rol.");
        pausar();
        return;
    }

    usuario.id_usuario = id_usuario;

    switch(rol){
        case 1:{
            FILE *archivoCliente = fopen("data/cliente.dat", "ab");
            if(archivoCliente != NULL){
                Cliente cliente;
                cliente.id_usuario = id_usuario;
                mostrarInput("Ingrese Direccion");
                scanf(" %[^\n]", cliente.direccion);
                convertirEspaciosAGuiones(cliente.direccion);
                int resultado = fwrite(&cliente, sizeof(Cliente), 1, archivoCliente);
                fflush(archivoCliente);
                fclose(archivoCliente);
                if(resultado == 1){
                    mostrarExito("Rol Cliente agregado exitosamente.");
                } else {
                    mostrarError("Fallo al escribir rol de cliente.");
                }
            } else {
                mostrarError("No se pudo abrir archivo de clientes.");
            }
            break;
        }
        case 2:{
            FILE *archivoEncargado = fopen("data/encargado.dat", "ab");
            if(archivoEncargado != NULL){
                Encargado encargado;
                encargado.id_usuario = id_usuario;
                printf("\nIngrese ID del Restaurante: ");
                scanf("%d", &encargado.id_restaurante);
                mostrarInput("Ingrese Turno");
                scanf(" %[^\n]", encargado.turno);
                convertirEspaciosAGuiones(encargado.turno);
                int resultado = fwrite(&encargado, sizeof(Encargado), 1, archivoEncargado);
                fflush(archivoEncargado);
                fclose(archivoEncargado);
                if(resultado == 1){
                    mostrarExito("Rol Encargado agregado exitosamente.");
                } else {
                    mostrarError("Fallo al escribir rol de encargado.");
                }
            } else {
                mostrarError("No se pudo abrir archivo de encargados.");
            }
            break;
        }
        case 3:{
            FILE *archivoRepartidor = fopen("data/repartidor.dat", "ab");
            if(archivoRepartidor != NULL){
                Repartidor repartidor;
                repartidor.id_usuario = id_usuario;
                mostrarInput("Ingrese Vehiculo");
                scanf(" %[^\n]", repartidor.vehiculo);
                convertirEspaciosAGuiones(repartidor.vehiculo);
                mostrarInput("Ingrese Estado de Disponibilidad");
                scanf(" %[^\n]", repartidor.estado_disponibilidad);
                convertirEspaciosAGuiones(repartidor.estado_disponibilidad);
                int resultado = fwrite(&repartidor, sizeof(Repartidor), 1, archivoRepartidor);
                fflush(archivoRepartidor);
                fclose(archivoRepartidor);
                if(resultado == 1){
                    mostrarExito("Rol Repartidor agregado exitosamente.");
                } else {
                    mostrarError("Fallo al escribir rol de repartidor.");
                }
            } else {
                mostrarError("No se pudo abrir archivo de repartidores.");
            }
            break;
        }
        case 4:{
            FILE *archivoAdministrador = fopen("data/administrador.dat", "ab");
            if(archivoAdministrador != NULL){
                Administrador administrador;
                administrador.id_usuario = id_usuario;
                mostrarInput("Ingrese Nivel de Acceso (superadmin, admin, supervisor)");
                scanf(" %[^\n]", administrador.nivel_acceso);
                convertirEspaciosAGuiones(administrador.nivel_acceso);
                int resultado = fwrite(&administrador, sizeof(Administrador), 1, archivoAdministrador);
                fflush(archivoAdministrador);
                fclose(archivoAdministrador);
                if(resultado == 1){
                    mostrarExito("Rol Administrador agregado exitosamente.");
                } else {
                    mostrarError("Fallo al escribir rol de administrador.");
                }
            } else {
                mostrarError("No se pudo abrir archivo de administradores.");
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

    limpiarPantalla();
    mostrarCaja("ELIMINAR USUARIO");
    listarUsuarios();

    mostrarInput("Ingrese el ID del usuario a eliminar");
    scanf("%d", &id_a_eliminar);

    archivo = fopen("data/usuario.dat", "rb");
    if(archivo == NULL){
        mostrarError("No se puede abrir archivo de usuarios.");
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
        char msg[120];
        sprintf(msg, "Usuario con ID %d no encontrado.", id_a_eliminar);
        mostrarError(msg);
        return;
    }

    if(usuario.id_usuario == usuario_actual.id_usuario){
        mostrarError("No puedes eliminar tu propio usuario.");
        system("pause");
        return;
    }

    // Mostrar datos y pedir confirmación
    mostrarCaja("CONFIRMAR ELIMINACIÓN");
    mostrarInfo("¿Desea eliminar este usuario?");
    char datosUsuario[200];
    sprintf(datosUsuario, "Nombre: %s %s | Email: %s | ID: %d", usuario.nombre, usuario.apellido, usuario.email, usuario.id_usuario);
    mostrarInfo(datosUsuario);
    mostrarInfo("Esta acción NO se puede deshacer.");
    mostrarOpcion(1, "Sí, eliminar usuario");
    mostrarOpcion(2, "No, cancelar");
    mostrarCajaFin();
    mostrarInput("Opción");

    scanf("%d", &confirmacion);

    if(confirmacion != 1){
        mostrarExito("Operación cancelada.");
        system("pause");
        return;
    }

    FILE *auxiliar;
    Usuario reg;
    int eliminado = 0;

    archivo = fopen("data/usuario.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

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

    remove("data/usuario.dat");
    rename("data/auxiliar.dat", "data/usuario.dat");

    if(eliminado){
        mostrarExito("Usuario eliminado correctamente.");
    } else {
        mostrarError("No se pudo eliminar el usuario.");
    }

    system("pause");
}

void eliminarRestaurantePorId(){
    int id_a_eliminar;
    int confirmacion;
    FILE *archivo;
    Restaurante restaurante;
    int encontrado = 0;

    limpiarPantalla();
    mostrarCaja("ELIMINAR RESTAURANTE");
    mostrarSubtitulo("Confirme la operación");
    mostrarLinea();
    listarRestaurantes();

    mostrarInput("Ingrese el ID del restaurante a eliminar");
    scanf("%d", &id_a_eliminar);

    archivo = fopen("data/restaurante.dat", "rb");
    if(archivo == NULL){
        mostrarError("No se puede abrir archivo de restaurantes.");
        pausar();
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
        char msg[120];
        sprintf(msg, "Restaurante con ID %d no encontrado.", id_a_eliminar);
        mostrarError(msg);
        pausar();
        return;
    }

    limpiarPantalla();
    mostrarCaja("CONFIRMAR ELIMINACIÓN");
    mostrarInfo("¿Desea eliminar este restaurante?");
    char info[200];
    sprintf(info, "Nombre: %s | Teléfono: %s | Estado: %s | ID: %d", restaurante.nombre, restaurante.telefono, restaurante.estado, restaurante.id_restaurante);
    mostrarInfo(info);
    mostrarInfo("Esta acción NO se puede deshacer.");
    mostrarOpcion(1, "Sí, eliminar restaurante");
    mostrarOpcion(2, "No, cancelar");
    mostrarCajaFin();
    mostrarInput("Opción");

    scanf("%d", &confirmacion);

    if(confirmacion != 1){
        mostrarExito("Operación cancelada.");
        pausar();
        return;
    }

    FILE *auxiliar;
    Restaurante reg;
    int eliminado = 0;

    archivo = fopen("data/restaurante.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        mostrarError("No se pueden abrir los archivos.");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        pausar();
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

    remove("data/restaurante.dat");
    rename("data/auxiliar.dat", "data/restaurante.dat");

    if(eliminado){
        mostrarExito("Restaurante eliminado correctamente.");
    } else {
        mostrarError("No se pudo eliminar el restaurante.");
    }

    pausar();
}

// =========================
// RESTAURANTES Y PRODUCTOS
// =========================

//PANEL PARA ADMINISTRADOR
//Agregar
void agregarRestaurante(){
    Restaurante restaurante;

    limpiarPantalla();
    mostrarCaja("INGRESAR RESTAURANTES");
    mostrarSubtitulo("Complete los datos del restaurante");
    mostrarLinea();

    do {
        mostrarInput("Ingrese Nombre");
        scanf(" %[^\n]", restaurante.nombre);
        if (!validarNombre(restaurante.nombre)) {
            mostrarError("Nombre inválido. Reintente");
        } else {
            convertirEspaciosAGuiones(restaurante.nombre);
            break;
        }
    } while(1);

    do {
        mostrarInput("Ingrese Teléfono");
        scanf(" %[^\n]", restaurante.telefono);
        convertirEspaciosAGuiones(restaurante.telefono);
        if (!validarTelefono(restaurante.telefono)) {
            mostrarError("Teléfono inválido. Reintente");
        } else {
            break;
        }
    } while(1);

    do {
        mostrarInput("Ingrese Horario de Apertura (HH:MM)");
        scanf(" %[^\n]", restaurante.horario_apertura);
        convertirEspaciosAGuiones(restaurante.horario_apertura);
        if (!validarHorario(restaurante.horario_apertura)) {
            mostrarError("Horario inválido. Reintente");
        } else {
            break;
        }
    } while(1);

    do {
        mostrarInput("Ingrese Horario de Cierre (HH:MM)");
        scanf(" %[^\n]", restaurante.horario_cierre);
        convertirEspaciosAGuiones(restaurante.horario_cierre);
        if (!validarHorario(restaurante.horario_cierre)) {
            mostrarError("Horario inválido. Reintente");
        } else {
            break;
        }
    } while(1);

    do {
        mostrarInput("Ingrese Estado (activo/inactivo/mantenimiento)");
        scanf(" %[^\n]", restaurante.estado);
        convertirEspaciosAGuiones(restaurante.estado);
        if (!validarEstadoRestaurante(restaurante.estado)) {
            mostrarError("Estado inválido. Reintente");
        } else {
            break;
        }
    } while(1);

    mostrarCajaFin();
    agregarUbicacionRestaurante(restaurante);
}
void agregarUbicacionRestaurante(Restaurante restaurante){
    FILE *archivoRestaurante;
    FILE *archivoUbicacion;

    Restaurante auxRestaurante;
    UbicacionRestaurante ubicacion;

    int ultimoId = 0;

    archivoRestaurante = fopen("data/restaurante.dat", "rb");

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

    limpiarPantalla();
    mostrarCaja("INGRESAR UBICACIÓN");
    mostrarSubtitulo(restaurante.nombre);
    mostrarLinea();

    mostrarInput("Ingrese Dirección");
    scanf(" %[^\n]", ubicacion.direccion);
    convertirEspaciosAGuiones(ubicacion.direccion);

    mostrarInput("Ingrese Número");
    scanf("%d", &ubicacion.numero);

    mostrarInput("Ingrese Ciudad");
    scanf(" %[^\n]", ubicacion.ciudad);
    convertirEspaciosAGuiones(ubicacion.ciudad);

    mostrarInput("Ingrese Provincia");
    scanf(" %[^\n]", ubicacion.provincia);
    convertirEspaciosAGuiones(ubicacion.provincia);

    mostrarInput("Ingrese Código Postal");
    scanf(" %[^\n]", ubicacion.codigo_postal);
    convertirEspaciosAGuiones(ubicacion.codigo_postal);

    archivoRestaurante = fopen("data/restaurante.dat", "ab");
    archivoUbicacion = fopen("data/ubicacion_data/restaurante.dat", "ab");

    if(archivoRestaurante != NULL && archivoUbicacion != NULL){
        fwrite(&restaurante, sizeof(Restaurante), 1, archivoRestaurante);
        fwrite(&ubicacion, sizeof(UbicacionRestaurante), 1, archivoUbicacion);

        fclose(archivoRestaurante);
        fclose(archivoUbicacion);

        mostrarExito("Restaurante agregado correctamente.");
        char idMsg[100];
        sprintf(idMsg, "ID asignado: %d", restaurante.id_restaurante);
        mostrarInfo(idMsg);
        mostrarCajaFin();
        pausar();
    } else{
        mostrarError("Error al abrir archivos.");

        if(archivoRestaurante != NULL)
            fclose(archivoRestaurante);

        if(archivoUbicacion != NULL)
            fclose(archivoUbicacion);
        pausar();
    }
}

//Mostrar - Listar
void listarRestaurantes(){
    FILE *archivo;
    Restaurante restaurante;

    archivo = fopen("data/restaurante.dat", "rb");

    if(archivo == NULL){
        mostrarError("No se pudo abrir data/restaurante.dat");
        return;
    }

    limpiarPantalla();
    mostrarCaja("LISTADO DE RESTAURANTES");
    mostrarSubtitulo("Restaurantes registrados");
    mostrarLinea();

    while(fread(&restaurante, sizeof(Restaurante), 1, archivo) == 1){
        char info[300];
        sprintf(info, "ID: %d | Nombre: %s | Tel: %s | Estado: %s", restaurante.id_restaurante, restaurante.nombre, restaurante.telefono, restaurante.estado);
        mostrarInfo(info);
        char horario[120];
        sprintf(horario, "Horario: %s - %s", restaurante.horario_apertura, restaurante.horario_cierre);
        mostrarInfo(horario);
        listarUbicacionesRestaurante(restaurante.id_restaurante);
        mostrarLinea();
    }

    mostrarCajaFin();

    fclose(archivo);
}
void listarUbicacionesRestaurante(int id_restaurante){
    FILE *archivo;
    UbicacionRestaurante ubicacion;

    archivo = fopen("data/ubicacion_data/restaurante.dat", "rb");

    if(archivo == NULL){
        mostrarInfo("No se pudo abrir ubicacion_data/restaurante.dat");
        return;
    }

    while(fread(&ubicacion, sizeof(UbicacionRestaurante), 1, archivo) == 1){
        if(ubicacion.id_restaurante == id_restaurante){
            char ubicacionInfo[250];
            sprintf(ubicacionInfo, "Ubicación: %s | N° %d | %s, %s | CP: %s", ubicacion.direccion, ubicacion.numero, ubicacion.ciudad, ubicacion.provincia, ubicacion.codigo_postal);
            mostrarInfo(ubicacionInfo);
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
    char tipoProducto[4][50] = {
        "[1] Desayuno",
        "[2] Comida",
        "[3] Postre",
        "[4] Guarnicion"
    };
    int categoria;

    limpiarPantalla();
    mostrarCaja("AGREGAR PRODUCTO");
    mostrarSubtitulo("Complete los datos del producto");
    mostrarLinea();

    do {
        mostrarInput("Ingrese Nombre del Producto");
        scanf(" %[^\n]", producto.nombre_producto);
        convertirEspaciosAGuiones(producto.nombre_producto);
        if (!validarNombre(producto.nombre_producto)) {
            mostrarError("Nombre inválido. Reintente");
        } else {
            break;
        }
    } while(1);

    mostrarInput("Ingrese Descripción (max 500 caracteres)");
    scanf(" %[^\n]", producto.descripcion);
    convertirEspaciosAGuiones(producto.descripcion);

    do {
        mostrarInput("Ingrese Precio");
        if(scanf("%lf", &producto.precio) != 1 || producto.precio <= 0) {
            while(getchar() != '\n');
            mostrarError("Precio debe ser mayor a 0.");
        } else {
            while(getchar() != '\n');
            break;
        }
    } while(1);

    mostrarInfo("Seleccione categoría:");
    generarMenu(tipoProducto, 4);
    mostrarCajaFin();
    mostrarInput("Ingrese Categoría");
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

    archivoProducto = fopen("data/producto.dat", "rb");
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

    archivoProducto = fopen("data/producto.dat", "ab");
    if(archivoProducto != NULL){
        int resultado = fwrite(&producto, sizeof(Producto), 1, archivoProducto);
        fflush(archivoProducto);
        fclose(archivoProducto);
        if(resultado == 1){
            mostrarExito("Producto agregado exitosamente.");
            char idProductoMsg[100];
            sprintf(idProductoMsg, "ID: %d", producto.id_producto);
            mostrarInfo(idProductoMsg);
        } else {
            mostrarError("Fallo al guardar producto.");
        }
    } else {
        mostrarError("No se pudo abrir archivo de productos.");
    }
    pausar();
}

void listarProductosRestaurante(int id_restaurante){
    FILE *archivo;
    Producto producto;
    int cantidad = 0;

    limpiarPantalla();
    mostrarCaja("MENÚ DEL RESTAURANTE");
    mostrarSubtitulo("Productos disponibles");
    mostrarLinea();

    archivo = fopen("data/producto.dat", "rb");
    if(archivo == NULL){
        mostrarInfo("No hay productos disponibles aún.");
        mostrarCajaFin();
        pausar();
        return;
    }

    while(fread(&producto, sizeof(Producto), 1, archivo) == 1){
        if(producto.id_menu == id_restaurante && strcmp(producto.disponibilidad, "disponible") == 0){
            cantidad++;
            char prodInfo[250];
            sprintf(prodInfo, "[%d] %s | Precio: $%.2f | Categoría: %s | Estado: %s", producto.id_producto, producto.nombre_producto, producto.precio, producto.categoria, producto.disponibilidad);
            mostrarInfo(prodInfo);
            char descInfo[250];
            sprintf(descInfo, "Descripción: %s", producto.descripcion);
            mostrarInfo(descInfo);
        }
    }

    if(cantidad == 0){
        mostrarInfo("No hay productos disponibles.");
    } else {
        char totalMsg[100];
        sprintf(totalMsg, "Total de productos: %d", cantidad);
        mostrarInfo(totalMsg);
    }

    mostrarCajaFin();
    fclose(archivo);
    pausar();
}

void modificarProducto(int id_restaurante){
    FILE *archivo;
    FILE *auxiliar;
    Producto producto;
    int id_buscar;
    int encontrado = 0;
    int opcion;

    limpiarPantalla();
    mostrarCaja("MODIFICAR PRODUCTO");
    mostrarSubtitulo("Seleccione el producto a actualizar");
    mostrarLinea();

    mostrarInput("Ingrese ID del producto a modificar");
    scanf("%d", &id_buscar);

    archivo = fopen("data/producto.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\n[ERROR] No se pueden abrir los archivos.\n");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&producto, sizeof(Producto), 1, archivo) == 1){
        if(producto.id_producto == id_buscar && producto.id_menu == id_restaurante){
            encontrado = 1;
            char encontradoMsg[120];
            sprintf(encontradoMsg, "Producto encontrado: %s", producto.nombre_producto);
            mostrarInfo(encontradoMsg);
            mostrarInfo("¿Qué deseas modificar?");
            mostrarOpcion(1, "Nombre");
            mostrarOpcion(2, "Descripción");
            mostrarOpcion(3, "Precio");
            mostrarOpcion(4, "Categoría");
            mostrarOpcion(5, "Disponibilidad");
            mostrarOpcion(6, "Cancelar");
            mostrarInput("Opción");
            scanf("%d", &opcion);

            switch(opcion){
                case 1:
                    mostrarInput("Nuevo nombre");
                    scanf(" %[^\n]", producto.nombre_producto);
                    convertirEspaciosAGuiones(producto.nombre_producto);
                    break;
                case 2:
                    mostrarInput("Nueva descripción");
                    scanf(" %[^\n]", producto.descripcion);
                    convertirEspaciosAGuiones(producto.descripcion);
                    break;
                case 3:
                    mostrarInput("Nuevo precio");
                    scanf("%lf", &producto.precio);
                    break;
                case 4:
                    mostrarInput("Nueva categoría");
                    scanf(" %[^\n]", producto.categoria);
                    convertirEspaciosAGuiones(producto.categoria);
                    break;
                case 5:
                    mostrarInput("Nuevo estado (disponible/inactivo)");
                    scanf(" %[^\n]", producto.disponibilidad);
                    convertirEspaciosAGuiones(producto.disponibilidad);
                    break;
                case 6:
                    mostrarExito("Operación cancelada.");
                    break;
            }
        }

        fwrite(&producto, sizeof(Producto), 1, auxiliar);
    }

    fclose(archivo);
    fclose(auxiliar);

    if(encontrado){
        remove("data/producto.dat");
        rename("data/auxiliar.dat", "data/producto.dat");
        mostrarExito("Producto modificado exitosamente.");
    } else {
        remove("data/auxiliar.dat");
        mostrarError("Producto no encontrado.");
    }
    pausar();
}

void listarProductos(){
    FILE *archivo;
    Producto producto;

    printf("\n========== LISTADO DE TODOS LOS PRODUCTOS ==========\n");

    archivo = fopen("data/producto.dat", "rb");
    if(archivo == NULL){
        mostrarInfo("No hay productos en el sistema.");
        mostrarCajaFin();
        pausar();
        return;
    }

    while(fread(&producto, sizeof(Producto), 1, archivo) == 1){
        char info[250];
        sprintf(info, "[%d] %s | Menú ID: %d | Precio: $%.2f | Categoría: %s | Estado: %s", producto.id_producto, producto.nombre_producto, producto.id_menu, producto.precio, producto.categoria, producto.disponibilidad);
        mostrarInfo(info);
        char descInfo[250];
        sprintf(descInfo, "Descripción: %s", producto.descripcion);
        mostrarInfo(descInfo);
        mostrarLinea();
    }

    mostrarCajaFin();
    fclose(archivo);
    pausar();
}

// =========================
// PEDIDOS Y ENTREGAS
// =========================

int obtenerSiguientePedidoId(){
    FILE *archivo = fopen("data/pedido.dat", "rb");
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

    limpiarPantalla();
    mostrarCaja("REALIZAR PEDIDO");
    mostrarSubtitulo("Seleccione un restaurante");
    mostrarLinea();

    // Listar restaurantes disponibles
    archivoRestaurante = fopen("data/restaurante.dat", "rb");
    if(archivoRestaurante == NULL || (fseek(archivoRestaurante, 0, SEEK_END) == 0 && ftell(archivoRestaurante) == 0)){
        mostrarError("No hay restaurantes disponibles.");
        mostrarCajaFin();
        if(archivoRestaurante != NULL) fclose(archivoRestaurante);
        pausar();
        return;
    }

    mostrarInfo("Restaurantes disponibles:");
    fseek(archivoRestaurante, 0, SEEK_SET);

    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurante) == 1){
        cantidad_restaurantes++;
        mostrarOpcion(restaurante.id_restaurante, restaurante.nombre);
    }
    fclose(archivoRestaurante);

    if(cantidad_restaurantes == 0){
        mostrarError("No hay restaurantes disponibles.");
        mostrarCajaFin();
        pausar();
        return;
    }

    mostrarCajaFin();
    mostrarInput("Seleccione ID de restaurante");
    scanf("%d", &seleccion);

    // Verificar que exista el restaurante
    archivoRestaurante = fopen("data/restaurante.dat", "rb");
    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurante) == 1){
        if(restaurante.id_restaurante == seleccion){
            id_restaurante = restaurante.id_restaurante;
            break;
        }
    }
    fclose(archivoRestaurante);

    if(id_restaurante == -1){
        mostrarError("Restaurante no encontrado.");
        pausar();
        mostrarCajaFin();
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
        limpiarPantalla();
        mostrarCaja("SELECCIONAR PRODUCTOS");
        mostrarSubtitulo("Elija los productos para su pedido");
        mostrarLinea();

        char restauranteMsg[100];
        sprintf(restauranteMsg, "Restaurante seleccionado: %d", id_restaurante);
        mostrarInfo(restauranteMsg);

        char totalMsg[100];
        sprintf(totalMsg, "Total actual: $%.2f", total_pedido);
        mostrarInfo(totalMsg);
        mostrarInfo("Productos disponibles:");

        archivoProducto = fopen("data/producto.dat", "rb");
        if(archivoProducto != NULL){
            while(fread(&producto, sizeof(Producto), 1, archivoProducto) == 1){
                if(producto.id_menu == id_restaurante && strcmp(producto.disponibilidad, "disponible") == 0){
                    char prodInfo[200];
                    sprintf(prodInfo, "%s - $%.2f", producto.nombre_producto, producto.precio);
                    mostrarOpcion(producto.id_producto, prodInfo);
                }
            }
            fclose(archivoProducto);
        }

        mostrarOpcion(0, "Terminar selección");
        mostrarCajaFin();
        mostrarInput("Ingrese ID de producto (o 0 para terminar)");
        scanf("%d", &producto_id);

        if(producto_id == 0){
            seguir = 0;
            break;
        }

        archivoProducto = fopen("data/producto.dat", "rb");
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
            mostrarError("Producto no encontrado o no disponible.");
            pausar();
            continue;
        }

        mostrarInput("Ingrese cantidad");
        scanf("%d", &cantidad_producto);

        if(cantidad_producto <= 0){
            mostrarError("La cantidad debe ser mayor a 0.");
            pausar();
            continue;
        }

        detalle.id_orden = pedido.id_pedido;
        detalle.id_producto = producto_id;
        detalle.cantidad = cantidad_producto;
        strcpy(detalle.estado_item, "Pendiente");
        strcpy(detalle.observaciones, "");

        archivoDetalle = fopen("data/detalle_orden.dat", "ab");
        if(archivoDetalle != NULL){
            fwrite(&detalle, sizeof(DetalleOrden), 1, archivoDetalle);
            fflush(archivoDetalle);
            fclose(archivoDetalle);
        }

        total_pedido += precio_producto * cantidad_producto;
        char addedMsg[200];
        sprintf(addedMsg, "Producto agregado. Subtotal: $%.2f", total_pedido);
        mostrarExito(addedMsg);
    }

    if(total_pedido == 0){
        mostrarError("El pedido debe tener al menos un producto.");
        pausar();
        mostrarCajaFin();
        return;
    }

    // Ingresar datos de entrega
    limpiarPantalla();
    mostrarCaja("DATOS DE ENTREGA");
    mostrarInput("Dirección de entrega");
    scanf(" %[^\n]", pedido.direccion_entrega);

    mostrarInput("Observaciones (opcional)");
    scanf(" %[^\n]", pedido.observaciones);

    pedido.total = total_pedido;

    archivoPedido = fopen("data/pedido.dat", "ab");
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

    archivoOrden = fopen("data/orden_preparacion.dat", "ab");
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

    archivoHistorial = fopen("data/historial_estado.dat", "ab");
    if(archivoHistorial != NULL){
        fwrite(&historial, sizeof(HistorialEstado), 1, archivoHistorial);
        fflush(archivoHistorial);
        fclose(archivoHistorial);
    }

    realizarPago(usuario, pedido.id_pedido);

    limpiarPantalla();
    mostrarCaja("PEDIDO CREADO EXITOSAMENTE");
    char successMsg[200];
    sprintf(successMsg, "ID: %d | Total: $%.2f | Estado: %s", pedido.id_pedido, pedido.total, pedido.estado);
    mostrarExito(successMsg);
    mostrarCajaFin();
}

// CLIENTE: Ver mis pedidos
void listarMisPedidos(Usuario usuario){
    FILE *archivo;
    Pedido pedido;
    Pedido pedidosUsuario[100];
    int cantidad = 0;
    int seleccion = 0;

    limpiarPantalla();
    mostrarCaja("MIS PEDIDOS");

    archivo = fopen("data/pedido.dat", "rb");
    if(archivo == NULL){
        mostrarInfo("No tienes pedidos registrados.");
        mostrarCajaFin();
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
        if(pedido.id_cliente == usuario.id_usuario){
            pedidosUsuario[cantidad++] = pedido;
            if(cantidad >= 100){
                break;
            }
        }
    }
    fclose(archivo);

    if(cantidad == 0){
        mostrarInfo("No tienes pedidos registrados.");
        mostrarCajaFin();
        return;
    }

    mostrarInfo("Tus pedidos disponibles:");
    for(int i = 0; i < cantidad; i++){
        char pedidoInfo[320];
        snprintf(pedidoInfo, sizeof(pedidoInfo), "ID: %d | Fecha: %s | Estado: %s | Dir: %s",
                 pedidosUsuario[i].id_pedido, pedidosUsuario[i].fecha_pedido,
                 pedidosUsuario[i].estado, pedidosUsuario[i].direccion_entrega);
        mostrarOpcion(i + 1, pedidoInfo);
    }

    mostrarInput("Seleccione un pedido para ver detalles (0 para volver)");
    if(scanf("%d", &seleccion) != 1){
        while(getchar() != '\n');
        seleccion = -1;
    }

    if(seleccion <= 0 || seleccion > cantidad){
        mostrarInfo("No se seleccionó ningún pedido.");
        mostrarCajaFin();
        pausar();
        return;
    }

    limpiarPantalla();
    mostrarCaja("DETALLE DEL PEDIDO");

    Pedido pedidoSeleccionado = pedidosUsuario[seleccion - 1];
    char resumenPedido[300];
    snprintf(resumenPedido, sizeof(resumenPedido), "Pedido ID: %d | Fecha: %s | Estado: %s | Total: $%.2f",
             pedidoSeleccionado.id_pedido, pedidoSeleccionado.fecha_pedido,
             pedidoSeleccionado.estado, pedidoSeleccionado.total);
    mostrarInfo(resumenPedido);

    char direccionMsg[220];
    snprintf(direccionMsg, sizeof(direccionMsg), "Dirección: %s", pedidoSeleccionado.direccion_entrega);
    mostrarInfo(direccionMsg);

    char obsMsg[220];
    snprintf(obsMsg, sizeof(obsMsg), "Observaciones: %s", pedidoSeleccionado.observaciones[0] != '\0' ? pedidoSeleccionado.observaciones : "Sin observaciones");
    mostrarInfo(obsMsg);
    mostrarLinea();

    FILE *archivoDetalle = fopen("data/detalle_orden.dat", "rb");
    FILE *archivoProducto = fopen("data/producto.dat", "rb");
    if(archivoDetalle != NULL && archivoProducto != NULL){
        DetalleOrden detalle;
        Producto producto;
        int hayProductos = 0;
        double totalProductos = 0;

        mostrarInfo("Productos del pedido:");
        while(fread(&detalle, sizeof(DetalleOrden), 1, archivoDetalle) == 1){
            if(detalle.id_orden != pedidoSeleccionado.id_pedido){
                continue;
            }

            rewind(archivoProducto);
            int encontradoProducto = 0;
            while(fread(&producto, sizeof(Producto), 1, archivoProducto) == 1){
                if(producto.id_producto == detalle.id_producto){
                    encontradoProducto = 1;
                    break;
                }
            }

            if(encontradoProducto){
                double subtotal = detalle.cantidad * producto.precio;
                totalProductos += subtotal;
                hayProductos = 1;
                char productoMsg[360];
                snprintf(productoMsg, sizeof(productoMsg), "- %s | Cant: %d | Precio unit.: $%.2f | Subtotal: $%.2f",
                         producto.nombre_producto, detalle.cantidad, producto.precio, subtotal);
                mostrarInfo(productoMsg);
            }
        }

        if(!hayProductos){
            mostrarInfo("No hay productos registrados para este pedido.");
        } else {
            char totalProductosMsg[160];
            snprintf(totalProductosMsg, sizeof(totalProductosMsg), "Total calculado de productos: $%.2f", totalProductos);
            mostrarInfo(totalProductosMsg);
        }
    } else {
        mostrarInfo("No se pudo cargar la información de productos.");
    }

    if(archivoDetalle != NULL) fclose(archivoDetalle);
    if(archivoProducto != NULL) fclose(archivoProducto);

    mostrarLinea();
    mostrarInfo("Use el menú principal para continuar.");
    mostrarCajaFin();
    pausar();
}

// Ver historial de estados de un pedido
void obtenerHistorialEstados(int id_pedido){
    FILE *archivo;
    HistorialEstado historial;

    printf("\n--- Historial de Estados (Pedido #%d) ---\n", id_pedido);

    archivo = fopen("data/historial_estado.dat", "rb");
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
    FILE *archivo = fopen("data/pago.dat", "rb");
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

    limpiarPantalla();
    mostrarCaja("REALIZAR PAGO");

    // Verificar que el pedido pertenezca al usuario
    archivoPedido = fopen("data/pedido.dat", "rb");
    if(archivoPedido == NULL){
        mostrarError("No se encontraron pedidos.");
        pausar();
        mostrarCajaFin();
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
        mostrarError("Pedido no encontrado o no pertenece a tu cuenta.");
        pausar();
        mostrarCajaFin();
        return;
    }

    mostrarInfo("Selecciona método de pago:");
    mostrarOpcion(1, "Efectivo");
    mostrarOpcion(2, "Tarjeta de Débito");
    mostrarOpcion(3, "Tarjeta de Crédito");
    mostrarOpcion(4, "Billetera Digital");
    mostrarInput("Opción");
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
            mostrarError("Opción no válida.");
            pausar();
            mostrarCajaFin();
            return;
    }

    archivoPago = fopen("data/pago.dat", "ab");
    if(archivoPago != NULL){
        fwrite(&pago, sizeof(Pago), 1, archivoPago);
        fflush(archivoPago);
        fclose(archivoPago);

        mostrarExito("Pago registrado exitosamente.");
        char pagoInfo[200];
        sprintf(pagoInfo, "ID: %d | Método: %s | Estado: %s | Monto: $%.2f", 
                pago.id_pago, pago.metodo_pago, pago.estado_pago, pago.monto_total);
        mostrarInfo(pagoInfo);

        calcularComisionPedido(id_pedido, pago.id_pago, pedido.id_restaurante, pago.monto_total);
    } else {
        mostrarError("No se pudo guardar el pago.");
    }
    mostrarCajaFin();
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

    limpiarPantalla();
    mostrarCaja("ÓRDENES PENDIENTES");

    archivoOrdenes = fopen("data/orden_preparacion.dat", "rb");
    if(archivoOrdenes == NULL){
        mostrarInfo("No hay órdenes disponibles.");
        mostrarCajaFin();
        pausar();
        return;
    }

    archivoPedidos = fopen("data/pedido.dat", "rb");
    if(archivoPedidos == NULL){
        mostrarError("No se pudo acceder a pedidos.");
        fclose(archivoOrdenes);
        mostrarCajaFin();
        pausar();
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
        mostrarInfo("No hay órdenes pendientes en este momento.");
    } else {
        char totalMsg[100];
        sprintf(totalMsg, "Total de órdenes pendientes: %d", cantidad);
        mostrarInfo(totalMsg);
    }

    mostrarCajaFin();
    fclose(archivoOrdenes);
    fclose(archivoPedidos);
    pausar();
}

//Para el Repartidor
void listarPedidoDisponibles(Usuario usuario){
    FILE *archivoPedidos;
    FILE *archivoOrdenes;
    Pedido pedido;
    OrdenPreparacion orden;
    int cantidad = 0;

    limpiarPantalla();
    mostrarCaja("MIS PEDIDOS");

    archivoPedidos = fopen("data/pedido.dat", "rb");
    archivoOrdenes = fopen("data/orden_preparacion.dat", "rb");
    if(archivoPedidos == NULL || archivoOrdenes == NULL){
        mostrarInfo("No hay pedidos disponibles en este momento.");
        mostrarCajaFin();
        if(archivoPedidos != NULL) fclose(archivoPedidos);
        if(archivoOrdenes != NULL) fclose(archivoOrdenes);
        pausar();
        return;
    }

    while(fread(&orden, sizeof(OrdenPreparacion), 1, archivoOrdenes) == 1){
        fseek(archivoPedidos, 0, SEEK_SET);
        while(fread(&pedido, sizeof(Pedido), 1, archivoPedidos) == 1){
            if(pedido.id_pedido == orden.id_pedido){
                int pedidoPreparado = strcmp(orden.estado_preparacion, "Preparado") == 0;
                int pedidoListo = strcmp(pedido.estado, "Preparado") == 0;
                int pedidoSinAsignar = pedido.id_repartidor == -1;

                if((pedidoPreparado || pedidoListo) && pedidoSinAsignar){
                    printf("\n[%d] Fecha: %s", pedido.id_pedido, pedido.fecha_pedido);
                    printf("\n    Dirección: %s", pedido.direccion_entrega);
                    printf("\n    Estado: %s\n", orden.estado_preparacion);
                    cantidad++;
                }
                break;
            }
        }
    }

    fclose(archivoPedidos);
    fclose(archivoOrdenes);

    if(cantidad > 0){
        aceptarPedido(usuario);
    } else {
        mostrarInfo("No hay pedidos preparados para aceptar.");
        mostrarCajaFin();
        pausar();
    }
}

void aceptarPedido(Usuario usuario){
    FILE *archivo;
    FILE *auxiliar;
    FILE *archivoOrdenes;
    FILE *auxiliarOrdenes;

    Pedido pedido;
    OrdenPreparacion orden;

    int id_buscar;
    int encontrado = 0;
    int pedidoDisponible = 0;

    mostrarInput("Ingrese ID del pedido");
    scanf("%d", &id_buscar);

    crearDirectorioAuxiliar();

    archivo = fopen("data/pedido.dat", "rb");
    auxiliar = fopen("data/auxiliar_data/pedido.dat", "wb");
    archivoOrdenes = fopen("data/orden_preparacion.dat", "rb");
    auxiliarOrdenes = fopen("data/auxiliar_data/orden_preparacion.dat", "wb");

    if(archivo == NULL || auxiliar == NULL || archivoOrdenes == NULL || auxiliarOrdenes == NULL){
        printf("\nError al abrir archivos.");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        if(archivoOrdenes != NULL) fclose(archivoOrdenes);
        if(auxiliarOrdenes != NULL) fclose(auxiliarOrdenes);
        return;
    }

    int estadoPreparado = 0;
    rewind(archivoOrdenes);
    while(fread(&orden, sizeof(OrdenPreparacion), 1, archivoOrdenes) == 1){
        if(orden.id_pedido == id_buscar){
            estadoPreparado = strcmp(orden.estado_preparacion, "Preparado") == 0;
            break;
        }
    }

    rewind(archivo);
    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
        if(pedido.id_pedido == id_buscar){
            encontrado = 1;
            int sinAsignar = pedido.id_repartidor == -1 || pedido.id_repartidor == 0;
            if(sinAsignar && estadoPreparado){
                pedidoDisponible = 1;
                pedido.id_repartidor = usuario.id_usuario;
                strcpy(pedido.estado, "En_Camino");
            }
        }
        fwrite(&pedido, sizeof(Pedido), 1, auxiliar);
    }

    rewind(archivoOrdenes);
    while(fread(&orden, sizeof(OrdenPreparacion), 1, archivoOrdenes) == 1){
        if(orden.id_pedido == id_buscar && pedidoDisponible){
            strcpy(orden.estado_preparacion, "Listo_Entrega");
        }
        fwrite(&orden, sizeof(OrdenPreparacion), 1, auxiliarOrdenes);
    }

    fclose(archivo);
    fclose(auxiliar);
    fclose(archivoOrdenes);
    fclose(auxiliarOrdenes);

    if(encontrado && pedidoDisponible){
        remove("data/pedido.dat");
        rename("data/auxiliar_data/pedido.dat", "data/pedido.dat");
        remove("data/orden_preparacion.dat");
        rename("data/auxiliar_data/orden_preparacion.dat", "data/orden_preparacion.dat");
        mostrarExito("Pedido aceptado correctamente.");
    }
    else{
        remove("data/auxiliar_data/pedido.dat");
        remove("data/auxiliar_data/orden_preparacion.dat");
        if(!encontrado){
            mostrarError("Pedido no encontrado.");
        } else {
            mostrarError("El pedido no está preparado para aceptar.");
        }
    }
    mostrarCajaFin();
    pausar();
}

static void entregarPedidoRepartidor(int id_pedido){
    FILE *archivoPedido;
    FILE *auxiliarPedido;
    FILE *archivoOrden;
    FILE *auxiliarOrden;

    Pedido pedido;
    OrdenPreparacion orden;
    int encontrado = 0;

    crearDirectorioAuxiliar();

    archivoPedido = fopen("data/pedido.dat", "rb");
    auxiliarPedido = fopen("data/auxiliar_data/pedido.dat", "wb");
    archivoOrden = fopen("data/orden_preparacion.dat", "rb");
    auxiliarOrden = fopen("data/auxiliar_data/orden_preparacion.dat", "wb");

    if(archivoPedido == NULL || auxiliarPedido == NULL || archivoOrden == NULL || auxiliarOrden == NULL){
        mostrarError("No se pudo actualizar el estado del pedido.");
        if(archivoPedido != NULL) fclose(archivoPedido);
        if(auxiliarPedido != NULL) fclose(auxiliarPedido);
        if(archivoOrden != NULL) fclose(archivoOrden);
        if(auxiliarOrden != NULL) fclose(auxiliarOrden);
        mostrarCajaFin();
        pausar();
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivoPedido) == 1){
        if(pedido.id_pedido == id_pedido){
            encontrado = 1;
            strcpy(pedido.estado, "Finalizado");
        }
        fwrite(&pedido, sizeof(Pedido), 1, auxiliarPedido);
    }

    while(fread(&orden, sizeof(OrdenPreparacion), 1, archivoOrden) == 1){
        if(orden.id_pedido == id_pedido){
            strcpy(orden.estado_preparacion, "Entregado");
        }
        fwrite(&orden, sizeof(OrdenPreparacion), 1, auxiliarOrden);
    }

    fclose(archivoPedido);
    fclose(auxiliarPedido);
    fclose(archivoOrden);
    fclose(auxiliarOrden);

    if(encontrado){
        remove("data/pedido.dat");
        rename("data/auxiliar_data/pedido.dat", "data/pedido.dat");
        remove("data/orden_preparacion.dat");
        rename("data/auxiliar_data/orden_preparacion.dat", "data/orden_preparacion.dat");
        mostrarExito("Pedido entregado correctamente.");
    } else {
        remove("data/auxiliar_data/pedido.dat");
        remove("data/auxiliar_data/orden_preparacion.dat");
        mostrarError("Pedido no encontrado.");
    }

    mostrarCajaFin();
    pausar();
}

void listarPedidosAceptados(int id_usuario){
    FILE *archivo;
    Pedido pedido;
    Pedido pedidosUsuario[100];
    int cantidad = 0;
    int seleccion = 0;
    int opcion = 0;

    archivo = fopen("data/pedido.dat", "rb");

    if(archivo == NULL){
        mostrarError("No se pudo abrir data/pedido.dat");
        mostrarCajaFin();
        pausar();
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivo) == 1){
        if(pedido.id_repartidor == id_usuario && strcmp(pedido.estado, "En_Camino") == 0){
            pedidosUsuario[cantidad++] = pedido;
            if(cantidad >= 100){
                break;
            }
        }
    }
    fclose(archivo);

    limpiarPantalla();
    mostrarCaja("PEDIDOS EN CAMINO");

    if(cantidad == 0){
        mostrarInfo("No tienes pedidos en camino.");
        mostrarCajaFin();
        pausar();
        return;
    }

    mostrarInfo("Tus pedidos asignados:");
    for(int i = 0; i < cantidad; i++){
        char pedidoCamino[260];
        snprintf(pedidoCamino, sizeof(pedidoCamino), "[%d] ID: %d | Dirección: %s | Estado: %s",
                 i + 1, pedidosUsuario[i].id_pedido, pedidosUsuario[i].direccion_entrega, pedidosUsuario[i].estado);
        mostrarOpcion(i + 1, pedidoCamino);
    }
    mostrarOpcion(0, "Volver");

    mostrarInput("Seleccione un pedido para ver detalles");
    if(scanf("%d", &seleccion) != 1){
        while(getchar() != '\n');
        seleccion = -1;
    }

    if(seleccion <= 0 || seleccion > cantidad){
        mostrarInfo("No se seleccionó ningún pedido.");
        mostrarCajaFin();
        pausar();
        return;
    }

    limpiarPantalla();
    mostrarCaja("DETALLE DEL PEDIDO");

    Pedido pedidoSeleccionado = pedidosUsuario[seleccion - 1];
    char resumenPedido[320];
    snprintf(resumenPedido, sizeof(resumenPedido), "Pedido ID: %d | Fecha: %s | Estado: %s | Total: $%.2f",
             pedidoSeleccionado.id_pedido, pedidoSeleccionado.fecha_pedido,
             pedidoSeleccionado.estado, pedidoSeleccionado.total);
    mostrarInfo(resumenPedido);

    char direccionMsg[220];
    snprintf(direccionMsg, sizeof(direccionMsg), "Dirección: %s", pedidoSeleccionado.direccion_entrega);
    mostrarInfo(direccionMsg);

    char obsMsg[220];
    snprintf(obsMsg, sizeof(obsMsg), "Observaciones: %s", pedidoSeleccionado.observaciones[0] != '\0' ? pedidoSeleccionado.observaciones : "Sin observaciones");
    mostrarInfo(obsMsg);
    mostrarLinea();
    mostrarInfo("¿Qué deseas hacer?");
    mostrarOpcion(1, "Entregar Pedido");
    mostrarOpcion(2, "Volver");

    mostrarInput("Seleccione una opción");
    if(scanf("%d", &opcion) != 1){
        while(getchar() != '\n');
        opcion = -1;
    }

    if(opcion == 1){
        entregarPedidoRepartidor(pedidoSeleccionado.id_pedido);
    } else {
        mostrarInfo("Volviendo al menú.");
        mostrarCajaFin();
        pausar();
    }
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

    limpiarPantalla();
    mostrarCaja("ACTUALIZAR ESTADO DE ORDEN");

    mostrarInput("Ingrese ID de la orden a actualizar");
    scanf("%d", &id_orden_buscar);

    archivo = fopen("data/orden_preparacion.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        printf("\n[ERROR] No se pueden abrir los archivos.\n");
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&orden, sizeof(OrdenPreparacion), 1, archivo) == 1){
        if(orden.id_orden == id_orden_buscar){
            encontrado = 1;
            mostrarInfo("Orden encontrada.");
            char ordenInfo[200];
            sprintf(ordenInfo, "ID Orden: %d | Estado Actual: %s", orden.id_orden, orden.estado_preparacion);
            mostrarInfo(ordenInfo);

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
                    mostrarError("Opción inválida.");
                    break;
                }
            }
            char nuevoEstadoMsg[120];
            sprintf(nuevoEstadoMsg, "Nuevo Estado: %s", orden.estado_preparacion);
            mostrarInfo(nuevoEstadoMsg);
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
        remove("data/orden_preparacion.dat");
        rename("data/auxiliar.dat", "data/orden_preparacion.dat");
        mostrarExito("Estado de la orden actualizado correctamente.");
    }else{
        remove("data/auxiliar.dat");
        mostrarError("Orden no encontrada.");
    }
    mostrarCajaFin();
    pausar();
}

void actualizarPedidoXid(int id_pedido, char nuevoEstado[]){
    FILE *archivo;
    FILE *auxiliar;
    Pedido pedido;
    int encontrado = 0;
    crearDirectorioAuxiliar();
    archivo = fopen("data/pedido.dat", "rb");
    auxiliar = fopen("data/auxiliar_data/pedido.dat", "wb");

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
        remove("data/pedido.dat");
        rename("data/auxiliar_data/pedido.dat", "data/pedido.dat");
        mostrarExito("Estado actualizado correctamente.");
    }
    else{
        remove("data/auxiliar_data/pedido.dat");
        mostrarError("Pedido no encontrado.");
    }
    mostrarCajaFin();
    pausar();
}

// =========================
// FINANZAS - COMISIONES Y PAGOS
// =========================

void calcularComisionPedido(int id_pedido, int id_pago, int id_restaurante, double monto_total){
    FILE *archivo;
    ComisionDetalle comision;
    int ultimoId = 0;

    archivo = fopen("data/comision.dat", "rb");
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

    archivo = fopen("data/comision.dat", "ab");
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

    archivo = fopen("data/comision.dat", "rb");
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

    mostrarInfo("--- COMISIONES PENDIENTES DE PAGO ---");
    char pendienteMsg[120];
    sprintf(pendienteMsg, "Total pendiente: $%.2f (%d pedidos)", total_pendiente, cantidad_pendiente);
    mostrarInfo(pendienteMsg);
    mostrarInfo("--- COMISIONES PAGADAS ---");
    char pagadoMsg[120];
    sprintf(pagadoMsg, "Total pagado: $%.2f (%d pedidos)", total_pagado, cantidad_pagado);
    mostrarInfo(pagadoMsg);
    mostrarInfo("--- RESUMEN TOTAL ---");
    char totalIngresosMsg[120];
    sprintf(totalIngresosMsg, "Ingresos totales: $%.2f", total_pendiente + total_pagado);
    mostrarInfo(totalIngresosMsg);
    mostrarCajaFin();
    pausar();
}

void realizarPagoRestaurante(){
    FILE *archivoRestaurantes, *archivoComisiones, *archivoPagos;
    Restaurante restaurante;
    ComisionDetalle comision;
    PagoRestaurante pago;
    int id_restaurante, ultimoId = 0;
    double total_pagar = 0;
    int cantidad_pedidos = 0;

    limpiarPantalla();
    mostrarCaja("REALIZAR PAGO A RESTAURANTE");

    // Listar restaurantes
    archivoRestaurantes = fopen("data/restaurante.dat", "rb");
    if(archivoRestaurantes == NULL){
        mostrarError("No hay restaurantes.");
        mostrarCajaFin();
        pausar();
        return;
    }

    mostrarInfo("Restaurantes disponibles:");
    while(fread(&restaurante, sizeof(Restaurante), 1, archivoRestaurantes) == 1){
        char restauranteInfo[160];
        sprintf(restauranteInfo, "[%d] %s", restaurante.id_restaurante, restaurante.nombre);
        mostrarInfo(restauranteInfo);
    }
    fclose(archivoRestaurantes);

    mostrarInput("Ingrese ID del restaurante");
    scanf("%d", &id_restaurante);

    // Calcular total a pagar
    archivoComisiones = fopen("data/comision.dat", "rb");
    if(archivoComisiones == NULL){
        mostrarError("No hay comisiones registradas.");
        mostrarCajaFin();
        pausar();
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
        mostrarInfo("No hay pagos pendientes para este restaurante.");
        mostrarCajaFin();
        pausar();
        return;
    }

    mostrarInfo("--- CONFIRMACIÓN DE PAGO ---");
    char confirmacionMsg[200];
    sprintf(confirmacionMsg, "Restaurante ID: %d | Total a pagar: $%.2f | Cantidad de pedidos: %d", id_restaurante, total_pagar, cantidad_pedidos);
    mostrarInfo(confirmacionMsg);
    mostrarInput("¿Confirmar pago? [1] SÍ [2] NO");

    int confirmacion;
    scanf("%d", &confirmacion);

    if(confirmacion != 1){
        mostrarInfo("Pago cancelado.");
        mostrarCajaFin();
        pausar();
        return;
    }

    // Obtener próximo ID
    archivoPagos = fopen("data/pago_data/restaurante.dat", "rb");
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

    archivoPagos = fopen("data/pago_data/restaurante.dat", "ab");
    if(archivoPagos != NULL){
        fwrite(&pago, sizeof(PagoRestaurante), 1, archivoPagos);
        fflush(archivoPagos);
        fclose(archivoPagos);
    }

    // Marcar comisiones como pagadas
    marcarComisionsComoPagadas(id_restaurante);

    mostrarExito("Pago registrado exitosamente.");
    char pagoRestauranteMsg[120];
    sprintf(pagoRestauranteMsg, "ID Pago: %d | Monto: $%.2f", pago.id_pago_restaurante, pago.monto_total);
    mostrarInfo(pagoRestauranteMsg);
    mostrarCajaFin();
    pausar();
}

void marcarComisionsComoPagadas(int id_restaurante){
    FILE *archivo, *auxiliar;
    ComisionDetalle comision;

    archivo = fopen("data/comision.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

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

    remove("data/comision.dat");
    rename("data/auxiliar.dat", "data/comision.dat");
}

void verIngresoRepartidor(int id_repartidor){
    FILE *archivo;
    IngresoRepartidor ingreso;
    double total_propina = 0, total_bonus = 0;
    int cantidad_entregas = 0;

    limpiarPantalla();
    mostrarCaja("MIS INGRESOS");

    archivo = fopen("data/ingreso_data/repartidor.dat", "rb");
    if(archivo == NULL){
        mostrarInfo("No hay ingresos registrados.");
        mostrarCajaFin();
        pausar();
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

    char entregasMsg[120];
    sprintf(entregasMsg, "Total de entregas: %d", cantidad_entregas);
    mostrarInfo(entregasMsg);
    char propinasMsg[120];
    sprintf(propinasMsg, "Total en propinas: $%.2f", total_propina);
    mostrarInfo(propinasMsg);
    char bonosMsg[120];
    sprintf(bonosMsg, "Total en bonos: $%.2f", total_bonus);
    mostrarInfo(bonosMsg);
    char ingresoTotalMsg[120];
    sprintf(ingresoTotalMsg, "Ingreso total: $%.2f", total_propina + total_bonus);
    mostrarInfo(ingresoTotalMsg);
    mostrarCajaFin();
    pausar();
}

void verFinanzasTotales(){
    FILE *archComisiones, *archPagos;
    ComisionDetalle comision;
    PagoRestaurante pago;
    double ingresos_sistema = 0, monto_pagado = 0;
    int pedidos_totales = 0;

    limpiarPantalla();
    mostrarCaja("FINANZAS GENERALES DEL SISTEMA");

    archComisiones = fopen("data/comision.dat", "rb");
    if(archComisiones != NULL){
        while(fread(&comision, sizeof(ComisionDetalle), 1, archComisiones) == 1){
            ingresos_sistema += comision.monto_neto;
            pedidos_totales++;
        }
        fclose(archComisiones);
    }

    archPagos = fopen("data/pago_data/restaurante.dat", "rb");
    if(archPagos != NULL){
        while(fread(&pago, sizeof(PagoRestaurante), 1, archPagos) == 1){
            monto_pagado += pago.monto_total;
        }
        fclose(archPagos);
    }

    mostrarInfo("--- INGRESOS DEL SISTEMA ---");
    char comisionesMsg[120];
    sprintf(comisionesMsg, "Comisiones totales: $%.2f", ingresos_sistema);
    mostrarInfo(comisionesMsg);
    char pedidosMsg[120];
    sprintf(pedidosMsg, "Pedidos procesados: %d", pedidos_totales);
    mostrarInfo(pedidosMsg);

    mostrarInfo("--- PAGOS A RESTAURANTES ---");
    char pagadoMsg[120];
    sprintf(pagadoMsg, "Total pagado: $%.2f", monto_pagado);
    mostrarInfo(pagadoMsg);
    char diferenciaMsg[120];
    sprintf(diferenciaMsg, "Diferencia (comisiones retomadas): $%.2f", ingresos_sistema - monto_pagado);
    mostrarInfo(diferenciaMsg);

    mostrarInfo("--- PROMEDIO POR PEDIDO ---");
    if(pedidos_totales > 0){
        char promedioMsg[120];
        sprintf(promedioMsg, "Comisión promedio: $%.2f", ingresos_sistema / pedidos_totales);
        mostrarInfo(promedioMsg);
    }
    mostrarCajaFin();
    pausar();
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

    limpiarPantalla();
    mostrarCaja("CALIFICAR PEDIDO");

    archivoPedidos = fopen("data/pedido.dat", "rb");
    if(archivoPedidos == NULL){
        mostrarInfo("No tienes pedidos.");
        mostrarCajaFin();
        pausar();
        return;
    }

    int hayPedidos = 0;
    mostrarInfo("Tus pedidos finalizados:");
    while(fread(&pedido, sizeof(Pedido), 1, archivoPedidos) == 1){
        int pedidoFinalizado = strcmp(pedido.estado, "Finalizado") == 0 || strcmp(pedido.estado, "Entregado") == 0;
        if(pedido.id_cliente == usuario.id_usuario && pedidoFinalizado){
            hayPedidos = 1;
            char pedidoInfo[220];
            snprintf(pedidoInfo, sizeof(pedidoInfo), "ID: %d | Fecha: %s | Estado: %s", pedido.id_pedido, pedido.fecha_pedido, pedido.estado);
            mostrarOpcion(pedido.id_pedido, pedidoInfo);
        }
    }
    fclose(archivoPedidos);

    if(!hayPedidos){
        mostrarInfo("No tienes pedidos finalizados para calificar.");
        mostrarCajaFin();
        pausar();
        return;
    }

    mostrarInput("Ingrese ID del pedido a calificar");
    scanf("%d", &id_pedido);

    archivoPedidos = fopen("data/pedido.dat", "rb");
    while(fread(&pedido, sizeof(Pedido), 1, archivoPedidos) == 1){
        if(pedido.id_pedido == id_pedido && pedido.id_cliente == usuario.id_usuario){
            encontrado = 1;
            break;
        }
    }
    fclose(archivoPedidos);

    if(!encontrado){
        mostrarError("Pedido no encontrado.");
        pausar();
        mostrarCajaFin();
        return;
    }

    archivoCalificaciones = fopen("data/calificacion.dat", "rb");
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

    limpiarPantalla();
    mostrarCaja("CALIFICAR");
    mostrarInput("Puntuación comida (1-5)");
    scanf("%d", &calificacion.puntuacion_comida);

    mostrarInput("Puntuación repartidor (1-5)");
    scanf("%d", &calificacion.puntuacion_repartidor);

    mostrarInput("Puntuación entrega (1-5)");
    scanf("%d", &calificacion.puntuacion_entrega);

    mostrarInfo("¿Recomendarías este restaurante?");
    mostrarOpcion(1, "Sí");
    mostrarOpcion(2, "NO");
    mostrarInput("Selecciona opción");
    scanf("%d", &calificacion.fue_recomendado);

    mostrarInput("Comentario (opcional)");
    scanf(" %[^\n]", calificacion.comentario);
    convertirEspaciosAGuiones(calificacion.comentario);

    time_t ahora = time(NULL);
    struct tm *info = localtime(&ahora);
    strftime(calificacion.fecha_calificacion, 11, "%d/%m/%Y", info);
    strcpy(calificacion.estado_resenia, "Visible");

    archivoCalificaciones = fopen("data/calificacion.dat", "ab");
    if(archivoCalificaciones != NULL){
        fwrite(&calificacion, sizeof(Calificacion), 1, archivoCalificaciones);
        fflush(archivoCalificaciones);
        fclose(archivoCalificaciones);
    }

    actualizarPromedioRestaurante(calificacion.id_restaurante);

    mostrarExito("Calificación registrada exitosamente.");
}

void verCalificacionesRestaurante(int id_restaurante){
    FILE *archivo;
    Calificacion calificacion;
    int cantidad = 0;
    double promedio_comida = 0, promedio_repartidor = 0, promedio_entrega = 0;

    limpiarPantalla();
    mostrarCaja("CALIFICACIONES DEL RESTAURANTE");

    archivo = fopen("data/calificacion.dat", "rb");
    if(archivo == NULL){
        mostrarInfo("No hay calificaciones aún.");
        mostrarCajaFin();
        pausar();
        return;
    }

    while(fread(&calificacion, sizeof(Calificacion), 1, archivo) == 1){
        if(calificacion.id_restaurante == id_restaurante && strcmp(calificacion.estado_resenia, "Visible") == 0){
            cantidad++;
            promedio_comida += calificacion.puntuacion_comida;
            promedio_repartidor += calificacion.puntuacion_repartidor;
            promedio_entrega += calificacion.puntuacion_entrega;

            char reseñaMsg[220];
            sprintf(reseñaMsg, "--- Reseña #%d ---", cantidad);
            mostrarInfo(reseñaMsg);
            char fechaMsg[160];
            sprintf(fechaMsg, "Fecha: %s", calificacion.fecha_calificacion);
            mostrarInfo(fechaMsg);
            char puntuacionMsg[220];
            sprintf(puntuacionMsg, "Comida: %d/5 | Repartidor: %d/5 | Entrega: %d/5", calificacion.puntuacion_comida, calificacion.puntuacion_repartidor, calificacion.puntuacion_entrega);
            mostrarInfo(puntuacionMsg);
            char comentarioMsg[260];
            sprintf(comentarioMsg, "Comentario: %s", calificacion.comentario);
            mostrarInfo(comentarioMsg);
            char recomendacionMsg[120];
            sprintf(recomendacionMsg, "Recomendado: %s", calificacion.fue_recomendado ? "SÍ" : "NO");
            mostrarInfo(recomendacionMsg);
        }
    }
    fclose(archivo);

    if(cantidad > 0){
        mostrarInfo("--- PROMEDIOS ---");
        char comidaMsg[120];
        sprintf(comidaMsg, "Comida: %.2f/5", promedio_comida / cantidad);
        mostrarInfo(comidaMsg);
        char repartidorMsg[120];
        sprintf(repartidorMsg, "Repartidor: %.2f/5", promedio_repartidor / cantidad);
        mostrarInfo(repartidorMsg);
        char entregaMsg[120];
        sprintf(entregaMsg, "Entrega: %.2f/5", promedio_entrega / cantidad);
        mostrarInfo(entregaMsg);
        char totalResenasMsg[120];
        sprintf(totalResenasMsg, "Total de reseñas: %d", cantidad);
        mostrarInfo(totalResenasMsg);
    } else {
        mostrarInfo("No hay calificaciones visibles.");
    }
    mostrarCajaFin();
    pausar();
}

void verMisCalificaciones(Usuario usuario){
    FILE *archivo;
    Calificacion calificacion;

    limpiarPantalla();
    mostrarCaja("MIS CALIFICACIONES");

    archivo = fopen("data/calificacion.dat", "rb");
    if(archivo == NULL){
        mostrarInfo("No has hecho calificaciones.");
        mostrarCajaFin();
        pausar();
        return;
    }

    while(fread(&calificacion, sizeof(Calificacion), 1, archivo) == 1){
        if(calificacion.id_cliente == usuario.id_usuario){
            char calificacionMsg[220];
            sprintf(calificacionMsg, "[Pedido #%d] Fecha: %s", calificacion.id_pedido, calificacion.fecha_calificacion);
            mostrarInfo(calificacionMsg);
            char puntuacionMsg[220];
            sprintf(puntuacionMsg, "Puntuaciones: Comida %d/5, Repartidor %d/5, Entrega %d/5", calificacion.puntuacion_comida, calificacion.puntuacion_repartidor, calificacion.puntuacion_entrega);
            mostrarInfo(puntuacionMsg);
            char comentarioMsg[260];
            sprintf(comentarioMsg, "Comentario: %s", calificacion.comentario);
            mostrarInfo(comentarioMsg);
        }
    }
    fclose(archivo);
    mostrarCajaFin();
    pausar();
}

void reportarResenia(int id_calificacion){
    FILE *archivo, *auxiliar;
    Calificacion calificacion;
    int encontrado = 0;

    limpiarPantalla();
    mostrarCaja("REPORTAR RESEÑA");

    archivo = fopen("data/calificacion.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

    if(archivo == NULL || auxiliar == NULL){
        if(archivo != NULL) fclose(archivo);
        if(auxiliar != NULL) fclose(auxiliar);
        return;
    }

    while(fread(&calificacion, sizeof(Calificacion), 1, archivo) == 1){
        if(calificacion.id_calificacion == id_calificacion){
            encontrado = 1;
            strcpy(calificacion.estado_resenia, "Reportada");
            mostrarExito("Reseña reportada.");
        }
        fwrite(&calificacion, sizeof(Calificacion), 1, auxiliar);
    }

    fclose(archivo);
    fclose(auxiliar);

    if(encontrado){
        remove("data/calificacion.dat");
        rename("data/auxiliar.dat", "data/calificacion.dat");
    } else {
        remove("data/auxiliar.dat");
        mostrarError("Reseña no encontrada.");
    }
    mostrarCajaFin();
    pausar();
}

void actualizarPromedioRestaurante(int id_restaurante){
    FILE *archivoCalificaciones, *archivoRestaurantes, *auxiliar;
    Calificacion calificacion;
    Restaurante restaurante;
    double suma_puntuaciones = 0;
    int total_puntuaciones = 0;
    int total_calificaciones = 0;

    // Calcular promedio
    archivoCalificaciones = fopen("data/calificacion.dat", "rb");
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
    archivoRestaurantes = fopen("data/restaurante.dat", "rb");
    auxiliar = fopen("data/auxiliar.dat", "wb");

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

    remove("data/restaurante.dat");
    rename("data/auxiliar.dat", "data/restaurante.dat");
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

    limpiarPantalla();
    mostrarCaja("INFORMACIÓN DEL RESTAURANTE");

    // Buscar restaurante
    archivoRestaurantes = fopen("data/restaurante.dat", "rb");
    if(archivoRestaurantes == NULL){
        mostrarError("No se encontraron restaurantes.");
        mostrarCajaFin();
        pausar();
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
        mostrarError("Restaurante no encontrado.");
        mostrarCajaFin();
        pausar();
        return;
    }

    // Contar productos: primero leer menus, luego productos
    archivoMenu = fopen("data/menu.dat", "rb");
    if(archivoMenu != NULL){
        while(fread(&menu, sizeof(Menu), 1, archivoMenu) == 1){
            if(menu.id_restaurante == id_restaurante){
                // Para cada menu, contar productos
                archivoProductos = fopen("data/producto.dat", "rb");
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
    archivoPedidos = fopen("data/pedido.dat", "rb");
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
    mostrarInfo("--- DATOS BÁSICOS ---");
    char idMsg[120];
    sprintf(idMsg, "ID: %d", restaurante.id_restaurante);
    mostrarInfo(idMsg);
    char nombreMsg[200];
    sprintf(nombreMsg, "Nombre: %s", restaurante.nombre);
    mostrarInfo(nombreMsg);
    char telefonoMsg[160];
    sprintf(telefonoMsg, "Teléfono: %s", restaurante.telefono);
    mostrarInfo(telefonoMsg);
    char estadoMsg[160];
    sprintf(estadoMsg, "Estado: %s", restaurante.estado);
    mostrarInfo(estadoMsg);

    mostrarInfo("--- HORARIOS ---");
    char aperturaMsg[160];
    sprintf(aperturaMsg, "Apertura: %s", restaurante.horario_apertura);
    mostrarInfo(aperturaMsg);
    char cierreMsg[160];
    sprintf(cierreMsg, "Cierre: %s", restaurante.horario_cierre);
    mostrarInfo(cierreMsg);

    mostrarInfo("--- CALIFICACIONES ---");
    char promedioMsg[160];
    sprintf(promedioMsg, "Promedio: %.2f/5.0", restaurante.promedio_calificacion);
    mostrarInfo(promedioMsg);
    char reseñasMsg[160];
    sprintf(reseñasMsg, "Total de reseñas: %d", restaurante.total_calificaciones);
    mostrarInfo(reseñasMsg);

    mostrarInfo("--- ESTADÍSTICAS DEL NEGOCIO ---");
    char productosMsg[160];
    sprintf(productosMsg, "Productos en menú: %d", cantidad_productos);
    mostrarInfo(productosMsg);
    char pedidosTotalesMsg[160];
    sprintf(pedidosTotalesMsg, "Pedidos totales: %d", cantidad_pedidos_totales);
    mostrarInfo(pedidosTotalesMsg);
    char ingresosMsg[160];
    sprintf(ingresosMsg, "Ingresos totales: $%.2f", ingresos_totales);
    mostrarInfo(ingresosMsg);

    if(cantidad_pedidos_totales > 0){
        char ticketMsg[160];
        sprintf(ticketMsg, "Ticket promedio: $%.2f", ingresos_totales / cantidad_pedidos_totales);
        mostrarInfo(ticketMsg);
    }
    mostrarCajaFin();
    pausar();
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
    archivo = fopen("data/usuario.dat", "rb");
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

        FILE *archivoCliente = fopen("data/cliente.dat", "ab");
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
        mostrarInput("Ingrese Estado de Disponibilidad");
        scanf("%d", &opcion);
        if(opcion == 1){
            strcpy(repartidor.estado_disponibilidad, "Activo");
        }else if(opcion == 2){
            strcpy(repartidor.estado_disponibilidad, "Inactivo");
        }

        FILE *archivoRepartidor = fopen("data/repartidor.dat", "ab");
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
        mostrarInput("Ingrese ID del Restaurante");
        scanf("%d", &encargado.id_restaurante);

        generarMenu(menuTurno, 3);
        mostrarInput("Ingrese Turno");
        scanf("%d", &opcion);
        if(opcion == 1){
            strcpy(encargado.turno, "Mañana");
        }else if(opcion == 2){
            strcpy(encargado.turno, "Tarde");
        }else if(opcion == 3){
            strcpy(encargado.turno, "Noche");
        }


        FILE *archivoEncargado = fopen("data/encargado.dat", "ab");
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
        mostrarInput("Ingrese Nivel de Acceso");
        scanf("%d", &opcion);
        if(opcion == 1){
            strcpy(administrador.nivel_acceso, "superadmin");
        }else if(opcion == 2){
            strcpy(administrador.nivel_acceso, "admin");
        }else if(opcion == 3){
            strcpy(administrador.nivel_acceso, "supervisor");
        }

        FILE *archivoAdministrador = fopen("data/administrador.dat", "ab");
        if(archivoAdministrador != NULL){
            fwrite(&administrador, sizeof(Administrador), 1, archivoAdministrador);
            fflush(archivoAdministrador);
            fclose(archivoAdministrador);
        }
    }
}





