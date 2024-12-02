%{
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <string.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);
int variable=0;

// Tabla de símbolos (variables)
struct SymbolTable {
    char nombre[32];
    int inicializada;
    int esConstante;  // Nuevo campo para marcar las constantes
};

#define MAX_SYMBOLS 100
struct SymbolTable tablaSimbolos[MAX_SYMBOLS];
int numSimbolos = 0;

int buscarVariable(char* nombre) {
    for (int i = 0; i < numSimbolos; i++) {
        if (strcmp(tablaSimbolos[i].nombre, nombre) == 0) {
            return i; // Variable encontrada
        }
    }
    return -1; // Variable no encontrada
}

void agregarVariable(char* nombre, int esConstante) {
    if (numSimbolos < MAX_SYMBOLS) {
        strcpy(tablaSimbolos[numSimbolos].nombre, nombre);
        tablaSimbolos[numSimbolos].inicializada = 0; // Inicialmente no está asignada
        tablaSimbolos[numSimbolos].esConstante = esConstante; // Marcar como constante si corresponde
        numSimbolos++;
    }
}

void inicializarVariable(char* nombre) {
    int index = buscarVariable(nombre);
    if (index != -1) {
        tablaSimbolos[index].inicializada = 1; // Marcamos como inicializada
    }
}

int estaInicializada(char* nombre) {
    int index = buscarVariable(nombre);
    if (index != -1) {
        return tablaSimbolos[index].inicializada; // Devuelve si está inicializada
    }
    return 0; // Si no está en la tabla, consideramos que no está inicializada
}

int esConstante(char* nombre) {
    int index = buscarVariable(nombre);
    if (index != -1) {
        return tablaSimbolos[index].esConstante; // Devuelve si es constante
    }
    return 0; // Si no está en la tabla, consideramos que no es constante
}

%}

%union{
   char* cadena;
   int num;
} 

%token INICIO FIN LEER ESCRIBIR ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO
%token <cadena> ID
%token <num> CONSTANTE
%token CONST   // Agregar el token de constante
%%

sentencias: sentencias sentencia 
| sentencia
;

sentencia: CONST ID ASIGNACION expresion PYCOMA { 
    // Declaración de constante
    printf("Constante declarada: %s\n", yytext);
    int idx = buscarVariable(yytext);
    if (idx == -1) {
        agregarVariable(yytext, 1); // Marca como constante
    }
}
| ID ASIGNACION expresion PYCOMA { 
    // Asignación de variable
    printf("Asignacion a variable: %s\n", yytext);
    if (esConstante(yytext)) {
        yyerror("Error semantico: la constante ya fue inicializada.");
    }
    int idx = buscarVariable(yytext);
    if (idx == -1) {
        agregarVariable(yytext, 0); // Marca como variable normal
    }
    else {
        inicializarVariable(yytext); // Si la variable existe, inicialízala
    }
}
;

expresion: primaria 
| expresion operadorAditivo primaria
;

primaria: ID {
    printf("Variable utilizada: %s\n", yytext);
    if (!estaInicializada(yytext)) {
        yyerror("Error semantico: variable no inicializada.");
    }
}
| CONSTANTE { printf("Valor constante: %d\n", atoi(yytext)); }
| PARENIZQUIERDO expresion PARENDERECHO
;

operadorAditivo: SUMA 
| RESTA
;

%%

int main() {
    yyparse();
}

void yyerror(char *s) {
    printf("Mi error personalizado: %s\n", s);
}

int yywrap() {
    return 1;  
}
