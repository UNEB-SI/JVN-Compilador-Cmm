#include <stdio.h>
#include <stdlib.h>
#include "Analex.h"

int main(int argc, char *argv[])
{   	
    if ((fp=fopen("texto.txt","r")) == NULL ) {
        printf("Desculpe, o arquivo nao pode ser aberto.");
        exit(1);
    }
 	
    TOKEN token1;

    while(1){ 
			 
    	prog();
    
		// puts(token1.lexema);
		/*    puts(token1.CodSn);
	    printf("Tipo %s \n\n",Tabela_Categoria[token1.tipo]);
	    if(token1.tipo==PR) {puts(Tab_Pr[token1.CodPr] );}
	  	if(token1.tipo==CTL) {puts(Tab_Pos_Lit[token1.Posicao_Literal] );} */
	    if (feof(fp)) break;

	}
    
    
	fclose(fp);
  
  	system("PAUSE");	
  	return 0;
}


