/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

typedef enum Respostas{Rsim,Rnao,Reditar,Rapagar,Rcriar,Rabrir}resposta;
typedef enum TipoPergunta{multipla,simples,inicializacao}pergunta;

int Resposta(unsigned int);
void Vinte_Perguntas(arvore **, int);
void Pergunta_Final(arvore **, arvore **,int, int);
