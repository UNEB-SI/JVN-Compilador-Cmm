#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"

int main(){
    FILE *arquivo;
    TOKEN token;

    arquivo = abrir_Arquivo("TESTE.txt");

	while (!feof(arquivo)){
		token = analex(arquivo);
    }

	system("PAUSE");
    fclose(arquivo);
    return 0;
}


