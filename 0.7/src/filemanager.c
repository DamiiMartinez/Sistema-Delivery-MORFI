#include <stdio.h>
#include <stdlib.h>
#include "filemanager.h"
#include "BBD.h"
#include "ui.h"

void abrirArchivo(char nombre[]){
    FILE *archivo = fopen(nombre, "wt");

    if(archivo != NULL){
        mostrarExito("Archivo creado correctamente.");
        fclose(archivo);
    }else{
        mostrarError("Error al crear el archivo.");
    }
}

void leerRegistro(char nombre[]){
    FILE *archivo = fopen(nombre, "rt");

    int letra;

    if(archivo != NULL){

        while((letra = fgetc(archivo)) != EOF){
            printf("%c", letra);
        }

        fclose(archivo);

    }else{
        mostrarError("No existe el archivo.");
    }
}

void escribirArchivo(char nombre[], char texto[]){
    FILE *archivo = fopen(nombre, "at");

    if(archivo != NULL){
        fprintf(archivo, "%s", texto);
        fclose(archivo);
    }else{
        mostrarError("Error al abrir el archivo.");
    }
}

void busquedaXid(char nombre[], int id){
    FILE *archivo;
    char linea[300];
    int id_leido;

    archivo = fopen(nombre, "rt");

    if(archivo == NULL){
        mostrarError("No existe el archivo.");
        return;
    }

    while(fgets(linea, sizeof(linea), archivo) != NULL){

        sscanf(linea, "%d", &id_leido);

        if(id_leido == id){

            mostrarExito("Registro encontrado.");
            mostrarInfo(linea);

            fclose(archivo);
            return;
        }
    }

    mostrarError("ID no encontrado.");

    fclose(archivo);
}

void listarArchivo(char nombre[]){
    leerRegistro(nombre);
}


