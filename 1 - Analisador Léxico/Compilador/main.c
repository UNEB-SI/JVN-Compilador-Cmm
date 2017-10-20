#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"

char TAB_SN[SIZE_SN][COMP_SN] = {'(', ')', '{', '}','+', '-', '/', '*', ',', '.', ';', '=', '==', '!', '!=', '>', '<', '>=', '<=', '&&', '││'};
char TAB_PR[SIZE_PR][COMP_PR] = {"caracter", "inteiro", "real", "booleano", "semparam", "semretorno", "se", "senao", "enquanto", "para", "retorne"};

char TAB_CTL[SIZE_CTL][COMP_CTL]; 
int ultimaPosicaoCTL = -1;

int contLinha = 1;

int main () {
	TOKEN token;
	FILE* fp;

	fp = abreArquivo();


	while (!feof (fp)) {

		token = analex(fp);

		imprimeToken(token);
	}

	printf ("\n\nAnalise lexica concluida.\n \nPressione Enter para sair.");
	getchar();
	fflush(stdin);

	fechaArquivo (fp);

	return 0;
}
