#include <stdio.h>
#include <stdlib.h>
#define SALIR 0
#define SUMAR 1
#define RESTAR 2
#define MULTIPLICAR 3
#define DIVIDIR 4
#define RAIZ 5
#define CUADRADO 6
#define ERR_OK 0
#define ERR_SYNTAX 1
#define ERR_DivByZero 555
#define ERR_NegativeRoot 556
#define TOLERANCIA 1e-12
#define MAX_ITERACIONES 100
// Funciones
// Sirve para dividir el problema
// Valor y Referencia (punteros)
// devolver el error
// Ambito de las variable o ciclo de vida
// *operador de indireccion y para declarar punteros
// &operador de direccion

int suma(double s1, double s2, double *r);//declaracion de funcion
int resta(double s1, double s2, double *r);
int multiplicacion(double m1, double m2, double *r);
int division(double dividendo, double divisor, double *r);
int raiz_cuadrada(double n, double *r);
int al_cuadrado(double n, double *r);


int main()
{
    int menu = -1;
    double n1 = 0.0;
    double n2 = 0.0;
    double result = 0.0;//variable global
    int err = ERR_OK;
    printf("\nCALCULADORA V1.0");
    do
    {
        printf("\n0-SALIR\n1-SUMAR\n2-RESTAR\n3-MULTIPLICAR\n4-DIVIDIR\n5-RAIZ CUADRADA\n6-ELEVAR AL CUADRADO\n");
        scanf("%i",&menu);

        if(menu == SUMAR)
        {
            printf("\nSUMA");
            printf("\nEscriba el primer numero:");
            scanf("%lf",&n1);
            printf("\nEscriba el segundo numero:");
            scanf("%lf",&n2);
            err = suma(n1,n2,&result);
            if(err == ERR_OK)
            {
                printf("\nResultado de la SUMA de %lf + %lf = %lf",n1,n2,result);
            }
            else
            {

            }
        }
        if(menu == RESTAR)
        {
            printf("\nRESTAR");
            printf("\nEscriba el primer numero:");
            scanf("%lf",&n1);
            printf("\nEscriba el segundo numero:");
            scanf("%lf",&n2);
            err = resta(n1,n2,&result);
            if(err == ERR_OK)
            {
                printf("\nResultado de la RESTA de %lf - %lf = %lf",n1,n2,result);
            }
            else
            {

            }
        }
        if(menu == MULTIPLICAR)
        {
            printf("\nMULTIPLICAR");
            printf("\nEscriba el primer numero:");
            scanf("%lf",&n1);
            printf("\nEscriba el segundo numero:");
            scanf("%lf",&n2);
            err = multiplicacion(n1,n2,&result);
            if(err == ERR_OK)
            {
                printf("\nResultado de la MULTIPLICACION DE %lf * %lf = %lf",n1,n2,result);
            }
            else
            {

            }

        }
        if(menu == DIVIDIR)
        {
            printf("\nDIVIDIR");
            printf("\nEscriba el Dividendo:");
            scanf("%lf",&n1);
            printf("\nEscriba el Divisor:");
            scanf("%lf",&n2);
            err = division(n1,n2,&result);
            if(err == ERR_OK)
            {
                printf("\nDivision %lf/%lf=%lf",n1,n2,result);
            }
            else
            {
                if(err == ERR_DivByZero)
                {
                    printf("\nNo se puede dividir entre cero");
                }
            }
        }
        if(menu == RAIZ)
        {
            printf("\nRAIZ CUADRADA");
            printf("\nEscrita el numero:");
            scanf("%lf",&n1);
            err = raiz_cuadrada(n1,&result);
            if(err == ERR_OK)
             {
               printf("\nRaiz cuadrada de %lf = %lf",n1,result);
            }

     else
     {
         if(err == ERR_NegativeRoot)
         {
             printf("\nNo existe la raiz cuadrada real de un numero negativo");
         }

       }

     }
     if(menu == CUADRADO)
    {
        printf("\nELEVAR AL CUADRADO");
        printf("\nEscriba el numero:");
        scanf("%lf",&n1);
        err = al_cuadrado(n1,&result);
        if(err == ERR_OK)
        {
            printf("\nEl cuadrado de %lf = %lf",n1,result);
        }
        else
        {

        }
       }
    }
    while(menu != SALIR);
    return 0;
}

int suma(double s1, double s2, double *r)
{
    *r = s1 + s2;
    return ERR_OK;
}

int resta(double s1, double s2, double *r)
{
    *r = s1 - s2;
    return ERR_OK;
}
int multiplicacion(double m1, double m2, double*r)
{
    *r = m1 * m2;
    return ERR_OK;
}

int division(double dividendo, double divisor, double *r)
{
    if(divisor != 0)
    {
        *r = dividendo / divisor;
        return ERR_OK;
    }
    else
    {
        return ERR_DivByZero;
    }
}
int  raiz_cuadrada(double n, double *r)
{
    double x;
    double x_nuevo;
    double diferencia;
    int i = 0;

    if(n < 0)
    {
         return ERR_NegativeRoot;
    }
    if (n == 0)
    {
        *r = 0.0;
        return ERR_OK;
    }

    x = (n >= 1) ? n : 1.0;
    do
    {
        x_nuevo = (x + n / x) / 2.0;
        diferencia = x_nuevo - x;
        if(diferencia < 0)
        {
            diferencia = -diferencia;
        }
        x = x_nuevo;
        i ++;
    }
    while(diferencia > TOLERANCIA && i < MAX_ITERACIONES);

    *r = x;
    return ERR_OK;
}
int al_cuadrado(double n, double *r)
{
    *r = n * n;
    return ERR_OK;
}
