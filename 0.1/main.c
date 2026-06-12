#include <stdio.h>
#include <stdlib.h>

/** funciones de alta, baja, modificación, */
/** listado para cada tabla. */
#include "crud.h"

/** funciones para abrir archivos, */
/** leer registros, escribir, buscar por ID, */
/** listar todos.*/
#include "informes.h"

/** generación de informes en texto*/
#include "filemanager.h"

/** direccion de las estructuras*/
#include "BBD.h"

/*
Archivos Binarios, pudiendo variar en por ejemplo la extensión a .bin:
usuarios.dat
restaurantes.dat
platos.dat
pedidos.dat
detalles_pedido.dat

*/

int main()
{
    int opcion = 0;
    char opcionInforme[10];

    char menuSistema[9][50]={
    "[1] ABM de Usuarios\n",
    "[2] ABM de Restaurantes\n",
    "[3] ABM de Platos\n",
    "[4] Registrar nuevo Pedido\n",
    "[5] Actualizar estado de Pedido\n",
    "[6] Listar Pedidos por Usuario\n",
    "[7] Informes en archivo de texto\n",
    "[8] Salir\n",
    "Opcion: "
    };

    char menuABM[6][50]={
    "[a] Agregar\n",
    "[b] Actualizar por ID\n",
    "[c] Eliminar por ID\n",
    "[d] Listar\n",
    "[e] Volver\n",
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
        printf("----------SISTEMA DE DELIVERY: MENU----------\n");
        generarMenu(menuSistema, 9);
        scanf("%d", &opcion);
        switch(opcion){
            case 1:{
                system("cls");
                do{
                    printf("----------Usuarios----------\n");
                    generarMenu(menuABM, 6);
                    scanf("%s", opcionInforme);
                    if(opcionInforme[0] == 'a'){
                            /** AGREGAR */
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'b'){
                            /**ACTUALIZAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'c'){
                            /**ELIMINAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'd'){
                            /**LISTAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'e'){
                            printf("\n\nVolviendo.......\n\n");
                            system("pause");
                            system("cls");
                    }else{
                        printf("\n\n----------ERROR----------\n\n");
                        system("pause");
                        system("cls");
                    }
                }while(opcionInforme[0] != 'e');
                break;
            }
            case 2:{
                system("cls");
                do{
                    printf("----------Restaurantes----------\n");
                    generarMenu(menuTipoInformes, 6);
                    scanf("%s", opcionInforme);
                    if(opcionInforme[0] == 'a'){
                            /** AGREGAR */
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'b'){
                            /**ACTUALIZAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'c'){
                            /**ELIMINAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'd'){
                            /**LISTAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'e'){
                            printf("\n\nVolviendo.......\n\n");
                            system("pause");
                            system("cls");
                    }else{
                        printf("\n\n----------ERROR----------\n\n");
                        system("pause");
                        system("cls");
                    }
                }while(opcionInforme[0] != 'e');

                break;
            }
            case 3:{
                system("cls");
                do{
                    printf("----------Platos----------\n");
                    generarMenu(menuTipoInformes, 6);
                    scanf("%s", opcionInforme);
                    if(opcionInforme[0] == 'a'){
                            /** AGREGAR */
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'b'){
                            /**ACTUALIZAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'c'){
                            /**ELIMINAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'd'){
                            /**LISTAR*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'e'){
                            printf("\n\nVolviendo.......\n\n");
                            system("pause");
                            system("cls");
                    }else{
                        printf("\n\n----------ERROR----------\n\n");
                        system("pause");
                        system("cls");
                    }
                }while(opcionInforme[0] != 'e');

                break;
            }
            case 4:{
                /**Registrar nuevo Pedido*/
                system("cls");

                system("cls");
                break;
            }
            case 5:{
                /**Actualizar estado de Pedido*/
                system("cls");

                system("cls");
                break;
            }
            case 6:{
                /**Listar Pedidos por Usuario*/
                system("cls");

                system("cls");
                break;
            }
            case 7:{
                /**Informes en archivo de texto*/
                system("cls");
                do{
                    printf("----------INFORMES----------\n");
                    generarMenu(menuTipoInformes, 6);
                    scanf("%s", opcionInforme);
                    if(opcionInforme[0] == 'a'){
                            /**Listado de todos los restaurantes con su calificación > 4.0 (salida: restaurantes_top.txt)*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'b'){
                            /**Pedidos de un usuario específico (ingresar ID_usuario) ->  pedidos_usuario_<ID>.txt*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'c'){
                            /**Platos más pedidos (top 5) → top_platos.txt*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'd'){
                            /** Factura de un pedido (detalle + total) -> factura_<ID_pedido>.txt*/
                            system("cls");
                            system("cls");
                    }else if(opcionInforme[0] == 'e'){
                            printf("\n\nVolviendo.......\n\n");
                            system("pause");
                            system("cls");
                    }else{
                        printf("\n\n----------ERROR----------\n\n");
                        system("pause");
                        system("cls");
                    }
                }while(opcionInforme[0] != 'e');

                break;
            }
            case 8:{
                printf("\n----------FIN DEL SISTEMA----------");
                break;
            }
            default:{
                printf("\n\n----------ERROR----------\n\n");
                system("pause");
                system("cls");
            }
        }
    }while(opcion != 8);

    return 0;
}
