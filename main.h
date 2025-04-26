#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include "inventario.h"
#include "acciones.h"


typedef struct {
    Tablero * tablero ; // Puntero al struct Tablero
    Ingrediente ** inventario ;
    Pedido * pedidos ;
    int turnos_restantes ;
    int dificultad ;
    } Juego ; 



void moverJugador(Tablero* tablero, Jugador* jugador, int nueva_x, int nueva_y);
Jugador* buscarJugador(Tablero* tablero);


#endif