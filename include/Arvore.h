/*
Propriedade de Andre Garrido Damaceno.
mat. 15/0117531.
*/

/*@brief Assertiva estrutural
*A árvore binária 'Arvore' descrita abaixo deve seguir os seguintes critérios:
*Podem apenas ser criados um nó 'sim' e um nó 'não' por nó da arvore.
*Os nós podem apenas apontar para novos nós, não podendo apontar para nós existêntes
*ou duplicados da árvore.
*Os nós da esqueda não podem apontar para nós da direita e vice versa.
*Os nós não podem apontar para o nó pai.
*Quando Arvore != NULL, Pergunta é != NUll.
*/

typedef struct Arvore
{
    char Pergunta[100];
    struct Arvore *sim, *nao;
} arvore;

void Constroi_Manual (arvore **, char *, unsigned int);
void Constroi_TXT (arvore **, FILE *);
void Salva_TXT (arvore **, FILE *);
void Le (arvore *);
void NavegaSim(arvore **);
void NavegaNao(arvore **);
void Desconstroi (arvore **);
