#ifndef CRUD_H_INCLUDED
#define CRUD_H_INCLUDED

#include "BBD.h"
#include "validaciones.h"

/** funciones de alta, baja, modificaci�n, */
/** listado para cada tabla. */

void abrirBDD();

// =========================
// USUARIOS Y PERFILES
// =========================

void agregarUsuario();
void agregarCliente(Usuario usuario);
void agregarRepartidor(Usuario usuario);
void agregarEncargado(Usuario usuario);
void agregarAdministrador(Usuario usuario);

void eliminarUsuario(Usuario usuario);
void eliminarCliente(int id_usuario);
void eliminarRepartidor(int id_usuario);
void eliminarEncargado(int id_usuario);
void eliminarAdministrador(int id_usuario);

// Funciones de eliminación con confirmación (para administrador)
void eliminarUsuarioPorId(Usuario usuario_actual);
void eliminarRestaurantePorId();

void actualizarUsuarioXid(Usuario usuario);
void actualizarClienteXid(int id_usuario);
void actualizarRepartidorXid(int id_usuario);
void actualizarEncargadoXid(int id_usuario);
void actualizarAdministradorXid(int id_usuario);

void listarUsuarios();
void listarClientes();
void listarRepartidores();
void listarEncargados();
void listarAdministradores();

void seleccionarCuenta(Usuario usuario);
int esCliente(int id_usuario);
int esEncargado(int id_usuario);
int esRepartidor(int id_usuario);
int esAdministrador(int id_usuario);

// Funciones auxiliares para gestión de roles
int obtenerIdPorEmail(const char email[]);
int contarRolesDelUsuario(int id_usuario);
int tieneRol(int id_usuario, int rol);
void obtenerRolesDelUsuario(int id_usuario, int roles[4]);
void agregarRolExistente(int id_usuario);

// =========================
// RESTAURANTES Y PRODUCTOS
// =========================

void agregarRestaurante();
void agregarUbicacionRestaurante(Restaurante restaurante);
//Eliminar
void eliminarRestaurante(Restaurante restaurante);
void eliminarUbicacionRestaurante(int id_ubicacion);
//Actualizar
void actualizarRestauranteXid(Restaurante restaurante);
void actualizarUbicacionRestauranteXid(int id_ubicacion);
//Mostrar - Listar
void listarRestaurantes();
void listarUbicacionesRestaurante(int id_restaurante);

// =========================
// MENÚ Y PRODUCTOS (ENCARGADO)
// =========================

void agregarProducto(int id_restaurante);
void modificarProducto(int id_restaurante);
void listarProductosRestaurante(int id_restaurante);
void listarProductos();
void listarProductoPorId(int id_producto);

// =========================
// PEDIDOS Y ENTREGAS - SON TABLAS HISTORICAS: NO SE ELIMINAN, SE CAMBIAN A CANCELADA
// =========================

// CLIENTE
void agregarPedido(Usuario usuario);
void listarMisPedidos(Usuario usuario);
void obtenerHistorialEstados(int id_pedido);

// Sistema
void agregarOrdenPreparacion(Pedido pedido);
void agregarDetalleOrden(Pedido pedido, int id_producto, int cantidad);
void agregarHistorialEstado(Pedido pedido);

void actualizarPedido(Usuario usuario);
void actualizarPedidoXid(int id_pedido, char nuevoEstado[]);

void listarPedidos();
void listarOrdenesPreparacion();

void listarPedidoDisponibles();
void aceptarPedido(Usuario usuario);

void listarDetallesOrden();
void listarHistorialEstados();

// =========================
// PAGOS Y FACTURACIÓN
// =========================

void realizarPago(Usuario usuario, int id_pedido);
void listarHistorialEstados();

// =========================
// ATENCION AL CLIENTE
// =========================

void agregarCalificacion(Usuario usuario);
void agregarReclamo(Usuario usuario);
void agregarConsulta(Usuario usuario);

void eliminarCalificacion(int id_calificacion);
void eliminarReclamo(int id_reclamo);
void eliminarConsulta(int id_consulta);

void actualizarCalificacionXid(int id_calificacion);
void actualizarReclamoXid(int id_reclamo);
void actualizarConsultaXid(int id_consulta);

void listarCalificaciones();
void listarReclamos();
void listarConsultas();

// =========================
// PAGOS Y FACTURACION
// =========================

void agregarPago(Pedido pedido);
void agregarTransaccion(Pago pago);
void agregarComision(Pago pago);
void agregarRecibo(Pago pago);

void eliminarPago(int id_pago);
void eliminarTransaccion(int id_transaccion);
void eliminarComision(int id_comision);
void eliminarRecibo(int id_recibo);

void actualizarPagoXid(int id_pago);
void actualizarTransaccionXid(int id_transaccion);
void actualizarComisionXid(int id_comision);
void actualizarReciboXid(int id_recibo);

void listarPagos();
void listarTransacciones();
void listarComisiones();
void listarRecibos();

// =========================
// ADMINISTRACION
// =========================

void agregarSolicitudInforme(Usuario usuario);
void eliminarSolicitudInforme(int id_solicitud);
void actualizarSolicitudInformeXid(int id_solicitud);
void listarSolicitudesInforme();

#endif // CRUD_H_INCLUDED
