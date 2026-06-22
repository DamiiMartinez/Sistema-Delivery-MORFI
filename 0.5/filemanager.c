#include <stdio.h>
#include <stdlib.h>
#include "filemanager.h"
#include "BBD.h"

void abrirArchivo(char nombre[30]){
    FILE *archivo = fopen(nombre, "wt");
    if(archivo){
        printf("\nEl archivo fue abierto");
    }else{
        printf("\nEl archivo no fue creado....");
        printf("\nCreando....");
        printf("\n\nEl archivo fue creado exitosamente.");
    }
    system("pause");
}

void leerRegistro(char nombre[30]){
    FILE *archivo = fopen(nombre, "rt");
    int letra;
    if(archivo != NULL){
        while((letra = fgetc(archivo)) != EOF)
            printf("%c", letra);
    }else{
        printf("\nNo hay lectura");
    }
}

void escribirArchivo(char nombre[30]){

}

void busquedaXid(char nombre[30], int id){

}

void listarArchivo(char nombre[30]){

}
