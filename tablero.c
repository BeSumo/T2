#include "tablero.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include"main.h"
#include "acciones.h"
#include "inventario.h"

// inicalizamos el tablero con una matriz de celdas vacias, luego lo llenamos con estaciones y un jugador en posiciones aleatorias
// Recibe el tablero, filas y columnas
// No retorna nada
void inicializarTablero ( Tablero * tablero , int filas , int columnas ) {
    
    // por buena practica , en teoria nunca deberia pasar esto
    if ( tablero == NULL || filas <= 0 || columnas <= 0) {
        return; // Manejo de errores
    }

    tablero->filas = filas; // Asignar el numero de filas 
    
    tablero->columnas = columnas; // lo mismo para columnas
    
    tablero->celdas = (void***)malloc(filas *sizeof(void**));
    
    for (int i = 0; i < filas; i++){
        tablero->celdas[i] = (void**)malloc(columnas * sizeof(void*));
        for (int j = 0; j < columnas; j++){
            tablero->celdas[i][j]=NULL; // inicialmente todas las celdas no tienen nada
        }
    }

    Jugador *jugador =(Jugador*)malloc(sizeof(Jugador)); // Jugador
    
    jugador->x = rand()% filas; 
    
    jugador->y = rand()%columnas;
    
    jugador->en_llamas = 0;
    
    // Insercion de jugador en el tablero
    
    tablero->celdas[jugador->x][jugador->y] = jugador;
    
    // Insertamos las Estaciones en el tablero
    
    char Simbolo[4] = {'T','C','A','E'};
    for (int i = 0; i < 4; i++){
        Estacion *estacion = (Estacion*)malloc(sizeof(Estacion)); //casting a Estacion
        estacion->simbolo = Simbolo[i];
        estacion->accion = NULL; // Asignar la función correspondiente según el tipo de estación
        estacion->turnos_inhabilitada = 0;
        
        bool flag = true;
        int x, y;
        while (flag){
            x = rand() % (filas-1); // Generar coordenadas aleatorias
            y = rand() % (columnas-1);
            
            if (tablero->celdas[x][y] == NULL) { // Verificar si la celda está vacía
                tablero->celdas[x][y] = estacion; // Asignar la estación a la celda
                flag = false; // Salir del bucle si se asignó correctamente
            }
        }

    }
}


// Muestra el tablero en la consola
// Recibe el tablero, y recorre el tablero mostrando cada celda, si se encuentra una celda ocupada,asume que es una estacion y la imprime, si detecta que no es una estacion, asume que es el jugador y lo imprime
// No retorna nada
void mostrarTablero(Tablero *tablero) {
    if (tablero == NULL) {
        return; // Manejo de errores
    }
    
    for (int i = 0; i < tablero->filas; i++) {
        for (int j = 0; j < tablero->columnas; j++) {
            if (tablero->celdas[i][j] != NULL) {
                Estacion *estacion = (Estacion *)tablero->celdas[i][j]; // Cast a Estacion
                if (estacion->simbolo == 'T') {
                    printf("[T] "); // imprime la tabla de cortar
                } else if (estacion->simbolo == 'C') {
                    printf("[C] "); // imprime la cocina
                } else if (estacion->simbolo == 'A') {
                    printf("[A] "); // imprime el almacen
                } else if (estacion->simbolo == 'E') {
                    printf("[E] "); // imprime el extintor
                }else{
                    printf("[O] "); // imprime el jugador
                } 
            } else {
                printf("[ ] "); // imprime un punto si la celda es NULL
            }
        }
        printf("\n"); // Nueva línea al final de cada fila
    }
}

// Actualiza la celda en el tablero con un nuevo elemento
// Recibe el tablero, coordenadas x, y y el nuevo elemento
// No retorna nada
// Si la celda ya tiene un elemento, libera la memoria de ese elemento antes de asignar el nuevo
void actualizarCelda(Tablero *tablero, int x, int y, void *elemento) {
    if (tablero == NULL || x < 0 || y < 0 || x >= tablero->filas || y >= tablero->columnas) {
        return; // Manejo de errores
    }
    
    if (tablero->celdas[x][y] != NULL) {
        free(tablero->celdas[x][y]); // Liberar la memoria de la celda anterior
    }
    
    tablero->celdas[x][y] = elemento; // Asignar el nuevo elemento a la celda
}


// libera la memoria del tablero y sus celdas
// Recibe el tablero
// No retorna nada
// Si el tablero es NULL, no hace nada
void liberarTablero(Tablero *tablero) {
    if (tablero == NULL) {
        return; // Manejo de errores
    }
    
    for (int i = 0; i < tablero->filas; i++) {
        for (int j = 0; j < tablero->columnas; j++) {
            if (tablero->celdas[i][j] != NULL) {
                free(tablero->celdas[i][j]); // Liberar la memoria de cada celda
            }
        }
        free(tablero->celdas[i]); // Liberar la memoria de cada fila
    }
    free(tablero->celdas); // Liberar la memoria del puntero a filas
    tablero->celdas = NULL; // Evitar puntero colgante
    tablero->filas = 0; // Reiniciar filas
    tablero->columnas = 0; // Reiniciar columnas
}