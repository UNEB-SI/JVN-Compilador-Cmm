//### ANALISADOR SINTÁTICO ###

#include "Analex.h"
#include "Anasint.h"

void erro (FILE* fp) {
	printf("\n Token Erro: %s \n",token.lexema);
	printf("\n Token Erro: %i \n",token.atr.CodigoPr);
	system("PAUSE");
 	exit(1);
}

void inicio (FILE* fp) {
	token=analex(fp);
}

void decl_Var(FILE* fp){
	 if(token.cat==ID) token=analex(fp);
	 else{
	 printf("ERRO, Tipo Esperado %d",contLinha);
	 system("PAUSE");
	 exit(1);
	 }
	 }

//	 ############################# TIPO ######################################

	 void tipo(FILE* fp){

	 	  		if(( (token.atr.CodigoPr==CARACTER)||(token.atr.CodigoPr==INTEIRO)||(token.atr.CodigoPr==REAL)||(token.atr.CodigoPr==BOOLEANO) )&& (token.cat==PR))
				     token=analex(fp);
				else {

		   			 printf("ERRO, Tipo Esperado!%d",contLinha);
	 				 system("PAUSE");
	 				 exit(1);
					 }
				/*	 }
		  else{
		  	   printf("!%d",token.cat);
		  	   printf("ERRO, Tipo Esperado!%d",contLinha);
	 		   system("PAUSE");
	 		   exit(1);
			  } */
		  }


//
int eh_Tipo(FILE* fp){

	 	  if(token.cat==PR){
	 	  		if( (token.atr.CodigoPr==CARACTER)||(token.atr.CodigoPr==INTEIRO)||(token.atr.CodigoPr==REAL)||(token.atr.CodigoPr==BOOLEANO) )
				     return 1;
					 }
					 else return 0;
					 return 0;
}





// ################################## TIPOS_P_OPC ###############################


void tipos_p_opc(FILE* fp){
	if((token.cat==PR)&&(token.atr.CodigoPr==SEMPARAM))
	 	token=analex(fp);
    else{
		tipo(fp);
	 	if(token.cat==ID) token=analex(fp);
		while((token.atr.CodigoSn==VIRGULA)&&(token.cat==SN)){
	            token=analex(fp);
				tipo(fp);
				if(token.cat==ID) token=analex(fp);
		}
	}
}


// ################################## TIPOS_PARAM ###############################


void tipos_Param(FILE* fp){
	if((token.cat==PR)&&(token.atr.CodigoPr==SEMPARAM)) token=analex(fp);
    else{
	 	tipo(fp);
 		if(token.cat==ID){
		   token=analex(fp);
		   while((token.atr.CodigoSn==VIRGULA)&&(token.cat==SN)){
                token=analex(fp);
				tipo(fp);
				if(token.cat==ID)
				      token=analex(fp);
				else{
					 printf("ERRO, ID Esperado!");
		  			 erro(fp);
				 }
			}
	   	}
	    else{
		 	printf("ERRO, ID Esperado!");
			erro(fp);
		}
	}
}

// ###############################	PROG ####################################

void prog(FILE* fp){


	//PROTOTIPO
	 if((token.cat==PR)&&(token.atr.CodigoPr==PROTOTIPO)) {
		token=analex(fp);

    	if((token.cat==PR)&&(token.atr.CodigoPr==SEMRETORNO)) {
		 	token=analex(fp);

		 	if(token.cat==ID) token=analex(fp);
		 	else  {
		 		printf ("ERRO, ID Esperado!");
		 		erro(fp);
		 	}

	 		if((token.cat==SN)&&(token.atr.CodigoSn==ABRE_PARENTESE)) token=analex(fp);
	 		else {
				printf("ERRO, ( Esperado!na linha %d",contLinha);
		   	    erro(fp);
			}
			tipos_p_opc(fp);

			 if((token.cat==SN)&&(token.atr.CodigoSn==FECHA_PARENTESE)) token=analex(fp);
			 else {
			 	printf("ERRO, ) Esperado!na linha %d",contLinha);
		   	        erro(fp);
			 }

			 while(token.cat!= SN || token.atr.CodigoSn!=PONTO_E_VIGULA) {

		 		if((token.atr.CodigoSn==VIRGULA)&&(token.cat==SN)) token=analex(fp);
		 		else
		        {printf("ERRO, , Esperado!na linha %d",contLinha);
		   	         erro(fp);
				}

				if(token.cat==ID) token=analex(fp);
				else
		        {printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	         erro(fp);
				}

				if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)) token=analex(fp);
				else
				{ printf("ERRO, ( Esperado!na linha %d",contLinha);
		   	         erro(fp);
				}

				tipos_p_opc(fp);

				if((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN)) token=analex(fp);
				else {
					printf("ERRO, ) Esperado!na linha %d",contLinha);
            			erro(fp);
	  			}
			}

			if(token.atr.CodigoSn==PONTO_E_VIGULA && token.cat==SN) token=analex(fp);
			else {
				printf("ERRO, ; Esperado!na linha %d",contLinha);
	   	        erro(fp);
			}

		}

		else {
			tipo(fp);
			if(token.cat==ID) token=analex(fp);
		 	else  {
		 		printf ("ERRO, ID Esperado!");
		 		erro(fp);
		 	}

	 		if((token.cat==SN)&&(token.atr.CodigoSn==ABRE_PARENTESE)) token=analex(fp);
			else {
				printf("ERRO, ( Esperado!na linha %d",contLinha);
		   	         system("PAUSE");
		  	         exit(1);
			}

			tipos_p_opc(fp);

	        if((token.cat==SN)&&(token.atr.CodigoSn==FECHA_PARENTESE)) token=analex(fp);
			else {
			 	printf("ERRO, ) Esperado!na linha %d",contLinha);
		   	        erro(fp);
			}
		 	while(token.cat!= SN || token.atr.CodigoSn!=PONTO_E_VIGULA) {
		 		if((token.atr.CodigoSn==VIRGULA)&&(token.cat==SN)) token=analex(fp);
		 		else
		        {printf("ERRO, , Esperado!na linha %d",contLinha);
		   	         erro(fp);
				}

				if(token.cat==ID) token=analex(fp);
				else
		        {printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	         erro(fp);
				}
				if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
					token=analex(fp);
					tipos_p_opc(fp);
				}
				else {
				 	printf("ERRO, ( Esperado!na linha %d",contLinha);
					erro(fp);
				}
				if((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN)) token=analex(fp);
				else
				{ 	printf("ERRO, ) Esperado!na linha %d",contLinha);
					erro(fp);
	  			}
			}
			if(token.atr.CodigoSn==PONTO_E_VIGULA && token.cat==SN) token=analex(fp);
			else {
				printf("ERRO, ; Esperado!na linha %d",contLinha);
	   	        erro(fp);
			}
		}
	}

	//SEM RETORNO
	if((token.atr.CodigoPr==SEMRETORNO)&&(token.cat==PR)) {
		token=analex(fp);
		if(token.cat==ID) token=analex(fp);
		else {
			printf("ERRO, ID Esperado!na linha %d",contLinha);
   	        erro(fp);
		}
		if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)) token=analex(fp);
		else {
			printf("ERRO, ( Esperado!na linha %d",contLinha);
   	        erro(fp);
		}
		tipos_Param(fp);
		if(token.atr.CodigoSn==FECHA_PARENTESE && token.cat==SN) token=analex(fp);
		else {
			printf("ERRO, ) Esperado!na linha %d",contLinha);
   	        erro(fp);
		}
		if(token.atr.CodigoSn==ABRE_CHAVE && token.cat==SN) token=analex(fp);
		else {
			printf("ERRO, { Esperado!na linha %d",contLinha);
   	        erro(fp);
		}
		while (token.cat==PR && (token.atr.CodigoPr==CARACTER||token.atr.CodigoPr==INTEIRO||token.atr.CodigoPr==REAL||token.atr.CodigoPr==BOOLEANO)) {
				token=analex(fp);
				if(token.cat==ID) token=analex(fp);
				else {
					printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	        erro(fp);
				}
				while (token.cat == SN && token.atr.CodigoSn==VIRGULA) {
					token=analex(fp);
					if(token.cat==ID) token=analex(fp);
					else {
						printf("ERRO, ID Esperado!na linha %d",contLinha);
 		   	         	erro(fp);
					}
				}
				if(token.atr.CodigoSn==PONTO_E_VIGULA && token.cat==SN) token=analex(fp);
				else {
					printf("ERRO, ; Esperado!na linha %d",contLinha);
		   	        erro(fp);
				}
		}

		//while (token.cat!= SN || token.atr.CodigoSn != FECHA_CHAVE) {
		while ((token.cat==PR && (token.atr.CodigoPr==SE ||token.atr.CodigoPr==ENQUANTO||token.atr.CodigoPr==PARA||token.atr.CodigoPr==RETORNE))||token.cat==ID||(token.cat==SN && (token.atr.CodigoSn==ABRE_CHAVE||token.atr.CodigoSn==PONTO_E_VIGULA))) {
			cmd(fp);
		}

		if(token.atr.CodigoSn==FECHA_CHAVE && token.cat==SN) token=analex(fp);
		else {
			printf("ERRO, } Esperado!na linha %d",contLinha);
   	        erro(fp);
		}
	}

	//TIPO
	if (token.cat == PR && (token.atr.CodigoPr==CARACTER||token.atr.CodigoPr==INTEIRO||token.atr.CodigoPr==REAL||token.atr.CodigoPr==BOOLEANO)) {

		token=analex(fp);
		if(token.cat==ID) token=analex(fp);
		else {
			printf("ERRO, ID Esperado!na linha %d",contLinha);
   	         	erro(fp);
		}
		if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)) {
			token=analex(fp);
			tipos_Param(fp);
			if(token.atr.CodigoSn==FECHA_PARENTESE && token.cat==SN) token=analex(fp);
			else {
				printf("ERRO, ) Esperado!na linha %d",contLinha);
	   	        erro(fp);
			}
			if(token.atr.CodigoSn==ABRE_CHAVE && token.cat==SN) token=analex(fp);
			else {
				printf("ERRO, { Esperado!na linha %d",contLinha);
	   	        erro(fp);
			}

			while (token.cat==PR && (token.atr.CodigoPr==CARACTER||token.atr.CodigoPr==INTEIRO||token.atr.CodigoPr==REAL||token.atr.CodigoPr==BOOLEANO)) {
				token=analex(fp);
				if(token.cat==ID) token=analex(fp);
				else {
					printf("ERRO, ID Esperado!na linha %d",contLinha);
		   	        erro(fp);
				}
				while (token.cat==SN && token.atr.CodigoSn==VIRGULA) {
					token=analex(fp);
					if(token.cat==ID) token=analex(fp);
					else {
						printf("ERRO, ID Esperado!na linha %d",contLinha);
 		   	         	erro(fp);
					}
				}
				if(token.atr.CodigoSn==PONTO_E_VIGULA && token.cat==SN) token=analex(fp);
				else {
					printf("ERRO, ; Esperado!na linha %d",contLinha);
		   	        erro(fp);
				}
			}

			while ((token.cat==PR && (token.atr.CodigoPr==SE ||token.atr.CodigoPr==ENQUANTO||token.atr.CodigoPr==PARA||token.atr.CodigoPr==RETORNE))||token.cat==ID||(token.cat==SN && (token.atr.CodigoSn==ABRE_CHAVE||token.atr.CodigoSn==PONTO_E_VIGULA))) {
				cmd(fp);
			}

			/*while (token.atr.CodigoSn!=FECHA_CHAVE) {
				cmd(fp);
			}*/

			if(token.atr.CodigoSn==FECHA_CHAVE && token.cat==SN) token=analex(fp);
			else {
				printf("ERRO, } Esperado!na linha %d",contLinha);
	   	        erro(fp);
			}
		}

		else if (token.cat== SN && (token.atr.CodigoSn==PONTO_E_VIGULA || token.atr.CodigoSn==VIRGULA)) {
			while (token.cat!= SN || token.atr.CodigoSn!=PONTO_E_VIGULA) {
				if(token.atr.CodigoSn==VIRGULA && token.cat==SN) token=analex(fp);
				else{
				 printf("ERRO, , Esperado!na linha %d",contLinha);
				 erro(fp);
				}
				if(token.cat==ID) token=analex(fp);
				else {
					printf("ERRO, ID Esperado!na linha %d",contLinha);
	   	         	erro(fp);
				}
			}
			if(token.atr.CodigoSn==PONTO_E_VIGULA && token.cat==SN) token=analex(fp);
			else {
				printf("ERRO, ; Esperado!na linha %d",contLinha);
	   	        erro(fp);
			}
		}

		else {
			printf("ERRO, prog tipo invalido linha %d",contLinha);
			erro(fp);
		}


	}

	else if (token.cat==CMT) {
		 token=analex(fp);
	}

	//PRECISA? CASO NAO SEJA NENHUM DOS 3
	else {
		printf("ERRO, prog fora invalido linha %d",contLinha);
		erro(fp);
		}

}

	// ############################ CMD ############################3

void cmd(FILE* fp){

	//SE
	if((token.atr.CodigoPr==SE)&&(token.cat==PR)){
				token=analex(fp);
				if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
					token=analex(fp);
					expr(fp);
		 		 	if((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN)){
			 				token=analex(fp);
							cmd(fp);

	   						if((token.atr.CodigoPr==SENAO)&&(token.cat==PR)){
								token=analex(fp);
								cmd(fp);
							}
					}
				 	else{
					    printf("ERRO, ) Esperado!");
   				        erro(fp);
		        	}
                }
				else{
					 printf("ERRO, (  Esperado!");
	   				 erro(fp);
			  	}
  	}

  	//ENQUANTO
  	else if((token.atr.CodigoPr==ENQUANTO)&&(token.cat==PR)){

       token=analex(fp);
       if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
     		token=analex(fp);
 	 		expr(fp);

 			if((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN)){
 				token=analex(fp);
				cmd(fp);
         	}
        	else{
         	     printf("ERRO, ) Esperado!");
                 erro(fp);
            }
     	}
 		else{
	     	printf("ERRO, (  Esperado!");
		    erro(fp);
    	}
  	}

	//PARA
	else if((token.atr.CodigoPr==PARA)&&(token.cat==PR)){
           token=analex(fp);
			   if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
		   				token=analex(fp);
						if(token.cat!= SN || token.atr.CodigoSn!=PONTO_E_VIGULA) atrib(fp);
						if((token.atr.CodigoSn==PONTO_E_VIGULA)&&(token.cat==SN)) token=analex(fp);
						else{
         	                printf("ERRO, ; Esperado!");
                            erro(fp);
	                    }

						// PODE VIR UM TERMO AQUI, POIS O SINAL NÃO É OBRIGATORIO
						if(!((token.atr.CodigoSn==PONTO_E_VIGULA)&&(token.cat==SN))) expr(fp);

						if((token.atr.CodigoSn==PONTO_E_VIGULA)&&(token.cat==SN))token=analex(fp);
						else{
							 printf("ERRO, ; Esperado! na linha %d ",contLinha);
                             erro(fp);
	                    }
						if(!((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN))) atrib(fp);
						if((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN)) token=analex(fp);
						else{
							printf("ERRO, ) Esperado!");
                            erro(fp);
                        }
						cmd(fp);
						}
			else{
		 	  printf("ERRO, ( Esperado!");
              erro(fp);
            }
	}


	//RETORNE
	else if((token.atr.CodigoPr==RETORNE)&&(token.cat==PR))  {

	   	token=analex(fp);
		if(!((token.atr.CodigoSn==PONTO_E_VIGULA)&&(token.cat==SN))) expr(fp);
		if((token.atr.CodigoSn==PONTO_E_VIGULA)&&(token.cat==SN))token=analex(fp);
		else{
	 	printf("ERRO, ; Esperado! linha %d",contLinha);
            erro(fp);
        }
	}

	//ID
	else if(token.cat==ID){

		token=analex(fp);
		if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
		  	token=analex(fp);
			if(!((token.cat==SN)&&(token.atr.CodigoSn==FECHA_PARENTESE))){
  				expr(fp);
				while((token.atr.CodigoSn==VIRGULA)&&(token.cat==SN)){
					token=analex(fp);
					expr(fp);
				}
	  		}
	  		token=analex(fp);
			if((token.atr.CodigoSn==PONTO_E_VIGULA)&&(token.cat==SN)){ token=analex(fp); }
	  		else{
				printf("ERRO, ;  Esperado!na linha %d",contLinha);
           		erro(fp);
     		}
		}
		else if (token.atr.CodigoSn==ATRIBUI && token.cat==SN) {
			token=analex(fp);
			expr(fp);
			if(token.atr.CodigoSn==PONTO_E_VIGULA && token.cat==SN) token=analex(fp);
	  		else{
				printf("ERRO, ;  Esperado!na linha %d",contLinha);
           		erro(fp);
     		}
		}
	 	else{
	 	  printf("ERRO, ( Esperado!na linha %d",contLinha);
          erro(fp);
      	}
 	}

	// {CMD}
	else if((token.atr.CodigoSn==ABRE_CHAVE)&&(token.cat==SN)){
		token=analex(fp);
		while(!((token.atr.CodigoSn==FECHA_CHAVE)&&(token.cat==SN))) cmd(fp);
		if((token.atr.CodigoSn==FECHA_CHAVE)&&(token.cat==SN)) token=analex(fp);
		else{
			printf("ERRO, } Esperado! na linha %d",contLinha);
            erro(fp);
        }
	}

    else if((token.atr.CodigoSn==PONTO_E_VIGULA)&&(token.cat==SN)) token=analex(fp);

  	else {
  		printf("ERRO, Comando Esperado!na linha %d",contLinha);
    	erro(fp);
    }

}

//######################################### ATRIB ######################################



void atrib(FILE* fp){
	 if(token.cat==ID){
	 			token=analex(fp);
				if((token.atr.CodigoSn==ATRIBUI)&&(token.cat==SN)){
							token=analex(fp);
							expr(fp);
				 }
				else
				{
				  printf("ERRO, = Esperado!na linha %d",contLinha);
	 		   	  system("PAUSE");
	 		  	  exit(1);
			 	 }
				 }
				 else
				 {
				  printf("ERRO, ID Esperado!na linha %d",contLinha);
	 		   	  system("PAUSE");
	 		  	  exit(1);
			 	 }
}

// ################################### EXPR ###############################3

void expr(FILE* fp){
           exSimp(fp);
           if(op_Rel(fp)) exSimp(fp);

		   }

// ############################ EXSIMP ################################

void exSimp(FILE* fp){
	//ESSA CONDICAO E OPCIONAL, VERIFIQUE O USO DE UM ELSE CHAMANDO TERMO(fp)
	 if((token.atr.CodigoSn==SOMA||token.atr.CodigoSn==SUBTRAI)&&(token.cat==SN)) token=analex(fp);
	 termo(fp);
	 //AQUI JA É UMA OCORRENCIA OBRIGATORIA DE UM DOS 3
	 while(((token.atr.CodigoSn==SOMA)||(token.atr.CodigoSn==SUBTRAI)||(token.atr.CodigoSn==OU_LOGICO))&&(token.cat==SN)){
	 							token=analex(fp);
								termo(fp);
								}
}


// ############################# TERMO ####################################


void termo(FILE* fp){
	   fator(fp);
	   while(((token.atr.CodigoSn==MULTIPLICA)||(token.atr.CodigoSn==DIVIDE)||(token.atr.CodigoSn==E_LOGICO))&&(token.cat==SN)){

	   										token=analex(fp);
											fator(fp);
											}
}

// ############################ FATOR ############################

void fator(FILE* fp){

	 if((token.cat==CTI)|| (token.cat==CTR)|| (token.cat==CTC)|| (token.cat==CTL)) {
	    token=analex(fp);
	}
	else if((token.atr.CodigoSn==NEGA)&&(token.cat==SN)){
		token=analex(fp);
		fator(fp);
	}

	else if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
		token=analex(fp);
		expr(fp);
		if(!((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN))){
			printf("ERRO, )  Esperado!na linha %d",contLinha);
	 		erro(fp);
		}
		token=analex(fp);
	}

	else if(token.cat==ID){
		token=analex(fp);
		if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
			token=analex(fp);
			if( token.atr.CodigoSn!=FECHA_PARENTESE){
		 	   	expr(fp);
				while((token.atr.CodigoSn==VIRGULA)&&(token.cat==SN)){
					token=analex(fp);
					expr(fp);
				}
			}
			if((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN)) token=analex(fp);
			else{
				printf("ERRO, ) Esperado! na linha %d",contLinha);
	            erro(fp);
	        }
		}
	}

	else{
   		printf("ERRO, fator Esperado!na linha %d",contLinha);
        erro(fp);
	}

 }

 //################################## OP_ REL ###################################


 int op_Rel(FILE* fp){

	  if(token.cat==SN){
		 if( token.atr.CodigoSn==IGUALA || token.atr.CodigoSn==DIFERENTE || token.atr.CodigoSn==MENOR_QUE || token.atr.CodigoSn==MENOR_OU_IGUAL || token.atr.CodigoSn==MAIOR_QUE || token.atr.CodigoSn==MAIOR_OU_IGUAL ){
           token=analex(fp);
           return 1;
		   }
		   }
		   else
		   return 0;
		   return 0;
}


// #################### DECL #######################

void decl(FILE* fp){

	 while((token.atr.CodigoSn==VIRGULA)&&(token.cat==SN)){
	 			token=analex(fp);
				if(token.cat==ID){
						token=analex(fp);
						if((token.atr.CodigoSn==ABRE_PARENTESE)&&(token.cat==SN)){
										token=analex(fp);
										tipos_Param(fp);
										if((token.atr.CodigoSn==FECHA_PARENTESE)&&(token.cat==SN)) token=analex(fp);
										else{
											  printf("ERRO, ) Esperado!na linha %d",contLinha);
	 		   	                			  system("PAUSE");
	 		  	                			  exit(1);
							  				}
						}
						else
						{ printf("ERRO, ( Esperado!na linha %d",contLinha);
	 		   	          system("PAUSE");
	 		  	          exit(1);
						}
				}
				else
				        {printf("ERRO, ID Esperado!na linha %d",contLinha);
	 		   	         system("PAUSE");
	 		  	         exit(1);
						}

 }
}
