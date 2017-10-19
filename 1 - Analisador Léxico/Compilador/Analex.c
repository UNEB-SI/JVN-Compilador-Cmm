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

                if(EH_ESPACO(c))
                {
                    //espaço é ' ', \n
                    estado = 0;
                    c = fgetc(fd);
                    coluna++;
                    continue;
                }
                if(c == '\t')
                {
                    estado = 0;
                    c = fgetc(fd);
                    linha++;
                    continue;
                }
                else if(EH_DIGITO(c))
                {
                    estado = 18;
                    continue;
                }
                else if(EH_LETRA(c))
                {
                    estado = 23;
                    continue;
                }
                else if(EH_LETRA(c))
                {
                    estado = 23;
                    continue;
                }/*=====INÍCIO SINAIS=====*/
                else if(c == '\'')
                {
                    estado = 1;
                    continue;
                }
                else if(c == '\"')
                {
                    estado = 10;
                    continue;
                }
                else if(c == ';')
                {
                    estado = 25;
                    continue;
                }
                else if(c == '-')
                {
                    estado = 26;
                    continue;
                }
                else if(c == '+')
                {
                    estado = 27;
                    continue;
                }
                else if(c == '{')
                {
                    estado = 28;
                    continue;
                }
                else if(c == '}')
                {
                    estado = 29;
                    continue;
                }
                else if(c == '(')
                {
                    estado = 30;
                    continue;
                }
                else if(c == ')')
                {
                    estado = 31;
                    continue;
                }
                else if(c == '*')
                {
                    estado = 32;
                    continue;
                }
                else if(c == ',')
                {
                    estado = 33;
                    continue;
                }
                else if(c == '│')
                {
                    estado = 33;
                    continue;
                }
                else if(c == '&')
                {
                    estado = 36;
                    continue;
                }
                else if(c == '=')
                {
                    estado = 38;
                    continue;
                }
                else if(c == '!')
                {
                    estado = 41;
                    continue;
                }
                else if(c == '>')
                {
                    estado = 44;
                    continue;
                }
                else if(c == '<')
                {
                    estado = 47;
                    continue;
                }
                else if(c == '/')
                {
                    estado = 51;
                    continue;
                }/*=====FIM SINAIS=====*/ 
                else if( (estado == 0) && (!(EH_ESPACO(c)) ││ !(c=='\t')) )
                 {
                     printf("ERRO 0: Caractere '%c' não era esperado na linha %d coluna %d!", c, linha, coluna);
                     exit(1);  
                 }

                break;
            case 1:

                c = fgetc(fd);
                coluna++;

                if(c == '\\')
                {
                    estado = 3;
                    continue;
                }
                else if(c == 'ch') //Quem será ch?
                {
                    estado = 2;
                    continue;
                }

                break;
            case 2:

                c = fgetc(fd);
                coluna++;

                if(c == '\'')
                {
                    estado = 6;
                    continue;
                }

                break;
            case 3:
            
                c = fgetc(fd);
                coluna++;

                if(c == 'n')
                {
                    estado = 4;
                    continue;
                }
                else if(c == '0')
                {
                    estado = 5;
                    continue;
                }
                else if(c == '\'')
                {
                    estado = 7;
                    continue;
                }

                break;
            case 4:
            
                c = fgetc(fd);
                coluna++;

                if(c == '\'')
                {
                    estado = 6;
                    continue;
                }
                
                break;
            case 5:
            
                c = fgetc(fd);
                coluna++;

                if(c == '\'')
                {
                    estado = 6;
                    continue;
                }
                
                break;
            case 6:
                /*
                    ESTADO DE ACEITAÇÃO
                    CARACCON
                */
                
                break;
            case 7:

                if(c == '\'')
                {
                    estado = 8;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 9;
                    continue;
                }
                
                break;
            case 8:
                /*
                    ESTADO DE ACEITAÇÃO
                    APÓSTROFO
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 9:
                /*
                    ESTADO DE ACEITAÇÃO
                    BARRA INVERTIDA
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 10:
            
                c = fgetc(fd);
                coluna++;

                if(c == 'ch') //Quem será ch?
                {
                    estado = 11;
                    continue;
                }
                
                break;
            case 11:
            
                c = fgetc(fd);
                coluna++;

                if(c == 'ch') //Quem será ch?
                {
                    estado = 11;
                    continue;
                }
                else if(c == '\"')
                {
                    estado = 12;
                    continue;
                }
                else if(c == '/')
                {
                    estado = 13;
                    continue;
                }
                
                break;
            case 12:
                /*
                    ESTADO DE ACEITAÇÃO
                    CADEIACON
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 13:
            
                c = fgetc(fd);
                coluna++;

                if(c == '\"')
                {
                    estado = 14;
                    continue;
                }
                else if(c == 'n')
                {
                    estado = 15;
                    continue;
                }
                
                break;
            case 14:
            
                c = fgetc(fd);
                coluna++;

                if(c == '\"')
                {
                    estado = 16;
                    continue;
                }
                
                break;
            case 15:
            
                c = fgetc(fd);
                coluna++;

                if(c == '\"')
                {
                    estado = 17;
                    continue;
                }
                
                break;
            case 16:
                /*
                    ESTADO DE ACEITAÇÃO
                    ASPAS DUPLAS
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 17:
                /*
                    ESTADO DE ACEITAÇÃO
                    NEW LINE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 18:
            
                c = fgetc(fd);
                coluna++;

                if(EH_DIGITO(c))
                {
                    estado = 18;
                    continue;
                }
                else if('.')
                {
                    estado = 20;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 19;
                    continue;
                }
                
                break;
            case 19:
                /*
                    ESTADO DE ACEITAÇÃO
                    INTCON
                */
            
                c = fgetc(fd);
                coluna++;

                t->cat = INTEIRO;
                t->lexema[j++] = c;
                t->valorInteiro = atoi(t->lexema);
                
                return t;
                
                break;
            case 20:
            
                c = fgetc(fd);
                coluna++;

                if(EH_DIGITO(c))
                {
                    estado = 21;
                    continue;
                }
                
                break;
            case 21:  
            
                c = fgetc(fd);
                coluna++;              

                if(EH_DIGITO(c))
                {
                    estado = 21;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 22;
                    continue;
                }
                
                break;
            case 22:
                /*
                    ESTADO DE ACEITAÇÃO
                    REALCON
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 23:
            
                c = fgetc(fd);
                coluna++;

                if(EH_ALFA(c))
                {
                    estado = 23;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 24;
                    continue;
                }
                
                break;
            case 24:
                /*
                    ESTADO DE ACEITAÇÃO
                    ID
                */

                c = fgetc(fd);
                coluna++;
                
                t->cat = ID;
                t->lexema[j++] = c;
                t->CodigoPr = EH_PALAVRA_RESERVADA(c);
                A_IGUAL_A_B(t->lexema, TAB_PR[EH_PALAVRA_RESERVADA(c)]);
                         
                return token;
                
                break;
            case 25:
                /*
                    ESTADO DE ACEITAÇÃO
                    PONTO E VÍGULA
                */
            
                c = fgetc(fd);
                coluna++;

                t->cat = SINAL;
                t->lexema[0] = ';';
                t->lexema[1] = '\0';
                t->CodSinal = DIVIDE;                  
                return t;
                
                break;
            case 26:
                /*
                    ESTADO DE ACEITAÇÃO
                    SUBTRAI
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 27:
                /*
                    ESTADO DE ACEITAÇÃO
                    SOMA
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 28:
                /*
                    ESTADO DE ACEITAÇÃO
                    ABRE CHAVE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 29:
                /*
                    ESTADO DE ACEITAÇÃO
                    FECHA CHAVE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 30:
                /*
                    ESTADO DE ACEITAÇÃO
                    ABRE PARENTESE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 31:
                /*
                    ESTADO DE ACEITAÇÃO
                    FECHA PARENTESE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 32:
                /*
                    ESTADO DE ACEITAÇÃO
                    MULTIPLICA
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 33:
                /*
                    ESTADO DE ACEITAÇÃO
                    VÍRGULA
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 34:
            
                c = fgetc(fd);
                coluna++;

                if(c == '│')
                {
                    estado = 35;
                    continue;
                }
                
                break;
            case 35:
                /*
                    ESTADO DE ACEITAÇÃO
                    OU LÓGICO
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 36:
            
                c = fgetc(fd);
                coluna++;

                if(c == '&')
                {
                    estado = 37;
                    continue;
                }
                
                break;
            case 37:
                /*
                    ESTADO DE ACEITAÇÃO
                    E LÓGICO
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 38:
            
                c = fgetc(fd);
                coluna++;

                if(c == '=')
                {
                    estado = 39;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 40;
                    continue;
                }
                
                break;
            case 39:
                /*
                    ESTADO DE ACEITAÇÃO
                    IGUALA
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 40:
                /*
                    ESTADO DE ACEITAÇÃO
                    ATRIBUI
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 41:
            
                c = fgetc(fd);
                coluna++;

                if(c == '=')
                {
                    estado = 42;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 43;
                    continue;
                }
                
                break;
            case 42:
                /*
                    ESTADO DE ACEITAÇÃO
                    DIFERENTE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 43:
                /*
                    ESTADO DE ACEITAÇÃO
                    NEGA
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 44:
            
                c = fgetc(fd);
                coluna++;

                if(c == '=')
                {
                    estado = 45;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 46;
                    continue;
                }
                
                break;
            case 45:
                /*
                    ESTADO DE ACEITAÇÃO
                    MAIOR OU IGUAL
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 46:
                /*
                    ESTADO DE ACEITAÇÃO
                    MAIOR QUE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 47:
            
                c = fgetc(fd);
                coluna++;

                if(c == '=')
                {
                    estado = 48;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 49;
                    continue;
                }
                
                break;
            case 48:
                /*
                    ESTADO DE ACEITAÇÃO
                    MENOR OU IGUAL
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 49:
                /*
                    ESTADO DE ACEITAÇÃO
                    MAIOR QUE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?
                
                break;
            case 50:

                if(c == 'EOI') // COMO IDENTIFICAR EOI?
                {
                    estado = 6;
                    continue;
                }
            
                c = fgetc(fd);
                coluna++;
                
                break;
            case 51:
            
                c = fgetc(fd);
                coluna++;

                if(c == '*')
                {
                    estado = 53;
                    continue;
                }
                else
                {
                    //outro*
                    estado = 52;
                    continue;
                }
                
                break;
            case 52:
                /*
                    ESTADO DE ACEITAÇÃO
                    DIVIDE
                */
            
                c = fgetc(fd);
                coluna++;

                t->cat = SINAL;
                t->lexema[j++] = '/';
                t->CodSinal = DIVIDE;                  
                return t;
                
                break;
            case 53:
            
                c = fgetc(fd);
                coluna++;

                if(EH_LETRA(c) ││ EH_DIGITO(c))
                {
                    estado = 54;
                    continue;
                }
                
                break;
            case 54:
            
                c = fgetc(fd);
                coluna++;

                if(EH_LETRA(c) ││ EH_DIGITO(c))
                {
                    estado = 54;
                    continue;
                }
                else if(c == '*')
                {
                    estado = 55;
                    continue;
                }
                
                break;
            case 55:
            
                c = fgetc(fd);
                coluna++;

                if(EH_LETRA(c) ││ EH_DIGITO(c))
                {
                    estado = 54;
                    continue;
                }
                else if(c == '*')
                {
                    estado = 55;
                    continue;
                }
                else if(c == '/')
                {
                    estado = 56;
                    continue;
                }

                break;
            case 56:
                /*
                    ESTADO DE ACEITAÇÃO
                    DIVIDE
                */
            
                c = fgetc(fd);
                coluna++;

                //O QUE FAZER?

                break;
        }
    }

    return NULL;
}
