#include <stdio.h>
#include <stdlib.h>
#include "BBD.h"
#include "crud.h"
#include "informes.h"
#include "filemanager.h"
#include "ui.h"

void generarMenu(char menu[][50], int opciones){
    for(int i=0; i<opciones; i++){
        mostrarInfo(menu[i]);
    }
}

void panelCliente(Usuario usuario){
    int opcion = 0;
    int id_pedido_temp = 0;

    do{
        limpiarPantalla();
        mostrarCaja("PANEL CLIENTE");

        mostrarSubtitulo("¿Qué deseas hacer?");
        mostrarLinea();
        mostrarOpcion(1, "Realizar Pedido");
        mostrarOpcion(2, "Ver Mis Pedidos");
        mostrarOpcion(3, "Ver Estado del Pedido");
        mostrarOpcion(4, "Calificar Pedido");
        mostrarOpcion(5, "Ver Mis Datos");
        mostrarOpcion(6, "Cerrar Sesión");
        mostrarCajaFin();

        mostrarInput("Elige una opción");
        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n');
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                limpiarPantalla();
                agregarPedido(usuario);
                break;
            }
            case 2:{
                limpiarPantalla();
                listarMisPedidos(usuario);
                pausar();
                break;
            }
            case 3:{
                limpiarPantalla();
                mostrarInput("ID del pedido");
                scanf("%d", &id_pedido_temp);
                obtenerHistorialEstados(id_pedido_temp);
                pausar();
                break;
            }
            case 4:{
                limpiarPantalla();
                calificarPedido(usuario);
                pausar();
                break;
            }
            case 5:{
                limpiarPantalla();
                mostrarCaja("MIS DATOS");
                printf("%s%s  ID: %s%d\n", CYAN, BOX_V, WHITE, usuario.id_usuario);
                printf("%s%s  Nombre: %s%s %s\n", CYAN, BOX_V, WHITE, usuario.nombre, usuario.apellido);
                printf("%s%s  Email: %s%s\n", CYAN, BOX_V, WHITE, usuario.email);
                printf("%s%s  Teléfono: %s%s\n", CYAN, BOX_V, WHITE, usuario.telefono);
                mostrarCajaFin();
                pausar();
                break;
            }
            case 6:{
                limpiarPantalla();
                mostrarExito("Sesión cerrada correctamente");
                pausar();
                break;
            }
            default:{
                mostrarError("Opción no válida.");
                pausar();
                break;
            }
        }
    } while(opcion != 6);
}

void panelRepartidor(Usuario usuario){
    int opcion = 0;

    do{
        limpiarPantalla();
        mostrarCaja("PANEL REPARTIDOR");

        mostrarSubtitulo("¿Qué deseas hacer?");
        mostrarLinea();
        mostrarOpcion(1, "Ver Entregas Disponibles");
        mostrarOpcion(2, "Ver Pedido");
        mostrarOpcion(3, "Mis Datos");
        mostrarOpcion(4, "Cerrar Sesión");
        mostrarCajaFin();

        mostrarInput("Elige una opción");
        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n');
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                limpiarPantalla();
                listarPedidoDisponibles(usuario);
                pausar();
                break;
            }
            case 2:{
                limpiarPantalla();
                listarPedidosAceptados(usuario.id_usuario);
                pausar();
                break;
            }
            case 3:{
                limpiarPantalla();
                mostrarCaja("MIS DATOS");
                printf("%s%s  ID: %s%d\n", CYAN, BOX_V, WHITE, usuario.id_usuario);
                printf("%s%s  Nombre: %s%s %s\n", CYAN, BOX_V, WHITE, usuario.nombre, usuario.apellido);
                printf("%s%s  Teléfono: %s%s\n", CYAN, BOX_V, WHITE, usuario.telefono);
                mostrarCajaFin();
                pausar();
                break;
            }
            case 4:{
                limpiarPantalla();
                mostrarExito("Sesión cerrada correctamente");
                pausar();
                break;
            }
            default:{
                mostrarError("Opción no válida.");
                pausar();
                break;
            }
        }
    } while(opcion != 4);
}

void panelEncargador(Usuario usuario){
    int opcion = 0;
    int id_restaurante = -1;
    FILE *archivoEncargado;
    Encargado encargado;

    archivoEncargado = fopen("data/encargado.dat", "rb");
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
        limpiarPantalla();
        mostrarError("No se encontró restaurante asignado.");
        pausar();
        return;
    }

    do{
        limpiarPantalla();
        mostrarCaja("PANEL ENCARGADO");

        mostrarSubtitulo("¿Qué deseas hacer?");
        mostrarLinea();
        mostrarOpcion(1, "Agregar Producto al Menú");
        mostrarOpcion(2, "Modificar Plato");
        mostrarOpcion(3, "Ver Menú del Restaurante");
        mostrarOpcion(4, "Mostrar Órdenes Pendientes");
        mostrarOpcion(5, "Modificar Estado Pedidos");
        mostrarOpcion(6, "Ver Información del Restaurante");
        mostrarOpcion(7, "Mis Datos");
        mostrarOpcion(8, "Cerrar Sesión");
        mostrarCajaFin();

        mostrarInput("Elige una opción");
        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n');
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                limpiarPantalla();
                agregarProducto(id_restaurante);
                pausar();
                break;
            }
            case 2:{
                limpiarPantalla();
                listarProductosRestaurante(id_restaurante);
                modificarProducto(id_restaurante);
                pausar();
                break;
            }
            case 3:{
                limpiarPantalla();
                listarProductosRestaurante(id_restaurante);
                pausar();
                break;
            }
            case 4:{
                limpiarPantalla();
                listarOrdenesRestaurante(id_restaurante);
                pausar();
                break;
            }
            case 5:{
                limpiarPantalla();
                listarOrdenesRestaurante(id_restaurante);
                actualizarEstadoOrden(id_restaurante);
                pausar();
                break;
            }
            case 6:{
                limpiarPantalla();
                mostrarInfoRestaurante(id_restaurante);
                pausar();
                break;
            }
            case 7:{
                limpiarPantalla();
                mostrarCaja("MIS DATOS");
                printf("%s%s  ID: %s%d\n", CYAN, BOX_V, WHITE, usuario.id_usuario);
                printf("%s%s  Nombre: %s%s %s\n", CYAN, BOX_V, WHITE, usuario.nombre, usuario.apellido);
                printf("%s%s  Email: %s%s\n", CYAN, BOX_V, WHITE, usuario.email);
                printf("%s%s  Teléfono: %s%s\n", CYAN, BOX_V, WHITE, usuario.telefono);
                mostrarCajaFin();
                pausar();
                break;
            }
            case 8:{
                limpiarPantalla();
                mostrarExito("Sesión cerrada correctamente");
                pausar();
                break;
            }
            default:{
                mostrarError("Opción no válida.");
                pausar();
                break;
            }
        }
    } while(opcion != 8);
}

void panelAdministrador(Usuario usuario){
    int opcion = 0;
    char informeOpcion[10];

    int idUsuario;
    int idPedido;

    do{
        limpiarPantalla();
        mostrarCaja("PANEL ADMINISTRADOR");

        mostrarSubtitulo("¿Qué deseas hacer?");
        mostrarLinea();
        mostrarOpcion(1, "Mostrar Cuentas");
        mostrarOpcion(2, "Mostrar Restaurantes");
        mostrarOpcion(3, "Gestión de Finanzas");
        mostrarOpcion(4, "Eliminar Usuario");
        mostrarOpcion(5, "Agregar Restaurante");
        mostrarOpcion(6, "Eliminar Restaurante");
        mostrarOpcion(7, "Informes");
        mostrarOpcion(8, "Cerrar Sesión");
        mostrarCajaFin();

        char menuTipoInformes[6][50]={
            "[a] Listado restaurantes con calificacion +4.0\n",
            "[b] Platos mas pedidos\n",
            "[c] Pedidos de un usuario especifico\n",
            "[d] Factura de un pedido\n",
            "[e] Volver\n",
            "Opcion: "
        };

        mostrarInput("Elige una opción");
        if(scanf("%d", &opcion) != 1){
            while (getchar() != '\n');
            opcion = -1;
        }

        switch(opcion){
            case 1:{
                limpiarPantalla();
                listarUsuarios();
                pausar();
                break;
            }
            case 2:{
                limpiarPantalla();
                listarRestaurantes();
                pausar();
                break;
            }
            case 3:{
                limpiarPantalla();
                int opcion_finanzas = 0;
                do{
                    limpiarPantalla();
                    mostrarCaja("GESTIÓN DE FINANZAS");
                    mostrarSubtitulo("¿Qué deseas ver?");
                    mostrarLinea();
                    mostrarOpcion(1, "Ver Ingresos Totales del Sistema");
                    mostrarOpcion(2, "Ver Ingresos por Restaurante");
                    mostrarOpcion(3, "Realizar Pago a Restaurante");
                    mostrarOpcion(4, "Ver Ingresos de Repartidor");
                    mostrarOpcion(5, "Ver Calificaciones de Restaurantes");
                    mostrarOpcion(6, "Volver");
                    mostrarCajaFin();

                    mostrarInput("Elige una opción");
                    if(scanf("%d", &opcion_finanzas) != 1){
                        while(getchar() != '\n');
                        opcion_finanzas = -1;
                    }

                    switch(opcion_finanzas){
                        case 1:{
                            limpiarPantalla();
                            verFinanzasTotales();
                            pausar();
                            break;
                        }
                        case 2:{
                            limpiarPantalla();
                            int id_rest;
                            listarRestaurantes();
                            mostrarInput("ID del restaurante");
                            scanf("%d", &id_rest);
                            verIngresosRestaurante(id_rest);
                            pausar();
                            break;
                        }
                        case 3:{
                            limpiarPantalla();
                            realizarPagoRestaurante();
                            pausar();
                            break;
                        }
                        case 4:{
                            limpiarPantalla();
                            int id_repartidor;
                            listarRepartidores();

                            mostrarInput("ID del repartidor");
                            scanf("%d", &id_repartidor);
                            verIngresoRepartidor(id_repartidor);
                            pausar();
                            break;
                        }
                        case 5:{
                            limpiarPantalla();
                            int id_rest_cal;
                            listarRestaurantes();
                            mostrarInput("ID del restaurante");
                            scanf("%d", &id_rest_cal);
                            verCalificacionesRestaurante(id_rest_cal);
                            pausar();
                            break;
                        }
                        case 6:{
                            break;
                        }
                    }
                } while(opcion_finanzas != 6);
                break;
            }
            case 4:{
                limpiarPantalla();
                listarUsuarios();
                eliminarUsuarioPorId(usuario);
                pausar();
                break;
            }
            case 5:{
                limpiarPantalla();
                agregarRestaurante();
                pausar();
                break;
            }
            case 6:{
                limpiarPantalla();
                listarRestaurantes();
                eliminarRestaurantePorId();
                pausar();
                break;
            }
            case 7:{
                limpiarPantalla();
                generarMenu(menuTipoInformes, 6);
                scanf("%s", informeOpcion);
                switch(informeOpcion[0]){
                    case 'a':{
                        limpiarPantalla();
                        listadoCalificacion();
                        listarArchivo("docs/restaurantes_top.txt");
                        pausar();
                        break;
                    }
                    case 'b':{
                        limpiarPantalla();
                        platosMasPedidos();
                        listarArchivo("docs/top_platos.txt");
                        pausar();
                        break;
                    }
                    case 'c':{
                        limpiarPantalla();
                        mostrarInput("Ingrese ID usuario");
                        scanf("%d", &idUsuario);
                        pedidosUsuario(idUsuario);
                        listarArchivo("docs/reporte_pedidos_usuario.txt");
                        pausar();
                        break;
                    }
                    case 'd':{
                        limpiarPantalla();
                        mostrarInput("Ingrese ID pedido");
                        scanf("%d", &idPedido);
                        listarArchivo("docs/factura_pedido.txt");
                        pausar();
                        break;
                    }
                    default:{
                        limpiarPantalla();
                        mostrarError("Opción no válida.");
                        pausar();
                        break;
                    }
                }

            }
            case 8:{
                limpiarPantalla();
                mostrarExito("Sesión cerrada correctamente");
                pausar();
                break;
            }
            default:{
                mostrarError("Opción no válida.");
                pausar();
                break;
            }
        }
    } while(opcion != 8);
}


