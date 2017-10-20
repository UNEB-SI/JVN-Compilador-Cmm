#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

//quantidade e comprimento maximo de elementos

#define QTD_PR      12
#define COMP_PR     11

#define QTD_CTL     255
#define COMP_CTL    255

#define QTD_SN      20
#define COMP_SN     3

#define COMP_NUM    20  //comprimento maximo de uma constante inteira
#define COMP_LEXEMA 31  //comprimento maximo de um identificador

//_____________________________________________

#define EOS         '\0' //final da string
#define ARQ         100  //maximo de 99 caracteres/nome de arquivo

extern char TAB_PR[QTD_PR][COMP_PR];        //palavras-reservadas
extern char TAB_SN [QTD_SN][COMP_SN];        //simbolos de sinais
extern char TAB_CTL[QTD_CTL][COMP_CTL];     //simbolos de constantes literais
extern int posUltimaCTL;                    //posicao da ultima constante literal inserida na tabCTL
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
typedef enum { ID, PR, CTI, CTR, CTC, CTL, SN, FA } CATEGORIA;
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
/*Especificacao da (estrutura do) token
    lexema          :   PR, ID, SN
    CodigoPr        :   PR
    CodigoSn        :   SN
    ValorInteiro    :   CTI ; CTC
    ValorReal       :   CTR
    PosicaoLiteral  :   CTL

OBS.: A codificacao inteira de constante caracter (CTC) sera um inteiro em valorInt.
*/
typedef struct
{
    CATEGORIA cat;
    char lexema[COMP_LEXEMA];

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
FILE* abrirArq ();
TOKEN analex(FILE*);
int buscarTabPR(char []);
int inserirTabCTL(char []);
void imprimirToken(TOKEN);
void fecharArq (FILE*);

/*######### FIM  ##########*/
