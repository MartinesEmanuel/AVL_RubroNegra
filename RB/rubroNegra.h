#ifndef LISTA8_RUBRONEGRA_H
#define LISTA8_RUBRONEGRA_H

typedef struct no no;
typedef struct rb rb;


//Função que cria e retorna uma estrutura do tipo árvore balanceada utilizando o algoritmo AVL
rb *criaArvore();

//Função que insere um elemento na árvore
//Retorna 1 se a inserção foi realizada com sucesso
//Retorna 0 se não foi possível realizar a inserção
int insereNo(rb *arv, int valor);

//Função que remove um elemento da árvore implementando a remoção por cópia usando o sucessor
//Retorna 1 se o elemento foi removido
//Retorna 0 se a árvore estiver vazia
//Retorna -1 caso o elemento a ser removido não esteja na árvore
int removeNo(rb *arv, int valor);

void imprimeOrdem(no *raiz);
void imprimePreOrdem(rb *arv, no *raiz);

//Função que retorna a raiz da árvore
no *getRaiz(rb *arv);

//Função que retorna a quantidade de elementos da árvore
int getNumElementos(rb *arv);
int processaCarga(rb *arv, char *nomeArquivo, int tipo);

/***********FUNÇÕES DA Rubro Negra**************/

//Função que corrige o balanceamento após a inserção
void balanceamentoInsercao(rb *arv, no *noDesbal);

//Função que corrige o balanceamento após a remoção
void balanceamentoRemocao(rb *arv, no *noDesbal, no *pai, int valor);

//Função que implementa a rotação à direita
void rotacaoDir(rb * arv, no *noDesbal);

//Função que implementa a rotação à esquerda
void rotacaoEsq(rb * arv, no *noDesbal);

//Função que retorna o contador de rotações
int Rotations();

//Função que reseta o contador;
void ResetaContador();

//Função busca nó, retorna o Nó na arvore, implementada de forma recursiva
struct no* buscaNo(rb *arv, int valor); 

//Função que libera nó
void liberaNos(no *raiz, no *sentinelaFolha);

//Limpa a arvore
void limpaArvore(rb *arv);

#endif //LISTA8_RUBRONEGRA_H
