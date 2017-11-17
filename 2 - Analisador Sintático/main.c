#include "Analex.h"


char TAB_SN[SIZE_SN][COMP_SN] = {'(', ')', '{', '}','+', '-', '/', '*', ',', '.', ';', '=', '==', '!', '!=', '>', '<', '>=', '<=', '&&', '││'};
char TAB_PR[SIZE_PR][COMP_PR] = {"caracter", "inteiro", "real", "booleano", "semparam", "semretorno", "se", "senao", "enquanto", "para", "retorne", "prototipo"};

char TAB_CTL[SIZE_CTL][COMP_CTL];
int ultimaPosicaoCTL = -1;

int contLinha = 1;


int main (int argc, char *argv[]) {
  TOKEN token;
  FILE* fp;

  fp = abreArquivo();


  inicio(fp);
  while (!feof (fp)) {
    prog(fp);
    
    //token = analex(fp);
    //imprimir(token);
  }

  printf ("\nAnalise simtatica concluida.\n \nPressione Enter para sair.");
  getchar();
  fflush(stdin);

  fechaArquivo (fp);

  return 0;
}