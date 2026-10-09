
#include <stdio.h>

/* Ordenacion por insercion directa. */

#define MAX 100

void Lectura(int *, int);
void Ordena(int *, int);     /* Prototipos de funciones. */
void Imprime(int *, int);

int main(void)
{
    int TAM, VEC[MAX];

    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM > MAX || TAM < 1);   /* Se verifica que el tamano sea correcto. */

    Lectura(VEC, TAM);
    Ordena(VEC, TAM);
    Imprime(VEC, TAM);
    return 0;
}

void Lectura(int A[], int T)
/* Lee un arreglo unidimensional de T elementos de tipo entero. */
{
    int I;
    for (I = 0; I < T; I++)
    {
        printf("Ingrese el elemento %d: ", I + 1);
        scanf("%d", &A[I]);
    }
}

void Imprime(int A[], int T)
/* Escribe un arreglo unidimensional ordenado de T elementos de tipo entero. */
{
    int I;
    for (I = 0; I < T; I++)
        printf("\nA[%d]: %d", I, A[I]);
}

void Ordena(int A[], int T)
/* Utiliza el metodo de insercion directa para ordenar los elementos
   del arreglo unidimensional A. */
{
    int AUX, L, I;
    for (I = 1; I < T; I++)
    {
        AUX = A[I];
        L = I - 1;
        while ((L >= 0) && (AUX < A[L]))
        {
            A[L + 1] = A[L];
            L--;
        }
        A[L + 1] = AUX;
    }
}
