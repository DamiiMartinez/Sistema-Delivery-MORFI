#include "validaciones.h"

int validarEmail(const char email[]) {
    if (email == NULL || strlen(email) == 0) {
        printf("\n[ERROR] Email no puede estar vacío.\n");
        return 0;
    }

    // Verificar que contenga @ y . (formato básico)
    int tieneArroba = 0;
    int tienePunto = 0;
    int posicionArroba = -1;
    int posicionPunto = -1;

    for (int i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            tieneArroba++;
            posicionArroba = i;
        }
        if (email[i] == '.') {
            tienePunto++;
            posicionPunto = i;
        }
    }

    // Debe tener exactamente 1 @, al menos 1 . después de @
    if (tieneArroba != 1) {
        printf("\n[ERROR] Email debe contener exactamente un (@).\n");
        return 0;
    }

    if (tienePunto == 0 || posicionPunto <= posicionArroba) {
        printf("\n[ERROR] Email debe contener un punto (.) después del (@).\n");
        return 0;
    }

    if (posicionArroba == 0 || posicionPunto == strlen(email) - 1) {
        printf("\n[ERROR] Formato de email inválido.\n");
        return 0;
    }

    return 1;
}

int validarTelefono(const char telefono[]) {
    if (telefono == NULL || strlen(telefono) == 0) {
        printf("\n[ERROR] Teléfono no puede estar vacío.\n");
        return 0;
    }

    int longitud = strlen(telefono);

    // Validar longitud (7-20 dígitos)
    if (longitud < 7 || longitud > 20) {
        printf("\n[ERROR] Teléfono debe tener entre 7 y 20 dígitos.\n");
        return 0;
    }

    // Validar que solo contenga dígitos y caracteres permitidos (-, +, espacio)
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(telefono[i]) && telefono[i] != '-' && telefono[i] != '+' && telefono[i] != ' ') {
            printf("\n[ERROR] Teléfono solo puede contener dígitos, guiones (+, -).\n");
            return 0;
        }
    }

    return 1;
}

int validarContrasena(const char contrasena[]) {
    if (contrasena == NULL || strlen(contrasena) == 0) {
        printf("\n[ERROR] Contraseña no puede estar vacía.\n");
        return 0;
    }

    if (strlen(contrasena) < 6) {
        printf("\n[ERROR] Contraseña debe tener mínimo 6 caracteres.\n");
        return 0;
    }

    // Verificar que no contenga espacios
    for (int i = 0; contrasena[i] != '\0'; i++) {
        if (contrasena[i] == ' ') {
            printf("\n[ERROR] Contraseña no puede contener espacios.\n");
            return 0;
        }
    }

    return 1;
}

int validarNombre(const char nombre[]) {
    if (nombre == NULL || strlen(nombre) == 0) {
        printf("\n[ERROR] Nombre no puede estar vacío.\n");
        return 0;
    }

    if (strlen(nombre) > 50) {
        printf("\n[ERROR] Nombre no puede superar 50 caracteres.\n");
        return 0;
    }

    return esTextoValido(nombre);
}

int esTextoValido(const char texto[]) {
    if (texto == NULL || strlen(texto) == 0) {
        printf("\n[ERROR] Texto no puede estar vacío.\n");
        return 0;
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        // Permitir letras (mayúsculas, minúsculas) y espacios
        if (!isalpha(texto[i]) && texto[i] != ' ' && texto[i] != '-') {
            printf("\n[ERROR] El texto solo puede contener letras, espacios o guiones.\n");
            return 0;
        }
    }

    return 1;
}

int esNumeroValido(const char texto[]) {
    if (texto == NULL || strlen(texto) == 0) {
        return 0;
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isdigit(texto[i])) {
            return 0;
        }
    }

    return 1;
}

void convertirEspaciosAGuiones(char texto[]) {
    if (texto == NULL) return;

    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == ' ') {
            texto[i] = '_';
        }
    }
}

int validarHorario(const char horario[]) {
    if (horario == NULL || strlen(horario) == 0) {
        printf("\n[ERROR] Horario no puede estar vacío.\n");
        return 0;
    }

    // Validar formato HH:MM
    if (strlen(horario) != 5) {
        printf("\n[ERROR] Horario debe tener formato HH:MM (ejemplo: 09:00).\n");
        return 0;
    }

    if (horario[2] != ':') {
        printf("\n[ERROR] Horario debe tener formato HH:MM (dos puntos en posición 2).\n");
        return 0;
    }

    // Validar que HH y MM sean números
    if (!isdigit(horario[0]) || !isdigit(horario[1]) || 
        !isdigit(horario[3]) || !isdigit(horario[4])) {
        printf("\n[ERROR] Horario debe contener solo dígitos. Formato: HH:MM.\n");
        return 0;
    }

    // Validar rango de horas (0-23) y minutos (0-59)
    int horas = (horario[0] - '0') * 10 + (horario[1] - '0');
    int minutos = (horario[3] - '0') * 10 + (horario[4] - '0');

    if (horas < 0 || horas > 23) {
        printf("\n[ERROR] Horas deben estar entre 00 y 23.\n");
        return 0;
    }

    if (minutos < 0 || minutos > 59) {
        printf("\n[ERROR] Minutos deben estar entre 00 y 59.\n");
        return 0;
    }

    return 1;
}

int validarEstadoRestaurante(const char estado[]) {
    if (estado == NULL || strlen(estado) == 0) {
        printf("\n[ERROR] Estado no puede estar vacío.\n");
        return 0;
    }

    // Estados válidos: activo, inactivo, mantenimiento
    if (strcmp(estado, "activo") != 0 && 
        strcmp(estado, "inactivo") != 0 && 
        strcmp(estado, "mantenimiento") != 0) {
        printf("\n[ERROR] Estado debe ser: 'activo', 'inactivo' o 'mantenimiento'.\n");
        return 0;
    }

    return 1;
}
