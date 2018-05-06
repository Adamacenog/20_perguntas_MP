/*
*Propriedade de Andre Garrido Damaceno.
*mat. 15/0117531.
*/

/**
 * @file Funcs.c
 * @author Andre Garrido Damaceno
 * @brief Arquivo que contem a função de concatenação de string e de criar arquivos txt (abrir ou salvar).
 *
 */

/**Como esse arquivo contem apenas funções auxiliares, necessita apenas dos headers padrões.
 */

/**@brief Header de funções padrão, para I/O, manipulação de strings.
*/
#ifndef _Primary_libraries
  #define _Primary_libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>
    #include <assert.h>
#endif

/**@brief Header da biblioteca de funções (criação de arquivo e concatenação de strings).
*/
#ifndef _Funcs_library
  #define _Funcs_library
    #include "Funcs.h"
#endif

/**@brief Função de Criação de arquivos (abertura ou leitura).
*
*Parametros: Essa função recebe como parametro o tipo de abertura 'char *type' ("r" - para read, "w" - para write)
*e também uma string 'char *opcao' para ser impresso na tela (informando ao usuário se o arquivo esta sendo aberto ou salvo).
*A função retorna o arquivo 'FILE *'.
*
*Tratamento de erros: Caso o arquivo não exista, ou ele será criado (no caso do tipo "w" - write), ou a função retornará NULL no 'FILE *'.
*
*Descrição: Essa função apenas abre um arquivo e o retorna para o usuário.
*
*Assertivas de entrada: string 'type' e 'opcao' não NULLs.
*
*Requisitos: A função deve perguntar ao usuário qual o nome do arquivo e abrir ou criar um arquivo de acordo com o parâmetro 'type'.
*
*Hipoteses: A função deve abrir o arquivo de forma adequada de acordo com a forma de abertura 'type' requisitado, retornando o arquivos
*aberto/criado.
*
*Assertivas de saida: Arquivo aberto/criado não ser NUL
*
*Interface explicita:
*
*Interface implicita:
*
*Contrato na especificação: A função deve receber a forma de abertura/criação do arquivo 'type', e uma string com a informação para o
*usuário do que está ocorrendo. Então, deve ser aberto/criado o arquivo de acordo com o parâmetro 'type' e o nome informado pelo usuário,
*e por fim, deve ser retornado o arquivo.
*
*/
FILE * CriaArquivo(char *type, char *opcao)
{
  assert(type != NULL); //Verifica se o tipo é NULL
  assert(opcao != NULL); //Verifica se a opção é NULL

  FILE *arq;  //Ponteiro para o arquivo (para abrir/salvar em .txt).
  char nome[20];  //Variável usada para salvar o nome do arquivo a ser salvo/aberto.
  printf("Digite o nome do arquivo a ser %s: \n",opcao);
  scanf("%19s",nome);
  arq = fopen(nome, type);  //Captura do arquivo de acordo com seu nome e o tipo de abertura, no computador.

  if(arq == NULL)
  {
    printf("Arquivo não encontrado!\n");
  }

  return arq;
}

/**@brief Função de concatenação de string.
*
*Parametros: Essa função recebe como parametro duas strings 'char *no' e 'char *filho', concatena a string 'filho' na
*string 'no', e retorna essa string 'char *'.
*
*Tratamento de erros: Caso o computador negue a alocação de memória, o programa é finalizado.
*
*Descrição: Inicialmente a função aloca memória suficiente para a concatenação das strings, em seguida copia a string 'no'
*para a memoria alocada, por fim, concatena a string 'filho' na memoria alocada, retornando assim a string com 'no' e
*'filho' concatenados devidamente.
*
*Assertivas de entrada: As strings 'no' e 'filho' não podem ser NULLs.
*
*Requisitos: A função deve concatenar as duas strings recebidas 'no' e 'filho' e retornar a string concatenada.
*
*Hipoteses: A função aloca devidamente memória suficiente para a string final concatenada, e faz a concatenação de forma
*correta, concatenando no sentido 'no' e 'filho'.
*
*Assertivas de saida: A string com o resultado da concatenação não deve ser NULL, O tamanho da string retornada deve ser
*o tamanho de 'no' + 'filho', e o final da string deve conter o caracter '\0'.
*
*Interface explicita:
*
*Interface implicita:
*
*Contrato na especificação: A função deve receber duas strings 'no' e 'filho' não nulas, deve então alocar uma nova string
*'noFilho' que deve possuir o tamanho de 'no' e 'filho' juntas, em seguida colocar o resultado da concatenação de 'no' e 'filho' em
*'noFilho' e retornar 'noFilho'.
*
*/
char * ConstroiNo(char *no, char *filho)
{
  assert(no != NULL); //Verifica a string 'no' diferente de NULL
  assert(filho != NULL); //Verifica a string 'filho' diferente de NULL

  char *noFilho = (char *) malloc (strlen(no) + strlen(filho) + 1);  //Alocação de memoria do tamanho de ambas strings + o finalizador '\0'

  if(noFilho == NULL)  //Caso a alocação dê erro, o programa é finalizado.
  {
    exit(1);
  }

  strcpy(noFilho, no);  //Copia a string 'no' para o novo espaço alocado
  strcat(noFilho, filho);  //Concatena a string 'no' com a string 'filho'
  noFilho[strlen(no) + strlen(filho) + 1] = '\0'; //Coloca o '\0' no final da string

  assert(noFilho != NULL);
  assert(strlen(noFilho) == (strlen(no) + strlen(filho)));
  assert(noFilho[strlen(noFilho) + 1] == '\0');

  return noFilho;
}
