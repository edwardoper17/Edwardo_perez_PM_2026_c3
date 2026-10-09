#include <stdio.h>

/* Cuadrado magico.
   El programa genera un cuadrado magico siguiendo los criterios enunciados
   anteriormente. */

#define MAX 50

void Cuadrado(int [][MAX], int);
void Imprime(int [][MAX], int);   /* Prototipos de funciones. */

int main(void)
{
    int CMA[MAX][MAX], TAM;

    do
    {
        printf("Ingrese el tamano impar de la matriz: ");
        scanf("%d", &TAM);
    }
    while (TAM > MAX || TAM < 1 || TAM % 2 == 0);
    /* Se verifica el tamano del arreglo y el orden (impar) del mismo. */

    Cuadrado(CMA, TAM);
    Imprime(CMA, TAM);
    return 0;
}

void Cuadrado(int A[][MAX], int N)
/* Forma el cuadrado magico. */
{
    int I = 1, FIL = 0, COL = N / 2, NUM = N * N;
    while (I <= NUM)
    {
        A[FIL][COL] = I;
        if (I % N != 0)
        {
            FIL = (FIL - 1 + N) % N;   /* Fila anterior (circular). */
            COL = (COL + 1) % N;       /* Columna posterior (circular). */
        }
        else
            FIL++;                     /* Misma columna, fila posterior. */
        I++;
    }
}

void Imprime(int A[][MAX], int N)
/* Escribe el cuadrado magico. */
{
    int I, J;
    for (I = 0; I < N; I++)
        for (J = 0; J < N; J++)
            printf("\nElemento %d %d: %d", I + 1, J + 1, A[I][J]);
}
