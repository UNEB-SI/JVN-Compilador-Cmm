#include "analex.h"

int coluna=1;
int linha=1;

char TAB_LIT[100][400];
int cont_literal=-1;

int EH_PALAVRA_RESERVADA(char palavra[]){
    int i;  
    
    for(i=0;i<11;i++){
        if (!strcmp(palavra,TAB_PR[i]))
        { 
            return i;
        }
    }

    return -1;
}
int EH_SINAL(char palavra[]){
    int i;  
    
    for(i=0;i<21;i++){
        if (!strcmp(palavra,TAB_SN[i]))
        { 
            return i;
        }
    }

    return 0;
}
#define EH_LETRA(x)((x>='a')&&(x<='z'))||((x>='A')&&(x<='Z'))
#define EH_DIGITO(x)(x>='0')&&(x<='9')
#define EH_ESPACO(x)(x==' ')||(x=='\n')
#define EH_ALFA(x)EH_LETRA(x)||EH_DIGITO(x)||(x=='_')
#define A_IGUAL_A_B(A,B) (strcmp((char *)A,(char *)B) == 0)


TOKEN * analex(FILE * fd)
{
    int estado = 0;
    static char c = '\0';
    int i = 0;
    int j = 0;
    int k = 0;
    TOKEN * t = (TOKEN *) malloc( sizeof(TOKEN) );

    if(c == '\0')
    {
        c = fgetc(fd);
    }

    while(1){

        if(feof(fd))
        {
             break;
        }

        switch(estado)
        {
            case 0:
                //espaço é ' ', \n
                if(EH_ESPACO(c)) {estado = 0; c = fgetc(fd); coluna++; continue; }
                else if(c == '\t') {estado = 0; c = fgetc(fd); linha++; continue; } 
                else if(EH_DIGITO(c)) {estado = 20; continue; } 
                else if(EH_LETRA(c)) {estado = 25; continue; }
                /*=====INÍCIO SINAIS=====*/ 
                else if(c == '/') {estado = 1; continue; }
                else if(c == '\'') {estado = 6; continue; } 
                else if(c == '\"') {estado = 17; continue; } 
                else if(c == ';') {estado = 27; continue; } 
                else if(c == '-') {estado = 28; continue; } 
                else if(c == '+') {estado = 29; continue; } 
                else if(c == '{') {estado = 30; continue; } 
                else if(c == '}') {estado = 31; continue; } 
                else if(c == '(') {estado = 32; continue; } 
                else if(c == ')') {estado = 33; continue; } 
                else if(c == '*') {estado = 34; continue; } 
                else if(c == ',') {estado = 35; continue; } 
                else if(c == '│') {estado = 36; continue; } 
                else if(c == '&') {estado = 38; continue; } 
                else if(c == '=') {estado = 40; continue; } 
                else if(c == '!') {estado = 43; continue; } 
                else if(c == '>') {estado = 46; continue; } 
                else if(c == '<') {estado = 49; continue; } 
                /*=====FIM SINAIS=====*/ 
                else if( (estado == 0) && (!(EH_ESPACO(c)) ││ !(c=='\t')) )
                {
                     printf("ERRO 0: Caractere '%c' não era esperado na linha %d coluna %d!", c, linha, coluna);
                     exit(1);  
                }

                break;
            case 1:

                if(c == '*')
                {
                    estado = 3;
                    continue;
                }
                else
                {
                    estado = 2;
                    continue;
                }

                break;
            case 2:
                /*
                    ESTADO DE ACEITAÇÃO
                    DIVIDE
                */

                break;
            case 3:

                if(c == QUALQUER_COISA)
                {
                    estado = 4;
                    continue;
                }


                break;
            case 4:

                if(c == QUALQUER_COISA)
                {
                    estado = 4;
                    continue;
                }
                else if(c == '*')
                {
                    estado = 5;
                    continue;
                }
                
                break;
            case 5:

                if(c == QUALQUER_COISA)
                {
                    estado = 4;
                    continue;
                }
                else if(c == '/')
                {
                    estado = 0;
                    continue;
                }
            
                break;
            case 6:

                if(isprint(c) && c != '\\' && c != '\'')
                {
                    estado = 7;
                    continue;
                }
                else if(c == '/')
                {
                    estado = 8;
                    continue;
                }

                break;
            case 7:

                break;
            case 8:

                break;
            case 9:
                /*
                    ESTADO DE ACEITAÇÃO
                    CARACCON
                */
                
                break;
            case 10:
            
                break;
            case 11:
            
                break;
            case 12:
                
                break;
            case 13:
                /*
                    ESTADO DE ACEITAÇÃO
                    CARACCON
                */
            
                break;
            case 14:
                /*
                    ESTADO DE ACEITAÇÃO
                    CARACCON
                */
            
                break;
            case 15:
                /*
                    ESTADO DE ACEITAÇÃO
                    APÓSTROFO
                */
            
                break;
            case 16:
                /*
                    ESTADO DE ACEITAÇÃO
                    BARRA INVERTIDA
                */
                
                break;
            case 17:

                if(isprint(c) && c != '\"' && c != '\n')
                {
                    estado = 7;
                    continue;
                }
                else if(c == '/')
                {
                    estado = 8;
                    continue;
                }
            
                
                break;
            case 18:
            
                break;
            case 19:
                /*
                    ESTADO DE ACEITAÇÃO
                    CADEIACON
                */
                
                break;
            case 20:
                            
                break;
            case 21:
                /*
                    ESTADO DE ACEITAÇÃO
                    INTCON
                */
            
                break;
            case 22:
                
                break;
            case 23:
            
                break;
            case 24:
                /*
                    ESTADO DE ACEITAÇÃO
                    REALCON
                */
               
                break;
            case 25:
                
                break;
            case 26:
                /*
                    ESTADO DE ACEITAÇÃO
                    ID
                */
                
                break;
            case 27:
                /*
                    ESTADO DE ACEITAÇÃO
                    PONTO E VÍRGULA
                */
                
                break;
            case 28:
                /*
                    ESTADO DE ACEITAÇÃO
                    SUBTRAI
                */
                
                break;
            case 29:
                /*
                    ESTADO DE ACEITAÇÃO
                    SOMA
                */
                
                break;
            case 30:
                /*
                    ESTADO DE ACEITAÇÃO
                    ABRE CHAVE
                */             

                break;
            case 31:
                /*
                    ESTADO DE ACEITAÇÃO
                    FECHA CHAVE
                */
                
                break;
            case 32:   
                /*
                    ESTADO DE ACEITAÇÃO
                    ABRE PARENTESE
                */

                break;
            case 33:
                /*
                    ESTADO DE ACEITAÇÃO
                    FECHA PARENTESE
                */
                
                break;
            case 34:
                /*
                    ESTADO DE ACEITAÇÃO
                    MULTIPLICA
                */
                
                break;
            case 35:
                /*
                    ESTADO DE ACEITAÇÃO
                    VÍRGULA
                */
                
                break;
            case 36:
            
                break;
            case 37:
                /*
                    ESTADO DE ACEITAÇÃO
                    OU LÓGICO
                */
                
                break;
            case 38:
            
                break;
            case 39:
                /*
                    ESTADO DE ACEITAÇÃO
                    E LÓGICO
                */
                
                break;
            case 40:
                
                break;
            case 41:
                /*
                    ESTADO DE ACEITAÇÃO
                    IGUALA
                */
            
                break;
            case 42:
                /*
                    ESTADO DE ACEITAÇÃO
                    ATRIBUI
                */
                
                break;
            case 43:
                
                break;
            case 44:
                /*
                    ESTADO DE ACEITAÇÃO
                    DIFERENTE
                */
            
                break;
            case 45:
                /*
                    ESTADO DE ACEITAÇÃO
                    NEGA
                */
                
                break;
            case 46:
                
                break;
            case 47:
                /*
                    ESTADO DE ACEITAÇÃO
                    MAIOR OU IGUAL
                */
                
                break;
            case 48:
                /*
                    ESTADO DE ACEITAÇÃO
                    MAIOR QUE
                */
                
                break;
            case 49:
                
                break;
            case 50:
                /*
                    ESTADO DE ACEITAÇÃO
                    MENOR OU IGUAL
                */
                
                break;
            case 51:
                /*
                    ESTADO DE ACEITAÇÃO
                    MENOR QUE
                */
            
                break;
            case 52:
                /*
                    ESTADO DE ACEITAÇÃO
                    EOF
                */
                
                break;
        }
    }

    return NULL;
}
