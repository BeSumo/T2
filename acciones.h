#ifndef ACCIONES_H
#define ACCIONES_H


typedef struct {
    char simbolo;      // 'T' (Tabla), 'C' (Cocina), 'A' (Almacen), 'E' (Extintor)
    void (*accion)(void*, int, int); // Puntero a función (ej: cocinar, cortar)
    int en_llamas;     // 1 si hay incendio, 0 si no
    int turnos_inhabilitada; // Para estaciones apagadas con extintor
} Estacion;

typedef struct {
    char nombre_plato[50]; // Ej: McCharly
    Ingrediente** ingredientes_requeridos; // Lista de ingredientes necesarios
    int completado;    // 1 si entregado, 0 si pendiente
} Pedido;

// Funciones clave vinculadas a estaciones
void cortar(void* contexto, int x, int y);       // Tabla de cortar
void cocinar(void* contexto, int x, int y);      // Cocina
void buscar_ingrediente(void* contexto, int x, int y); // Almacen
void apagar_incendio(void* contexto, int x, int y); // Extintor
void entregar_pedido(void* contexto);

#endif