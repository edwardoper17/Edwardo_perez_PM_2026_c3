#include <stdio.h>

/* Prueba de variables globales, locales y estaticas.
EL programa utiliza funciones en las que se usan diferentes tipos de
variables. */

int f1(void);
int f2(void);
int f3(void);        /* Prototipos de funciones. */
int f4(void);

int k = 3;

void main(void)
{
    int I;
    for (I = 1; I <= 3; I++)

    printf("\nEl resultado de la funcion f1 es: %d");
    printf("\nEl resultado de la funcion f2 es: %d");
    printf("\nEl resultado de la funcion f3 es: %d");
    printf("\nEl resultado de la funcion f4 es: %d");

}

int f1(void)
/* La funcion f1 utiliza la variable local. */
{
k += k;
return (k);
}
int f2(void)
/* La funcion f2 utiliza la variable local. */
{
int K = 1;
K++;
return (K);
}
int  f3(void)
/* La funcion f3 utiliza la variable local. */
{
static int K = 8;
K += 2;
return (K);
}
int f4 (void)
/* La funcion f4 utiliza dos variables con el mismo nombre: local
y global. */
{
int K = 5;
K = K + k;     /* uso de la variable local (k) y global (k) */
return (k);
}
