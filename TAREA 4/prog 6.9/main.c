#include <stdio.h>

/* Asigna.
   El programa, al recibir un arreglo bidimensional cuadrado, asigna elementos
   en funcion del modulo (residuo) a un arreglo unidimensional.

   Para cada indice I del arreglo unidimensional B:
   - Si I%3 == 1: B[I] = suma de MAT[J][I], con J de 0 a I.
   - Si I%3 == 2: B[I] = producto de MAT[J][I], con J de I a N-1.
   - En otro caso: B[I] = (producto de MAT[J][I]) / (suma de MAT[J][I]),
     con J de 0 a N-1. */

#define MAX 10

void Lectura(int [][MAX], int);
void Calcula(int [][MAX], float [], int);
float Mod0(int [][MAX], int, int);
float Mod1(int [][MAX], int);   /* Prototipos de funciones. */
float Mod2(int [][MAX], int, int);
void Imprime(float [], int);

int main(void)
{
    int MAT[MAX][MAX], TAM;
    float VEC[MAX];

    do
    {
        printf("Ingrese el tamano de la matriz: ");
        scanf("%d", &TAM);
    }
    while (TAM > MAX || TAM < 1);

    Lectura(MAT, TAM);
    Calcula(MAT, VEC, TAM);
    Imprime(VEC, TAM);
    return 0;
}

void Lectura(int A[][MAX], int N)
/* Lee un arreglo bidimensional cuadrado de tipo entero. */
{
    int I, J;
    for (I = 0; I < N; I++)
        for (J = 0; J < N; J++)
        {
            printf("Ingrese el elemento %d %d: ", I + 1, J + 1);
            scanf("%d", &A[I][J]);
        }
}

void Calcula(int A[][MAX], float B[], int N)
/* Calcula el modulo entre el indice del arreglo unidimensional y 3, y
   llama a la funcion correspondiente para resolver el problema. */
{
    int I;
    for (I = 0; I < N; I++)
        switch (I % 3)
        {
            case 1: B[I] = Mod1(A, I);
                    break;
            case 2: B[I] = Mod2(A, I, N);
                    break;
            default: B[I] = Mod0(A, I, N);
                    break;
        }
}

float Mod0(int A[][MAX], int K, int M)
/* Calcula el cociente entre una productoria y una sumatoria. */
{
    int I;
    float PRO = 1.0, SUM = 0.0;
    for (I = 0; I < M; I++)
    {
        PRO *= A[I][K];
        SUM += A[I][K];
    }
    return (PRO / SUM);
}

float Mod1(int A[][MAX], int N)
/* Obtiene el resultado de una sumatoria (columna N, filas 0 a N). */
{
    int I;
    float SUM = 0.0;
    for (I = 0; I <= N; I++)
        SUM += A[I][N];
    return (SUM);
}

float Mod2(int A[][MAX], int N, int M)
/* Obtiene el resultado de la productoria (columna N, filas N a M-1). */
{
    int I;
    float PRO = 1.0;
    for (I = N; I < M; I++)
        PRO *= A[I][N];
    return (PRO);
}

void Imprime(float B[], int N)
/* Escribe un arreglo unidimensional de tipo real de N elementos. */
{
    int I;
    for (I = 0; I < N; I++)
        printf("\nElemento %d: %.2f ", I, B[I]);
}
