#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validarEmail(const char email[]);
int validarTelefono(const char telefono[]);
int validarContrasena(const char contrasena[]);
int validarNombre(const char nombre[]);
int validarHorario(const char horario[]);
int validarEstadoRestaurante(const char estado[]);

int esTextoValido(const char texto[]);
int esNumeroValido(const char texto[]);

void convertirEspaciosAGuiones(char texto[]);

#endif
