#ifndef BBD_H_INCLUDED
#define BBD_H_INCLUDED

typedef struct{
    int ID_usuario;
    char nombre[50];
    char email[50];
    char direccion[50];
    int telefono;
} Usuarios;

typedef struct{
    int ID_restaurante;
    char nombre[50];
    char direccion[50];
    char rubro[10];
    float calificacion;
} Restaurantes;

typedef struct{
    int ID_plato;
    int ID_restaurante;
    char nombre[50];
    float precio;
    char disponible[10];
} Platos;

typedef struct{
    int ID_pedido;
    int ID_usuario;
    int ID_restaurante;
    char fecha[10];
    float total;
    char estado[10];
} Pedidos;

typedef struct{
    int ID_detalle;
    int ID_pedido;
    int ID_plato;
    int cantidad;
    float subtotal;
} DetallesPedidos;


void generarMenu(char menu[][50], int opciones);

#endif // BBD_H_INCLUDED
