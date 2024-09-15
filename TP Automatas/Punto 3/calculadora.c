#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "convertirNotacion.h"
#include "resultadoPosfija.h"

int columna(int c)
{
    switch(c)
    {
        case '0': return 0;
        case '1': return 1;
        case '2': return 1;
        case '3': return 1;
        case '4': return 1;
        case '5': return 1;
        case '6': return 1;
        case '7': return 1;
        case '8': return 1;
        case '9': return 1;
        case '+': return 2;
        case '-': return 3;
        case '*': return 4;
        case '/': return 5;
    }
}

int esEstadoFinal(int estado)
{
    if(estado == 2 || estado == 4)
    {
        return 1;
    }
    return 0;
}

int esPalabra(char *cadena)
{
    const int tt[6][6] = {
        {2,2,1,1,5,5},
        {2,2,5,5,5,5},
        {5,5,1,1,1,3},
        {5,4,5,5,5,5},
        {5,5,1,1,1,3},
        {5,5,5,5,5,5}
    };

    int estado = 0;
    int i = 0;
    int c = cadena[i];

    while(c != '\0' && estado != 5)
    {
        estado = tt[estado][columna(c)];
        c = cadena[++i];
    }

    if(esEstadoFinal(estado))
    {
        return 1; 
    }
    
    return 0;
}

int perteneceAlfabeto(char c)
{
    return isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/';
}

int verifica(char *cadena)
{
    unsigned i; 

    for(i = 0; cadena[i]; i++)
    {
        if(!perteneceAlfabeto(cadena[i]))
        {
            return 0;
        }
    }

    return 1; 
}


int main() {
    char operacion[256]; 

    //Abrimos el archivo
    FILE *archivo = fopen("archivoPunto3.txt", "r");

    printf("\n");

    printf("Elegi un numero!:\n");
    printf("1. Ingresar cadena por linea de comandos\n");
    printf("2. Leer cadena desde un archivo\n");


    int opcion;
    scanf("%d", &opcion);
    getchar(); 

    printf("\n");




    //Aca simplemente preguntamos si queres ingresar por linea de comandos o por archivo

    switch(opcion) {
        case 1:

            //Opcion 1, ingresar por linea de comandos

            printf("Ingresa una cadena: ");
            fgets(operacion, sizeof(operacion), stdin);
            operacion[strcspn(operacion, "\n")] = '\0';
            break;

       case 2:
            
            //Oopcion 2, leer por archivo

            fgets(operacion, sizeof(operacion), archivo); 
            operacion[strcspn(operacion, "\n")] = '\0'; 
            printf("La cadena leida fue: %s\n", operacion);
            break;

        default:
            printf("Era un numero entre el 1 y el 2 :( \n");
            break;

    }







    if (!verifica(operacion)) {

    printf("Error lexico :(\n");

    return 0; 
    }

    if (esPalabra(operacion)) {
    printf("\nLa cadena pertenece al lenguaje! :)\n\n");  

    char* notacionPosfija = infixToPostfix(operacion);

    printf("La notacion postfija es: %s\n\n", notacionPosfija);  

    int resultado = evaluatePostfix(notacionPosfija);

    printf("El resultado de la operacion es: %d\n", resultado);  

    free(notacionPosfija);

    return 0;
    }  

    else    
    {
    printf("La cadena insertada no pertenece al lenguaje :(\n");  
    return 0;
    }
}