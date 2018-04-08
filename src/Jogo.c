/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Arvore.h"
#include "Funcs.h"
#include "Vinte_Perguntas.h"
#include "Jogo.h"

int main()
{
  Jogo_init();
  return 0;
}

void Jogo_init(void)
{
  int opcao;
  arvore *ainicio;
  FILE *arq;

  printf("\nDigite 'abrir' para abrir um arquivo ou 'criar' para criar um jogo do zero\n");
  opcao = Resposta(inicializacao);
  if(opcao == Rabrir)
  {
    char r[2] = "r";
    char aberto[7] = "aberto";
    arq = CriaArquivo(r, aberto);
    Constroi_TXT(&ainicio, arq);
    fclose(arq);
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
    fclose(arq);
  }
  Desconstroi(&ainicio);

  return;
}
