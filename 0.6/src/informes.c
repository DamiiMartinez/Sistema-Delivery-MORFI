#include <stdio.h>
#include <stdlib.h>
#include "informes.h"
#include "BBD.h"
#include "ui.h"

void listadoCalificacion(){
    FILE *archRestaurante;
    FILE *archCalificacion;
    FILE *reporte;

    Restaurante restaurante;
    Calificacion calificacion;

    float suma;
    int cantidad;

    limpiarPantalla();
    mostrarCaja("INFORME DE CALIFICACIONES");
    mostrarSubtitulo("Restaurantes destacados");
    mostrarLinea();
    mostrarInfo("Generando reporte...");

    reporte = fopen("docs/restaurantes_top.txt", "wt");

    if(reporte == NULL){
        mostrarError("Error al generar reporte.");
        pausar();
        return;
    }
    archRestaurante = fopen("data/restaurante.dat", "rb");
    while(archRestaurante != NULL && fread(&restaurante,sizeof(Restaurante),1,archRestaurante)==1){
        suma = 0;
        cantidad = 0;
        archCalificacion = fopen("data/calificacion.dat","rb");
        while(archCalificacion != NULL && fread(&calificacion,sizeof(Calificacion),1,archCalificacion)==1){
            if(calificacion.id_restaurante == restaurante.id_restaurante){
                suma += calificacion.id_restaurante;
                cantidad++;
            }
        }
        if(archCalificacion != NULL) fclose(archCalificacion);
        if(cantidad > 0){
            float promedio = suma / cantidad;
            if(promedio > 4.0){
                fprintf(reporte, "ID: %d\n Nombre: %s\n Calificacion: %.2f\n\n", restaurante.id_restaurante, restaurante.nombre, promedio);
            }
        }
    }
    if(archRestaurante != NULL) fclose(archRestaurante);
    fclose(reporte);
    mostrarExito("Reporte de calificaciones generado.");
    mostrarInfo("Ruta: docs/restaurantes_top.txt");
    mostrarCajaFin();
    pausar();
}

void platosMasPedidos(){
    FILE *archivoDetalle;
    FILE *archivoProducto;
    FILE *reporte;

    DetalleOrden detalle;
    Producto producto;

    RankingProducto ranking[100];

    int totalProductos = 0;
    int encontrado;
    int i, j;

    limpiarPantalla();
    mostrarCaja("INFORME DE PLATOS");
    mostrarSubtitulo("Top 5 más pedidos");
    mostrarLinea();
    mostrarInfo("Generando reporte...");

    archivoDetalle = fopen("data/detalle_orden.dat", "rb");

    if(archivoDetalle == NULL){
        mostrarError("No existe data/detalle_orden.dat");
        pausar();
        return;
    }

    while(fread(&detalle, sizeof(DetalleOrden), 1, archivoDetalle) == 1){
        encontrado = 0;
        for(i = 0; i < totalProductos; i++){
            if(ranking[i].id_producto == detalle.id_producto){
                ranking[i].cantidad += detalle.cantidad;
                encontrado = 1;
                break;
            }
        }
        if(!encontrado){
            ranking[totalProductos].id_producto = detalle.id_producto;
            ranking[totalProductos].cantidad = detalle.cantidad;
            totalProductos++;
        }
    }

    fclose(archivoDetalle);

    /* Ordenar descendente */
    for(i = 0; i < totalProductos - 1; i++){
        for(j = i + 1; j < totalProductos; j++){
            if(ranking[j].cantidad > ranking[i].cantidad){
                RankingProducto aux = ranking[i];
                ranking[i] = ranking[j];
                ranking[j] = aux;
            }
        }
    }
    reporte = fopen("docs/top_platos.txt", "wt");
    if(reporte == NULL){
        mostrarError("No se pudo crear el reporte.");
        pausar();
        return;
    }
    fprintf(reporte, "===== TOP 5 PLATOS MAS PEDIDOS =====\n\n");
    for(i = 0; i < totalProductos && i < 5; i++){
        archivoProducto = fopen("data/producto.dat", "rb");
        if(archivoProducto != NULL){
            while(fread(&producto, sizeof(Producto), 1, archivoProducto) == 1){
                if(producto.id_producto == ranking[i].id_producto){
                    fprintf(reporte, "%d) %s - %d unidades\n", i + 1, producto.nombre_producto, ranking[i].cantidad);
                    break;
                }
            }
            fclose(archivoProducto);
        }
    }
    fclose(reporte);
    mostrarExito("Reporte de platos generado.");
    mostrarInfo("Ruta: docs/top_platos.txt");
    mostrarCajaFin();
    pausar();
}

void pedidosUsuario(int id_usuario){
    FILE *archivoPedido;
    FILE *reporte;
    Pedido pedido;

    limpiarPantalla();
    mostrarCaja("INFORME DE PEDIDOS");
    mostrarSubtitulo("Historial del usuario");
    mostrarLinea();
    mostrarInfo("Generando reporte...");

    archivoPedido = fopen("data/pedido.dat", "rb");
    reporte = fopen("docs/reporte_pedidos_usuario.txt", "wt");

    if(archivoPedido == NULL || reporte == NULL){
        mostrarError("Error al abrir archivos.");
        pausar();
        return;
    }

    fprintf(reporte, "===== PEDIDOS DEL USUARIO %d =====\n\n", id_usuario);

    while(fread(&pedido, sizeof(Pedido), 1, archivoPedido) == 1){
        if(pedido.id_cliente == id_usuario){
            fprintf(reporte,
                    "ID Pedido: %d\n"
                    "Fecha: %s\n"
                    "Estado: %s\n"
                    "Direccion: %s\n\n",
                    pedido.id_pedido,
                    pedido.fecha_pedido,
                    pedido.estado,
                    pedido.direccion_entrega);
        }
    }
    fclose(archivoPedido);
    fclose(reporte);
    mostrarExito("Reporte de pedidos generado.");
    mostrarInfo("Ruta: docs/reporte_pedidos_usuario.txt");
    mostrarCajaFin();
    pausar();
}

void facturaPedido(int id_pedido){
    FILE *archivoPedido;
    FILE *archivoDetalle;
    FILE *reporte;

    Pedido pedido;
    DetalleOrden detalle;

    limpiarPantalla();
    mostrarCaja("FACTURA DE PEDIDO");
    mostrarSubtitulo("Detalle del comprobante");
    mostrarLinea();
    mostrarInfo("Generando factura...");

    archivoPedido = fopen("data/pedido.dat", "rb");
    archivoDetalle = fopen("data/detalle_orden.dat", "rb");
    reporte = fopen("docs/factura_pedido.txt", "wt");

    if(archivoPedido == NULL ||
       archivoDetalle == NULL ||
       reporte == NULL){
        mostrarError("Error al abrir archivos.");
        pausar();
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivoPedido) == 1){
        if(pedido.id_pedido == id_pedido){
            fprintf(reporte, "========== FACTURA ==========\n\n");
            fprintf(reporte,"Pedido N�: %d\n Fecha: %s\n Estado: %s\n\n",
                    pedido.id_pedido,
                    pedido.fecha_pedido,
                    pedido.estado);

            rewind(archivoDetalle);
            while(fread(&detalle, sizeof(DetalleOrden), 1, archivoDetalle) == 1){
                if(detalle.id_orden == pedido.id_pedido){
                    fprintf(reporte, "Producto: %d\n Cantidad: %d\n\n", detalle.id_producto, detalle.cantidad);
                }
            }
        }
    }

    fclose(archivoPedido);
    fclose(archivoDetalle);
    fclose(reporte);

    mostrarExito("Factura generada correctamente.");
    mostrarInfo("Ruta: docs/factura_pedido.txt");
    mostrarCajaFin();
    pausar();
}


