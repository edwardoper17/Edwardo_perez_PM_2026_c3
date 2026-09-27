#include <stdio.h>
#include <math.h>

/* Funcion.
El programa, al recibir como dato un valor entero, calcula el resultado de
una funcion

Y: variable  de tipo entero.
x: variable  de tipo real. */

int main(void)
{
    float x;
    int Y;
    printf("Ingrese el valor de Y: ");
    scanf("%d", &Y);
    if (Y < 0 || Y > 50)
        x = 0;
    else
          if (Y <= 10)
              x = 4 / Y - Y;
          else
                if (Y <= 25)
                    x = pow(Y, 3) - 12;
          else
            x = pow(Y, 2) + pow(Y, 3) - 18;

    printf("\n\nY = %d\tX = %8.2f", Y, x);
    return 0;
}
