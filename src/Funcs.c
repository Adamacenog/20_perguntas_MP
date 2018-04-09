/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Funcs.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a função de concatenação de string e de criar arquivos txt (abrir ou salvar)
 *
 *Como esse arquivo contem apenas funções auxiliares, necessita apenas dos headers padrões.
 */

 /*
 *@brief Header de funções padrão, para I/O, manipulação de strings.
 */
#ifndef _Primary_libraries
  #define _Primary_libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
#endif

/*
*@brief Header da biblioteca de funções (criação de arquivo e concatenação de strings).
*/
#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

/*
*@brief Função de Criação de arquivos (abertura ou leitura).
*Essa função recebe como parametro o tipo de abertura 'char *type' ("r" - para read, "w" - para write)
*e também uma string 'char *opcao' para ser impresso na tela (informando ao usuário se o arquivo esta sendo aberto ou salvo).
*A função retorna o arquivo 'FILE *'. Essa função apenas abre um arquivo e o retorna para o usuário.
*Caso o arquivo não exista, ou ele será criado (no caso do tipo "w" - write), ou a função retornará NULL no 'FILE *'.
*/
FILE * CriaArquivo(char *type, char *opcao)
{
  FILE *arq;  //Ponteiro para o arquivo (para abrir/salvar em .txt).
  char nome[20];  //Variável usada para salvar o nome do arquivo a ser salvo/aberto.
  printf("Digite o nome do arquivo a ser %s: \n",opcao);
  scanf("%19s",nome);
  arq = fopen(nome, type);  //Captura do arquivo de acordo com seu nome e o tipo de abertura, no computador.
  return arq;
}

/*
*@brief Função de concatenação de string.
*Essa função recebe como parametro duas strings 'char *no' e 'char *filho', concatena a string 'filho' na
*string 'no', e retorna essa string 'char *'. Inicialmente a função aloca memória suficiente para a concatenação
*das strings, em seguida copia a string 'no' para a memoria alocada, por fim, concatena a string 'filho' na memoria
*alocada, retornando assim a string com 'no' e 'filho' concatenados devidamente.
*Caso o computador negue a alocação de memória, o programa é finalizado.
*/
char * ConstroiNo(char *no, char *filho)
{
  char *noFilho = (char *) malloc (strlen(no) + strlen(filho) + 1);  //Alocação de memoria do tamanho de ambas strings + o finalizador '\0'

  if(noFilho == NULL)  //Caso a alocação dê erro, o programa é finalizado.
  {
    exit(1);
  }

  strcpy(noFilho, no);  //Copia a string 'no' para o novo espaço alocado
  strcat(noFilho, filho);  //Concatena a string 'no' com a string 'filho'

  return noFilho;
}
