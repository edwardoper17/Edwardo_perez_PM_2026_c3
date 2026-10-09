#include <stdio.h>

/* Prueba de parametros por referencia. */

int f1 (int *);
/* Prototipo de funcion. El parametro es de tipo entero y por referencia
observa el uso del operador de indireccion. */

void main(void)
{
    int I, k = 4;
    for (I= 1; I <= 3; I++)
    {
        printf("\n\Valor de k antes de llamar a la funcion: %d", ++k);
        printf("\nValor de k despues de llamar a la funcion: %d", f1(&k));
        /* Llamada  a la funcion f1. se pasa la direccion de la variable k,
       por medio del operador de direccion: &. */
    }
    }
    int f1 (int *R)
    /* La funcion f1 recibe un parametro por referencia. Cada vez que el
    parametro se utiliza en la funcion debe ir procedio  por el operador de
    indireccion. */
    {
        *R += *R;
        return *R;
    }


