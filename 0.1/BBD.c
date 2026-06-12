#include <stdio.h>
#include <stdlib.h>
#include "BBD.h"

/** direccion de las estructuras*/

void generarMenu(char menu[][50], int opciones){
    for(int i=0; i<opciones; i++){
        printf("\n%s", menu[i]);
    }
}
