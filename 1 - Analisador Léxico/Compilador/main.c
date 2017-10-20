#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"

char TAB_SN[QTD_SN][COMP_SN] = {'(', ')', '{', '}','+', '-', '/', '*', ',', '.', ';', '=', '==', '!', '!=', '>', '<', '>=', '<=', '&&', '││'};
char TAB_PR[SSIZE_SN][COMP_PR] = {"caracter", "inteiro", "real", "booleano", "semparam", "semretorno", "se", "senao", "enquanto", "para", "retorne"};

char TAB_CTL[SIZE_CTL][COMP_CTL];   //tabela de simbolos de constantes literais
int posUltimaCTL = -1;            //posicao da ultima constante literal inserida na tabCTL

int contLinha = 1; //contador de linhas

int main () {
	TOKEN token;
	FILE* fp;

	fp = abrirArq();


	while (!feof (fp)) {

		token = analex(fp);

		imprimirToken(token);
	}

	printf ("\n\nAnalise lexica concluida.\n \nPressione Enter para sair.");
	getchar();
	fflush(stdin);

	fecharArq (fp);

	return 0;
}
