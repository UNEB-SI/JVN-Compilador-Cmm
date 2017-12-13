#include "Analex.h"

int ultimo = -1;            //posicao da ultima constante literal inserida na tabCTL
int contLinha = 1;          //contador de linhas

int buscarTabPR(char lexema[ID_TAM]) {

    int i;
  for (i = 0; i < PR_QTD; i++) {
    if (strcmp (tabPR[i], lexema) == 0) return i; //encontrou
  }
  return -1; //nao encontrou
}

int inserirTabCTL (char literal[CTL_TAM]) {

  if (ultimo != -1) {
         int i = 0;
     while (i <= ultimo) {
           if (strcmp (tabCTL[i], literal) == 0) return i;
               i++;
         }
  }

  if (ultimo + 1 >= CTL_QTD)
    printf("quantidade maxima de literais atingido");

  else {  //nao encontrou
        ultimo++;
    strcpy (tabCTL[ultimo], literal); //insere
    return ultimo; //retorna a posicao
  }
}


Token analex(FILE* fp) {

  char literal[CTL_TAM]; //armazena temporariamente a constante literal
  char num[NUM_TAM];    //armazena temporariamente a constante inteira e real
  int c;
  int estado = 0;
  int pos = 0;
  Token token;

  while (1) {

    switch (estado) {

    case 0:
      c = fgetc(fp);

      if (c == ' ' || c == '\t')  //espacos em branco e tab
        estado = 0;
      else if (c == '\n')   //newLine e linha ++
        estado = 21;
      else if (c == '(')
        estado = 45;
      else if (c == ')')
        estado = 47;
      else if (c == '!')
        estado = 19;
      else if (c == '+')
        estado = 27;
      else if (c == '*')
        estado = 31;
      else if (c == '/')
        estado = 33;
      else if (c == '=')
        estado = 23;
      else if (c == '<')
        estado  = 14;
      else if (c == '>')
        estado = 10;
      else if (c == '|')
        estado = 35;
      else if (c == '&')
        estado = 38;
      else if (c == '-')
        estado = 29;
      else if (c == ',')
        estado = 42;
      else if (c == ';')
        estado = 3;
      else if (c == '\'')   //constantes caracteres
        estado = 44;
      else if (c == '\"')   //constantes literais
        estado = 26;
      else if (c == '{')
        estado = 41;
      else if (c == '}')
        estado = 43;
      else if (isalpha(c))  //palavras-reservadas e identificadores
        estado = 1;
      else if (isdigit(c))  //constantes inteiras e reais
        estado = 4;
      else if (c== EOF)   //final do arquivo
        estado = 9;
      else
        estado = 49;    //ERRO: caractere invï¿½lido

      break;


    case 1:
      token.lexema[pos] = c;
      c = fgetc(fp);
      pos++;
      if (pos >= ID_TAM)
        printf("Linha: %i - Comprimento do ID muito grande", contLinha);
      if (isalnum(c) || c == '_')
        estado = 1;
      else {
        token.lexema[pos] = EOS;
        estado = 2;
      }
      break;

    case 2:
      ungetc(c, fp);
      int p = buscarTabPR(token.lexema);
      if (p == -1) token.tipo = ID;
      else {
        token.tipo = PR;
        token.valor.codPR = p;
      }
      return token;
      break;

    case 3:
      token.tipo = SN;
      strcpy (token.lexema, ";");
      token.valor.codSN = SN_PONTO_VIRGULA;
      return token;
      break;

    case 4:
      num[pos] = c;
      c = fgetc(fp);
      pos++;
      if (pos >= NUM_TAM)
        printf("Linha: %i - Comprimento da constante real ou inteira muito grande", contLinha);
      if (isdigit(c)) estado = 4;
      else if (c == '.') {
        num[pos] = c;
        pos++;
        if (pos >= NUM_TAM)
          printf("Linha: %i - Comprimento da constante real ou inteira muito grande", contLinha);
        estado = 5;
      }
      else {
        num[pos] = EOS;
        estado = 8;
      }
      break;

    case 5:
      c = fgetc(fp);
      if (isdigit(c)) estado = 6;
      else printf("Linha: %i - Token invalido", contLinha);
      break;

    case 6:
      num[pos] = c;
      c = fgetc(fp);
      pos++;
      if (pos >= NUM_TAM)
        printf("Linha: %i - Comprimento da constante real ou inteira muito grande", contLinha);
      if (isdigit(c)) estado = 6;
      else {
        num[pos] = EOS;
        estado = 7;
      }
      break;

    case 7:
      ungetc(c, fp);
      token.tipo = CTR;
      token.valor.valorReal = atof(num);
      return token;
      break;

    case 8:
      ungetc(c, fp);
      token.tipo = CTI;
      token.valor.valorInt = atoi(num);
      return token;

    case 9:
      token.tipo = FA;
      strcpy (token.comentario, "Final do Arquivo");
      return token;
      break;

    case 10:
      c = fgetc(fp);
      if (c == '=') estado = 11;
      else estado = 12;
      break;

    case 11:
      token.tipo = SN;
      strcpy (token.lexema, ">=");
      token.valor.codSN = SN_MAIOR_IGUAL;
      return token;
      break;

    case 12:
      ungetc(c, fp);
      token.tipo = SN;
      strcpy (token.lexema, ">");
      token.valor.codSN = SN_MAIOR;
      return token;
      break;

    case 13:
      token.tipo = CTL;
      token.valor.posLiteral = inserirTabCTL(literal);
      return token;
      break;

    case 14:
      c = fgetc(fp);
      if (c == '=') estado = 15;
      else estado = 16;
      break;

    case 15:
      token.tipo = SN;
      strcpy (token.lexema, "<=");
      token.valor.codSN = SN_MENOR_IGUAL;
      return token;
      break;

    case 16:
      ungetc(c, fp);
      token.tipo = SN;
      strcpy (token.lexema, "<");
      token.valor.codSN = SN_MENOR;
      return token;
      break;

    case 17:
      token.tipo = CTC;
      return token;
      break;

    case 18:
      break;

    case 19:
      c = fgetc(fp);
      if (c == '=') estado = 20;
      else estado = 22;
      break;

    case 20:
      token.tipo = SN;
      strcpy (token.lexema, "!=");
      token.valor.codSN = SN_DIFERENTE;
      return token;
      break;

    case 21:
      contLinha++;
      estado = 0;
      break;

    case 22:
      ungetc(c, fp);
      token.tipo = SN;
      strcpy (token.lexema, "!");
      token.valor.codSN = SN_NEGACAO;
      return token;
      break;

    case 23:
      c = fgetc(fp);
      if (c == '=') estado = 24;
      else estado = 25;
      break;

    case 24:
      token.tipo = SN;
      strcpy (token.lexema, "==");
      token.valor.codSN = SN_IGUALDADE;
      return token;
      break;

    case 25:
      ungetc(c, fp);
      token.tipo = SN;
      strcpy (token.lexema, "=");
      token.valor.codSN = SN_ATRIBUICAO;
      return token;
      break;

    case 26:
      c = fgetc(fp);
      if (isprint(c) && c != '\"' && c != '\n') estado = 28;
      else if (c == '\"') {
        token.valor.valorInt = -1; //ausencia de caractere
        estado = 13;
      }
      else printf("Linha: %i - Token invalido", contLinha);
      break;

    case 27:
      token.tipo = SN;
      strcpy (token.lexema, "+"); //strcpy (token.lexema, tabSN[SN_MAIS]);
      token.valor.codSN = SN_MAIS;
      return token;
      break;

    case 28:
      literal[pos] = c;
      c = fgetc(fp);
      pos++;

      if (pos >= CTL_TAM)
        printf("Linha: %i - Comprimento da constante literal muito grande", contLinha);
      if (isprint(c) && c != '\"' && c != '\n') estado = 28;
      else if (c == '\"') {
        literal[pos] = EOS;
        estado = 13;
      }
      else printf("Linha: %i - token invalido", contLinha);
      break;

    case 29:
      token.tipo = SN;
      strcpy (token.lexema, "-");
      token.valor.codSN = SN_MENOS;
      return token;
      break;

    case 30:
      c = fgetc(fp);
      if (c == '*') {
        token.comentario[pos] = c;
        pos++;
        estado = 34;
        }
      else if (c==EOF) {
        estado = 37;
      }
      else {
        token.comentario[pos] = c;
        pos++;
        estado = 32;
        }
      if (c=='\n') contLinha++;
      break;

    case 31:
      token.tipo = SN;
      strcpy (token.lexema, "*");
      token.valor.codSN = SN_VEZES;
      return token;
      break;

    case 32:
      c = fgetc(fp);
      if (c == '*') {
        token.comentario[pos] = c;
        pos++;
        estado = 34;
        }
      else {
        token.comentario[pos] = c;
        pos++;
        estado = 32;
      }
      if (c==EOF) {
        estado = 37;
      }
      if (c=='\n') contLinha++;
      break;

    case 33:
      c = fgetc(fp);
      if (c == '*') estado = 30;
      else estado = 40;
      break;

    case 34:
      c = fgetc(fp);
      if (c == '*') {
        token.comentario[pos] = c;
        pos++;
        estado = 34;
      }
      else if (c == '/') {
        pos--;
        estado = 37;
      }
      else if (c==EOF) {
        estado = 37;
      }
      else {
        token.comentario[pos] = c;
        pos++;
        estado = 32;
      }
      if (c=='\n') contLinha++;
      break;

    case 35:
      c = fgetc(fp);
      if (c == '|') estado = 36;
      else printf("Linha: %i - Token invalido", contLinha);
      break;

    case 36:
      token.tipo = SN;
      strcpy (token.lexema, "||");
      token.valor.codSN = SN_OR;
      return token;
      break;

    case 37:
      token.tipo = CMT;
      token.comentario[pos] = EOS;
      return token;
      estado = 0;
      break;

    case 38:
      c = fgetc(fp);
      if (c == '&') estado = 39;
      else printf("Linha: %i - Token invalido", contLinha);
      break;

    case 39:
      token.tipo = SN;
      strcpy (token.lexema, "&&");
      token.valor.codSN = SN_AND;
      return token;
      break;

    case 40:
      ungetc(c, fp);
      token.tipo = SN;
      strcpy (token.lexema, "/");
      token.valor.codSN = SN_DIVISAO;
      return token;
      break;

    case 41:
      token.tipo = SN;
      strcpy (token.lexema, "{");
      token.valor.codSN = SN_ABRI_CHAVE;
      return token;
      break;

    case 42:
      token.tipo = SN;
      strcpy (token.lexema, ",");
      token.valor.codSN = SN_VIRGULA;
      return token;
      break;

    case 43:
      token.tipo = SN;
      strcpy (token.lexema, "}");
      token.valor.codSN = SN_FECHA_CHAVE;
      return token;
      break;

    case 44:
      c = fgetc(fp);
      if (c == '\\') estado = 48;
      else if (isprint(c) && c != '\'') estado = 46;
      else printf("Linha: %i - Token invalido", contLinha);
      break;

    case 45:
      token.tipo = SN;
      strcpy (token.lexema, "(");
      token.valor.codSN = SN_ABRI_PARENTESE;
      return token;
      break;

    case 46:
      token.valor.valorInt = c;
      c = fgetc(fp);
      if (c == '\'') estado = 17;
      else printf("Linha: %i - Token invalido", contLinha);
      break;

    case 47:
      token.tipo = SN;
      strcpy (token.lexema, ")");
      token.valor.codSN = SN_FECHA_PARENTESE;
      return token;
      break;

    case 48:
      c = fgetc(fp);
      if (c == 'n') {
        c = '\n';
        estado = 46;
      }
      else if (c == '0') {
        c = '\0';
        estado = 46;
      }
      else printf("Linha: %i - Token invalido", contLinha);
      break;

    case 49:
      printf("\nLinha: %i - Token %c invalido", contLinha,c);
      token.tipo = INV;
      return token;
      break;

    default:
      printf("Linha: %i - Caracter invalido", contLinha);
    }
  }
}


void imprimir(Token token) {

  switch (token.tipo) {

  case PR:
    printf ("\n< PR , posicao %d, %s>", token.valor.codPR, token.lexema);
    break;

  case ID:
    printf ("\n< ID , %s >",token.lexema);
    break;

  case CTL:
    printf ("\n< CTL, posicao %d, %s>", token.valor.posLiteral, tabCTL[token.valor.posLiteral]);
    break;

  case CTI:
    printf ("\n< CTI, %d >", token.valor.valorInt);
    break;

  case CTC:
    if (token.valor.valorInt == -1) printf ("\n< CTC, \'\' >");
    else if (token.valor.valorInt == '\n') printf ("\n< CTC, \\n >");
    else if (token.valor.valorInt == '\0') printf ("\n< CTC, \\0 >");
    else printf ("\n< CTC, %c >", token.valor.valorInt);
    break;

  case SN:
    printf ("\n< SN , posicao %d, %s>", token.valor.codSN,token.lexema);
    break;

  case CTR:
    printf ("\n< CTR, %f >", token.valor.valorReal);
    break;

  case FA:
    printf ("\n< FA , %s >", token.comentario);
    break;

  case CMT:
    printf ("\n< CMT , /* %s */ >", token.comentario);
    break;

  case INV:

    break;
  }
}


FILE* abrirArq () {
  char arquivo[25];  //nome do arquivo com no max 25 caracteres
  FILE* fp;

  printf ("Digite o nome do arquivo que deseja abrir:");
  gets (arquivo);
  fflush (stdin);

  if ((fp = fopen (arquivo, "rt")) == NULL) {
    printf ("\n\tO arquivo nao pode ser aberto.\n\nPressione Enter para sair.");
    getchar();
    fflush(stdin);
    exit (1);
  }

  return (fp);
}


void fecharArq (FILE* fp) {
  if (fclose(fp)) { //retorna zero se a operação de fechamento for bem-sucedida
    printf ("\n\tO arquivo nao pode ser fechado.\n\nPressione Enter para sair.");
    getchar();
    fflush(stdin);
    exit (1);
  }
}

char tabSN [SN_QTD] [SN_TAM] = { //tabela sinais e simbolos
  "!=", "!",  
  "+",  "-",  
  "*",  "/",  
  "<=", "<",  
  ">=", ">",
  "==", "=",  
  "&&", "||", 
  ";",  ",",  
  "(",  ")",  
  "{",  "}" };

char tabPR [PR_QTD] [PR_TAM] = { //tabela de simbolos de palavras-reservadas
  "semretorno",    "caracter",    "inteiro",     "real", 
  "booleano",      "semparam",    "se",          "senao",
  "enquanto",      "para",        "retorne",     "principal",
  "prototipo"  };

char tabCTL [CTL_QTD][CTL_TAM];   //tabela de simbolos de constantes literais


/*char tabSN [SN_QTD] [SN_TAM] = { //tabela sinais e simbolos
  "=", "==", "!=", ">=", "<=",
  "+", "-" , "*" , "/" , "!" ,
  "<", ">" , "(" , ")" , "&&",
  "{", "}" , "||", ";" , ","  };*/
