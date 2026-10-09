#include <stdio.h>

/* Busqueda secuencial en arreglos desordenados. */

#define MAX 100

void Lectura(int [], int);   /* Prototipos de funciones. */
int Busca(int *, int, int);

int main(void)
{
    int RES, ELE, TAM, VEC[MAX];

    do
    {
        printf("Ingrese el tamano del arreglo: ");
        scanf("%d", &TAM);
    }
    while (TAM > MAX || TAM < 1);   /* Se verifica que el tamano sea correcto. */

    Lectura(VEC, TAM);
    printf("\nIngrese el elemento a buscar: ");
    scanf("%d", &ELE);
    RES = Busca(VEC, TAM, ELE);     /* Se llama a la funcion que busca. */

    if (RES)
        /* Si RES es verdadero (diferente de 0), se escribe la posicion
           en la que se encontro el elemento. */
        printf("\nEl elemento se encuentra en la posicion %d", RES);
    else
        printf("\nEl elemento no se encuentra en el arreglo");
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

int Busca(int A[], int T, int K)
/* Localiza en el arreglo un elemento determinado. Si lo encuentra, regresa
   la posicion correspondiente. En caso contrario, regresa 0. */
{
    int I = 0, BAN = 0, RES;
    while (I < T && !BAN)
        if (A[I] == K)
            BAN++;
        else
            I++;
    if (BAN)
        RES = I + 1;   /* I+1 porque las posiciones empiezan desde cero. */
    else
        RES = BAN;
    return (RES);
}
