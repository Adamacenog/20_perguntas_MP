/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

typedef enum Respostas{Rsim,Rnao,Reditar,Rapagar,Rcriar,Rabrir}resposta;
typedef enum TipoPergunta{multipla,simples,inicializacao}pergunta;

unsigned int Resposta(unsigned int);
FILE * CriaArquivo(char *, char *);
char * PosicaoNo(char *, char *);
