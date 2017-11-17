//### ANALISADOR SINTÁTICO ###

#include "Compilador.h"




void erro () {
	printf("\n Token Erro: %s \n",token.lexema);
	system("PAUSE");
 	exit(1);
}

void inicio () {
	token=analex();
}

void decl_Var(){
	 if(token.tipo==ID) token=analex();
	 else{
	 printf("ERRO, Tipo Esperado %d",linhas);
	 system("PAUSE");
	 exit(1);
	 }
	 }

//	 ############################# TIPO ######################################

	 void tipo(){

	 	  		if(( (token.CodPr==caracter)||(token.CodPr==inteiro)||(token.CodPr==real)||(token.CodPr==booleano) )&& (token.tipo==PR))
				     token=analex();
				else {

		   			 printf("ERRO, Tipo Esperado!%d",linhas);
	 				 system("PAUSE");
	 				 exit(1);
					 }
				/*	 }
		  else{
		  	   printf("!%d",token.tipo);
		  	   printf("ERRO, Tipo Esperado!%d",linhas);
	 		   system("PAUSE");
	 		   exit(1);
			  } */
		  }


//
int eh_Tipo(){

	 	  if(token.tipo==PR){
	 	  		if( (token.CodPr==caracter)||(token.CodPr==inteiro)||(token.CodPr==real)||(token.CodPr==booleano) )
				     return 1;
					 }
					 else return 0;
					 return 0;
}





// ################################## TIPOS_P_OPC ###############################


void tipos_p_opc(){
	if((token.tipo==PR)&&(token.CodPr==semparam))
	 	token=analex();
    else{
		tipo();
	 	if(token.tipo==ID) token=analex();
		while((token.CodSn==virgula)&&(token.tipo==SN)){
	            token=analex();
				tipo();
				if(token.tipo==ID) token=analex();
		}
	}
}


// ################################## TIPOS_PARAM ###############################


void tipos_Param(){
	if((token.tipo==PR)&&(token.CodPr==semparam)) token=analex();
    else{
	 	tipo();
 		if(token.tipo==ID){
		   token=analex();
		   while((token.CodSn==virgula)&&(token.tipo==SN)){
                token=analex();
				tipo();
				if(token.tipo==ID)
				      token=analex();
				else{
					 printf("ERRO, ID Esperado!");
		  			 erro();
				 }
			}
	   	}
	    else{
		 	printf("ERRO, ID Esperado!");
			erro();
		}
	}
}

// ###############################	PROG ####################################

void prog(){
	

	//PROTOTIPO
	 if((token.tipo==PR)&&(token.CodPr==prototipo)) {
		token=analex();

    	if((token.tipo==PR)&&(token.CodPr==semretorno)) {
		 	token=analex();

		 	if(token.tipo==ID) token=analex();
		 	else  {
		 		printf ("ERRO, ID Esperado!");
		 		erro();
		 	}

	 		if((token.tipo==SN)&&(token.CodSn==abreparenteses)) token=analex();
	 		else {
				printf("ERRO, ( Esperado!na linha %d",linhas);
		   	    erro();
			}
			tipos_p_opc();

			 if((token.tipo==SN)&&(token.CodSn==fechaparenteses)) token=analex();
			 else {
			 	printf("ERRO, ) Esperado!na linha %d",linhas);
		   	        erro();
			 }

			 while(token.tipo!= SN || token.CodSn!=pontovirgula) {

		 		if((token.CodSn==virgula)&&(token.tipo==SN)) token=analex();
		 		else
		        {printf("ERRO, , Esperado!na linha %d",linhas);
		   	         erro();
				}

				if(token.tipo==ID) token=analex();
				else
		        {printf("ERRO, ID Esperado!na linha %d",linhas);
		   	         erro();
				}

				if((token.CodSn==abreparenteses)&&(token.tipo==SN)) token=analex();
				else
				{ printf("ERRO, ( Esperado!na linha %d",linhas);
		   	         erro();
				}

				tipos_p_opc();

				if((token.CodSn==fechaparenteses)&&(token.tipo==SN)) token=analex();
				else {
					printf("ERRO, ) Esperado!na linha %d",linhas);
            			erro();
	  			}
			}

			if(token.CodSn==pontovirgula && token.tipo==SN) token=analex();
			else {
				printf("ERRO, ; Esperado!na linha %d",linhas);
	   	        erro();
			}

		}

		else {
			tipo();
			if(token.tipo==ID) token=analex();
		 	else  {
		 		printf ("ERRO, ID Esperado!");
		 		erro();
		 	}

	 		if((token.tipo==SN)&&(token.CodSn==abreparenteses)) token=analex();
			else {
				printf("ERRO, ( Esperado!na linha %d",linhas);
		   	         system("PAUSE");
		  	         exit(1);
			}

			tipos_p_opc();

	        if((token.tipo==SN)&&(token.CodSn==fechaparenteses)) token=analex();
			else {
			 	printf("ERRO, ) Esperado!na linha %d",linhas);
		   	        erro();
			} 
		 	while(token.tipo!= SN || token.CodSn!=pontovirgula) {
		 		if((token.CodSn==virgula)&&(token.tipo==SN)) token=analex();
		 		else
		        {printf("ERRO, , Esperado!na linha %d",linhas);
		   	         erro();
				}

				if(token.tipo==ID) token=analex();
				else
		        {printf("ERRO, ID Esperado!na linha %d",linhas);
		   	         erro();
				}
				if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
					token=analex();
					tipos_p_opc();
				}
				else {
				 	printf("ERRO, ( Esperado!na linha %d",linhas);
					erro();
				}
				if((token.CodSn==fechaparenteses)&&(token.tipo==SN)) token=analex();
				else
				{ 	printf("ERRO, ) Esperado!na linha %d",linhas);
					erro();
	  			}
			}
			if(token.CodSn==pontovirgula && token.tipo==SN) token=analex();
			else {
				printf("ERRO, ; Esperado!na linha %d",linhas);
	   	        erro();
			}
		}
	}

	//SEM RETORNO
	if((token.CodPr==semretorno)&&(token.tipo==PR)) {
		token=analex();
		if(token.tipo==ID) token=analex();
		else {
			printf("ERRO, ID Esperado!na linha %d",linhas);
   	        erro();
		}
		if((token.CodSn==abreparenteses)&&(token.tipo==SN)) token=analex();
		else {
			printf("ERRO, ( Esperado!na linha %d",linhas);
   	        erro();
		}
		tipos_Param();
		if(token.CodSn==fechaparenteses && token.tipo==SN) token=analex();
		else {
			printf("ERRO, ) Esperado!na linha %d",linhas);
   	        erro();
		}
		if(token.CodSn==abrechave && token.tipo==SN) token=analex();
		else {
			printf("ERRO, { Esperado!na linha %d",linhas);
   	        erro();
		}
		while (token.tipo==PR && (token.CodPr==caracter||token.CodPr==inteiro||token.CodPr==real||token.CodPr==booleano)) {
				token=analex();
				if(token.tipo==ID) token=analex();
				else {
					printf("ERRO, ID Esperado!na linha %d",linhas);
		   	        erro();
				}
				while (token.tipo == SN && token.CodSn==virgula) {
					token=analex();
					if(token.tipo==ID) token=analex();
					else {
						printf("ERRO, ID Esperado!na linha %d",linhas);
 		   	         	erro();
					}
				}
				if(token.CodSn==pontovirgula && token.tipo==SN) token=analex();
				else {
					printf("ERRO, ; Esperado!na linha %d",linhas);
		   	        erro();
				}
		}

		//while (token.tipo!= SN || token.CodSn != fechachave) {
		while ((token.tipo==PR && (token.CodPr==se ||token.CodPr==enquanto||token.CodPr==para||token.CodPr==retorne))||token.tipo==ID||(token.tipo==SN && (token.CodSn==abrechave||token.CodSn==pontovirgula))) {
			cmd();
		}

		if(token.CodSn==fechachave && token.tipo==SN) token=analex();
		else {
			printf("ERRO, } Esperado!na linha %d",linhas);
   	        erro();
		}
	}

	//TIPO
	if (token.tipo == PR && (token.CodPr==caracter||token.CodPr==inteiro||token.CodPr==real||token.CodPr==booleano)) {
		
		token=analex();
		if(token.tipo==ID) token=analex();
		else {
			printf("ERRO, ID Esperado!na linha %d",linhas);
   	         	erro();
		}
		if((token.CodSn==abreparenteses)&&(token.tipo==SN)) {
			token=analex();
			tipos_Param();
			if(token.CodSn==fechaparenteses && token.tipo==SN) token=analex();
			else {
				printf("ERRO, ) Esperado!na linha %d",linhas);
	   	        erro();
			}
			if(token.CodSn==abrechave && token.tipo==SN) token=analex();
			else {
				printf("ERRO, { Esperado!na linha %d",linhas);
	   	        erro();
			}

			while (token.tipo==PR && (token.CodSn==caracter||token.CodSn==inteiro||token.CodSn==real||token.CodSn==booleano)) {
				token=analex();
				if(token.tipo==ID) token=analex();
				else {
					printf("ERRO, ID Esperado!na linha %d",linhas);
		   	        erro();
				}
				while (token.tipo==SN && token.CodSn==virgula) {
					token=analex();
					if(token.tipo==ID) token=analex();
					else {
						printf("ERRO, ID Esperado!na linha %d",linhas);
 		   	         	erro();
					}
				}
				if(token.CodSn==pontovirgula && token.tipo==SN) token=analex();
				else {
					printf("ERRO, ; Esperado!na linha %d",linhas);
		   	        erro();
				}
			}
			
			while ((token.tipo==PR && (token.CodPr==se ||token.CodPr==enquanto||token.CodPr==para||token.CodPr==retorne))||token.tipo==ID||(token.tipo==SN && (token.CodSn==abrechave||token.CodSn==pontovirgula))) {
				cmd();
			}

			/*while (token.CodSn!=fechachave) {
				cmd();
			}*/
			
			if(token.CodSn==fechachave && token.tipo==SN) token=analex();
			else {
				printf("ERRO, } Esperado!na linha %d",linhas);
	   	        erro();
			}
		}

		else if (token.tipo== SN && (token.CodSn==pontovirgula || token.CodSn==virgula)) {
			while (token.tipo!= SN || token.CodSn!=pontovirgula) {
				if(token.CodSn==virgula && token.tipo==SN) token=analex();
				else{
				 printf("ERRO, , Esperado!na linha %d",linhas);
				 erro();
				}
				if(token.tipo==ID) token=analex();
				else {
					printf("ERRO, ID Esperado!na linha %d",linhas);
	   	         	erro();
				}
			}
			if(token.CodSn==pontovirgula && token.tipo==SN) token=analex();
			else {
				printf("ERRO, ; Esperado!na linha %d",linhas);
	   	        erro();
			}
		}

		else {
			printf("ERRO, prog tipo invalido linha %d",linhas);
			erro();
		}


	}

	//PRECISA? CASO NAO SEJA NENHUM DOS 3
	else {
		printf("ERRO, prog fora invalido linha %d",linhas);
		erro();
		}

}

/*	 			while(eh_Tipo()){

	 				  token=analex();
					  decl_Var();
					  while((token.CodSn==virgula)&&(token.tipo==SN)){
					  							  token=analex();
												  decl_Var();
												  }
					  if((token.CodSn==pontovirgula)&&(token.tipo==SN))
					  							   token=analex();
					  else {
					  	    printf("ERRO, ; Esperado!");
	 		   				system("PAUSE");
	 		  				 exit(1);
			 				  }

					 }
				 while(token.CodSn!=fechachave) cmd();
				 token=analex();

*/

	// ############################ CMD ############################3

void cmd(){

	//SE
	if((token.CodPr==se)&&(token.tipo==PR)){
				token=analex();
				if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
					token=analex();
					expr();
		 		 	if((token.CodSn==fechaparenteses)&&(token.tipo==SN)){
			 				token=analex();
							cmd();

	   						if((token.CodPr==senao)&&(token.tipo==PR)){
								token=analex();
								cmd();
							}
					}
				 	else{
					    printf("ERRO, ) Esperado!");
   				        erro();
		        	}
                }
				else{
					 printf("ERRO, (  Esperado!");
	   				 erro();
			  	}
  	}

  	//ENQUANTO
  	else if((token.CodPr==enquanto)&&(token.tipo==PR)){

       token=analex();
       if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
     		token=analex();
 	 		expr();

 			if((token.CodSn==fechaparenteses)&&(token.tipo==SN)){
 				token=analex();
				cmd();
         	}
        	else{
         	     printf("ERRO, ) Esperado!");
                 erro();
            }
     	}
 		else{
	     	printf("ERRO, (  Esperado!");
		    erro();
    	}
  	}

	//PARA
	else if((token.CodPr==para)&&(token.tipo==PR)){
           token=analex();
			   if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
		   				token=analex();
						if(token.tipo!= SN || token.CodSn!=pontovirgula) atrib();
						if((token.CodSn==pontovirgula)&&(token.tipo==SN)) token=analex();
						else{
         	                printf("ERRO, ; Esperado!");
                            erro();
	                    }

						// PODE VIR UM TERMO AQUI, POIS O SINAL NÃO É OBRIGATORIO
						if(!((token.CodSn==pontovirgula)&&(token.tipo==SN))) expr();

						if((token.CodSn==pontovirgula)&&(token.tipo==SN))token=analex();
						else{
							 printf("ERRO, ; Esperado! na linha %d ",linhas);
                             erro();
	                    }
						if(!((token.CodSn==fechaparenteses)&&(token.tipo==SN))) atrib();
						if((token.CodSn==fechaparenteses)&&(token.tipo==SN)) token=analex();
						else{
							printf("ERRO, ) Esperado!");
                            erro();
                        }
						cmd();
						}
			else{
		 	  printf("ERRO, ( Esperado!");
              erro();
            }
	}


	//RETORNE
	else if((token.CodPr==retorne)&&(token.tipo==PR))  {

	   	token=analex();
		if(!((token.CodSn==pontovirgula)&&(token.tipo==SN))) expr();
		if((token.CodSn==pontovirgula)&&(token.tipo==SN))token=analex();
		else{
	 	printf("ERRO, ; Esperado! linha %d",linhas);
            erro();
        }
	}

	//ID
	else if(token.tipo==ID){

		token=analex();
		if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
		  	token=analex();
			if(!((token.tipo==SN)&&(token.CodSn==fechaparenteses))){
  				expr();
				while((token.CodSn==virgula)&&(token.tipo==SN)){
					token=analex();
					expr();
				}
	  		}
	  		token=analex();
			if((token.CodSn==pontovirgula)&&(token.tipo==SN)){ token=analex(); }
	  		else{
				printf("ERRO, ;  Esperado!na linha %d",linhas);
           		erro();
     		}
		}
		else if (token.CodSn==igual && token.tipo==SN) {
			token=analex();
			expr();
			if(token.CodSn==pontovirgula && token.tipo==SN) token=analex();
	  		else{
				printf("ERRO, ;  Esperado!na linha %d",linhas);
           		erro();
     		}
		}
	 	else{
	 	  printf("ERRO, ( Esperado!na linha %d",linhas);
          erro();
      	}
 	}

	// {CMD}
	else if((token.CodSn==abrechave)&&(token.tipo==SN)){
		token=analex();
		while(!((token.CodSn==fechachave)&&(token.tipo==SN))) cmd();
		if((token.CodSn==fechachave)&&(token.tipo==SN)) token=analex();
		else{
			printf("ERRO, } Esperado! na linha %d",linhas);
            erro();
        }
	}

    else if((token.CodSn==pontovirgula)&&(token.tipo==SN)) token=analex();

  	else {
  		printf("ERRO, Comando Esperado!na linha %d",linhas);
    	erro();
    }

}

//######################################### ATRIB ######################################



void atrib(){
	 if(token.tipo==ID){
	 			token=analex();
				if((token.CodSn==igual)&&(token.tipo==SN)){
							token=analex();
							expr();
				 }
				else
				{
				  printf("ERRO, = Esperado!na linha %d",linhas);
	 		   	  system("PAUSE");
	 		  	  exit(1);
			 	 }
				 }
				 else
				 {
				  printf("ERRO, ID Esperado!na linha %d",linhas);
	 		   	  system("PAUSE");
	 		  	  exit(1);
			 	 }
}

// ################################### EXPR ###############################3

void expr(){
           expr_Simp();
           if(op_Rel()) expr_Simp();

		   }

// ############################ EXPR_SIMP ################################

void expr_Simp(){
	//ESSA CONDICAO E OPCIONAL, VERIFIQUE O USO DE UM ELSE CHAMANDO TERMO()
	 if((token.CodSn==soma||token.CodSn==subtrai)&&(token.tipo==SN)) token=analex();
	 termo();
	 //AQUI JA É UMA OCORRENCIA OBRIGATORIA DE UM DOS 3
	 while(((token.CodSn==soma)||(token.CodSn==subtrai)||(token.CodSn==alternativa))&&(token.tipo==SN)){
	 							token=analex();
								termo();
								}
}


// ############################# TERMO ####################################


void termo(){
	   fator();
	   while(((token.CodSn==multiplica)||(token.CodSn==divisao)||(token.CodSn==ecomercs))&&(token.tipo==SN)){

	   										token=analex();
											fator();
											}
}

// ############################ FATOR ############################

void fator(){

	 if((token.tipo==CTI)|| (token.tipo==CTR)|| (token.tipo==CTC)) {
	    token=analex();
	}
	else if((token.CodSn==not)&&(token.tipo==SN)){
		token=analex();
		fator();
	}

	else if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
		token=analex();
		expr();
		if(!((token.CodSn==fechaparenteses)&&(token.tipo==SN))){
			printf("ERRO, )  Esperado!na linha %d",linhas);
	 		erro();
		}
		token=analex();
	}

	else if(token.tipo==ID){
		token=analex();
		if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
			token=analex();
			if( token.CodSn!=fechaparenteses){
		 	   	expr();
				while((token.CodSn==virgula)&&(token.tipo==SN)){
					token=analex();
					expr();
				}
			}
			if((token.CodSn==fechaparenteses)&&(token.tipo==SN)) token=analex();
			else{
				printf("ERRO, ) Esperado! na linha %d",linhas);
	            erro();
	        }
		}
	}

	else{
   		printf("ERRO, fator Esperado!na linha %d",linhas);
        erro();
	}

 }

 //################################## OP_ REL ###################################


 int op_Rel(){

	  if(token.tipo==SN){
		 if( token.CodSn==igualigual || token.CodSn==notigual || token.CodSn==menorque || token.CodSn==menorigual || token.CodSn==maiorque || token.CodSn==maiorigual ){
           token=analex();
           return 1;
		   }
		   }
		   else
		   return 0;
		   return 0;
}




// ######################### PROG ####################################

/*


void prog(){

	 token=analex();

	 while( (( token.CodPr==semretorno)&&(token.tipo==PR)) || (eh_Tipo()) ){

      if(eh_Tipo())
	 {		   token=analex();

	 		   if (token.tipo==ID){
			   	  			token=analex();
							if((token.CodSn==virgula)&&(token.tipo==SN)){
													 while((token.CodSn==virgula)&&(token.tipo==SN)){

													 				token=analex();

																	 decl_Var();

													 }
	 												 if((token.CodSn==pontovirgula)&&(token.tipo==SN)) token=analex();
	 												 else{
													 	  printf("ERRO, ; Esperado!na linha %d",linhas);
	 		   	                						  system("PAUSE");
	 		  	                						  exit(1);
							  							  }
					        }
					        else
					            if((token.CodSn==abreparenteses)&&(token.tipo==SN)){

												token=analex();
												tipos_Param();

												if((token.CodSn==fechaparenteses)&&(token.tipo==SN)) token=analex();
												else{
												    printf("ERRO, ) Esperado!na linha %d",linhas);
	 		   	                						  system("PAUSE");
	 		  	                						  exit(1);
							  						 }
												if((token.CodSn==abrechave)&&(token.tipo==SN)){

																		   token=analex();

																		   func();
																		   }
																		   else{
									   									   		decl();
									   											if((token.CodSn==pontovirgula)&&(token.tipo==SN)) token=analex();
									   												else{
																						 printf("ERRO, ; Esperado!na linha %d",linhas);
	 		   	                														 system("PAUSE");
	 		  	                					 									 exit(1);
							  						 									 }
																						 }


									   }
									   else{

									   		if((token.CodSn==pontovirgula)&&(token.tipo==SN)) token=analex();
									   		else{

												    printf("ERRO, ; ou ( Esperado!na linha %d",linhas);
	 		   	                					system("PAUSE");
	 		  	                					 exit(1);
							  						 }

													 }
						 }else{
						 	   printf("ERRO, ID Esperado!na linha %d",linhas);
	 		   	               system("PAUSE");
	 		  	               exit(1);
							  						 }


													 }else{




				 token=analex();

	 		   if (token.tipo==ID){
			   	  			token=analex();


					            if((token.CodSn==abreparenteses)&&(token.tipo==SN)){

												token=analex();
												tipos_Param();

												if((token.CodSn==fechaparenteses)&&(token.tipo==SN)) token=analex();
												else{
												    printf("ERRO, ) Esperado!na linha %d",linhas);
	 		   	                						  system("PAUSE");
	 		  	                						  exit(1);
							  						 }
												if((token.CodSn==abrechave)&&(token.tipo==SN)){

																		   token=analex();

																		   func();
																		   }
																		   else{
									   									   		decl();
									   											if((token.CodSn==pontovirgula)&&(token.tipo==SN)) token=analex();
									   												else{
																						 printf("ERRO, ; Esperado!na linha %d",linhas);
	 		   	                														 system("PAUSE");
	 		  	                					 									 exit(1);
							  						 									 }
																						 }


									   }
									   else{
												    printf("ERRO,   Tipo Esperado na linha %d ",linhas);
	 		   	                					system("PAUSE");
	 		  	                					 exit(1);


													 }
						 }else{
						 	   printf("ERRO, ID Esperado!na linha %d",linhas);
	 		   	               system("PAUSE");
	 		  	               exit(1);
							  						 }
													 }
	 }


}
*/


// #################### DECL #######################

void decl(){

	 while((token.CodSn==virgula)&&(token.tipo==SN)){
	 			token=analex();
				if(token.tipo==ID){
						token=analex();
						if((token.CodSn==abreparenteses)&&(token.tipo==SN)){
										token=analex();
										tipos_Param();
										if((token.CodSn==fechaparenteses)&&(token.tipo==SN)) token=analex();
										else{
											  printf("ERRO, ) Esperado!na linha %d",linhas);
	 		   	                			  system("PAUSE");
	 		  	                			  exit(1);
							  				}
						}
						else
						{ printf("ERRO, ( Esperado!na linha %d",linhas);
	 		   	          system("PAUSE");
	 		  	          exit(1);
						}
				}
				else
				        {printf("ERRO, ID Esperado!na linha %d",linhas);
	 		   	         system("PAUSE");
	 		  	         exit(1);
						}

 }
}
