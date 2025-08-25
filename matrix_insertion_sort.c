#include <stdio.h>
#include <stdlib.h>

/*
 * EJERCICIO:
 * Se quiere definir un programa que, dada una matriz cuadrada con valores enteros,
 * devuelva una permutación de los valores de modo que:
 *
 * 1. Cada renglón esté ordenado de menor a mayor.
 * 2. Todos los elementos del segundo renglón (de arriba hacia abajo)
 *    sean mayores que los del primero, los del tercero mayores que los del segundo, etc.
 *
 * Regla importante:
 * - Cuando se ordenan los elementos de un renglón, por cada elemento de dicho renglón,
 *   se mueven también todos los elementos que se encuentran por debajo en la misma columna.
 *
 * INSTRUCCIONES:
 * - Completa la función sort_matrix() que debe modificar la matriz en su lugar.
 * - Puedes escribir funciones auxiliares si lo deseas.
 * - NO cambies la firma de sort_matrix().
 */

void sort_matrix(int **matriz, int n) {
    for (int filaObjetivo = 0; filaObjetivo < n; filaObjetivo++) {                   // Recorre cada fila donde fijaremos valores de izquierda a derecha
        for (int colObjetivo = 0; colObjetivo < n; colObjetivo++) {                  // Recorre cada columna destino dentro de la fila actual

            int filaMin = filaObjetivo;                                              // Fila del valor minimo encontrado (inicialmente, la celda destino)
            int colMin  = colObjetivo;                                               // Columna del valor minimo hallado
            int valorMin = matriz[filaObjetivo][colObjetivo];                        // Valor minimo actual (inicialmente, el de la celda destino)

            for (int fila = filaObjetivo; fila < n; fila++) {                        // Busca el valor minimo en la submatriz no fijada
                for (int columna = 0; columna < n; columna++) {                      // Recorre todas las columnas
                    if (fila == filaObjetivo && columna < colObjetivo) continue;     // No toca el prefijo ya fijado de la fila actual
                    if (matriz[fila][columna] < valorMin) {                          // Si encontramos un valor más pequeño
                        valorMin = matriz[fila][columna];                            // Actualizamos el valor minimo
                        filaMin  = fila;                                             // Guardamos su fila
                        colMin   = columna;                                          // Guardamos su columna
                    }
                }
            }

            if (filaMin > filaObjetivo) {                                            // El valor minimo esta por debajo de la fila objetivo
                while (colMin < colObjetivo) {                                       // Lo movemos horizontalmente a la derecha
                    for (int f = filaObjetivo + 1; f < n; f++) {                     // Intercambiamos solo la cola
                        int tmp = matriz[f][colMin];                               
                        matriz[f][colMin] = matriz[f][colMin + 1];
                        matriz[f][colMin + 1] = tmp;
                    }
                    colMin++;                                                        // Avanzamos la columna del valor minimo
                }
                while (colMin > colObjetivo) {                                       // Lo movemos horizontalmente a la izquierda
                    for (int f = filaObjetivo + 1; f < n; f++) {                     // De nuevo, solo en la cola (no tocamos las filas superiores)
                        int tmp = matriz[f][colMin];                             
                        matriz[f][colMin] = matriz[f][colMin - 1];
                        matriz[f][colMin - 1] = tmp;
                    }
                    colMin--;                                                        // Retrocedemos la columna del valor minimo
                }
            } else {                                                                  // El valor minimo ya está en la misma fila objetivo
                while (colMin < colObjetivo) {                                       // Si está a la izquierda, lo movemos a la derecha
                    for (int f = filaObjetivo; f < n; f++) {                         // Intercambiamos columnas desde filaObjetivo hacia abajo
                        int tmp = matriz[f][colMin];                                 
                        matriz[f][colMin] = matriz[f][colMin + 1];
                        matriz[f][colMin + 1] = tmp;
                    }
                    colMin++;                                                        // Avanzamos la columna del valor minimo
                }
                while (colMin > colObjetivo) {                                       // Si está a la derecha, lo movemos a la izquierda
                    for (int f = filaObjetivo; f < n; f++) {                         // Intercambiamos las columnas desde filaObjetivo hacia abajo
                        int tmp = matriz[f][colMin];                                 
                        matriz[f][colMin] = matriz[f][colMin - 1];
                        matriz[f][colMin - 1] = tmp;
                    }
                    colMin--;                                                        // Retrocedemos la columna del valor minimo
                }
            }

            while (filaMin > filaObjetivo) {                                         // Una vez alineada la columna, subimos el valor minimo verticalmente
                int tmp = matriz[filaMin][colObjetivo];                              
                matriz[filaMin][colObjetivo] = matriz[filaMin - 1][colObjetivo];
                matriz[filaMin - 1][colObjetivo] = tmp;
                filaMin--;                                                           // Seguimos subiendo hasta la fila objetivo
            }
        }
    }
}

int main() {
    int n = 3;
    // Reserva dinámica de la matriz
    int **matrix = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Ejemplo de entrada
    int ejemplo[3][3] = {
        {4, 7, 2},
        {9, 5, 6},
        {8, 1, 3}
    };

    // Copiar ejemplo a la matriz dinámica
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ejemplo[i][j];
        }
    }

    printf("Matriz original:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Llamada a la función que deben completar
    sort_matrix(matrix, n);

    printf("\nMatriz ordenada:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
