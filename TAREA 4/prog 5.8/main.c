#include <stdio.h>

/* Primos.
   El programa almacena en un arreglo unidimensional los primeros 100 numeros
   primos. */

#define TAM 100

void Imprime(int [], int);   /* Prototipos de funciones. */
void Primo(int, int *);

int main(void)
{
    int P[TAM] = {1, 2};
    int FLA, J = 2, PRI = 3;

    while (J < TAM)
    {
        FLA = 1;
        Primo(PRI, &FLA);    /* Determina si PRI es primo. */
        if (FLA)             /* Si FLA es 1, entonces PRI es primo. */
        {
            P[J] = PRI;
            J++;
        }
        PRI += 2;
    }
    Imprime(P, TAM);
    return 0;
}

void Primo(int A, int *B)
/* Determina si A es primo, en cuyo caso el valor de *B no se altera. */
{
    int DI = 3;
    while (*B && (DI < (A / 2)))
    {
        if ((A % DI) == 0)
            *B = 0;
        DI++;
    }
}

void Imprime(int Primos[], int T)
/* Imprime el arreglo unidimensional de numeros primos. */
{
    int I;
    for (I = 0; I < T; I++)
        printf("\nPrimos[%d]: %d", I, Primos[I]);
}
