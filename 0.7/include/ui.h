#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"

// Colores de Texto
#define BLACK       "\033[30m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define GRAY        "\033[90m"
#define LIGHT_GRAY  "\033[37m"

#define BG_BLACK    "\033[40m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_YELLOW   "\033[43m"
#define BG_BLUE     "\033[44m"
#define BG_MAGENTA  "\033[45m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"
#define BG_DARK_BLUE "\033[44m"

#define BOX_TL      "╔"
#define BOX_TR      "╗"
#define BOX_BL      "╚"
#define BOX_BR      "╝"
#define BOX_H       "═"
#define BOX_V       "║"
#define BOX_MID_L   "╠"
#define BOX_MID_R   "╣"
#define BOX_MID_H   "═"
#define BULLET      "●"
#define ARROW       "→"
#define CHECKMARK   "✓"
#define ERROR_MARK  "✗"

void inicializarUI();
void limpiarPantalla();
void mostrarTitulo(const char *titulo);
void mostrarSubtitulo(const char *subtitulo);
void mostrarOpcion(int numero, const char *texto);
void mostrarError(const char *mensaje);
void mostrarExito(const char *mensaje);
void mostrarInfo(const char *mensaje);
void mostrarLinea();
void mostrarCaja(const char *titulo);
void mostrarCajaFin();
void mostrarInput(const char *prompt);
void pausar();

#endif
