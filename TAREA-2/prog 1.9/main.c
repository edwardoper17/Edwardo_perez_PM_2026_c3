#include <stdio.h>

/* Estancia
El programa, al recibircomo dato la superficie de una estancia expresada
en acres, la convierte a hactareas.

ECA: variable dd tipo real. */

int main(void)
{
    float ECA;
    printf("Ingrese la extension de la estancia ");
    scanf ("%f" , &ECA);
    ECA = ECA * 4047 / 10000;
    printf("\nExtension dc la estancia en hectareas: %5.2f",ECA);
    return 0;
}
