/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

#ifndef _Primary_libraries
  #define _Primary_libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
#endif

#ifndef _Arvore_library
  #define _Arvore_library
    #include "Arvore.h"
#endif

#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

#ifndef _Vinte_Perguntas_library
  #define _Vinte_Perguntas_library
    #include "Vinte_Perguntas.h"
#endif

#ifndef _Jogo_library
  #define _Jogo_library
    #include "Jogo.h"
#endif

int main()
{
  Jogo_init();
  return 0;
}

void Jogo_init(void)
{
  int opcao;
  arvore *ainicio = NULL;
  FILE *arq;

  printf("\nDigite 'abrir' para abrir um arquivo ou 'criar' para criar um jogo do zero\n");
  opcao = Resposta(inicializacao);
  if(opcao == Rabrir)
  {
    char r[2] = "r";
    char aberto[7] = "aberto";
    arq = CriaArquivo(r, aberto);
    Constroi_TXT(&ainicio, arq);
    if(arq != NULL)
    {
        fclose(arq);
    }
  }
  if(opcao == Rcriar)
  {
    char pai[4] = "PAI";
    Constroi_Manual(&ainicio, pai, 0);
  }

  Vinte_Perguntas(&ainicio, 0);
  printf("\nDigite 'sim' para salvar as perguntas em um arquivo ou 'nao' para finalizar\n");
  opcao = Resposta(simples);
  if(opcao == Rsim)
  {
    char w[2] = "w";
    char salvo[6] = "salvo";
    arq = CriaArquivo(w,salvo);
    Salva_TXT(&ainicio,arq);
    if(arq != NULL)
    {
        fclose(arq);
    }
  }
  Desconstroi(&ainicio);

  return;
}
