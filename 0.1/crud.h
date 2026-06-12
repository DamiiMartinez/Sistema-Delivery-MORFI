#ifndef CRUD_H_INCLUDED
#define CRUD_H_INCLUDED

/** funciones de alta, baja, modificación, */
/** listado para cada tabla. */

void agregarUsuario();
void agregarRestaurante();
void agregarPlato();
void agregarPedido();

void eliminarUsuario();
void eliminarRestaurante();
void eliminarPlato();
void eliminarPedido();

void actualizarUsuarioXid();
void actualizarRestauranteXid();
void actualizarPlatoXid();
void actualizarPedidoXid();

void listarUsuarios();
void listarRestaurantes();
void listarPlatos();
void listarPedidos();

#endif // CRUD_H_INCLUDED
