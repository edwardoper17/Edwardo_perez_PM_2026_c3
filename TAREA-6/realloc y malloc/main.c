#include <stdio.h>
#include <stdlib.h>

int main()
{
    char nombre[100];
    FILE *archivo;
    char *texto;
    int tamano = 10;
    int cantidad = 0;
    int letra;

    printf("Nombre del archivo: ");
    scanf("%99s", nombre);

    archivo = fopen(nombre, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }


    texto = malloc(tamano);
    if (texto == NULL) {
        printf("No hay memoria\n");
        return 1;
    }


    letra = fgetc(archivo);
    while (letra != EOF) {
        if (cantidad + 1 >= tamano) {
            tamano = tamano + 10;
            texto = realloc(texto, tamano);
            if (texto == NULL) {
                printf("No hay memoria\n");
                return 1;
            }
        }
        texto[cantidad] = letra;
        cantidad++;
        letra = fgetc(archivo);
    }
    texto[cantidad] = '\0';

    fclose(archivo);

    printf("\n%s\n", texto);
    printf("Letras leidas: %d\n", cantidad);

    free(texto);
    return 0;
}
