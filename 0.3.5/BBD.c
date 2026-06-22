#include <stdio.h>
#include <stdlib.h>
#include "BBD.h"
#include "crud.h"

/** direccion de las estructuras*/

void generarMenu(char menu[][50], int opciones){
    for(int i=0; i<opciones; i++){
        printf("\n%s", menu[i]);
    }
}

void panelCliente(Usuario usuario){
    int opcion = 0;
    int id_pedido_temp = 0;

    char menuUsuario[8][50]={
    "[1] Realizar Pedido\n",
    "[2] Ver Mis Pedidos\n",
    "[3] Ver Estado del Pedido\n",
    "[4] Realizar Pago\n",
    "[5] Calificar Pedido\n",
    "[6] Ver Mis Datos\n",
    "[7] Cerrar Sesión\n",
    "Opcion: "
    };

    system("cls");

    do{
        printf("\n===============================\n");
        printf("\n SISTEMA DE DELIVERY: CLIENTE\n");
        printf("\n===============================\n");

        generarMenu(menuUsuario, 7);

        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n');
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                system("cls");
                agregarPedido(usuario);
                system("pause");
                system("cls");
                break;
            }
            case 2:{
                system("cls");
                listarMisPedidos(usuario);
                system("pause");
                system("cls");
                break;
            }
            case 3:{
                system("cls");
                printf("\nIngrese ID del pedido: ");
                scanf("%d", &id_pedido_temp);
                obtenerHistorialEstados(id_pedido_temp);
                system("pause");
                system("cls");
                break;
            }
            case 4:{
                system("cls");
                printf("\nIngrese ID del pedido: ");
                scanf("%d", &id_pedido_temp);
                realizarPago(usuario, id_pedido_temp);
                system("pause");
                system("cls");
                break;
            }
            case 5:{
                system("cls");
                calificarPedido(usuario);
                system("pause");
                system("cls");
                break;
            }
            case 6:{
                system("cls");
                printf("\n--- MIS DATOS ---\n");
                printf("ID: %d\n", usuario.id_usuario);
                printf("Nombre: %s %s\n", usuario.nombre, usuario.apellido);
                printf("Email: %s\n", usuario.email);
                printf("Teléfono: %s\n", usuario.telefono);
                system("pause");
                system("cls");
                break;
            }
            case 7:{
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------\n");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 7);
}

void panelRepartidor(Usuario usuario){
    system("cls");

    int opcion = 0;

    char menuRepartidor[4][50]={
    "[1] Ver Entregas Disponibles\n",
    "[2] Mis Datos\n",
    "[3] Cerrar Sesión\n",
    "Opcion: "
    };

    do{
        printf("\n====================================\n");
        printf("\n SISTEMA DE DELIVERY: REPARTIDOR\n");
        printf("\n====================================\n");

        generarMenu(menuRepartidor, 3);

        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n');
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                system("cls");
                printf("\n[INFO] Entregas disponibles (en desarrollo)\n");
                system("pause");
                system("cls");
                break;
            }
            case 2:{
                system("cls");
                printf("\nID: %d\n", usuario.id_usuario);
                printf("Nombre: %s %s\n", usuario.nombre, usuario.apellido);
                printf("Teléfono: %s\n", usuario.telefono);
                system("pause");
                system("cls");
                break;
            }
            case 3:{
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------\n");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 3);
}

void panelEncargador(Usuario usuario){
    system("cls");

    int opcion = 0;
    int id_restaurante = -1;
    FILE *archivoEncargado;
    Encargado encargado;

    // Obtener id_restaurante del encargado
    archivoEncargado = fopen("encargado.dat", "rb");
    if(archivoEncargado != NULL){
        while(fread(&encargado, sizeof(Encargado), 1, archivoEncargado) == 1){
            if(encargado.id_usuario == usuario.id_usuario){
                id_restaurante = encargado.id_restaurante;
                break;
            }
        }
        fclose(archivoEncargado);
    }

    if(id_restaurante == -1){
        printf("\n[ERROR] No se encontró restaurante asignado.\n");
        system("pause");
        return;
    }

    char menuEncargado[8][50]={
    "[1] Agregar Producto al Menú\n",
    "[2] Modificar Plato\n",
    "[3] Ver Menú del Restaurante\n",
    "[4] Mostrar Órdenes Pendientes\n",
    "[5] Modificar Estado Pedidos\n",
    "[6] Ver Información del Restaurante\n",
    "[7] Mis Datos\n",
    "[8] Cerrar Sesión\n"
    };

    do{
        printf("\n====================================\n");
        printf("\n SISTEMA DE DELIVERY: ENCARGADO\n");
        printf("\n====================================\n");

        generarMenu(menuEncargado, 8);

        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n');
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                system("cls");
                agregarProducto(id_restaurante);
                system("pause");
                system("cls");
                break;
            }
            case 2:{
                system("cls");
                modificarProducto(id_restaurante);
                system("pause");
                system("cls");
                break;
            }
            case 3:{
                system("cls");
                listarProductosRestaurante(id_restaurante);
                system("pause");
                system("cls");
                break;
            }
            case 4:{
                system("cls");
                listarOrdenesRestaurante(id_restaurante);
                system("pause");
                system("cls");
                break;
            }
            case 5:{
                system("cls");
                actualizarEstadoOrden(id_restaurante);
                system("pause");
                system("cls");
                break;
            }
            case 6:{
                system("cls");
                mostrarInfoRestaurante(id_restaurante);
                system("pause");
                system("cls");
                break;
            }
            case 7:{
                system("cls");
                printf("\n--- MIS DATOS ---\n");
                printf("ID: %d\n", usuario.id_usuario);
                printf("Nombre: %s %s\n", usuario.nombre, usuario.apellido);
                printf("Email: %s\n", usuario.email);
                printf("Teléfono: %s\n", usuario.telefono);
                system("pause");
                system("cls");
                break;
            }
            case 8:{
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------\n");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 8);
}

void panelAdministrador(Usuario usuario){
    system("cls");

    int opcion = 0;

    char menuAdministrador[8][50]={
    "[1] Mostrar Cuentas\n",
    "[2] Mostrar Restaurantes\n",
    "[3] Mostrar Finanzas\n",
    "[4] Eliminar Usuario\n",
    "[5] Agregar Restaurante\n",
    "[6] Eliminar Restaurante\n",
    "[7] Cerrar Sesion\n",
    "Opcion: "
    };

    char menuTipoInformes[6][50]={
    "[a] Listado restaurantes con calificacion +4.0\n",
    "[b] Pedidos de un usuario especifico\n",
    "[c] Platos mas pedidos\n",
    "[d] Factura de un pedido\n",
    "[e] Volver\n",
    "Opcion: "
    };

    do{
        printf("\n====================================\n");
        printf("\n SISTEMA DE DELIVERY: ADMINISTRADOR\n");
        printf("\n====================================\n");

        generarMenu(menuAdministrador, 8);

        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n'); //Limpiamos el buffer para que no quede el caracter dando error
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                system("cls");
                listarUsuarios();
                system("pause");
                system("cls");
                break;
            }
            case 2:{
                system("cls");
                listarRestaurantes();
                system("pause");
                system("cls");
                break;
            }
            case 3:{
                system("cls");
                int opcion_finanzas = 0;
                do{
                    printf("\n====================================\n");
                    printf("\n       GESTIÓN DE FINANZAS\n");
                    printf("\n====================================\n");
                    printf("\n[1] Ver Ingresos Totales del Sistema");
                    printf("\n[2] Ver Ingresos por Restaurante");
                    printf("\n[3] Realizar Pago a Restaurante");
                    printf("\n[4] Ver Ingresos de Repartidor");
                    printf("\n[5] Ver Calificaciones de Restaurantes");
                    printf("\n[6] Volver");
                    printf("\nOpción: ");
                    
                    if(scanf("%d", &opcion_finanzas) != 1){
                        while(getchar() != '\n');
                        opcion_finanzas = -1;
                    }

                    switch(opcion_finanzas){
                        case 1:{
                            system("cls");
                            verFinanzasTotales();
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 2:{
                            system("cls");
                            int id_rest;
                            printf("\nIngrese ID del restaurante: ");
                            scanf("%d", &id_rest);
                            verIngresosRestaurante(id_rest);
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 3:{
                            system("cls");
                            realizarPagoRestaurante();
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 4:{
                            system("cls");
                            int id_repartidor;
                            printf("\nIngrese ID del repartidor: ");
                            scanf("%d", &id_repartidor);
                            verIngresoRepartidor(id_repartidor);
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 5:{
                            system("cls");
                            int id_rest_cal;
                            printf("\nIngrese ID del restaurante: ");
                            scanf("%d", &id_rest_cal);
                            verCalificacionesRestaurante(id_rest_cal);
                            system("pause");
                            system("cls");
                            break;
                        }
                        case 6:{
                            system("cls");
                            break;
                        }
                    }
                } while(opcion_finanzas != 6);
                break;
            }
            case 4:{
                system("cls");
                eliminarUsuarioPorId(usuario);
                system("cls");
                break;
            }
            case 5:{
                system("cls");
                agregarRestaurante();
                system("pause");
                system("cls");
                break;
            }
            case 6:{
                system("cls");
                eliminarRestaurantePorId();
                system("cls");
                break;
            }
            case 7:{
                system("pause");
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------\n");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 7);
}
