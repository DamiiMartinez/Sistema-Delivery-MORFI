#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"

#ifdef _WIN32
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
#endif

void inicializarUI(){
    #ifdef _WIN32
        // Habilitar colores ANSI en Windows 10+
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(handle, &mode);
        mode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
        SetConsoleMode(handle, mode);

        // Configurar tamaño de ventana
        system("title Morfi - Sistema de Delivery");
        system("mode con: cols=80 lines=30");
    #endif

    limpiarPantalla();
}

void limpiarPantalla(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("%s", "\033[44m");  // Fondo azul
    printf("%s", RESET);
}

void mostrarTitulo(const char *titulo){
    int ancho = 70;
    int largo_titulo = strlen(titulo);
    int espacios_totales = ancho - largo_titulo - 4;
    int espacios_izq = espacios_totales / 2;
    int espacios_der = espacios_totales - espacios_izq;

    printf("\n%s%s%s", CYAN, BOX_TL, "");
    for(int i = 0; i < ancho; i++) printf("%s", BOX_H);
    printf("%s%s\n", BOX_TR, RESET);

    printf("%s%s  ", CYAN, BOX_V);
    printf("%s%s%s", BOLD WHITE, titulo, RESET);
    for(int i = 0; i < espacios_der; i++) printf(" ");
    printf("%s%s%s\n", CYAN, BOX_V, RESET);

    printf("%s%s", CYAN, BOX_BL);
    for(int i = 0; i < ancho; i++) printf("%s", BOX_H);
    printf("%s%s\n", BOX_BR, RESET);
}

void mostrarSubtitulo(const char *subtitulo){
    printf("\n%s%s %s%s\n", CYAN, BOX_V, LIGHT_GRAY, subtitulo);
}

void mostrarOpcion(int numero, const char *texto){
    printf("%s%s  %s[%d]%s %s%s\n",
           CYAN, BOX_V,
           YELLOW, numero, RESET,
           WHITE, texto);
}

void mostrarError(const char *mensaje){
    printf("\n%s%s %s%s ERROR:%s %s\n%s%s\n",
           RED, BOX_V,
           BOLD RED, ERROR_MARK, RESET,
           RED, mensaje,
           RED, BOX_V);
}

void mostrarExito(const char *mensaje){
    printf("\n%s%s %s%s ÉXITO:%s %s\n%s%s\n",
           GREEN, BOX_V,
           BOLD GREEN, CHECKMARK, RESET,
           GREEN, mensaje,
           GREEN, BOX_V);
}

void mostrarInfo(const char *mensaje){
    printf("%s%s  %s%s%s\n",
           CYAN, BOX_V,
           LIGHT_GRAY, mensaje, RESET);
}

void mostrarLinea(){
    printf("%s%s", CYAN, BOX_V);
    for(int i = 0; i < 68; i++) printf("─");
    printf("%s\n", RESET);
}

void mostrarCaja(const char *titulo){
    printf("\n%s%s%s", CYAN, BOX_TL, "");
    for(int i = 0; i < 68; i++) printf("%s", BOX_H);
    printf("%s%s\n", BOX_TR, RESET);

    if(titulo && strlen(titulo) > 0){
        int largo = strlen(titulo);
        int espacios = (68 - largo) / 2;
        printf("%s%s", CYAN, BOX_V);
        for(int i = 0; i < espacios; i++) printf(" ");
        printf("%s%s%s", BOLD WHITE, titulo, RESET);
        for(int i = espacios + largo; i < 68; i++) printf(" ");
        printf("%s%s\n", CYAN, BOX_V, RESET);

        printf("%s%s", CYAN, BOX_MID_L);
        for(int i = 0; i < 68; i++) printf("%s", BOX_MID_H);
        printf("%s%s\n", BOX_MID_R, RESET);
    }
}

void mostrarCajaFin(){
    printf("%s%s", CYAN, BOX_BL);
    for(int i = 0; i < 68; i++) printf("%s", BOX_H);
    printf("%s%s\n\n", BOX_BR, RESET);
}

void mostrarInput(const char *prompt){
    printf("%s%s  %s%s: %s", CYAN, BOX_V, YELLOW, prompt, WHITE);
}

void pausar(){
    printf("\n%s%s %s[Presiona ENTER para continuar]%s\n",
           CYAN, BOX_V, DIM GRAY, RESET);
    #ifdef _WIN32
        system("pause > nul");
    #else
        getchar();
    #endif
}
