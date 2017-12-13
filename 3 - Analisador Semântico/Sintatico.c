//### ANALISADOR SINTÁTICO ###

#include "Analex.h"

cel_simbolo tab_simbolos[100];
int Escopo_Global, Zombie, pos_simb;
int num_linha;
int tipo_id_tmp;
int tipo_param_tmp;
char lexema_tmp[20];

FILE * codigo;
/*

 classe_simbolo
	VARIAVEL
	PROTOTIPO
	FUNCAO
	PARAMETRO
	ARGUMENTO
	NOMEPROGRAMA

TAB SIMBOLOS
        char lexema[32];		// Nome
        int  escopo; 			//0 global / 1 local
        classe_simbolo classe;
        int zombie; 			//0 inativo / 1 ativo
        int tipo;  				//Real, inteiro ...
        int posicao;
        char label[3];

*/


void inicio (FILE* fp) {
	token=analex(fp);
	num_linha = 1;
	pos_simb = -1;
}

/*Gerenciador da tabela de simbolos*/
int inserirSimbolo( char nlexema[], int nescopo, classe_simbolo nclasse, int nzombie, tipo_simbolo tipo ){
    pos_simb++;
    tab_simbolos[pos_simb].posicao = pos_simb;
    strcpy (tab_simbolos[pos_simb].lexema,nlexema);
    tab_simbolos[pos_simb].escopo = nescopo;
    tab_simbolos[pos_simb].classe = nclasse;
    tab_simbolos[pos_simb].zombie = nzombie;
    tab_simbolos[pos_simb].tipo   = tipo;
    return pos_simb;
}

int buscaSimboloSeNaoExistirInsere( char nlexema[], int nescopo, classe_simbolo nclasse, int nzombie, tipo_simbolo tipo ){
  /*Um identificador pode ser declarado no máximo uma vez como global e no maximo uma vez como local em uma função particular qualquer.
    um identificador pode aparecer como local em várias funções distintas
    Uma função pode ser definiada no maximo uma vez*/
  if( buscarSimbolo( nlexema, nescopo, nclasse, nzombie ) != -1 ){
      printf("na linha %d variavel: %s \n",  num_linha, nlexema);
      return 0;
  }else{
      inserirSimbolo( nlexema, nescopo, nclasse, nzombie, tipo );
      return 1;
  }
}

//vai desempilhando até encontrar o valor
int buscarSimbolo( char nlexema[], int nescopo, classe_simbolo nclasse, int nzombie ){
     int i;
     for(i=pos_simb; i>-1; i--){
        if(strcmp( tab_simbolos[i].lexema, nlexema ) == 0 && tab_simbolos[i].escopo == nescopo &&
            tab_simbolos[i].classe == nclasse && tab_simbolos[i].zombie == nzombie ){
          return i;
        }
     }
     return -1;
}

int deletarSimbolo( int position ){
    strcpy (tab_simbolos[position].lexema,"\0");
    tab_simbolos[position].escopo = 0;
    tab_simbolos[position].classe = (classe_simbolo) 0;
    tab_simbolos[position].zombie = 0;
    pos_simb--;
}

void imprimeTabSimbolos(){
     int i; //usado para imprimir a tabela de simbolos
     for(i=0; i <= pos_simb; i++){
          printf("ind : %d - lexem: %s - escopo %d - classe %d - zombie %d - tipo %d\n", i, tab_simbolos[i].lexema, tab_simbolos[i].escopo, tab_simbolos[i].classe, tab_simbolos[i].zombie,  tab_simbolos[i].tipo);
     }
}

int apagarVariaveisMesmoEscopo( int nescopo ){
  int i; //usado para imprimir a tabela de simbolos
  for(i=0; i < pos_simb; i++){
      if( tab_simbolos[i].escopo == nescopo && tab_simbolos[i].classe == VARIAVEL && tab_simbolos[i].zombie == 0 )
        deletarSimbolo(i);
  }
}




void erro () {
	system("PAUSE");
 	exit(1);
}




//	 ############################# TIPO ######################################

	 int tipo(FILE* fp){

	 	  		if(( (token.valor.codPR==PR_CARACTER)||(token.valor.codPR==PR_INTEIRO)||(token.valor.codPR==PR_REAL)||(token.valor.codPR==PR_BOOLEANO) )&& (token.tipo==PR))
				    if (token.valor.codPR==PR_INTEIRO) 	{ token=analex(fp); return 0; }
				    if (token.valor.codPR==PR_CARACTER) { token=analex(fp); return 1; }
					if (token.valor.codPR==PR_REAL)		{ token=analex(fp); return 2; }
					if (token.valor.codPR==PR_BOOLEANO)	{ token=analex(fp); return 3; }
				else {

		   			 printf("ERRO, Tipo Esperado! %d",contLinha);
                     erro ();
					 }
		  }

// ################################## TIPOS_P_OPC ###############################


void tipos_p_opc(FILE* fp){
	if((token.tipo==PR)&&(token.valor.codPR==PR_SEMPARAM))
	 	token=analex(fp);
    else{
		tipo_param_tmp = tipo(fp);
	 	if(token.tipo==ID) {
	 		//INSERE PARAMETRO OPCIONAL 1
	 		//ESCOPO_GLOBAL	0 ?
		 	//ZUMBI			1
		 	Escopo_Global 	= 0;
	 		Zombie 			= 1;
	 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PARAMETRO, Zombie, tipo_param_tmp);

	 		token=analex(fp);
	 	}
		while((token.valor.codSN==SN_VIRGULA)&&(token.tipo==SN)){
	            token=analex(fp);
				tipo_param_tmp = tipo(fp);
				if(token.tipo==ID) {
					//INSERE PARAMETRO OPCIONAL 2
					//ESCOPO_GLOBAL	0 ?
		 			//ZUMBI			1
		 			Escopo_Global 	= 0;
			 		Zombie 			= 1;
			 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PARAMETRO, Zombie, tipo_param_tmp);
					
					token=analex(fp);
				}
		}
	}
}


// ################################## TIPOS_PARAM ###############################


void tipos_Param(FILE* fp){
	if((token.tipo==PR)&&(token.valor.codPR==PR_SEMPARAM)) token=analex(fp);
    else{
	 	tipo_param_tmp = tipo(fp);
 		if(token.tipo==ID)  {
 			//INSERE PARAMETRO 1
 			//ESCOPO_GLOBAL	0 ?
		 	//ZUMBI			1
 			Escopo_Global 	= 0;
	 		Zombie 			= 1;
	 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PARAMETRO, Zombie, tipo_param_tmp);

 			token=analex(fp);
 		}
 		else{
		 	printf("ERRO, ID Esperado! na linha %d",contLinha);
			erro();
		}
	    while((token.valor.codSN==SN_VIRGULA)&&(token.tipo==SN)){
            token=analex(fp);
			tipo_param_tmp = tipo(fp);
			if(token.tipo==ID) {
				//INSERE PARAMETRO 2
				//ESCOPO_GLOBAL	0 ?
		 		//ZUMBI			1
		 		Escopo_Global 	= 0;
		 		Zombie 			= 1;
		 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PARAMETRO, Zombie, tipo_param_tmp);

				token=analex(fp);
			}
			else{
				 printf("ERRO, ID Esperado! na linha %d",contLinha);
	  			 erro();
			}
		}
	}
}

// ###############################	PROG ####################################

void prog(FILE* fp){


	//PROTOTIPO
	 if((token.tipo==PR)&&(token.valor.codPR==PR_PROTOTIPO)) {
		token=analex(fp);

    	if((token.tipo==PR)&&(token.valor.codPR==PR_SEMRETORNO)) {
		 	token=analex(fp);

		 	if(token.tipo==ID) {
		 		//INSERE ID FUNÇÃO PROTOTIPO SEMRETORNO1
		 		//ESCOPO_GLOBAL	1
		 		//ZUMBI			0
		 		Escopo_Global 	= 1;
		 		Zombie 			= 0;
		 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PROTOTIPO, Zombie, SEMRETORNO);
				//imprimeTabSimbolos();
		 		token=analex(fp);
			}

		 	else  {
		 		printf ("ERRO, ID Esperado! na linha %d",contLinha);
		 		erro();
		 	}

	 		if((token.tipo==SN)&&(token.valor.codSN==SN_ABRI_PARENTESE)) token=analex(fp);
	 		else {
				printf("ERRO, ( Esperado!na linha %d",contLinha);
		   	    erro();
			}
			tipos_p_opc(fp);

			 if((token.tipo==SN)&&(token.valor.codSN==SN_FECHA_PARENTESE)) token=analex(fp);
			 else {
			 	printf("ERRO, ) Esperado!na linha %d",contLinha);
		   	        erro();
			 }

			 while(token.tipo!= SN || token.valor.codSN!=SN_PONTO_VIRGULA) {

		 		if((token.valor.codSN==SN_VIRGULA)&&(token.tipo==SN)) token=analex(fp);
		 		else
		        {printf("ERRO, , Esperado!na linha %d",contLinha);
		   	         erro();
				}

				if(token.tipo==ID) {
					//NAO INSERE VARIAVEL LOCAL DA FUNÇÃO PROTOTIPO SEMRETORNO
					//INSERE ID FUNÇÃO PROTOTIPO SEMRETORNO2
					//ESCOPO_GLOBAL	1
		 			//ZUMBI			0
					Escopo_Global 	= 1;
		 			Zombie 			= 0;
		 			buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PROTOTIPO, Zombie, SEMRETORNO);
					
					token=analex(fp);
				}
				else
		        {printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	         erro();
				}

				if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)) token=analex(fp);
				else
				{ printf("ERRO, ( Esperado!na linha %d",contLinha);
		   	         erro();
				}

				tipos_p_opc(fp);

				if((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN)) token=analex(fp);
				else {
					printf("ERRO, ) Esperado!na linha %d",contLinha);
            			erro();
	  			}
			}

			if(token.valor.codSN==SN_PONTO_VIRGULA && token.tipo==SN) token=analex(fp);
			else {
				printf("ERRO, ; Esperado!na linha %d",contLinha);
	   	        erro();
			}

		}

		else {
			tipo_id_tmp = tipo(fp);
			if(token.tipo==ID) {
				//INSERE FUNÇÃO PROTOTIPO COM RETORNO1
				//ESCOPO_GLOBAL	1
		 		//ZUMBI			0

		 		Escopo_Global 	= 1;
		 		Zombie 			= 0;
		 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PROTOTIPO, Zombie, tipo_id_tmp);

				token=analex(fp);
			}
		 	else  {
		 		printf ("ERRO, ID Esperado! na linha %d",contLinha);
		 		erro();
		 	}

	 		if((token.tipo==SN)&&(token.valor.codSN==SN_ABRI_PARENTESE)) token=analex(fp);
			else {
				printf("ERRO, ( Esperado!na linha %d",contLinha);
		   	         erro();
			}

			tipos_p_opc(fp);

	        if((token.tipo==SN)&&(token.valor.codSN==SN_FECHA_PARENTESE)) token=analex(fp);
			else {
			 	printf("ERRO, ) Esperado!na linha %d",contLinha);
		   	        erro();
			}
		 	while(token.tipo!= SN || token.valor.codSN!=SN_PONTO_VIRGULA) {
		 		if((token.valor.codSN==SN_VIRGULA)&&(token.tipo==SN)) token=analex(fp);
		 		else
		        {printf("ERRO, , Esperado!na linha %d",contLinha);
		   	         erro();
				}

				if(token.tipo==ID) {
					//NAO INSERE VARIAVEL LOCAL DA FUNÇÃO PROTOTIPO COM RETORNO
					//INSERE FUNÇÃO PROTOTIPO COM RETORNO2
					//ESCOPO_GLOBAL	1
		 			//ZUMBI			0

					Escopo_Global 	= 1;
			 		Zombie 			= 0;
			 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, PROTOTIPO, Zombie, tipo_id_tmp);

					token=analex(fp);
				}
				else
		        {printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	         erro();
				}
				if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)){
					token=analex(fp);
					tipos_p_opc(fp);
				}
				else {
				 	printf("ERRO, ( Esperado!na linha %d",contLinha);
					erro();
				}
				if((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN)) token=analex(fp);
				else
				{ 	printf("ERRO, ) Esperado!na linha %d",contLinha);
					erro();
	  			}
			}
			if(token.valor.codSN==SN_PONTO_VIRGULA && token.tipo==SN) token=analex(fp);
			else {
				printf("ERRO, ; Esperado!na linha %d",contLinha);
	   	        erro();
			}
		}
	}

	//SEM RETORNO
	else if((token.valor.codPR==PR_SEMRETORNO)&&(token.tipo==PR)) {
		token=analex(fp);
		if(token.tipo==ID) {
			//INSERE FUNÇÃO SEM RETORNO
			//ESCOPO_GLOBAL	1
		 	//ZUMBI			0

		 	Escopo_Global 	= 1;
	 		Zombie 			= 0;
	 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, FUNCAO, Zombie, SEMRETORNO);
			//imprimeTabSimbolos();
			token=analex(fp);
		}
		else {
			printf("ERRO, ID Esperado!na linha %d",contLinha);
   	        erro();
		}
		if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)) token=analex(fp);
		else {
			printf("ERRO, ( Esperado!na linha %d",contLinha);
   	        erro();
		}
		tipos_Param(fp);
		if(token.valor.codSN==SN_FECHA_PARENTESE && token.tipo==SN) token=analex(fp);
		else {
			printf("ERRO, ) Esperado!na linha %d",contLinha);
   	        erro();
		}
		if(token.valor.codSN==SN_ABRI_CHAVE && token.tipo==SN) token=analex(fp);
		else {
			printf("ERRO, { Esperado!na linha %d",contLinha);
   	        erro();
		}
		while (token.tipo==PR && (token.valor.codPR==PR_CARACTER||token.valor.codPR==PR_INTEIRO||token.valor.codPR==PR_REAL||token.valor.codPR==PR_BOOLEANO)) {
				tipo_id_tmp = tipo(fp);
				if(token.tipo==ID) {
					//INSERE VARIAVEL LOCAL DA FUNÇÃO SEM RETORNO 1
					//ESCOPO_GLOBAL	0
		 			//ZUMBI			0
		 			Escopo_Global 	= 0;
			 		Zombie 			= 0;
			 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, VARIAVEL, Zombie, tipo_id_tmp);

					token=analex(fp);
				}
				else {
					printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	        erro();
				}
				while (token.tipo == SN && token.valor.codSN==SN_VIRGULA) {
					token=analex(fp);
					if(token.tipo==ID) {
						//INSERE VARIAVEL LOCAL DA FUNÇÃO SEM RETORNO 2
						//ESCOPO_GLOBAL	0
		 				//ZUMBI			0
						Escopo_Global 	= 0;
				 		Zombie 			= 0;
				 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, VARIAVEL, Zombie, tipo_id_tmp);

						token=analex(fp);
					}
					else {
						printf("ERRO, ID Esperado!na linha %d",contLinha);
 		   	         	erro();
					}
				}
				if(token.valor.codSN==SN_PONTO_VIRGULA && token.tipo==SN) token=analex(fp);
				else {
					printf("ERRO, ; Esperado!na linha %d",contLinha);
		   	        erro();
				}
		}

		//while (token.tipo!= SN || token.valor.codSN != SN_FECHA_CHAVE) {
		while ((token.tipo==PR && (token.valor.codPR==PR_SE ||token.valor.codPR==PR_ENQUANTO||token.valor.codPR==PR_PARA||token.valor.codPR==PR_RETORNE))||token.tipo==ID||(token.tipo==SN && (token.valor.codSN==SN_ABRI_CHAVE||token.valor.codSN==SN_PONTO_VIRGULA))) {
			cmd(fp);
		}

		if(token.valor.codSN==SN_FECHA_CHAVE && token.tipo==SN) token=analex(fp);
		else {
			printf("ERRO, } Esperado!na linha %d",contLinha);
   	        erro();
		}
	}

	//TIPO
	else if (token.tipo == PR && (token.valor.codPR==PR_CARACTER||token.valor.codPR==PR_INTEIRO||token.valor.codPR==PR_REAL||token.valor.codPR==PR_BOOLEANO)) {

		if (token.valor.codPR==PR_INTEIRO)	tipo_id_tmp=0;
		if (token.valor.codPR==PR_CARACTER) tipo_id_tmp=1;
		if (token.valor.codPR==PR_REAL)		tipo_id_tmp=2;
		if (token.valor.codPR==PR_BOOLEANO)	tipo_id_tmp=3;

		token=analex(fp);
		if(token.tipo==ID) {
			strcpy (lexema_tmp,token.lexema);
			token=analex(fp);
		}
		else {
			printf("ERRO, ID Esperado!na linha %d",contLinha);
   	         	erro();
		}
		if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)) {
			//INSERE FUNÇÃO COM RETORNO
			//ESCOPO_GLOBAL	1
		 	//ZUMBI			0

		 	Escopo_Global 	= 1;
	 		Zombie 			= 0;
	 		buscaSimboloSeNaoExistirInsere (lexema_tmp, Escopo_Global, FUNCAO, Zombie, tipo_id_tmp);
			//imprimeTabSimbolos();

			token=analex(fp);
			tipos_Param(fp);
			if(token.valor.codSN==SN_FECHA_PARENTESE && token.tipo==SN) token=analex(fp);
			else {
				printf("ERRO, ) Esperado!na linha %d",contLinha);
	   	        erro();
			}
			if(token.valor.codSN==SN_ABRI_CHAVE && token.tipo==SN) token=analex(fp);
			else {
				printf("ERRO, { Esperado!na linha %d",contLinha);
	   	        erro();
			}

			while (token.tipo==PR && (token.valor.codPR==PR_CARACTER||token.valor.codPR==PR_INTEIRO||token.valor.codPR==PR_REAL||token.valor.codPR==PR_BOOLEANO)) {
				tipo_id_tmp = tipo(fp);

				if(token.tipo==ID) {
					//INSERE VARIAVEL LOCAL FUNÇÃO COM RETORNO 1
					//ESCOPO_GLOBAL	0
		 			//ZUMBI			0
					Escopo_Global 	= 0;
			 		Zombie 			= 0;
			 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, VARIAVEL, Zombie, tipo_id_tmp);

					token=analex(fp);
				}
				else {
					printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	        erro();
				}
				while (token.tipo==SN && token.valor.codSN==SN_VIRGULA) {
					token=analex(fp);
					if(token.tipo==ID) {
						//INSERE VARIAVEL LOCAL FUNÇÃO COM RETORNO 2
						//ESCOPO_GLOBAL	0
		 				//ZUMBI			0
		 				Escopo_Global 	= 0;
				 		Zombie 			= 0;
				 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, VARIAVEL, Zombie, tipo_id_tmp);

						token=analex(fp);
					}
					else {
						printf("ERRO, ID Esperado!na linha %d",contLinha);
 		   	         	erro();
					}
				}
				if(token.valor.codSN==SN_PONTO_VIRGULA && token.tipo==SN) token=analex(fp);
				else {
					printf("ERRO, ; Esperado!na linha %d",contLinha);
		   	        erro();
				}
			}

			while ((token.tipo==PR && (token.valor.codPR==PR_SE ||token.valor.codPR==PR_ENQUANTO||token.valor.codPR==PR_PARA||token.valor.codPR==PR_RETORNE))||token.tipo==ID||(token.tipo==SN && (token.valor.codSN==SN_ABRI_CHAVE||token.valor.codSN==SN_PONTO_VIRGULA))) {
				cmd(fp);
			}

			/*while (token.valor.codSN!=SN_FECHA_CHAVE) {
				cmd(fp);
			}*/

			if(token.valor.codSN==SN_FECHA_CHAVE && token.tipo==SN) token=analex(fp);
			else {
				printf("ERRO, } Esperado!na linha %d",contLinha);
	   	        erro();
			}
		}

		else if (token.tipo== SN && (token.valor.codSN==SN_PONTO_VIRGULA || token.valor.codSN==SN_VIRGULA)) {
			//INSERE DECLARAÇÃO VARIAVEL 1
			//ESCOPO_GLOBAL	1
		 	//ZUMBI			0


		 	Escopo_Global 	= 1;
	 		Zombie 			= 0;
	 		buscaSimboloSeNaoExistirInsere (lexema_tmp, Escopo_Global, VARIAVEL, Zombie, tipo_id_tmp);
			//imprimeTabSimbolos();

			while (token.tipo!= SN || token.valor.codSN!=SN_PONTO_VIRGULA) {
				if(token.valor.codSN==SN_VIRGULA && token.tipo==SN) token=analex(fp);
				else{
				 printf("ERRO, , Esperado!na linha %d",contLinha);
				 erro();
				}
				if(token.tipo==ID) {
					//INSERE DECLARAÇÃO VARIAVEL 2
					//ESCOPO_GLOBAL	1
		 			//ZUMBI			0

					Escopo_Global 	= 1;
			 		Zombie 			= 0;
			 		buscaSimboloSeNaoExistirInsere (token.lexema, Escopo_Global, VARIAVEL, Zombie, tipo_id_tmp);
					//imprimeTabSimbolos();

					token=analex(fp);
				}
				else {
					printf("ERRO, ID Esperado!na linha %d",contLinha);
	   	         	erro();
				}
			}
			if(token.valor.codSN==SN_PONTO_VIRGULA && token.tipo==SN) token=analex(fp);
			else {
				printf("ERRO, ; Esperado!na linha %d",contLinha);
	   	        erro();
			}
		}

		else {
			printf("ERRO, tipo errado linha %d",contLinha);
			erro();
		}


	}

	else if (token.tipo==CMT) {
		 token=analex(fp);
	}

	//PRECISA? CASO NAO SEJA NENHUM DOS 3
	else {
		printf("ERRO, prog invalido linha %d",contLinha);
		erro();
		}

}

	// ############################ CMD ############################3

void cmd(FILE* fp){

	//SE
	if((token.valor.codPR==PR_SE)&&(token.tipo==PR)){
				token=analex(fp);
				if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)){
					token=analex(fp);
					expr(fp);
		 		 	if((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN)){
			 				token=analex(fp);
							cmd(fp);

	   						if((token.valor.codPR==PR_SENAO)&&(token.tipo==PR)){
								token=analex(fp);
								cmd(fp);
							}
					}
				 	else{
					    printf("ERRO, ) Esperado! na linha %d",contLinha);
   				        erro();
		        	}
                }
				else{
					 printf("ERRO, (  Esperado! na linha %d",contLinha);
	   				 erro();
			  	}
  	}

  	//ENQUANTO
  	else if((token.valor.codPR==PR_ENQUANTO)&&(token.tipo==PR)){

       token=analex(fp);
       if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)){
     		token=analex(fp);
 	 		expr(fp);

 			if((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN)){
 				token=analex(fp);
				cmd(fp);
         	}
        	else{
         	     printf("ERRO, ) Esperado! na linha %d",contLinha);
                 erro();
            }
     	}
 		else{
	     	printf("ERRO, (  Esperado! na linha %d",contLinha);
		    erro();
    	}
  	}

	//PARA
	else if((token.valor.codPR==PR_PARA)&&(token.tipo==PR)){
           token=analex(fp);
			   if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)){
		   				token=analex(fp);
						if(token.tipo!= SN || token.valor.codSN!=SN_PONTO_VIRGULA) atrib(fp);
						if((token.valor.codSN==SN_PONTO_VIRGULA)&&(token.tipo==SN)) token=analex(fp);
						else{
         	                printf("ERRO, ; Esperado! na linha %d",contLinha);
                            erro();
	                    }


						if(!((token.valor.codSN==SN_PONTO_VIRGULA)&&(token.tipo==SN))) expr(fp);

						if((token.valor.codSN==SN_PONTO_VIRGULA)&&(token.tipo==SN))token=analex(fp);
						else{
							 printf("ERRO, ; Esperado! na linha %d ",contLinha);
                             erro();
	                    }
						if(!((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN))) atrib(fp);
						if((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN)) token=analex(fp);
						else{
							printf("ERRO, ) Esperado! na linha %d",contLinha);
                            erro();
                        }
						cmd(fp);
						}
			else{
		 	  printf("ERRO, ( Esperado! na linha %d",contLinha);
              erro();
            }
	}


	//RETORNE
	else if((token.valor.codPR==PR_RETORNE)&&(token.tipo==PR))  {

	   	token=analex(fp);
		if(!((token.valor.codSN==SN_PONTO_VIRGULA)&&(token.tipo==SN))) expr(fp);
		if((token.valor.codSN==SN_PONTO_VIRGULA)&&(token.tipo==SN))token=analex(fp);
		else{
	 	printf("ERRO, ; Esperado! linha %d",contLinha);
            erro();
        }
	}

	//ID
	else if(token.tipo==ID){
		token=analex(fp);
		if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)){
		  	token=analex(fp);
			if(!((token.tipo==SN)&&(token.valor.codSN==SN_FECHA_PARENTESE))){
  				expr(fp);
				while((token.valor.codSN==SN_VIRGULA)&&(token.tipo==SN)){
					token=analex(fp);
					expr(fp);
				}
	  		}
	  		token=analex(fp);
			if((token.valor.codSN==SN_PONTO_VIRGULA)&&(token.tipo==SN)){ token=analex(fp); }
	  		else{
				printf("ERRO, ;  Esperado!na linha %d",contLinha);
           		erro();
     		}
		}
		else if (token.valor.codSN==SN_ATRIBUICAO && token.tipo==SN) {
			token=analex(fp);
			expr(fp);
			if(token.valor.codSN==SN_PONTO_VIRGULA && token.tipo==SN) token=analex(fp);
	  		else{
				printf("ERRO, ;  Esperado!na linha %d",contLinha);
           		erro();
     		}
		}
	 	else{
	 	  printf("ERRO, ( Esperado!na linha %d",contLinha);
          erro();
      	}
 	}

	// {CMD}
	else if((token.valor.codSN==SN_ABRI_CHAVE)&&(token.tipo==SN)){
		token=analex(fp);
		while(!((token.valor.codSN==SN_FECHA_CHAVE)&&(token.tipo==SN))) cmd(fp);
		if((token.valor.codSN==SN_FECHA_CHAVE)&&(token.tipo==SN)) token=analex(fp);
		else{
			printf("ERRO, } Esperado! na linha %d",contLinha);
            erro();
        }
	}

    else if((token.valor.codSN==SN_PONTO_VIRGULA)&&(token.tipo==SN)) token=analex(fp);

  	else {
  		printf("ERRO, Comando Esperado!na linha %d",contLinha);
    	erro();
    }

}

//######################################### ATRIB ######################################



void atrib(FILE* fp){
	 if(token.tipo==ID){
	 			token=analex(fp);
				if((token.valor.codSN==SN_ATRIBUICAO)&&(token.tipo==SN)){
							token=analex(fp);
							expr(fp);
				 }
				else
				{
				  printf("ERRO, = Esperado! na linha %d",contLinha);
	 		   	  erro();
			 	 }
				 }
				 else
				 {
				  printf("ERRO, ID Esperado! na linha %d",contLinha);
	 		   	  erro();
			 	 }
}

// ################################### EXPR ###############################3

void expr(FILE* fp){
           expr_Simp(fp);
           if(op_Rel(fp)) expr_Simp(fp);

		   }

// ############################ EXPR_SIMP ################################

void expr_Simp(FILE* fp){

	 if((token.valor.codSN==SN_MAIS||token.valor.codSN==SN_MENOS)&&(token.tipo==SN)) token=analex(fp);
	 termo(fp);

	 while(((token.valor.codSN==SN_MAIS)||(token.valor.codSN==SN_MENOS)||(token.valor.codSN==SN_OR))&&(token.tipo==SN)){
	 							token=analex(fp);
								termo(fp);
								}
}


// ############################# TERMO ####################################


void termo(FILE* fp){
	   fator(fp);
	   while(((token.valor.codSN==SN_VEZES)||(token.valor.codSN==SN_DIVISAO)||(token.valor.codSN==SN_AND))&&(token.tipo==SN)){

	   										token=analex(fp);
											fator(fp);
											}
}

// ############################ FATOR ############################

void fator(FILE* fp){

	 if((token.tipo==CTI)|| (token.tipo==CTR)|| (token.tipo==CTC)|| (token.tipo==CTL)) {
	    token=analex(fp);
	}
	else if((token.valor.codSN==SN_NEGACAO)&&(token.tipo==SN)){
		token=analex(fp);
		fator(fp);
	}

	else if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)){
		token=analex(fp);
		expr(fp);
		if(!((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN))){
			printf("ERRO, )  Esperado! na linha %d",contLinha);
	 		erro();
		}
		token=analex(fp);
	}

	else if(token.tipo==ID){
		token=analex(fp);
		if((token.valor.codSN==SN_ABRI_PARENTESE)&&(token.tipo==SN)){
			token=analex(fp);
			if( token.valor.codSN!=SN_FECHA_PARENTESE){
		 	   	expr(fp);
				while((token.valor.codSN==SN_VIRGULA)&&(token.tipo==SN)){
					token=analex(fp);
					expr(fp);
				}
			}
			if((token.valor.codSN==SN_FECHA_PARENTESE)&&(token.tipo==SN)) token=analex(fp);
			else{
				printf("ERRO, ) Esperado! na linha %d",contLinha);
	            erro();
	        }
		}
	}

	else{
   		printf("ERRO, fator Esperado! na linha %d",contLinha);
   		printf("token erro: %d",token.lexema);
        erro();
	}

 }

 //################################## OP_ REL ###################################


 int op_Rel(FILE* fp){

	  if(token.tipo==SN){
		 if( token.valor.codSN==SN_IGUALDADE || token.valor.codSN==SN_DIFERENTE || token.valor.codSN==SN_MENOR || token.valor.codSN==SN_MENOR_IGUAL || token.valor.codSN==SN_MAIOR || token.valor.codSN==SN_MAIOR_IGUAL ){
           token=analex(fp);
           return 1;
		   }
		   }
		   else
		   return 0;
		   return 0;
}
