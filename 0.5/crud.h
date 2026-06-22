#ifndef CRUD_H_INCLUDED
#define CRUD_H_INCLUDED

#include "BBD.h"
#include "validaciones.h"


void abrirBDD();

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
void seleccionarCuentaConRol(Usuario usuario, int opcion_app);
void registrarUsuarioConRol(int opcion_app);
void agregarRolEspecifico(int id_usuario, int opcion_app);
int esCliente(int id_usuario);
int esEncargado(int id_usuario);
int esRepartidor(int id_usuario);
int esAdministrador(int id_usuario);

int obtenerIdPorEmail(const char email[]);
int contarRolesDelUsuario(int id_usuario);
int tieneRol(int id_usuario, int rol);
void obtenerRolesDelUsuario(int id_usuario, int roles[4]);
void agregarRolExistente(int id_usuario);

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

void agregarProducto(int id_restaurante);
void modificarProducto(int id_restaurante);
void listarProductosRestaurante(int id_restaurante);
void listarProductos();

void agregarPedido(Usuario usuario);
void listarMisPedidos(Usuario usuario);
void obtenerHistorialEstados(int id_pedido);

void listarOrdenesRestaurante(int id_restaurante);
void actualizarEstadoOrden(int id_restaurante);

void agregarOrdenPreparacion(Pedido pedido);
void agregarDetalleOrden(OrdenPreparacion orden);
void agregarHistorialEstado(Pedido pedido);

void actualizarHistorialEstadoXid(int id_historial);

void listarPedidos();
void listarOrdenesPreparacion();
void listarDetallesOrden();
void listarHistorialEstados();

void realizarPago(Usuario usuario, int id_pedido);
void listarHistorialEstados();

void agregarCalificacion(Usuario usuario);
void agregarReclamo(Usuario usuario);
void agregarConsulta(Usuario usuario);

void calcularComisionPedido(int id_pedido, int id_pago, int id_restaurante, double monto_total);
void verIngresosRestaurante(int id_restaurante);
void realizarPagoRestaurante();
void verIngresoRepartidor(int id_repartidor);
void verFinanzasTotales();
void marcarComisionsComoPagadas(int id_restaurante);

void calificarPedido(Usuario usuario);
void verCalificacionesRestaurante(int id_restaurante);
void verMisCalificaciones(Usuario usuario);
void reportarResenia(int id_calificacion);
void actualizarPromedioRestaurante(int id_restaurante);

void mostrarInfoRestaurante(int id_restaurante);

void eliminarCalificacion(int id_calificacion);
void eliminarReclamo(int id_reclamo);
void eliminarConsulta(int id_consulta);

void actualizarCalificacionXid(int id_calificacion);
void actualizarReclamoXid(int id_reclamo);
void actualizarConsultaXid(int id_consulta);

void listarCalificaciones();
void listarReclamos();
void listarConsultas();

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

void agregarSolicitudInforme(Usuario usuario);
void eliminarSolicitudInforme(int id_solicitud);
void actualizarSolicitudInformeXid(int id_solicitud);
void listarSolicitudesInforme();

#endif // CRUD_H_INCLUDED
