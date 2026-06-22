#include <stdio.h>
#include <stdlib.h>
#include "informes.h"
#include "BBD.h"

void listadoCalificacion(){
    FILE *archRestaurante;
    FILE *archCalificacion;
    FILE *reporte;

    Restaurante restaurante;
    Calificacion calificacion;

    float suma;
    int cantidad;

    reporte = fopen("restaurantes_top.txt", "wt");

    if(reporte == NULL){
        printf("\nError al generar reporte.");
        return;
    }
    archRestaurante = fopen("restaurante.dat", "rb");
    while(fread(&restaurante,sizeof(Restaurante),1,archRestaurante)==1){
        suma = 0;
        cantidad = 0;
        archCalificacion = fopen("calificacion.dat","rb");
        while(fread(&calificacion,sizeof(Calificacion),1,archCalificacion)==1){
            if(calificacion.id_restaurante == restaurante.id_restaurante){
                suma += calificacion.id_restaurante;
                cantidad++;
            }
        }
        fclose(archCalificacion);
        if(cantidad > 0){
            float promedio = suma / cantidad;
            if(promedio > 4.0){
                fprintf(reporte, "ID: %d\n Nombre: %s\n Calificacion: %.2f\n\n", restaurante.id_restaurante, restaurante.nombre, promedio);
            }
        }
    }
    fclose(archRestaurante);
    fclose(reporte);
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
    archivoDetalle = fopen("detalle_orden.dat", "rb");

    if(archivoDetalle == NULL){
        printf("\nNo existe detalle_orden.dat");
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
    reporte = fopen("top_platos.txt", "wt");
    if(reporte == NULL){
        printf("\nNo se pudo crear el reporte.");
        return;
    }
    fprintf(reporte, "===== TOP 5 PLATOS MAS PEDIDOS =====\n\n");
    for(i = 0; i < totalProductos && i < 5; i++){
        archivoProducto = fopen("producto.dat", "rb");
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
    printf("\nReporte generado: top_platos.txt");
}

void pedidosUsuario(int id_usuario){
    FILE *archivoPedido;
    FILE *reporte;
    Pedido pedido;
    archivoPedido = fopen("pedido.dat", "rb");
    reporte = fopen("reporte_pedidos_usuario.txt", "wt");

    if(archivoPedido == NULL || reporte == NULL){
        printf("\nError al abrir archivos.");
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
    printf("\nReporte generado: reporte_pedidos_usuario.txt");
}

void facturaPedido(int id_pedido){
    FILE *archivoPedido;
    FILE *archivoDetalle;
    FILE *reporte;

    Pedido pedido;
    DetalleOrden detalle;

    archivoPedido = fopen("pedido.dat", "rb");
    archivoDetalle = fopen("detalle_orden.dat", "rb");
    reporte = fopen("factura_pedido.txt", "wt");

    if(archivoPedido == NULL ||
       archivoDetalle == NULL ||
       reporte == NULL){
        printf("\nError al abrir archivos.");
        return;
    }

    while(fread(&pedido, sizeof(Pedido), 1, archivoPedido) == 1){
        if(pedido.id_pedido == id_pedido){
            fprintf(reporte, "========== FACTURA ==========\n\n");
            fprintf(reporte,"Pedido N°: %d\n Fecha: %s\n Estado: %s\n\n",
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

    printf("\nFactura generada: factura_pedido.txt");
}
