#ifndef CRUD_H_INCLUDED
#define CRUD_H_INCLUDED

#include "BBD.h"
#include "validaciones.h"


/*=========================================
=            BASE DE DATOS                =
=========================================*/
void abrirBDD();

/*=========================================
=              USUARIOS                   =
=========================================*/
void agregarUsuario(Usuario usuario, int opcion_app);
void actualizarUsuarioXid(Usuario usuario);
void eliminarUsuario(Usuario usuario);
void eliminarUsuarioPorId(Usuario usuario_actual);
void listarUsuarios();
void seleccionarCuenta(Usuario usuario);

/*=========================================
=               ROLES                     =
=========================================*/
void agregarCliente(Usuario usuario);
void agregarRepartidor(Usuario usuario);
void agregarEncargado(Usuario usuario);
void agregarAdministrador(Usuario usuario);

void actualizarClienteXid(int id_usuario);
void actualizarRepartidorXid(int id_usuario);
void actualizarEncargadoXid(int id_usuario);
void actualizarAdministradorXid(int id_usuario);

void eliminarCliente(int id_usuario);
void eliminarRepartidor(int id_usuario);
void eliminarEncargado(int id_usuario);
void eliminarAdministrador(int id_usuario);

int esCliente(int id_usuario);
int esEncargado(int id_usuario);
int esRepartidor(int id_usuario);
int esAdministrador(int id_usuario);

int obtenerIdPorEmail(const char email[]);
int contarRolesDelUsuario(int id_usuario);
int tieneRol(int id_usuario, int rol);
void obtenerRolesDelUsuario(int id_usuario, int roles[4]);
void agregarRolExistente(int id_usuario);

/*=========================================
=            RESTAURANTES                 =
=========================================*/
void agregarRestaurante();
void agregarUbicacionRestaurante(Restaurante restaurante);

void eliminarRestaurantePorId();

void listarRestaurantes();
void listarUbicacionesRestaurante(int id_restaurante);

/*=========================================
=              PRODUCTOS                  =
=========================================*/
void agregarProducto(int id_restaurante);
void modificarProducto(int id_restaurante);
void listarProductos();
void listarProductosRestaurante(int id_restaurante);

/*=========================================
=               PEDIDOS                   =
=========================================*/
int obtenerSiguientePedidoId();

void agregarPedido(Usuario usuario);

void listarMisPedidos(Usuario usuario);
void listarPedidoDisponibles(Usuario usuario);
void listarOrdenesRestaurante(int id_restaurante);

void aceptarPedido(Usuario usuario);
void listarPedidosAceptados(int id_usuario);

void actualizarEstadoOrden(int id_restaurante);

void obtenerHistorialEstados(int id_pedido);

/*=========================================
=                PAGOS                    =
=========================================*/
int obtenerSiguientePagoId();
void realizarPago(Usuario usuario, int id_pedido);

#endif // CRUD_H_INCLUDED
