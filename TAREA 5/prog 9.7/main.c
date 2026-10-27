#include <stdio.h>

/* Archivos con variables enteras y reales.
   El programa lee información de los alumnos de una escuela, almacenada en un
   archivo. Utiliza una función para realizar la lectura, pero el archivo se abre
   y cierra desde el programa principal. */

void promedio(FILE *); /* Prototipo de función */

void main(void)
{
    FILE *ar;

    if ((ar = fopen("arc9.txt", "r")) != NULL)
    {
        promedio(ar); /* Se pasa el archivo como parámetro */
        fclose(ar);
    }
    else
    {
        printf("No se puede abrir el archivo\n");
    }
}

void promedio(FILE *ar1)
/* Esta función lee los datos de los alumnos desde un archivo, e imprime tanto
   la matrícula como el promedio de cada alumno. */
{
    int i, j, n, mat;
    float pro, cal;

    /* Lee el número total de alumnos */
    fscanf(ar1, "%d", &n);

    for (i = 0; i < n; i++)
    {
        /* Lee la matrícula del alumno */
        fscanf(ar1, "%d", &mat);
        printf("%d\t", mat);

        pro = 0;

        /* Lee las 5 calificaciones y acumula la suma */
        for (j = 0; j < 5; j++)
        {
            fscanf(ar1, "%f", &cal);
            pro += cal;
        }

        /* Imprime el promedio con dos decimales */
        printf("\t %.2f\n", pro / 5);
    }
}
