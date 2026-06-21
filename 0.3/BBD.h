#ifndef BBD_H_INCLUDED
#define BBD_H_INCLUDED

typedef struct {
    int id_usuario;
    char nombre[50];
    char apellido[50];
    char email[100];
    char contrasena[100];
    char telefono[20];
    char fecha_registro[20];
    char estado_cuenta[20];
} Usuario;

typedef struct {
    int id_usuario;
    char direccion[100];
} Cliente;

typedef struct {
    int id_usuario;
    char vehiculo[50];
    char estado_disponibilidad[20];
} Repartidor;

typedef struct {
    int id_usuario;
    int id_restaurante;
    char turno[20];
} Encargado;

typedef struct {
    int id_usuario;
    char nivel_acceso[20];
} Administrador;

//   RESTAURANTES Y PRODUCTOS

typedef struct {
    int id_restaurante;
    char nombre[100];
    char telefono[20];
    char horario_apertura[10];
    char horario_cierre[10];
    char estado[20];
} Restaurante;

typedef struct {
    int id_ubicacion;
    int id_restaurante;
    char direccion[100];
    int numero;
    char ciudad[50];
    char provincia[50];
    char codigo_postal[10];
} UbicacionRestaurante;

typedef struct {
    int id_menu;
    int id_restaurante;
} Menu;

typedef struct {
    int id_producto;
    int id_menu;
    char nombre_producto[100];
    char descripcion[500];
    double precio;
    char categoria[50];
    char disponibilidad[20];
} Producto;

//   PEDIDOS Y ENTREGAS

typedef struct {
    int id_pedido;
    int id_cliente;
    int id_repartidor;
    char fecha_pedido[20];
    char estado[20];
    char direccion_entrega[100];
    double total;
    char observaciones[100];
} Pedido;

typedef struct {
    int id_orden;
    int id_pedido;
    char fecha_creacion[10];
    char hora_inicio[9];
    char hora_fin[9];
    char estado_preparacion[20];
    char observaciones[100];
} OrdenPreparacion;

typedef struct {
    int id_orden;
    int id_producto;
    int cantidad;
    char estado_item[20];
    char observaciones[100];
} DetalleOrden;

typedef struct {
    int id_historial;
    int id_pedido;
    char estado[20];
    char fecha_actualizacion[10];
    char hora_actualizacion[10];
} HistorialEstado;

//   ATENCION AL CLIENTE


typedef struct {
    int id_calificacion;
    int id_pedido;
    int puntaje;
    char comentario[100];
    char fecha_calificacion[10];
} Calificacion;

typedef struct {
    int id_reclamo;
    int id_cliente;
    int id_pedido;
    char fecha_reclamo[20];
    char descripcion[100];
    char estado[20];
    char respuesta[100];
} Reclamo;

typedef struct {
    int id_consulta;
    int id_cliente;
    char fecha_consulta[20];
    char mensaje[500];
    char estado[20];
    char respuesta[500];
} Consulta;

//   PAGOS Y FACTURACION

typedef struct {
    int id_pago;
    int id_pedido;
    char fecha_pago[20];
    double monto_total;
    char metodo_pago[30];
    char estado_pago[20];
} Pago;

typedef struct {
    int id_transaccion;
    int id_pago;
    char codigo_autorizacion[50];
    char entidad_bancaria[100];
    char fecha_transaccion[20];
    char estado_transaccion[20];
} Transaccion;

typedef struct {
    int id_comision;
    int id_pago;
    double porcentaje;
    double monto_comision;
    double monto_neto;
} Comision;

typedef struct {
    int id_recibo;
    int id_pago;
    char fecha_emision[10];
    char numero_comprobante[30];
    char tipo_comprobante[20];
} Recibo;

//   ADMINISTRACION


typedef struct {
    int id_solicitud;
    int id_usuario;
    char fecha_solicitud[20];
    char tipo_informe[51];
    char estado_solicitud[21];
    char respuesta[500];
} SolicitudInforme;

void generarMenu(char menu[][50], int opciones);

//  INTERFAZ DE CADA USUARIO
void panelCliente(Usuario usuario);
void panelRepartidor(Usuario usuario);
void panelEncargador(Usuario usuario);
void panelAdministrador(Usuario usuario);

#endif // BBD_H_INCLUDED
