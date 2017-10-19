#include "analex.h"

int coluna=1;
int linha=1;

char TAB_LIT[100][400];
int cont_literal=-1;

int EH_PALAVRA_RESERVADA(char palavra[]){
    int i;  
    
    for(i=0;i<30;i++){
        if (!strcmp(palavra,TAB_PR[i]))
        { 
            return i;
        }
    }

    return -1;
}
int EH_SINAL(char palavra[]){
    int i;  
    
    for(i=0;i<30;i++){
        if (!strcmp(palavra,TAB_SN[i]))
        { 
            return i;
        }
    }

    return 0;
}
#define EH_LETRA(x)((x>='a')&&(x<='z'))||((x>='A')&&(x<='Z'))
#define EH_DIGITO(x)(x>='0')&&(x<='9')
#define EH_ESPACO(x)(x==' ')||(x=='\r')||(x=='\n')||(x=='\t')
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
                    estado = 0;
                    c = fgetc(fd);
                    coluna++;
                    continue;
                }

                if(c == '/')
                {
                    estado = 1;
                    continue;
                }

                if(c == '\'')
                {
                    estado = 6;
                    continue;
                }

                if(c == '\"')
                {
                    estado = 21;
                    continue;
                }

                if(EH_DIGITO(c))
                {
                    estado = 14;
                    continue;
                }

                if(EH_LETRA(c))
                {
                   estado = 20;
                   continue;
                }

                if(EH_SINAL(c))
                {
                    t->tipo = SINAL;
                    t->codigoSinal = i;  //este codigo é real
                    t->lexema[0]= c;
                    t->lexema[1]= '\0';

                    estado = 14;
                }

             // testa chaves de um unico cacactere
             for(i = 0; i < SN_SIZE; i++)
             {
                  //ja identificou como um sinal.. vai para o estado de aceitação..
                  if(c == TAB_SN[i])
                  {

                       t->tipo = SINAL;
                       t->codigoSinal = i;  //este codigo é real
                       t->lexema[0]= c;
                       t->lexema[1]= '\0';

                       estado = 14;
                  }
             }

             for(i = 0; i < CH_ESP_SIZE; i++)
             {
                  if(c == chavesEspeciais[i])
                  {
                       t->tipo = SINAL;
                       t->codigoSinal = i; //este codigo é apenas o indice do sinal, terá que ser convertido
                       t->lexema[0]= c;
                       t->lexema[1]= '\0';

                       estado = 15;
                  }
             }

             if(c == '&')
             {
                  estado = 17;
             }

             if(c == '|')
             {
                  estado = 19;
             }


             if( (estado == 0) && !(EH_ESPACO(c)) )
             {
                 printf("ERRO 0: Caractere '%c' não esperado na linha %d coluna 5d!", c, linha, coluna);
                 exit(1);
             }

            break;
            case 1:
                 //recebeu uma barra, aqui é o estado final de barra também
                 //corrigir no automato..

                 c = fgetc(fd);
                 coluna++;

                 if(c == '*')
                 {
                      estado = 2;
                 }
                 else
                 {
                     //se o proximo não for asterisco, este ja é o estado de aceitação
                      t->tipo = SINAL;
                      t->lexema[0] = '/';
                      t->lexema[1] = '\0';
                      t->codigoSinal = DIVIDIDO;
                      return t;
                 }

            break;
            case 2:

                 c = fgetc(fd);
                 coluna++;

                 if(c == '*')
                 {
                      estado = 3;
                 }
                 else
                 {
                      estado = 2;
                 }

            break;
            case 3:

                 c = fgetc(fd);
                 coluna++;

                 //manda para o estado inicial e consome um caracter.
                 if(c == '/')
                 {
                      estado = 0;
                      c = fgetc(fd);

                 }
                 else if(c == '*')
                 {
                      estado = 3;
                 }
                 else
                 {
                     estado = 2;
                 }

            break;
            case 4:

                 //estado de aceitação. ID

                 t->lexema[j++] = c;
                 c = fgetc(fd);
                 coluna++;

                 if(EH_ALFA(c))
                 {
                      estado = 4;
                 }
                 else
                 {

                     //TODO: verificar se é palavra reservada e colocar na tabela de palavras...

                     t->tipo = ID;
                     //t->lexema[j++] = c; para não pegar o char de outro t
                     t->lexema[j++] = '\0';


                     for(i = 0; i < PR_SIZE; i++)
                     {
                          if( A_IGUAL_A_B(t->lexema, Tab_PR[i]) )
                          {
                                t->tipo = PALAVRA;
                                t->codigoPR = i;
                          }
                     }



                     return t;
                 }

            break;
            case 5: // ACEITAÇÃO .. INTCON


                 t->lexema[j++] = c;
                 c = fgetc(fd);
                 coluna++;

                 if(EH_NUMERO(c))
                 {
                      estado = 5;
                 }
                 else if(c == '.')
                 {
                      estado = 6;
                 }
                 else
                 {


                     t->tipo = INTCON;
                     t->lexema[j++] = '\0';
                     t->valorInteiro = atoi(t->lexema);
                     return t;

                 }

            break;
            case 6:

                 t->lexema[j++] = c;
                 c = fgetc(fd);
                 coluna++;

                 if(EH_NUMERO(c))
                 {
                     estado = 7;
                 }
                 else
                 {
                     printf("ERRO 6: Caractere '%c' não esperado na linha %d coluna 5d!", c, linha, coluna);
                     exit(1);
                 }

            break;
            case 7: // ACEITAÇÃO ..

                 if(EH_NUMERO(c))
                 {
                      estado = 7;
                 }
                 else
                 {

                     t->tipo = REALCON;
                     t->lexema[j++] = '\0';
                     t->valorReal = atof(t->lexema);
                     return t;

                 }

                 t->lexema[j++] = c;
                 c = fgetc(fd);
                 coluna++;

            break;

            case 8:

                 //t->lexema[j++] = c; desprezando as aspas
                 c = fgetc(fd);
                 coluna++;

                 if(c == '\\')
                 {
                     estado = 9;
                 }
                 else if(c != '\'')
                 {
                     t->lexema[0] = c;
                     t->lexema[1] = '\0';

                     //novo
                     t->valorInteiro = c;

                     estado = 10;
                 }
                 else
                 {
                     printf("ERRO 8: Caractere '%c' não esperado na linha %d coluna 5d!", c, linha, coluna);
                     exit(1);
                 }

            break;
            case 9:

                 //t->lexema[j++] = c; // barra
                 c = fgetc(fd);
                 coluna++;

                 if(c == 'n')
                 {

                      t->lexema[0] = '\n';
                      t->lexema[1] = '\0';

                      //novo
                      t->valorInteiro = '\n';

                      estado = 10;
                 }
                 else if(c == '0')
                 {
                      t->lexema[0] = '\0';

                      //novo
                      t->valorInteiro = '\0';

                      estado = 10;
                 }
                 else
                 {
                     //TODO: ignorei a barra no char..
                     t->lexema[0] = c;
                     t->lexema[1] = '\0';
                     estado = 10;

                 }

            break;
            case 10:

                 //verifica que é char. fechamento das aspas;;

                 c = fgetc(fd);
                 coluna++;

                 if(c == '\'')
                 {
                      estado = 11;
                 }
                 else
                 {
                      printf("ERRO 10: Caractere '%c' não esperado na linha %d coluna 5d!", c, linha, coluna);
                      exit(1);
                 }


            break;
            case 11:  // ACEITAÇÃO ..

                 //avanca um char e sai..
                 c = fgetc(fd);
                 coluna++;
                 t->tipo = CHARCON;

                 return t;

            break;
            case 12:

                 c = fgetc(fd);
                 coluna++;

                 if(c != '"')
                 {
                     estado = 12;

                     //armazena somente os 30 primeiros caracteres..
                     if(j < 30)
                     {
                         t->lexema[j++] = c;
                     }

                     if(k < 200)
                     {
                          TAB_LITERAIS[cont_literal][k++] = c;
                     }
                 }
                 else // se == '"'
                 {

                     estado = 13;
                     t->lexema[j++] = '\0';
                 }

            break;
            case 13:  // ACEITAÇÃO ..

                 t->tipo = CADEIACON;

                 TAB_LITERAIS[cont_literal][k] = '\0';

                 t->posicaoLiteral = cont_literal;

                 //avanca um char e sai..
                 c = fgetc(fd);
                 coluna++;

                 return t;

            break;
            case 14: // ACEITAÇÃO ..

                 t->lexema[0] = c;
                 t->lexema[1] = '\0';

                 //printf("{%c}",c);


                 //avanca um char e sai..
                 c = fgetc(fd);
                 coluna++;

                 return t;

            break;
            case 15: // ACEITAÇÃO ..

                 //avanca um char e tenta sair..
                 c = fgetc(fd);
                 coluna++;

                 if(c == '=')
                 {
                     estado = 16;
                 }
                 else
                 {
                     //se sinal simples... converter o codigo do sinal especial de acordo com o indice..
                     t->codigoSinal = sinaisSimples[t->codigoSinal];
                     return t;
                 }

            break;
            case 16: // ACEITAÇÃO ..

                 t->codigoSinal = sinaisComIgual[t->codigoSinal];

                 // usado para imprimir o lexema..
                 t->lexema[1]= c;
                 t->lexema[2]= '\0';


                 //avanca um char e sai..
                 c = fgetc(fd);
                 coluna++;

                 return t;

            break;
            case 17:

                 c = fgetc(fd);
                 coluna++;

                 if(c == '&')
                 {
                     estado = 18;
                 }
                 else
                 {
                      printf("ERRO 17: Caractere '%c' não esperado na linha %d coluna 5d!", c, linha, coluna);
                      exit(1);
                 }

            break;
            case 18:  // ACEITAÇÃO ..

                 t->lexema[0]= '&';
                 t->lexema[1]= '&';
                 t->lexema[2]= '\0';

                 t->tipo = SINAL;
                 t->codigoSinal = ELOGICO;

                 //avanca um char e sai..
                 c = fgetc(fd);
                 coluna++;

                 return t;


            break;
            case 19:

                 c = fgetc(fd);
                 coluna++;

                 if(c == '|')
                 {
                     estado = 20;
                 }
                 else
                 {
                      printf("ERRO 19: Caractere '%c' não esperado na linha %d coluna 5d!", c, linha, coluna);
                      exit(1);
                 }

            break;
            case 20:  // ACEITAÇÃO ..

                 t->lexema[0]= '|';
                 t->lexema[1]= '|';
                 t->lexema[2]= '\0';

                 t->tipo = SINAL;
                 t->codigoSinal = OULOGICO;

                 //avanca um char e sai..
                 c = fgetc(fd);
                 coluna++;

                 return t;

            break;
        }
    }

    return NULL;
}
