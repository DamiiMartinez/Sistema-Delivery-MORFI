#include "validaciones.h"

int validarEmail(const char email[]) {
    if (email == NULL || strlen(email) == 0) {
        mostrarError("Email no puede estar vacío.");
        return 0;
    }

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

    if (tieneArroba != 1) {
        mostrarError("Email debe contener exactamente un (@).");
        return 0;
    }

    if (tienePunto == 0 || posicionPunto <= posicionArroba) {
        mostrarError("Email debe contener un punto (.) después del (@).");
        return 0;
    }

    if (posicionArroba == 0 || posicionPunto == strlen(email) - 1) {
        mostrarError("Formato de email inválido.");
        return 0;
    }

    return 1;
}

int validarTelefono(const char telefono[]) {
    if (telefono == NULL || strlen(telefono) == 0) {
        mostrarError("Teléfono no puede estar vacío.");
        return 0;
    }

    int longitud = strlen(telefono);

    if (longitud < 7 || longitud > 20) {
        mostrarError("Teléfono debe tener entre 7 y 20 dígitos.");
        return 0;
    }

    for (int i = 0; i < longitud; i++) {
        if (!isdigit(telefono[i]) && telefono[i] != '-' && telefono[i] != '+' && telefono[i] != ' ') {
            mostrarError("Teléfono solo puede contener dígitos, guiones (+, -).");
            return 0;
        }
    }

    return 1;
}

int validarContrasena(const char contrasena[]) {
    if (contrasena == NULL || strlen(contrasena) == 0) {
        mostrarError("Contraseña no puede estar vacía.");
        return 0;
    }

    if (strlen(contrasena) < 6) {
        mostrarError("Contraseña debe tener mínimo 6 caracteres.");
        return 0;
    }

    for (int i = 0; contrasena[i] != '\0'; i++) {
        if (contrasena[i] == ' ') {
            mostrarError("Contraseña no puede contener espacios.");
            return 0;
        }
    }

    return 1;
}

int validarNombre(const char nombre[]) {
    if (nombre == NULL || strlen(nombre) == 0) {
        mostrarError("Nombre no puede estar vacío.");
        return 0;
    }

    if (strlen(nombre) > 50) {
        mostrarError("Nombre no puede superar 50 caracteres.");
        return 0;
    }

    return esTextoValido(nombre);
}

int esTextoValido(const char texto[]) {
    if (texto == NULL || strlen(texto) == 0) {
        mostrarError("Texto no puede estar vacío.");
        return 0;
    }

    for (int i = 0; texto[i] != '\0'; i++) {
        if (!isalpha(texto[i]) && texto[i] != ' ' && texto[i] != '-') {
            mostrarError("El texto solo puede contener letras, espacios o guiones.");
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
        mostrarError("Horario no puede estar vacío.");
        return 0;
    }

    if (strlen(horario) != 5) {
        mostrarError("Horario debe tener formato HH:MM (ejemplo: 09:00).");
        return 0;
    }

    if (horario[2] != ':') {
        mostrarError("Horario debe tener formato HH:MM (dos puntos en posición 2).");
        return 0;
    }

    if (!isdigit(horario[0]) || !isdigit(horario[1]) || 
        !isdigit(horario[3]) || !isdigit(horario[4])) {
        mostrarError("Horario debe contener solo dígitos. Formato: HH:MM.");
        return 0;
    }

    int horas = (horario[0] - '0') * 10 + (horario[1] - '0');
    int minutos = (horario[3] - '0') * 10 + (horario[4] - '0');

    if (horas < 0 || horas > 23) {
        mostrarError("Horas deben estar entre 00 y 23.");
        return 0;
    }

    if (minutos < 0 || minutos > 59) {
        mostrarError("Minutos deben estar entre 00 y 59.");
        return 0;
    }

    return 1;
}

int validarEstadoRestaurante(const char estado[]) {
    if (estado == NULL || strlen(estado) == 0) {
        mostrarError("Estado no puede estar vacío.");
        return 0;
    }

    if (strcmp(estado, "activo") != 0 && 
        strcmp(estado, "inactivo") != 0 && 
        strcmp(estado, "mantenimiento") != 0) {
        mostrarError("Estado debe ser: 'activo', 'inactivo' o 'mantenimiento'.");
        return 0;
    }

    return 1;
}


