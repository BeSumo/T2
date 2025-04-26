#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "main.h"


// Función para buscar al jugador en el tablero
// Recibe el tablero
// No retorna nada
Jugador* buscarJugador(Tablero* tablero){
    
    int filas = tablero->filas;
    int columnas = tablero->columnas;

    for(int i = 0; i<filas ; i++){
        for(int j = 0; j<columnas ; j++){
            void* elemento = tablero->celdas[i][j];
            if (tablero->celdas[i][j]!=NULL){ // aqui veo si es que es un posible jugador
                
                Jugador* posiblejugador = ( Jugador*)elemento;
                if (posiblejugador->x == i && posiblejugador->y == j ){
                    return posiblejugador;
                

            }
        }
    }  
  }
  return NULL;
}
// funcion para verificar si una celda es una estacion
// Recibe el tablero y las coordenadas x, y
// Retorna el simbolo de la estacion si es una estacion, 0 si no lo es // no alcance a implementar
char esEstacion(Tablero* tablero, int x, int y) {
   
    if (tablero->celdas[x][y] == NULL) {
        return 0;
    }
    
    // Verificar si es una estación por su símbolo
    Estacion* estacion = (Estacion*)tablero->celdas[x][y];
    char simbolo = estacion->simbolo;
    free(estacion); // Liberar memoria de la estación (si es necesario)    
    return (simbolo == 'T' || simbolo == 'C' || simbolo == 'A' || simbolo == 'E') ? simbolo : 0;
}

// Funcion para mover al jugador en el tablero
// actualiza la posicion del jugador en el tablero y limpia la celda anterior
// Recibe el tablero, el jugador y las nuevas coordenadas
// no retorna nada

void moverJugador(Tablero* tablero, Jugador* jugador, int nueva_x, int nueva_y) {
    if (tablero == NULL || jugador == NULL) return;

    // Verificar límites del tablero
    if (nueva_x < 0 || nueva_y < 0 || 
        nueva_x >= tablero->filas || nueva_y >= tablero->columnas) {
        printf("Movimiento fuera de los límites del tablero\n");
        return;
    }

    // Guardar posición actual
    int x_actual = jugador->x;
    int y_actual = jugador->y;

    // Verificar si la nueva posición es una estación
    char tipo_estacion = esEstacion(tablero, nueva_x, nueva_y);
    
    tablero->celdas[x_actual][y_actual] = NULL;  // Limpiar posición anterior
    
    if (tipo_estacion != 0) {
        // Mostrar mensaje según tipo de estación
        switch(tipo_estacion) {
            case 'T': printf("Has llegado a la Tabla de cortar\n"); break;
            case 'C': printf("Has llegado a la Cocina\n"); break;
            case 'A': printf("Has llegado al Almacén\n"); break;
            case 'E': printf("Has llegado al Extintor\n"); break;
        }
    }
    tablero->celdas[nueva_x][nueva_y] = NULL; // Limpiar celda de la estación
    // Actualizar posición del jugador
    jugador->x = nueva_x;
    jugador->y = nueva_y;
    tablero->celdas[nueva_x][nueva_y] = jugador;
}

int main() {
    srand(time(NULL)); // Inicializar aleatoriedad
    int dificultad;
    // 1. Crear juego (como puntero)
    Juego* juego = malloc(sizeof(Juego));
    juego->tablero = malloc(sizeof(Tablero));

    printf("Seleccione dificultad: \n");
    printf("1.Facil\n");
    printf("2.Medio\n");
    printf("3.Dificil\n");

    scanf("%d", &dificultad);

    if ( dificultad == 1){
        juego->dificultad = 1;
        juego->tablero->filas = 5;
        juego->tablero->columnas = 5;
        juego->turnos_restantes = 60;
        inicializarTablero(juego->tablero, 5, 5); // Inicializar el tablero
    }
    
    else if ( dificultad == 2){
        juego->dificultad = 2;
        juego->tablero->filas = 8;
        juego->tablero->columnas = 8;
        juego->turnos_restantes = 50;
        inicializarTablero(juego->tablero, 8, 8); // Inicializar el tablero
    }
    
    else if ( dificultad == 3){
        juego->dificultad = 3;
        juego->tablero->filas = 10;
        juego->tablero->columnas = 10;
        juego->turnos_restantes = 45;
        inicializarTablero(juego->tablero, 10, 10); // Inicializar el tablero
    }
    else{
        printf("Dificultad no valida\n");
        free(juego->tablero);
        free(juego);
        return 1;
    }
    int turnos = juego->turnos_restantes;
    bool jugar = true;
    char input;
    
    while(jugar && (turnos > 0)){
        int espacios;
        mostrarTablero(juego->tablero);
        
        printf("Turnos restantes: %d\n", turnos);
        
        printf("1. Moverse (W, A, S, D)\n");
        printf("2. Accion \n");
        printf("3. Ver inventario\n");
        printf("4. Entregar plato\n");
        printf("5. Salir\n");
        
        
        scanf(" %c", &input);
        --turnos; // Disminuir turnos restantes al final de cada eleccion
        switch (input)
        {
        case 'W': // Arriba
            printf("Cuantos espacios quiere moverse?\n");
            scanf("%d", &espacios);
            // Moverse hacia arriba
            
            if (espacios > 0){
                Jugador* jugador = buscarJugador(juego->tablero);
                if (jugador != NULL) {
                    
                    int nueva_x = jugador->x - espacios; // Mover hacia arriba
                    
                    if (nueva_x >= 0) {
                        // Actualizar la posición del jugador en el tablero
                        moverJugador(juego->tablero, jugador, nueva_x, jugador->y);


                    } else {
                        printf("Movimiento no valido\n");
                    }
                } else {
                    printf("Jugador no encontrado\n");
                }
            break;
        case 'A':  
            printf("Cuantos espacios quiere moverse?\n");
            scanf("%d", &espacios);
            
            
            if (espacios > 0){
                Jugador* jugador = buscarJugador(juego->tablero);
                if (jugador != NULL) {
                    int nueva_y = jugador->y - espacios; // Mover hacia la izquierda
                    if (nueva_y >= 0) {

                        moverJugador(juego->tablero, jugador, jugador->x, nueva_y);
                        
                    } else {
                        printf("Movimiento no valido\n");
                    }
                } else {
                    printf("Jugador no encontrado\n");
                }
            }
            break;
        case 'S':
            printf("Cuantos espacios quiere moverse?\n");
            scanf("%d", &espacios);
            if (espacios > 0){
                Jugador* jugador = buscarJugador(juego->tablero);
                if (jugador != NULL) {
                    int nueva_x = jugador->x + espacios; // Mover hacia abajo
                    if (nueva_x < juego->tablero->filas) {
                        // Actualizar la posición del jugador en el tablero
                        moverJugador(juego->tablero, jugador, nueva_x, jugador->y);
                    } else {
                        printf("Movimiento no valido\n");
                    }
                } else {
                    printf("Jugador no encontrado\n");
                }
            }
            break;
        case 'D':
            printf("Cuantos espacios quiere moverse?\n");
            scanf("%d", &espacios);
            if (espacios > 0){
                Jugador* jugador = buscarJugador(juego->tablero);
                if (jugador != NULL) {
                    int nueva_y = jugador->y + espacios; // Mover hacia la derecha
                    if (nueva_y < juego->tablero->columnas) {
                        // Actualizar la posición del jugador en el tablero
                        moverJugador(juego->tablero, jugador, jugador->x, nueva_y);
                    } else {
                        printf("Movimiento no valido\n");
                    }
                } else {
                    printf("Jugador no encontrado\n");
                }
            }
            break;
        case '2':
            jugar = false;
            break;
        case '3':
            jugar = false;
            break;
        case '4':
            jugar = false;
            break;
        case '5':
            jugar = false;
            break;
        default:
            printf("Opcion no valida\n");
            break;
    
        }
    }
 }
    if (turnos == 0){
        printf("Se acabaron los turnos\n");
    }
    else if (jugar == false){
        printf("Juego terminado\n");
    }
    //Liberar memoria 
    liberarTablero(juego->tablero);
    free(juego->tablero);
    free(juego);
    
    return 0;

}