#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "crud.h"
#include "informes.h"
#include "filemanager.h"
#include "BBD.h"
#include "ui.h"

int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");
    inicializarUI();

    int opcion_app = 0;
    int opcion_sesion = 0;
    Usuario usuario;

    abrirBDD();

    // MENÚ PRINCIPAL: Seleccionar App
    do {
        limpiarPantalla();
        mostrarCaja("MORFI - SISTEMA DE DELIVERY");

        mostrarSubtitulo("¿Qué aplicación deseas abrir?");
        mostrarLinea();
        mostrarOpcion(1, "[ Morfi ] - Cliente");
        mostrarOpcion(2, "[ Morfi Riders ] - Repartidor");
        mostrarOpcion(3, "[ Morfi Restaurant ] - Encargado");
        mostrarOpcion(4, "[ Morfi Admin ]");
        mostrarOpcion(5, "Salir del Sistema");
        mostrarCajaFin();

        mostrarInput("Selecciona una opción");
        if(scanf("%d", &opcion_app) != 1){
            while (getchar() != '\n');
            opcion_app = -1;
        }

        if(opcion_app == 5) break;

        if(opcion_app < 1 || opcion_app > 4){
            mostrarError("Opción no válida. Intenta nuevamente.");
            pausar();
            continue;
        }

        // MENÚ DE SESIÓN: Para cada app
        do {
            limpiarPantalla();

            // Mostrar título según la app
            char titulo_app[50];
            switch(opcion_app){
                case 1: sprintf(titulo_app, "MORFI - CLIENTE"); break;
                case 2: sprintf(titulo_app, "MORFI - RIDERS"); break;
                case 3: sprintf(titulo_app, "MORFI - GESTIÓN"); break;
                case 4: sprintf(titulo_app, "MORFI - ADMIN"); break;
            }

            mostrarCaja(titulo_app);
            mostrarSubtitulo("¿Qué deseas hacer?");
            mostrarLinea();
            mostrarOpcion(1, "Iniciar Sesión");
            mostrarOpcion(2, "Crear Cuenta");
            mostrarOpcion(3, "Volver a seleccionar app");
            mostrarCajaFin();

            mostrarInput("Elige una opción");
            if(scanf("%d", &opcion_sesion) != 1){
                while (getchar() != '\n');
                opcion_sesion = -1;
            }

            if(opcion_sesion == 3) break;

            switch(opcion_sesion){
                case 1:{
                    limpiarPantalla();
                    mostrarCaja("INICIAR SESIÓN");
                    mostrarInput("Correo electrónico");
                    scanf(" %[^\n]", usuario.email);
                    mostrarInput("Contraseña");
                    scanf(" %[^\n]", usuario.contrasena);

                    seleccionarCuentaConRol(usuario, opcion_app);
                    pausar();
                    break;
                }
                case 2:{
                    limpiarPantalla();
                    registrarUsuarioConRol(opcion_app);
                    pausar();
                    break;
                }
                default:
                    mostrarError("Opción no válida.");
                    pausar();
                    break;
            }

        } while(opcion_sesion != 3 && opcion_sesion != -1);

    } while(opcion_app != 5);

    limpiarPantalla();
    mostrarCaja("GRACIAS POR USAR MORFI");
    printf("\n%s%s  %s¡Hasta pronto!%s\n", CYAN, BOX_V, YELLOW, RESET);
    mostrarCajaFin();

    return 0;
}

