#include "Analex.h"

/*=========INÍCIO FUNÇÕES=========*/

#define EH_LETRA(p)((p>='a')&&(p<='z'))||((p>='A')&&(p<='Z'))
#define EH_DIGITO(p)(p>='0')&&(p<='9')
#define EH_ESPACO(p)(p==' ')||(p=='\t')
#define EH_ALFA(p)EH_LETRA(p)||EH_DIGITO(p)||(p=='_')

void excecao(msg,linha){
    printf("Linha: %i - %s", linha,msg);
}

int buscaPalavraReservada(char lexema[COMP_LEXEMA]) {

    int i;
    for (i = 0; i < SIZE_PR; i++) {
        if (strcmp (TAB_PR[i], lexema) == 0) return i;
    }

    return -1;
}

FILE* abreArquivo () {
    char arq[ARQ];  //armazena o nome do arquivo
    char modo[4];   //armazena o modo de abertura do arquivo
    FILE* fp;       //ponteiro do arquivo

    strcpy (modo, "rt"); //modo de abertura
    printf ("Digite o nome do arquivo:");
    gets (arq);
    fflush (stdin);

    //abri arquivo em modo texto para leitura
    if ((fp = fopen (arq, modo)) == NULL) {
        printf ("\n\tErro fatal na abertura de arquivo. O programa sera fechado.\n\nPressione Enter para sair.");
        getchar();
        fflush(stdin);
        exit (1);
    }

    return (fp);
}


void fechaArquivo (FILE* fp) {
    if (fclose(fp)) { //retorna zero se a operação de fechamento for bem-sucedida
        printf ("\n\tErro fatal no fechamento de arquivo. O programa sera encerrado.\n\nPressione Enter para sair.");
        getchar();
        fflush(stdin);
        exit (1);
    }
}

void imprimeToken(TOKEN token) {

    switch (token.cat) {

    case PR:
        printf ("\n< PR , %s >", token.lexema);
        break;

    case ID:
        printf ("\n< ID , %s >",token.lexema);
        break;

    case CTL:
        printf ("\n< CTL, %s >", TAB_CTL[token.atr.PosicaoLiteral]);
        break;

    case CTI:
        printf ("\n< CTI, %d >", token.atr.ValorInteiro);
        break;

    case CTC:
        if (token.atr.ValorInteiro == -1)           printf ("\n< CTC, \'\' >");
        else if (token.atr.ValorInteiro == '\n')    printf ("\n< CTC, \\n >");
        else if (token.atr.ValorInteiro == '\0')    printf ("\n< CTC, \\0 >");
        else if (token.atr.ValorInteiro == '\'')    printf ("\n< CTC, \\\' >");
        else                                        printf ("\n< CTC, %c >", token.atr.ValorInteiro);
        break;

    case SN:
        printf ("\n< SN , %s >", token.lexema);
        break;

    case CTR:
        printf ("\n< CTR, %f >", token.atr.ValorReal);
        break;

    case CMT:
        printf ("\n< CMT , /* %s */ >", token.comentario);
        break;

    case FA:
        printf ("\n< FA , %s >", token.lexema);
        break;
    }
}

int insereInTabCtl (char literal[COMP_CTL]) {

    if (ultimaPosicaoCTL != -1) {

         int i = 0;
         while (i <= ultimaPosicaoCTL) {
               if (strcmp (TAB_CTL[i], literal) == 0) return i;
               i++;
         }
    }

    if (ultimaPosicaoCTL + 1 >= SIZE_CTL) 
    {
        printf("limite maximo de constantes literais/programa atingido");
    }
    else 
    {
        ultimaPosicaoCTL++;
        strcpy (TAB_CTL[ultimaPosicaoCTL], literal);
        return ultimaPosicaoCTL;
    }
}

/*=========FIM FUNÇÕES=========*/


TOKEN analex(FILE * fp)
{
    char literal[COMP_CTL];
    char num[COMP_NUM];
    int c;
    int estado = 0;
    int pos = 0;
    TOKEN token;

    while(1){

        switch(estado)
        {
            case 0:
                c = fgetc(fp);

                //espaço é ' ', \t
                //if(EH_ESPACO(c))        estado = 0;
                if(c == ' ' || c == '\t')   estado = 0;
                else if(c == '\n')          estado = 53;
                else if(c == '/')           estado = 1;
                else if(c == '\'')          estado = 6;
                else if(c == '\"')          estado = 17;
                else if(c == ';')           estado = 27;
                else if(c == '-')           estado = 28;
                else if(c == '+')           estado = 29;
                else if(c == '{')           estado = 30;
                else if(c == '}')           estado = 31;
                else if(c == '(')           estado = 32;
                else if(c == ')')           estado = 33;
                else if(c == '*')           estado = 34;
                else if(c == ',')           estado = 35;
                else if(c == '│')           estado = 36;
                else if(c == '&')           estado = 38;
                else if(c == '=')           estado = 40;
                else if(c == '!')           estado = 43;
                else if(c == '>')           estado = 46;
                else if(c == '<')           estado = 49;
                else if(isdigit(c))         estado = 20;
                else if(isalpha(c))         estado = 25;
                else if(c == EOF)           estado = 52;
                else                        estado = 54; // INVÁLIDO

                break;
            case 1://33

                c = fgetc(fp);

                if(c == '*')
                {
                    estado = 3;
                }
                else
                {
                    estado = 2;
                }

                break;
            case 2:
                /*
                    OUTRO*
                    ESTADO DE ACEITAÇÃO
                    DIVIDE
                */

                ungetc(c, fp);
                token.cat = SN;
                strcpy (token.lexema, "/");
                token.atr.CodigoSn = DIVIDE;
                return token;

                break;
            case 3://30

                c = fgetc(fp);

                if(c == '*')
                {                    
                    token.comentario[pos] = c;
                    pos++;
                    estado = 4;
                }
                else
                {
                    token.comentario[pos] = c;
                    pos++;
                    estado = 3;
                }

                break;
            case 4://34

                c = fgetc(fp);

                if(c == '*')
                {
                    token.comentario[pos] = c;
                    pos++;
                    estado = 5;
                }
                else
                {
                    token.comentario[pos] = c;
                    pos++;
                    estado = 4;
                }

                break;
            case 5:

                c = fgetc(fp);

                if(c == '/')
                {
                    token.cat = CMT;
                    token.comentario[pos] = EOS;
                    return token;
                    estado = 0;
                }
                else
                {
                    token.comentario[pos] = c;
                    estado = 4;
                }

                break;
            case 6:

                c = fgetc(fp);


                if(c == '/')
                {
                    estado = 8;
                }
                else if(isprint(c) && c != '\\' && c != '\'')
                {
                    estado = 7;
                }
                else
                {
                    excecao("token invalido",contLinha);
                }

                break;
            case 7:

                token.atr.ValorInteiro = c;
                c = fgetc(fp);

                if(c == '\'')
                {
                    estado = 9;
                }
                else
                {
                    excecao("token invalido",contLinha);
                }

                break;
            case 8:

                c = fgetc(fp);

                if(c == 'n')
                {
                    c = '\n';
                    estado = 10;
                }
                else if(c == '0')
                {
                    c = '\0';
                    estado = 11;
                }
                else if(c == '\'')
                {
                    c = '\'';
                    estado = 12;
                }
                else
                {
                    excecao("token invalido",contLinha);
                }

                break;
            case 9:
                /*
                    ESTADO DE ACEITAÇÃO
                    CARACCON
                */
                token.cat = CTC;
                return token;

                break;
            case 10:

                token.atr.ValorInteiro = c;
                c = fgetc(fp);
                if(c == '\'')
                {
                    estado = 13;
                }

                break;
            case 11:

                token.atr.ValorInteiro = c;
                c = fgetc(fp);
                if(c == '\'')
                {
                    estado = 14;
                }

                break;
            case 12:

                token.atr.ValorInteiro = c;
                c = fgetc(fp);
                if(c == '\'')
                {
                    estado = 15;
                }
                else
                {
                    estado = 16;
                }

                break;
            case 13:
                /*
                    ESTADO DE ACEITAÇÃO
                    CARACCON
                */
                token.cat = CTC;
                return token;

                break;
            case 14:
                /*
                    ESTADO DE ACEITAÇÃO
                    CARACCON
                */
                token.cat = CTC;
                return token;

                break;
            case 15:
                /*
                    ESTADO DE ACEITAÇÃO
                    APÓSTROFO
                */
                token.cat = CTC;
                return token;

                break;
            case 16:
                /*
                    ESTADO DE ACEITAÇÃO
                    BARRA INVERTIDA
                */
                token.cat = CTC;
                return token;

                break;
            case 17:

                if(isprint(c) && c != '\"' && c != '\n')
                {
                    estado = 18;
                }
                else if(c == '\"')
                {
                    token.atr.ValorInteiro = -1;
                    estado = 19;
                }
                else
                {
                    excecao("token invalido",contLinha);
                }

                break;
            case 18:

                literal[pos] = c;
                c = fgetc(fp);
                pos++;

                if (pos >= COMP_CTL)
                {
                    excecao("comprimento da constante literal maior do que o permitido",contLinha);
                }
                if(isprint(c) && c != '\"' && c != '\n')
                {
                    estado = 18;
                }
                else if(c == '\"')
                {
                    literal[pos] = EOS;
                    estado = 19;
                }
                else
                {
                    excecao("token invalido",contLinha);
                }

                break;
            case 19:
                /*
                    ESTADO DE ACEITAÇÃO
                    CADEIACON
                */
                token.cat = CTL;
                token.atr.PosicaoLiteral = insereInTabCtl(literal);
                return token;

                break;
            case 20:

                num[pos] = c;
                c = fgetc(fp);
                pos++;

                if (pos >= COMP_NUM)
                {
                    excecao("comprimento da constante inteira ou real maior do que o permitido",contLinha);
                }
                if(isdigit(c))
                {
                    estado = 20;
                }
                else if(c == '.')
                {
                    num[pos] = c;
                    pos++;

                    if (pos >= COMP_NUM)
                    {
                        excecao("comprimento da constante inteira ou real maior do que o permitido",contLinha);
                    }

                    estado = 22;
                }
                else
                {
                    num[pos] = EOS;
                    estado = 21;
                }

                break;
            case 21:
                /*
                    ESTADO DE ACEITAÇÃO
                    INTCON
                */

                ungetc(c, fp);
                token.cat = CTI;
                token.atr.ValorInteiro = atoi(num);
                return token;

                break;
            case 22:

                c = fgetc(fp);

                if(isdigit(c))
                {
                    estado = 23;
                }
                else
                {
                    excecao("token invalido",contLinha);
                }

                break;
            case 23:

                num[pos] = c;
                c = fgetc(fp);
                pos++;

                if (pos >= COMP_NUM)
                {
                    excecao("comprimento da constante inteira ou real maior do que o permitido",contLinha);
                }
                if(isdigit(c))
                {
                    estado = 23;
                }
                else
                {
                    num[pos] = EOS;
                    estado = 24;
                }

                break;
            case 24:
                /*
                    ESTADO DE ACEITAÇÃO
                    REALCON
                */

                ungetc(c, fp);
                token.cat = CTR;
                token.atr.ValorReal = atof(num);
                return token;

                break;
            case 25:

                token.lexema[pos] = c;
                c = fgetc(fp);
                pos++;

                if (pos >= COMP_LEXEMA)
                {
                    excecao("comprimento do identificador maior do que o permitido",contLinha);
                }
                if(isalnum(c) || c == '_')
                {
                    estado = 25;
                }
                else
                {
                    token.lexema[pos] = EOS;
                    estado = 26;
                }

                break;
            case 26:
                /*
                    ESTADO DE ACEITAÇÃO
                    ID
                */

                ungetc(c, fp);
                int p = buscaPalavraReservada(token.lexema);

                if (p == -1)
                {
                    token.cat = ID;
                }
                else
                {
                    token.cat = PR;
                    token.atr.CodigoPr = p;
                }
                return token;

                break;
            case 27:
                /*
                    ESTADO DE ACEITAÇÃO
                    PONTO E VÍRGULA
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[PONTO_E_VIGULA]);
                token.atr.CodigoSn = PONTO_E_VIGULA;
                return token;

                break;
            case 28:
                /*
                    ESTADO DE ACEITAÇÃO
                    SUBTRAI
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[SUBTRAI]);
                token.atr.CodigoSn = SUBTRAI;
                return token;

                break;
            case 29:
                /*
                    ESTADO DE ACEITAÇÃO
                    SOMA
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[SOMA]);
                token.atr.CodigoSn = SOMA;
                return token;

                break;
            case 30:
                /*
                    ESTADO DE ACEITAÇÃO
                    ABRE CHAVE
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[ABRE_CHAVE]);
                token.atr.CodigoSn = ABRE_CHAVE;
                return token;

                break;
            case 31:
                /*
                    ESTADO DE ACEITAÇÃO
                    FECHA CHAVE
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[FECHA_CHAVE]);
                token.atr.CodigoSn = FECHA_CHAVE;
                return token;

                break;
            case 32:
                /*
                    ESTADO DE ACEITAÇÃO
                    ABRE PARENTESE
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[ABRE_PARENTESE]);
                token.atr.CodigoSn = ABRE_PARENTESE;
                return token;

                break;
            case 33:
                /*
                    ESTADO DE ACEITAÇÃO
                    FECHA PARENTESE
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[FECHA_PARENTESE]);
                token.atr.CodigoSn = FECHA_PARENTESE;
                return token;

                break;
            case 34:
                /*
                    ESTADO DE ACEITAÇÃO
                    MULTIPLICA
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[MULTIPLICA]);
                token.atr.CodigoSn = MULTIPLICA;
                return token;

                break;
            case 35:
                /*
                    ESTADO DE ACEITAÇÃO
                    VÍRGULA
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[VIRGULA]);
                token.atr.CodigoSn = VIRGULA;
                return token;

                break;
            case 36:

                c = fgetc(fp);

                if(c == '|')
                {
                    estado = 37;
                }
                else
                {
                    excecao("token invalido",contLinha);
                    //printf("Linha: %i - token invalido", contLinha);
                }

                break;
            case 37:
                /*
                    ESTADO DE ACEITAÇÃO
                    OU LÓGICO
                */
                token.cat = SN;
                strcpy (token.lexema, TAB_SN[OU_LOGICO]);
                token.atr.CodigoSn = OU_LOGICO;
                return token;

                break;
            case 38:

                c = fgetc(fp);

                if(c == '&')
                {
                    estado = 39;
                }
                else
                {
                    excecao("token invalido",contLinha);
                    //printf("Linha: %i - token invalido", contLinha);
                }

                break;
            case 39:
                /*
                    ESTADO DE ACEITAÇÃO
                    E LÓGICO
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[E_LOGICO]);
                token.atr.CodigoSn = E_LOGICO;
                return token;

                break;
            case 40:

                c = fgetc(fp);

                if(c == '=')
                {
                    estado = 41;
                }
                else
                {
                    estado = 42;
                }

                break;
            case 41:
                /*
                    ESTADO DE ACEITAÇÃO
                    IGUALA
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[IGUALA]);
                token.atr.CodigoSn = IGUALA;
                return token;

                break;
            case 42:
                /*
                    OUTRO*
                    ESTADO DE ACEITAÇÃO
                    ATRIBUI
                */

                ungetc(c, fp);
                token.cat = SN;
                strcpy (token.lexema, TAB_SN[ATRIBUI]);
                token.atr.CodigoSn = ATRIBUI;
                return token;

                break;
            case 43:

                c = fgetc(fp);

                if(c == '=')
                {
                    estado = 44;
                }
                else
                {
                    estado = 45;
                }

                break;
            case 44:
                /*
                    ESTADO DE ACEITAÇÃO
                    DIFERENTE
                */
                token.cat = SN;
                strcpy (token.lexema, TAB_SN[DIFERENTE]);
                token.atr.CodigoSn = DIFERENTE;
                return token;

                break;
            case 45:
                /*
                    OUTRO*
                    ESTADO DE ACEITAÇÃO
                    NEGA
                */
                ungetc(c, fp);
                token.cat = SN;
                strcpy (token.lexema, TAB_SN[NEGA]);
                token.atr.CodigoSn = NEGA;
                return token;

                break;
            case 46:

                c = fgetc(fp);

                if(c == '=')
                {
                    estado = 47;
                }
                else
                {
                    estado = 48;
                }

                break;
            case 47:
                /*
                    ESTADO DE ACEITAÇÃO
                    MAIOR OU IGUAL
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[MAIOR_OU_IGUAL]);
                token.atr.CodigoSn = MAIOR_OU_IGUAL;
                return token;

                break;
            case 48:
                /*
                    OUTRO*
                    ESTADO DE ACEITAÇÃO
                    MAIOR QUE
                */
                ungetc(c, fp);
                token.cat = SN;
                strcpy (token.lexema, TAB_SN[MAIOR_QUE]);
                token.atr.CodigoSn = MAIOR_QUE;
                return token;

                break;
            case 49:

                c = fgetc(fp);

                if(c == '=')
                {
                    estado = 50;
                }
                else
                {
                    estado = 51;
                }

                break;
            case 50:
                /*
                    ESTADO DE ACEITAÇÃO
                    MENOR OU IGUAL
                */

                token.cat = SN;
                strcpy (token.lexema, TAB_SN[MENOR_OU_IGUAL]);
                token.atr.CodigoSn = MENOR_OU_IGUAL;
                return token;

                break;
            case 51:
                /*
                    OUTRO*
                    ESTADO DE ACEITAÇÃO
                    MENOR QUE
                */

                ungetc(c, fp);
                token.cat = SN;
                strcpy (token.lexema, TAB_SN[MENOR_QUE]);
                token.atr.CodigoSn = MENOR_QUE;
                return token;

                break;
            case 52:
                /*
                    ESTADO DE ACEITAÇÃO
                    EOF
                */

                token.cat = FA;
                strcpy (token.lexema, "Final do Arquivo");
                return token;

                break;
            case 53:
                /*
                    ESTADO DE ACEITAÇÃO
                    NEW LINE
                */

                contLinha++;
                estado = 0;

                break;
            default:
                excecao("caractere invalido",contLinha);
                //printf("Linha: %i - caractere invalido", contLinha);

        }
    }
}
