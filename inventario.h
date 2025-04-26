#ifndef INVENTARIO_H
#define INVENTARIO_H

#define MAX_INVENTARIO 5 // Capacidad máxima del inventario

#include"main.h"
#include "tablero.h"

typedef struct {
    char nombre[30];      // Ej: "pan", "pollo"
    int estado;           // Ej: 0 = crudo, 1 = cortado, etc.
    int es_extintor;      // 1 si es extintor, 0 si es ingrediente
    int turnos_elaboracion; // Turnos que tarda en prepararse
    int prob_incendio;    // Probabilidad de causar incendio (%)
} Ingrediente;

// Funciones obligatorias del inventario
void crearInventario(Ingrediente** inventario);
void agregarIngrediente(Ingrediente** inventario, Ingrediente* ingrediente);
void eliminarIngrediente(Ingrediente** inventario, int posicion);
void verInventario(Ingrediente** inventario);

// Funciones auxiliares recomendadas
int inventarioLleno(Ingrediente** inventario);
int inventarioVacio(Ingrediente** inventario);
int tieneExtintor(Ingrediente** inventario);

#endif