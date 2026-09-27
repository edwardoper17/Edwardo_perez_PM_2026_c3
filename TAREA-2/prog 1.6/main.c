#include <stdio.h>

/* Aplicacion de opradores. */

int main(void)
{
    int i = 15, j, k, l;

    j= (15 > i--) > (14< ++i);
    printf("\nEL valor de j es: %d" , j);

    k = ! ('b' != 'd') > (!i - 1);
    printf("\nEl valor dd k es: %d",k);

    l= (!(34 > (70 % 2)) || 0);
    printf("\nEl valor de l es: %d", l);
    return 0;
}
