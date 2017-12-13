#include "Analex.h"

int main (int argc, char *argv[]) {
  Token token;
  FILE* fp;
  
  fp = abrirArq();

  inicio(fp);
  while (!feof (fp)) {
    prog(fp);

    //token = analex(fp);
    //imprimir(token);
  }

  imprimeTabSimbolos();

  printf ("\nAnalise simtatica concluida.\n \nPressione Enter para sair.");
  getchar();
  fflush(stdin);

  fecharArq (fp);

  return 0;
}
