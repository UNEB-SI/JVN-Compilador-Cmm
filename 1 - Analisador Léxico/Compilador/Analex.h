#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SN_SIZE 21
#define PR_SIZE 11
#define CT_SIZE 8

/*######### INICIO CATEGORIAS ##########*/
//ID   - Identificador
//PR   - Palavra Reservada
//CTI  - Constante Inteira
//CTR  - Constante Real
//CTC  - Constante Caracter
//CTL  - Constante Literal
//SN   - Sinal
//EOF  - Ø
typedef enum { ID, PR, CTI, CTR, CTC, CTL, SN } CATEGORIA;
char TAB_CATEGORIA[CT_SIZE][25]={"IDENTIFICADOR", "PALAVRA RESERVADA", "CONSTANTE INTEIRA","CONSTANTE REAL"," CONSTANTE CARACTER", "CONSTANTE LITERAL","SINAL"};
/*######### FIM CATEGORIAS ##########*/

/*######### INICIO SINAIS ##########*/
// ( ) { } + - / * , ; = == ! != > < >= <= && ||
typedef enum { ABRE_PARENTESE, FECHA_PARENTESE, ABRE_CHAVE, FECHA_CHAVE, SOMA, SUBTRAI, DIVIDE, MULTIPLICA, VIRGULA, PONTO, PONTO_E_VIGULA,
               ATRIBUI, IGUALA, NEGA, DIFERENTE, MAIOR_QUE, MENOR_QUE, MAIOR_OU_IGUAL, MENOR_OU_IGUAL, E_LOGICO, OU_LOGICO
            } SINAIS;
char TAB_SN[SN_SIZE][2] = {'(', ')', '{', '}','+', '-', '/', '*', ',', '.', ';', '=', '==', '!', '!=', '>', '<', '>=', '<=', '&&', '││'};
/*######### FIM SINAIS ##########*/

/*######### INICIO PALAVRAS RESERVADAS ##########*/
//caracter inteiro real booleano semparam semretorno se senao enquanto para retorne
typedef enum { CARACTER,INTEIRO,REAL,BOOLEANO,SEMPARAM,SEMRETORNO,SE,SENAO,ENQUANTO,PARA,RETORNE } PALAVRA_RESERVADA;
char TAB_PR[PR_SIZE][15] = {"caracter", "inteiro", "real", "booleano", "semparam", "semretorno", "se", "senao", "enquanto", "para", "retorne"};
/*######### FIM PALAVRAS RESERVADAS ##########*/

/*######### INICIO TOKEN ##########*/
typedef struct
{
    CATEGORIA tipo;
    char lexema[31];

    union{
        PALAVRA_RESERVADA CodigoPr;
        SINAIS CodSinal;
        int ValorInteiro;
        float ValorReal;
        int PosicaoLiteral;
    };
} TOKEN;
/*######### FIM TOKEN ##########*/

/*######### INICIO  ##########*/
TOKEN * analex(FILE * fd);
// int op_Rel();
// void cmd();
// void atrib();
// void decl_Var();
// void tipo();
// int eh_Tipo();
// void tipos_Param();
// void func();
// void expr();
// void expr_Simp();
// void termo();
// void fator();
// void prog();
// void decl();

/*######### FIM  ##########*/