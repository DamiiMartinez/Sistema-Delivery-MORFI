#include <stdio.h>
#include <stdlib.h>
#include "filemanager.h"

/** direccion de las estructuras*/
#include "BBD.h"

/** generación de informes en texto*/

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
    char letra;
    if( archivo ){
        while(letra = fgetc(archivo) )
            fputc("%c", letra);
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
