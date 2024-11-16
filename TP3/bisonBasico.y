%{
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
extern char *yytext;
extern int yyleng;
extern int yylex(void);
extern void yyerror(char*);
int variable=0;
%}
%union{
   char* cadena;
   int num;
} 
%token INICIO FIN LEER ESCRIBIR ASIGNACION PYCOMA SUMA RESTA PARENIZQUIERDO PARENDERECHO
%token <cadena> ID
%token <num> CONSTANTE
%%
sentencias: sentencias sentencia 
|sentencia
;
sentencia: ID {printf("LA LONG es: %d",yyleng);if(yyleng>32) yyerror("Excediste la longitud maxima para identificadores");} ASIGNACION expresion PYCOMA
;
expresion: primaria 
|expresion operadorAditivo primaria 
; 
primaria: ID
|CONSTANTE {printf("valores %d %d",atoi(yytext),$1); }
|PARENIZQUIERDO expresion PARENDERECHO
;
operadorAditivo: SUMA 
| RESTA
;
%%
int main() {
yyparse();
}
void yyerror (char *s){
printf ("mi error personalizado es %s\n",s);
}
int yywrap()  {
  return 1;  
} 