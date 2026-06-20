#include <stdio.h>
#include <stdlib.h>
#include "BBD.h"

/** direccion de las estructuras*/

void generarMenu(char menu[][50], int opciones){
    for(int i=0; i<opciones; i++){
        printf("\n%s", menu[i]);
    }
}

void panelCliente(Usuario usuario){
    int opcion = 0;

    char menuUsuario[10][50]={
    "[1] Realizar Pedido\n",
    "[2] Mostrar Pedidos\n",
    "[3] Realizar Consulta\n",
    "[4] Mostrar Consultas\n",
    "[5] Realizar Reportes\n",
    "[6] Mostrar Reportes\n",
    "[7] Mostrar Cuenta\n",
    "[8] Eliminar Cuenta\n",
    "[9] Salir\n",
    "Opcion: "
    };

    system("pause");
    system("cls");

    do{
        printf("\n===============================\n");
        printf("\n SISTEMA DE DELIVERY: CLIENTE\n");
        printf("\n===============================\n");

        generarMenu(menuUsuario, 10);
        scanf("%d", &opcion);
        switch(opcion){
            case 1:{
                system("pause");
                system("cls");
                break;
            }
            case 2:{
                system("pause");
                system("cls");
                break;
            }
            case 3:{
                system("pause");
                system("cls");
                break;
            }
            case 4:{
                system("pause");
                system("cls");
                break;
            }
            case 5:{
                system("pause");
                system("cls");
                break;
            }
            case 6:{
                system("pause");
                system("cls");
                break;
            }
            case 7:{
                system("pause");
                system("cls");
                break;
            }
            case 8:{
                system("pause");
                system("cls");
                break;
            }
            case 9:{

                system("pause");
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 9);
}

void panelRepartidor(Usuario usuario){
    system("pause");
    system("cls");

    int opcion = 0;

    char menuRepartidor[5][50]={
    "[1] Mostrar Pedidos\n",
    "[2] Modificar Cuenta\n",
    "[3] Eliminar Cuenta\n",
    "[4] Salir\n",
    "Opcion: "
    };

    do{
        printf("\n====================================\n");
        printf("\n SISTEMA DE DELIVERY: REPARTIDOR\n");
        printf("\n====================================\n");

        generarMenu(menuRepartidor, 5);
        scanf("%d", &opcion);
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
                system("pause");
                system("cls");
                break;
            }
            case 4:{
                system("cls");
                agregarRestaurante();
                system("pause");
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 4);
}

void panelEncargador(Usuario usuario){
    system("pause");
    system("cls");

    int opcion = 0;

    char menuEncargado[9][50]={
    "[1] Ingresar Nuevo Menu\n",
    "[2] Modificar Plato\n",
    "[3] Mostrar Restaurante\n",
    "[4] Mostrar Ordenes\n",
    "[5] Mostrar Pedidos\n",
    "[6] Mostrar Informacion del Restaurante\n",
    "[7] Modificar Cuenta\n",
    "[8] Eliminar Cuenta\n",
    "Opcion: "
    };

    do{
        printf("\n====================================\n");
        printf("\n SISTEMA DE DELIVERY: ENCARGADO\n");
        printf("\n====================================\n");

        generarMenu(menuEncargado, 9);
        scanf("%d", &opcion);
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
                system("pause");
                system("cls");
                break;
            }
            case 4:{
                system("cls");
                agregarRestaurante();
                system("pause");
                system("cls");
                break;
            }
            case 5:{
                system("pause");
                system("cls");
                break;
            }
            case 6:{
                system("pause");
                system("cls");
                break;
            }
            case 7:{
                system("pause");
                system("cls");
                break;
            }
            case 8:{
                system("pause");
                system("cls");
                break;
            }
            case 9:{
                system("pause");
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 9);
}

void panelAdministrador(Usuario usuario){

    int opcion = 0;

    char menuAdministrador[8][50]={
    "[1] Mostrar Cuentas\n",
    "[2] Mostrar Restaurantes\n",
    "[3] Mostrar Finanzas\n",
    "[4] Eliminar Usuario\n",
    "[5] Agregar Restaurante\n",
    "[6] Eliminar Restaurante\n",
    "[7] Salir\n",
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
        scanf("%d", &opcion);
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
                system("pause");
                system("cls");
                break;
            }
            case 4:{
                system("cls");
                agregarRestaurante();
                system("pause");
                system("cls");
                break;
            }
            case 5:{
                system("pause");
                system("cls");
                break;
            }
            case 6:{
                system("pause");
                system("cls");
                break;
            }
            case 7:{
                system("pause");
                system("cls");
                break;
            }
            default:{
                printf("---------ERROR-------");
                system("pause");
                system("cls");
                break;
            }
        }
    } while(opcion != 7);
}
