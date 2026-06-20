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

/*
Comentario de la clase:

encontré un problema que acabo de solucionar,
cada que se hace un alta,
si no se carga del todo o salimos de la pestaña,
el archivo cierra mal y guarda basura.

*/

int main()
{
    int opcion = 0;
    int sesion = 0;
    char opcionInforme[10];

    char menuABM[6][50]={
    "[a] Agregar\n",
    "[b] Actualizar por ID\n",
    "[c] Eliminar por ID\n",
    "[d] Listar\n",
    "[e] Volver\n",
    "Opcion: "
    };

    char menuSesion[4][50]={
    "[1] Iniciar Sesion\n",
    "[2] Crear Cuenta\n",
    "[3] Salir\n",
    "Opcion: ",
    };

    Usuario usuario;

    abrirBDD();
    do{
        printf("\n===============================\n");
        printf("\n          CUENTAS\n");
        printf("\n===============================\n");
        generarMenu(menuSesion, 4);
        scanf("%d", &opcion);
        switch(opcion){
            case 1:{
                system("cls");

                printf("\nIngrese Correo: ");
                scanf("%s", usuario.email);
                printf("\nIngresa Password: ");
                scanf("%s", usuario.contrasena);

                seleccionarCuenta(usuario);

                break;
            }
            case 2:{
                system("cls");
                agregarUsuario();

                system("pause");
                system("cls");

                break;
            }
            case 3:{
                printf("\nFIN DEL SISTEMA");
                break;
            }
            default:{
                break;
            }
        }
    } while(opcion != 3);

    return 0;
}

