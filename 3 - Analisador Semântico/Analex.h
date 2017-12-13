#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define PR_QTD		13
#define PR_TAM		15
#define CTL_QTD		300
#define CTL_TAM		300
#define SN_QTD		20
#define SN_TAM		3
#define NUM_TAM		25
#define ID_TAM		33
#define EOS 		'\0' //final da string

extern char tabPR [PR_QTD] [PR_TAM];        //palavras-reservadas
extern char tabSN [SN_QTD] [SN_TAM];        //simbolos de sinais
extern char tabCTL [CTL_QTD][CTL_TAM];		//simbolos de constantes literais
extern int posUltimaCTL;					//posicao da ultima constante literal inserida na tabCTL
extern int contLinha;

enum categoria {
	ID, 	//	identificador
	PR, 	//	palavra-reservada
	CTC,	//	constante caracter
	SN, 	//	sinal
	CTL, 	//	constante literal (string)
	CTR,	//	constante real
	CTI, 	//	constante inteira
	CMT, 	//	comentario
	FA,		//	final do arquivo
	INV		//  token invalido
};
typedef enum categoria Categoria;

enum sinal {
	SN_DIFERENTE,	SN_NEGACAO,			SN_MAIS,			SN_MENOS,		SN_VEZES,
	SN_DIVISAO,		SN_MENOR_IGUAL, 	SN_MENOR,			SN_MAIOR_IGUAL,	SN_MAIOR,
	SN_IGUALDADE,	SN_ATRIBUICAO,		SN_AND,				SN_OR,			SN_PONTO_VIRGULA,
	SN_VIRGULA,		SN_ABRI_PARENTESE,	SN_FECHA_PARENTESE,	SN_ABRI_CHAVE,	SN_FECHA_CHAVE
};
typedef enum sinal Sinal;


enum palReservada {
	PR_SEMRETORNO,	PR_CARACTER,	PR_INTEIRO,	PR_REAL,
	PR_BOOLEANO,	PR_SEMPARAM,	PR_SE,		PR_SENAO,
	PR_ENQUANTO,	PR_PARA,		PR_RETORNE,	PR_PRINCIPAL,
	PR_PROTOTIPO
};
typedef enum palReservada PalReservada;

typedef struct {
	Categoria tipo;
	char lexema[ID_TAM];
	char comentario[2000];
	union campo {
		PalReservada	codPR;
		Sinal			codSN;
		int				valorInt;
		double			valorReal;
		int				posLiteral;
	} valor;
}Token;


typedef enum{ 
	VARIAVEL, 
	PROTOTIPO, 
	FUNCAO, 
	PARAMETRO, 
	NOMEPROGRAMA 
} classe_simbolo;

typedef enum{ 
	INTEIRO, 
	CARACTER, 
	REAL, 
	BOOLEANO,
	SEMRETORNO
} tipo_simbolo;

typedef struct{
        char lexema[32];
        int  escopo; 			//0 global / 1 local
        classe_simbolo classe;	
        int zombie; 			//0 inativo / 1 ativo
        tipo_simbolo tipo;  	//Real, inteiro ...
        int posicao;     
        char label[3];
}cel_simbolo;


//Prototipo das funcoes
Token token;


FILE* abrirArq ();
Token analex(FILE*);
int buscarTabPR(char []);
int inserirTabCTL(char []);
void imprimirToken(Token);
void fecharArq (FILE*);


