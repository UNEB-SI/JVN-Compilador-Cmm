#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*######### INICIO CONSTANTES ##########*/
#define SIZE_PR         12
#define COMP_PR         11

#define SIZE_CTL        255
#define COMP_CTL        255

#define SIZE_SN         20
#define COMP_SN         3

#define COMP_NUM        20
#define COMP_LEXEMA     31

#define EOS             '\0' //indica final da string
#define ARQ             100  //qtd máxima do nome do arquivo

/*######### FIM CONSTANTES ##########*/

extern char TAB_PR[SIZE_PR][COMP_PR];        //palavras-reservadas
extern char TAB_SN [SIZE_SN][COMP_SN];        //simbolos de sinais
extern char TAB_CTL[SIZE_CTL][COMP_CTL];     //simbolos de constantes literais
extern int ultimaPosicaoCTL;                    //posicao da ultima constante literal inserida na tabCTL
extern int contLinha;

/*######### INICIO CATEGORIAS ##########*/
//ID   - Identificador
//PR   - Palavra Reservada
//CTI  - Constante Inteira
//CTR  - Constante Real
//CTC  - Constante Caracter
//CTL  - Constante Literal
//SN   - Sinal
//EOF  - Ø
typedef enum { ID, PR, CTI, CTR, CTC, CTL, SN, FA, CMT } CATEGORIA;
/*######### FIM CATEGORIAS ##########*/

/*######### INICIO SINAIS ##########*/
// ( ) { } + - / * , ; = == ! != > < >= <= && ||
typedef enum {  ABRE_PARENTESE,     FECHA_PARENTESE,        ABRE_CHAVE,         FECHA_CHAVE,
                SOMA,               SUBTRAI,                DIVIDE,             MULTIPLICA,
                VIRGULA,            PONTO,                  PONTO_E_VIGULA,     ATRIBUI,
                IGUALA,             NEGA,                   DIFERENTE,          MAIOR_QUE,
                MENOR_QUE,          MAIOR_OU_IGUAL,         MENOR_OU_IGUAL,     E_LOGICO, OU_LOGICO
            } SINAIS;

/*######### FIM SINAIS ##########*/

/*######### INICIO PALAVRAS RESERVADAS ##########*/
//caracter inteiro real booleano semparam semretorno se senao enquanto para retorne
typedef enum { CARACTER,INTEIRO,REAL,BOOLEANO,SEMPARAM,SEMRETORNO,SE,SENAO,ENQUANTO,PARA,RETORNE } PALAVRA_RESERVADA;
/*######### FIM PALAVRAS RESERVADAS ##########*/

/*######### INICIO TOKEN ##########*/
//lexema          -   PR, ID, SN
//comentario      -   Qualquer caracter lido diferente de */
//CodigoPr        -   PR
//CodigoSn        -   SN
//ValorInteiro    -   CTI ; CTC
//ValorReal       -   CTR
//PosicaoLiteral  -   CTL

typedef struct
{
    CATEGORIA cat;
    char lexema[COMP_LEXEMA];
    char comentario[100];

    union{
        PALAVRA_RESERVADA CodigoPr;
        SINAIS CodigoSn;
        int ValorInteiro;
        float ValorReal;
        int PosicaoLiteral;
    } atr;
} TOKEN;
/*######### FIM TOKEN ##########*/

/*######### INICIO  ##########*/
FILE* abreArquivo ();
TOKEN analex(FILE*);
int buscaEmTabPr(char []);
int insereEmTabCtl(char []);
void imprimeToken(TOKEN);
void fechaArquivo (FILE*);

/*######### FIM  ##########*/
