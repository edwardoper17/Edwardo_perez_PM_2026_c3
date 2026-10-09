#include <stdio.h>
/* Medidas El programa, al recibir como datos la longitud y el peso de un objeto expresados en pies y libras, calcula los datos de este objeto pero en metros y kilogramos, respectivamente.
PIE, LIB, MET Y KIL: variables tipo real. */

int main()
{
    float PIE, LIB, MET, KIL;
    printf("Ingrese los datos del obejeto:");
    scanf("%f %f", &PIE, &LIB);
    MET = PIE * 0.09290;
    KIL = LIB * 0.45359;
    printf("\nDatos del objeto \nLongiyud: %5.2f \t Peso: %5.2f", MET,KIL);
    return 0;
}
