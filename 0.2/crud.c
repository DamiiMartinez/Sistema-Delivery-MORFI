#include <stdio.h>
#include <stdlib.h>
#include "crud.h"

/** direccion de las estructuras*/
#include "BBD.h"

/** funciones de alta, baja, modificación, */
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

    printf("\nBase de datos inicializada correctamente.\n");
}

/** Agregar Usuarios*/
void agregarUsuario(){
    int rol;
    Usuario usuario;

    char roles[4][50]={
        "\n[1] Cliente\n",
        "[2] Encargado\n",
        "[3] Repartidor\n",
        "[4] Administrador\n",
    };

    printf("\n===============================\n");
    printf("\n        INGRESAR USUARIO\n");
    printf("\n===============================\n");

    printf("\nIngrese Nombre: ");
    scanf("%s", usuario.nombre);
    printf("\nIngrese Apellido: ");
    scanf("%s", usuario.apellido);
    printf("\nIngrese Correo: ");
    scanf("%s", usuario.email);
    printf("\nIngrese Password: ");
    scanf("%s", usuario.contrasena);
    printf("\nIngrese Telefono: ");
    scanf("%d", &usuario.telefono);

    generarMenu(roles, 4);
    printf("\nIngrese Rol: ");
    scanf("%d", &rol);
    switch(rol){
        case 1:{
            agregarCliente(usuario);
            break;
        };
        case 2:{
            agregarEncargado(usuario);
            break;
        };
        case 3:{
            agregarRepartidor(usuario);
            break;
        };
        case 4:{
            agregarAdministrador(usuario);
            break;
        };
    };
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

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoCliente = fopen("cliente.dat", "ab");

    if(archivoUsuario != NULL && archivoCliente != NULL){
        fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        fwrite(&cliente, sizeof(Cliente), 1, archivoCliente);

        fclose(archivoUsuario);
        fclose(archivoCliente);

        printf("\nCliente agregado correctamente.");
        printf("\nID asignado: %d\n", usuario.id_usuario);
    }
    else{
        printf("\nError al abrir los archivos.\n");

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
    scanf("%s", repartidor.vehiculo);

    printf("\nIngrese Estado de Disponibilidad: ");
    scanf("%s", repartidor.estado_disponibilidad);

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoRepartidor = fopen("repartidor.dat", "ab");

    if(archivoUsuario != NULL && archivoRepartidor != NULL){
        fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        fwrite(&repartidor, sizeof(Repartidor), 1, archivoRepartidor);

        fclose(archivoUsuario);
        fclose(archivoRepartidor);

        printf("\nRepartidor agregado correctamente.");
        printf("\nID asignado: %d\n", usuario.id_usuario);
    }
    else{
        printf("\nError al abrir los archivos.\n");

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
    scanf("%s", encargado.turno);

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoEncargado = fopen("encargado.dat", "ab");

    if(archivoUsuario != NULL && archivoEncargado != NULL){
        fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        fwrite(&encargado, sizeof(Encargado), 1, archivoEncargado);

        fclose(archivoUsuario);
        fclose(archivoEncargado);

        printf("\nEncargado agregado correctamente.");
        printf("\nID asignado: %d\n", usuario.id_usuario);
    }
    else{
        printf("\nError al abrir los archivos.\n");

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
    scanf("%s", administrador.nivel_acceso);

    archivoUsuario = fopen("usuario.dat", "ab");
    archivoAdministrador = fopen("administrador.dat", "ab");

    if(archivoUsuario != NULL && archivoAdministrador != NULL){
        fwrite(&usuario, sizeof(Usuario), 1, archivoUsuario);
        fwrite(&administrador, sizeof(Administrador), 1, archivoAdministrador);

        fclose(archivoUsuario);
        fclose(archivoAdministrador);

        printf("\nAdministrador agregado correctamente.");
        printf("\nID asignado: %d\n", usuario.id_usuario);
    }
    else{
        printf("\nError al abrir los archivos.\n");

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
    else{ printf("\nCorreo o contraseña incorrectos."); }
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
            scanf("%s", reg.nombre);

            printf("\nIngrese Apellido: ");
            scanf("%s", reg.apellido);

            printf("\nIngrese Correo: ");
            scanf("%s", reg.email);

            printf("\nIngrese Password: ");
            scanf("%s", reg.contrasena);

            printf("\nIngrese Telefono: ");
            scanf("%s", reg.telefono);

            printf("\nSeleccione Rol:");
            printf("\n[1] Cliente");
            printf("\n[2] Encargado");
            printf("\n[3] Repartidor");
            printf("\n[4] Administrador");
            printf("\nOpcion: ");
            scanf("%d", &rol);

            switch(rol){
                case 1:{
                    actualizarClienteXid(usuario.id_usuario);

                    fseek(archivo, -sizeof(Usuario), SEEK_CUR);
                    fwrite(&reg, sizeof(Usuario), 1, archivo);

                    fclose(archivo);

                    printf("\nDatos generales actualizados.\n");

                    break;
                }
                case 2:{
                    actualizarEncargadoXid(usuario.id_usuario);

                    fseek(archivo, -sizeof(Usuario), SEEK_CUR);
                    fwrite(&reg, sizeof(Usuario), 1, archivo);

                    fclose(archivo);

                    printf("\nDatos generales actualizados.\n");

                    break;
                }
                case 3:{
                    actualizarRepartidorXid(usuario.id_usuario);

                    fseek(archivo, -sizeof(Usuario), SEEK_CUR);
                    fwrite(&reg, sizeof(Usuario), 1, archivo);

                    fclose(archivo);

                    printf("\nDatos generales actualizados.\n");

                    break;
                }
                case 4:{
                    actualizarAdministradorXid(usuario.id_usuario);

                    fseek(archivo, -sizeof(Usuario), SEEK_CUR);
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

            fseek(archivo, -sizeof(Cliente), SEEK_CUR);
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
            scanf("%s", repartidor.vehiculo);

            printf("\nNuevo Estado: ");
            scanf("%s", repartidor.estado_disponibilidad);

            fseek(archivo, -sizeof(Repartidor), SEEK_CUR);
            fwrite(&repartidor, sizeof(Repartidor), 1, archivo);

            printf("\nRepartidor actualizado.");
            fclose(archivo);
            return;
        }
    }

    printf("\Repartidor no encontrado.");
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
            scanf("%s", encargado.turno);

            fseek(archivo, -sizeof(Encargado), SEEK_CUR);
            fwrite(&encargado, sizeof(Encargado), 1, archivo);

            printf("\nEncargado actualizado.");
            fclose(archivo);
            return;
        }
    }

    printf("\Encargado no encontrado.");
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
            scanf("%s", administrador.nivel_acceso);

            fseek(archivo, -sizeof(Administrador), SEEK_CUR);
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
        printf("\nID: %d", usuario.id_usuario);
        printf("\nNombre: %s", usuario.nombre);
        printf("\nApellido: %s", usuario.apellido);
        printf("\nEmail: %s", usuario.email);
        printf("\nTelefono: %s", usuario.telefono);
        printf("\n----------------------------------");
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
    } fclose(archivo);

    if(!encontrado){ printf("\nCorreo o contraseña incorrectos.\n"); }
    else{ printf("\nBienvenido %s %s\n", usuario.nombre, usuario.apellido); }

    system("Pause");
    system("cls");

    if( esCliente(usuario.id_usuario) == 1 ){
        panelCliente(usuario);
    }else if( esEncargado(usuario.id_usuario) == 1 ){
        panelEncargador(usuario);
    }else if( esRepartidor(usuario.id_usuario) == 1 ){
        panelRepartidor(usuario);
    }else if( esAdministrador(usuario.id_usuario) == 1 ){
        panelAdministrador(usuario);
    }
}
int esCliente(int id_usuario){
    FILE *archivo;
    archivo = fopen("cliente.dat", "rb");

    Cliente cliente;

    if(archivo == NULL){ return 0; }

    while(fread(&cliente, sizeof(Cliente), 1, archivo) == 1){
        if(cliente.id_usuario == id_usuario){
            fclose(archivo);
            return 1;
        }
    } fclose(archivo);
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
// RESTAURANTES Y PRODUCTOS
// =========================

//PANEL PARA ADMINISTRADOR
//Agregar
void agregarRestaurante(){
    Restaurante restaurante;

    printf("\n===============================\n");
    printf("\n     INGRESAR RESTAURANTES\n");
    printf("\n===============================\n");

    printf("\nIngrese Nombre: ");
    scanf("%s", restaurante.nombre);

    printf("\nIngrese Telefono: ");
    scanf("%s", restaurante.telefono);

    printf("\nIngrese Horario de Apertura: ");
    scanf("%s", restaurante.horario_apertura);

    printf("\nIngrese Horario de Cierre: ");
    scanf("%s", restaurante.horario_cierre);

    printf("\nIngrese Estado: ");
    scanf("%s", restaurante.estado);

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
    scanf("%s", ubicacion.direccion);

    printf("\nIngrese Numero: ");
    scanf("%d", &ubicacion.numero);

    printf("\nIngrese Ciudad: ");
    scanf("%s", ubicacion.ciudad);

    printf("\nIngrese Provincia: ");
    scanf("%s", ubicacion.provincia);

    printf("\nIngrese Codigo Postal: ");
    scanf("%s", ubicacion.codigo_postal);

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

        printf("\nID Restaurante: %d", restaurante.id_restaurante);
        printf("\nNombre: %s", restaurante.nombre);
        printf("\nTelefono: %s", restaurante.telefono);
        printf("\nHorario Apertura: %s", restaurante.horario_apertura);
        printf("\nHorario Cierre: %s", restaurante.horario_cierre);
        printf("\nEstado: %s", restaurante.estado);

        printf("\n----------------------------------");
        listarUbicacionesRestaurante(restaurante.id_restaurante);
        printf("\n----------------------------------");
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

//PANEL PARA ENCARGADO
//Agregar
void agregarMenu(Menu menu);
void agregarProducto(Producto producto);
//Eliminar
void eliminarMenu();
void eliminarProducto();
//Actualizar
void actualizarMenuXid();
void actualizarProductoXid();
//Mostrar
void listarMenus();
void listarProductos();

// =========================
// PEDIDOS Y ENTREGAS
// =========================


//CLIENTE
void agregarPedido(Usuario usuario);

//PEDIDO
void agregarOrdenPreparacion(Pedido pedido);
void agregarDetalleOrden(OrdenPreparacion orden);
void agregarHistorialEstado(Pedido Pedido);

//CLIENTE
void actualizarHistorialEstadoXid(int id_historial);

//CLIENTE
void listarPedidos();
void listarHistorialEstados();

//ENCARGADO
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
