/* EMANUEL MARTINS 20220070423*/
#include "rubroNegra.h"
#include <stdio.h>
#include <stdlib.h>
struct no {int chave;
           char cor;
           struct no *Fesq;
           struct no *Fdir;
           struct no *pai;};
struct rb {struct no *sentinela;
           struct no *sentinelaFolha;
           int numElemento;};
rb *criaArvore() {
            rb *arv = (rb *)malloc(sizeof(rb));
        arv->sentinela = (no *)malloc(sizeof(no));
        arv->sentinela->Fdir = NULL;arv->sentinela->Fesq = NULL;
        arv->sentinela->pai = NULL;arv->sentinela->cor = 'P';
        arv->sentinela->chave = -1000;
        arv->sentinelaFolha = (no *)malloc(sizeof(no));
        arv->sentinelaFolha->Fdir = NULL;
        arv->sentinelaFolha->Fesq = NULL;
        arv->sentinelaFolha->pai = NULL;
        arv->sentinelaFolha->cor = 'P';
        arv->sentinelaFolha->chave = -2000;
        arv->numElemento = 0;
    return arv;
    }

int count = 0;
int insereNo(rb *arv, int valor) {
    no *novoNo = (no *)malloc(sizeof(no));novoNo->chave = valor;novoNo->cor = 'V';novoNo->Fesq = NULL;novoNo->Fdir = NULL;novoNo->pai = NULL;

    if (arv->sentinela->Fdir == NULL) {
        novoNo->pai = arv->sentinela;arv->sentinela->Fdir = novoNo;arv->sentinela->Fdir->cor = 'P';arv->numElemento++;
        return 1;
    } else {
        no *atual = arv->sentinela->Fdir;

        while (atual != NULL) {
            if (atual->chave == valor)return 0;

            else if (atual->chave > valor && atual->Fesq == NULL) {
                novoNo->pai = atual;atual->Fesq = novoNo;arv->numElemento++;if (atual->cor == 'V')balanceamentoInsercao(arv, atual->Fesq);return 1;
            } else if (atual->chave < valor && atual->Fdir == NULL) {
                novoNo->pai = atual;atual->Fdir = novoNo;
                arv->numElemento++;if (atual->cor == 'V')balanceamentoInsercao(arv, atual->Fdir);return 1;
            }
            if (atual->chave > valor) atual = atual->Fesq;
            else atual = atual->Fdir;
        }
    }
    return 0;
}
int removeNo(rb *arv, int valor) {
        if (arv == NULL)return 0;
        no *aux;
        no *actually = arv->sentinela->Fdir;
        no *LeftNode;
        while (actually != NULL) 
        {if (actually->chave == valor) {
            if(actually->cor == 'P') {
                if (actually->Fesq == NULL && actually->Fdir == NULL) {
                    if (actually->pai->chave > actually->chave)actually->pai->Fesq = NULL;
                    else actually->pai->Fdir = NULL;
                    if(arv->numElemento != 1)balanceamentoRemocao(arv, actually, actually->pai, valor);
                    free(actually);arv->numElemento--;
                    return 1;}
                else if (actually->Fesq == NULL && actually->Fdir != NULL)
                {aux = actually->Fdir;
                    if (actually->pai->chave > actually->chave) aux->pai->pai->Fesq = actually->Fdir;
                    else aux->pai->pai->Fdir = actually->Fdir;
                    aux->pai = actually->pai;
                    LeftNode = actually->Fdir;
                    while (LeftNode->Fesq != NULL) LeftNode = LeftNode->Fesq;
                    int a = LeftNode->chave;
                    if(arv->numElemento != 1)balanceamentoRemocao(arv, LeftNode, actually->pai, valor);
                    actually->chave = a;free(actually);
                    arv->numElemento--;
                    return 1;}
                    else if (actually->Fesq != NULL && actually->Fdir == NULL) {aux = actually->Fesq;if (actually->pai->chave > actually->chave) aux->pai->pai->Fesq = actually->Fesq;
                    else aux->pai->pai->Fdir = actually->Fesq;
                    aux->pai = actually->pai;LeftNode = actually->Fesq;
                    int a = LeftNode->chave;
                    if(arv->numElemento != 1)balanceamentoRemocao(arv, LeftNode, actually->pai, valor);
                    actually->chave = a;free(actually);
                    arv->numElemento--;return 1;}
                    else {LeftNode = actually->Fdir;
                    while (LeftNode->Fesq != NULL) LeftNode = LeftNode->Fesq;
                    int a = LeftNode->chave;
                    removeNo(arv, LeftNode->chave);
                    actually->chave = a;}} 
                else{ if (actually->Fesq == NULL && actually->Fdir == NULL) {
                    if (actually->pai->chave > actually->chave) actually->pai->Fesq = NULL;
                    else actually->pai->Fdir = NULL;
                    free(actually);
                    arv->numElemento--;return 1;} 
                    else if (actually->Fesq == NULL && actually->Fdir != NULL) {aux = actually->Fdir;
                    if (actually->pai->chave > actually->chave) aux->pai->pai->Fesq = actually->Fdir;
                    else aux->pai->pai->Fdir = actually->Fdir;
                    aux->pai = actually->pai;LeftNode = actually->Fdir;
                    while (LeftNode->Fesq != NULL) LeftNode = LeftNode->Fesq;
                    free(actually);arv->numElemento--;return 1;} 
                    else if (actually->Fesq != NULL && actually->Fdir == NULL) {aux = actually->Fesq;if (actually->pai->chave > actually->chave) aux->pai->pai->Fesq = actually->Fesq;
                    else aux->pai->pai->Fdir = actually->Fesq;
                    aux->pai = actually->pai;free(actually);arv->numElemento--;return 1;} 
                    else {LeftNode = actually->Fdir;
                    while (LeftNode->Fesq != NULL) LeftNode = LeftNode->Fesq;
                    int a = LeftNode->chave;removeNo(arv, LeftNode->chave);actually->chave = a;}}}
                    if (actually->chave < valor) actually = actually->Fdir;else actually = actually->Fesq;}
                    return -1;
}
void imprimeOrdem(no *raiz) {
if (raiz != NULL) {imprimeOrdem(raiz->Fesq);printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);imprimeOrdem(raiz->Fdir);}}
void imprimePreOrdem(rb *arv, no *raiz) {
if (raiz != NULL) {printf("%d: %c -- %d\n", raiz->chave, raiz->cor, raiz->pai->chave);imprimePreOrdem(arv, raiz->Fesq);imprimePreOrdem(arv, raiz->Fdir);}}

no *getRaiz(rb *arv) {return arv->sentinela->Fdir;}
int getNumElementos(rb *arv) {return arv->numElemento;}
int processaCarga(rb *arv, char *nomeArquivo, int tipo) {
FILE *arquivo;int valor;arquivo = fopen(nomeArquivo, "r");
if (arquivo == NULL) {printf("Erro ao abrir o arquivo");return -2;}
if (tipo == 1) 
{while (fscanf(arquivo, "%d", &valor) == 1) insereNo(arv, valor);}
if (tipo == 2)
{while (fscanf(arquivo, "%d", &valor) == 1) removeNo(arv, valor);}
fclose(arquivo);
return 1;
}
void balanceamentoInsercao(rb *arv, no *noDesbal) {
    no *tio;
    no *avo = noDesbal->pai->pai;
    if (noDesbal->chave < avo->chave) {
        if (avo->Fdir == NULL) tio = arv->sentinelaFolha; else tio = avo->Fdir;

        if (tio->cor == 'V') {
            noDesbal->pai->cor = 'P';
            tio->cor = 'P';
            avo->cor = 'V';
            if (avo->pai->cor == 'V') balanceamentoInsercao(arv, avo);
        } else { 
            if (noDesbal->chave > noDesbal->pai->chave) {
                rotacaoEsq(arv, noDesbal->pai);
                noDesbal->cor = 'P';
                avo->cor = 'V';
                rotacaoDir(arv, avo);
            }

            else { 
                noDesbal->pai->cor = 'P';
                avo->cor = 'V';
                rotacaoDir(arv, avo);}}
    } else { 

        if (avo->Fesq == NULL) 
            tio = arv->sentinelaFolha;
        else
            tio = avo->Fesq;

        if (tio->cor == 'V') {
            noDesbal->pai->cor = 'P';
            tio->cor = 'P';
            avo->cor = 'V';
            if (avo->pai->cor == 'V')
                balanceamentoInsercao(arv, avo);
        }

        else {

            if (noDesbal->chave < noDesbal->pai->chave) { 
                rotacaoDir(arv, noDesbal->pai);
                noDesbal->cor = 'P';
                avo->cor = 'V';
                rotacaoEsq(arv, avo);
            }

            else {
                noDesbal->pai->cor = 'P';
                avo->cor = 'V';
                rotacaoEsq(arv, avo);
            }
        }
    }
    arv->sentinela->Fdir->cor = 'P';
}
void balanceamentoRemocao(rb *arv, no *noDesbal, no *pai, int valor) {
    (void)valor;
    while (noDesbal != arv->sentinela->Fdir && (noDesbal == NULL || noDesbal->cor == 'P')) {
        if (noDesbal == pai->Fesq || pai->Fesq == NULL) {
            no *irmao = pai->Fdir;

            if (irmao == NULL) irmao = arv->sentinelaFolha;

            if (irmao->cor == 'V') {
                irmao->cor = 'P';
                pai->cor = 'V';
                rotacaoEsq(arv, pai);
                irmao = pai->Fdir;
            }

            if ((irmao->Fesq == NULL || irmao->Fesq->cor == 'P') &&
                (irmao->Fdir == NULL || irmao->Fdir->cor == 'P')) {
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            } else {
                if (irmao->Fdir == NULL || irmao->Fdir->cor == 'P') {
                    if (irmao->Fesq != NULL) irmao->Fesq->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoDir(arv, irmao);
                    irmao = pai->Fdir;
                }
                irmao->cor = pai->cor;
                pai->cor = 'P';
                if (irmao->Fdir != NULL) irmao->Fdir->cor = 'P';
                rotacaoEsq(arv, pai);
                noDesbal = arv->sentinela->Fdir;
                break;
            }
        } else {
            no *irmao = pai->Fesq;

            if (irmao == NULL) irmao = arv->sentinelaFolha;

            if (irmao->cor == 'V') {
                irmao->cor = 'P';
                pai->cor = 'V';
                rotacaoDir(arv, pai);
                irmao = pai->Fesq;
            }

            if ((irmao->Fesq == NULL || irmao->Fesq->cor == 'P') &&
                (irmao->Fdir == NULL || irmao->Fdir->cor == 'P')) {
                irmao->cor = 'V';
                noDesbal = pai;
                pai = noDesbal->pai;
            } else {
                if (irmao->Fesq == NULL || irmao->Fesq->cor == 'P') {
                    if (irmao->Fdir != NULL) irmao->Fdir->cor = 'P';
                    irmao->cor = 'V';
                    rotacaoEsq(arv, irmao);
                    irmao = pai->Fesq;
                }
                irmao->cor = pai->cor;
                pai->cor = 'P';
                if (irmao->Fesq != NULL) irmao->Fesq->cor = 'P';
                rotacaoDir(arv, pai);
                noDesbal = arv->sentinela->Fdir;
                break;
            }
        }
    }
    if (noDesbal != NULL) noDesbal->cor = 'P';
}
void rotacaoDir(rb *arv, no *noDesbal) {
    (void)arv;
    no *filhoEsquerdo = noDesbal->Fesq;noDesbal->Fesq = filhoEsquerdo->Fdir;
    if (filhoEsquerdo->Fdir != NULL) filhoEsquerdo->Fdir->pai = noDesbal;
    filhoEsquerdo->pai = noDesbal->pai;
    if (noDesbal == noDesbal->pai->Fdir) noDesbal->pai->Fdir = filhoEsquerdo; 
    else noDesbal->pai->Fesq = filhoEsquerdo;
    filhoEsquerdo->Fdir = noDesbal; noDesbal->pai = filhoEsquerdo;
    count++;
}

void rotacaoEsq(rb *arv, no *noDesbal) {
    (void)arv;        
    no *filhoDireito = noDesbal->Fdir;
    noDesbal->Fdir = filhoDireito->Fesq;
    if (filhoDireito->Fesq != NULL) filhoDireito->Fesq->pai = noDesbal;
    filhoDireito->pai = noDesbal->pai;
    if (noDesbal == noDesbal->pai->Fesq) noDesbal->pai->Fesq = filhoDireito;
    else noDesbal->pai->Fdir = filhoDireito;
    filhoDireito->Fesq = noDesbal;noDesbal->pai = filhoDireito;
    count ++;
}

int Rotations(){
    return count; 
}

void ResetaContador(){
    count = 0;
}


struct no* buscaNo(rb *arv, int valor) {
    no *atual = arv->sentinela->Fdir;
    while (atual != NULL && atual != arv->sentinelaFolha && atual->chave != valor) {
        if (valor < atual->chave)
            atual = atual->Fesq;
        else
            atual = atual->Fdir;
    }
    if (atual == arv->sentinelaFolha)
        return NULL; 
    return atual;
}

void liberaNos(no *raiz, no *sentinelaFolha) {
    if (raiz != sentinelaFolha && raiz != NULL) {
        liberaNos(raiz->Fesq, sentinelaFolha);
        liberaNos(raiz->Fdir, sentinelaFolha);
        free(raiz);
    }
}

void limpaArvore(rb *arv) {
    if (arv != NULL) {
        liberaNos(arv->sentinela->Fdir, arv->sentinelaFolha); // Libera todos os nós da árvore
        free(arv->sentinelaFolha); // Libera a sentinela folha
        free(arv->sentinela); // Libera a sentinela
        free(arv); // Libera a estrutura da árvore
    }
}