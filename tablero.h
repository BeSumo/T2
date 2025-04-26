#ifndef TABLERO_H
#define TABLERO_H

typedef struct {
    void*** celdas;    // Matriz 2D de elementos (puntero triple)
    int filas;
    int columnas;
} Tablero;

typedef struct {
    int x;             // Posicion X en el tablero
    int y;             // Posicion Y en el tablero
    int en_llamas;     // 1 si el jugador esta en llamas (por atravesar estacion incendiada)
} Jugador;

// Funciones obligatorias
void inicializarTablero(Tablero* tablero, int filas, int columnas);
void mostrarTablero(Tablero* tablero);
void actualizarCelda(Tablero* tablero, int x, int y, void* elemento);
void liberarTablero(Tablero* tablero);

#endif