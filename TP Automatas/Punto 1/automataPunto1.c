#include <stdio.h>
#include <ctype.h>
#include <string.h>

int columna(int c)
{
    switch(c)
    {
        case '+': return 0;
        case '-': return 1;
        case 'x': return 2;
        case 'X': return 3;
        case '0': return 4;
        case '1': return 5;
        case '2': return 6;
        case '3': return 7;
        case '4': return 8;
        case '5': return 9;
        case '6': return 10;
        case '7': return 11;
        case '8': return 12;
        case '9': return 13;
        case 'A': return 14;
        case 'B': return 15;
        case 'C': return 16;
        case 'D': return 17;
        case 'E': return 18;
        case 'F': return 19;
        case '#': return 20;
    }
}

int esEstadoFinal(int estado)
{
    if(estado == 2 || estado  == 5 || estado == 6)
    {
        return 1;
    }
    return 0;

}

void incrementarContadores(int estado, int* contOctal, int* contDecimal, int* contHexa)
{
    switch (estado)
    {
        case 6:
            ++(*contOctal);
            break;
        case 2:
            ++(*contDecimal);
            break;
        case 5:
            ++(*contHexa);
            break;
    }
}


int esPalabra(char *cadena, int* contOctal, int* contDecimal, int* contHexa)
{
    const int tt[8][21] = {
        {1,1,7,7,3,2,2,2,2,2,2,2,2,2,7,7,7,7,7,7,7},
        {7,7,7,7,7,2,2,2,2,2,2,2,2,2,7,7,7,7,7,7,7},
        {7,7,7,7,2,2,2,2,2,2,2,2,2,2,7,7,7,7,7,7,0},
        {7,7,4,4,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7},
        {7,7,7,7,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,7},
        {7,7,7,7,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0},
        {7,7,7,7,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,0},
        {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7}
    };

    int estado = 0;
    int i = 0;
    int c = cadena[i];

    while(c != '\0' && estado != 7)
    {
        estado = tt[estado][columna(c)];

        if(esEstadoFinal(estado) && (cadena[i + 1] == '\0' || cadena[i + 1] == '#'))
        {
            incrementarContadores(estado, contOctal, contDecimal, contHexa);
        }

        c = cadena[++i];
    }

    if(esEstadoFinal(estado))
    {
        return 1; 
    }
    
    return 0;
}

int esCaracterHexa(char c)
{
    if(c == 'x' || c == 'X' || c == 'A' || c == 'B' || c == 'C' || c == 'D' || c == 'E' || c == 'F')
    {
        return 1;
    }
    return 0; 
}

int perteneceAlfabeto(char c)
{
    if(isdigit(c) || esCaracterHexa(c) || c == '#' || c == '-' || c == '+')
    {
        return 1;
    }
    return 0; 
}

int verifica(char *cadena)
{
    unsigned i; 

    for(i = 0; cadena[i]; i++)
    {
        if(!(perteneceAlfabeto(cadena[i])))
        {
            return 0;
        }
    }

    return 1; 
}

int main() {
    char palabra[256]; 
    int contOctal = 0;
    int contDecimal = 0;
    int contHexa = 0;


    //Abrimos el archivo 
    FILE *archivo = fopen("archivoPunto1.txt", "r");

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
            fgets(palabra, sizeof(palabra), stdin);
            palabra[strcspn(palabra, "\n")] = '\0';
            break;

       case 2:
            
            //Oopcion 2, leer por archivo

            fgets(palabra, sizeof(palabra), archivo); 
            palabra[strcspn(palabra, "\n")] = '\0'; 
            printf("La cadena leida fue: %s\n\n", palabra);
            break;

        default:
            printf("Era un numero entre el 1 y el 2 :( \n");
            break;

    }






    //Aca verificamos si la cadena contiene algun caracter que NO pertenece al alfabeto
    //De ser el caso, verificamos si el automata la reconoce

    if(!verifica(palabra)) {
        printf("Error lexico :(\n");
        return 0; 
    }

    if(esPalabra(palabra, &contOctal, &contDecimal, &contHexa)) {

        printf("La cadena pertenece al lenguaje! :)\n\n");
        printf("Cantidad de octales: %d\n", contOctal);
        printf("Cantidad de decimales: %d\n", contDecimal);
        printf("Cantidad de hexadecimales: %d\n\n", contHexa);

    } else {

        printf("La cadena insertada no pertenece al lenguaje :(\n");

    }

    return 0;
}
