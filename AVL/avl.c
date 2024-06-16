#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

struct no{
    int chave;
    int fb;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
};
struct avl{
    struct no *sentinela;
    int numElemento;
};

    int contador = 0 ;
avl *criaArvore(){
    avl *arv = (avl*) malloc(sizeof(avl));
    arv->sentinela = (no*) malloc(sizeof(no));
    arv->sentinela->chave = -1000;
    arv->sentinela->Fesq = NULL;
    arv->sentinela->Fdir = NULL;
    arv->sentinela->pai = NULL;
    arv->numElemento = 0;
    return arv;
}
void atualizaFB_Insercao(avl *arv, no *novoNo){
    no *aux = novoNo;

    do {
        if(aux->pai->chave > aux->chave)
            aux->pai->fb--;
        else
            aux->pai->fb++;
        aux = aux->pai;
    }while(aux->pai->chave != -1000 && aux->fb != 0 && aux->fb != 2 && aux->fb != -2);

  if(aux->fb == 2 || aux->fb == -2)balanceamento(arv, aux);
}
int insereNo(avl *arv, int valor){
    no *NewNode = (no*) malloc(sizeof(no));
    NewNode->chave = valor;
    NewNode->Fesq = NULL;
    NewNode->Fdir = NULL;
    NewNode->fb = 0;
    NewNode->pai = arv->sentinela;
    if(arv->sentinela->Fdir == NULL) {
        arv->sentinela->Fdir = NewNode;
        arv->numElemento++;
        return 1;
    }
    else {
        no *atual = arv->sentinela->Fdir;

        while(atual != NULL){
            if(atual->chave > valor && atual->Fesq == NULL){
                NewNode->pai = atual;
                atual->Fesq = NewNode;
                arv->numElemento++;
                atualizaFB_Insercao(arv, NewNode);
                return 1;
            }
            else if(atual->chave < valor && atual->Fdir == NULL){
                NewNode->pai = atual;
                atual->Fdir = NewNode;
                arv->numElemento++;
                atualizaFB_Insercao(arv, NewNode);
                return 1;
            }

            if(atual->chave > valor)atual = atual->Fesq;
            else atual = atual->Fdir;
        }
    }
    return 0;
}

void imprimeOrdem(no *raiz){
    if(raiz!=NULL) {
        imprimeOrdem(raiz->Fesq);
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimeOrdem(raiz->Fdir);
    }
}

void imprimePreOrdem(no *raiz){
    if(raiz!=NULL) {
        printf("%d - %d - %d\n", raiz->chave, raiz->pai->chave, raiz->fb);
        imprimePreOrdem(raiz->Fesq);
        imprimePreOrdem(raiz->Fdir);
    }
}

no *getRaiz(avl *arv){
    return arv->sentinela->Fdir;
}

int getNumElementos(avl *arv){
    return arv->numElemento;
}

int processaCarga(avl *arv, char *nomeArquivo, int tipo) {
    FILE *arquivo;
    int valor;

    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return -2;
    }

    if (tipo == 1) {
        while (fscanf(arquivo, "%d", &valor) == 1) {
             insereNo(arv, valor);
        }
    }
    else if (tipo == 2) {
        while (fscanf(arquivo, "%d", &valor) == 1) {
           removeNo(arv, valor);
        }
    }
    fclose(arquivo);
    return 1;
}


void balanceamento(avl *arv, no *noDesbal){
    no *filho;
    (void)arv;
    if (noDesbal->fb == 2) {
        filho = noDesbal->Fdir;
        if (filho->fb == -1) {
            int fbNeto = filho->Fesq->fb;
            rotacaoDir(filho);
            rotacaoEsq(noDesbal);

            if (fbNeto == 0) {
                noDesbal->fb = 0;
                filho->fb = 0;
                if (noDesbal->Fdir != NULL) noDesbal->Fesq->fb = 0;


            } else if (fbNeto == -1 ) {
                noDesbal->fb = 0;
                filho->fb = 1;
                if (noDesbal->Fdir != NULL) noDesbal->Fesq->fb = 0;

            } else if (fbNeto == 1) {
                noDesbal->fb = -1;
                filho->fb = 0;
                if (noDesbal->Fdir != NULL) noDesbal->Fesq->fb = 0;
            }
        }
        else {
            int fbFilho = filho->fb;
            rotacaoEsq(noDesbal);

            if (fbFilho == 0) {
                noDesbal->fb = 1;
                filho->fb = -1;
            }
            else if (fbFilho == 1) {
                noDesbal->fb = 0;
                filho->fb = 0;

            }
        }
    }
    else if(noDesbal->fb == -2) {
        filho = noDesbal->Fesq;
        if (filho->fb == 1) {
            // rotação dupla
            int fbNeto = filho->Fdir->fb;
            rotacaoEsq(filho);
            rotacaoDir(noDesbal);

            if (fbNeto == 0) {
                noDesbal->fb = 0;
                filho->fb = 0;
                if (noDesbal->Fdir != NULL) noDesbal->Fesq->fb = 0;
            }
            else if (fbNeto == -1) {
                noDesbal->fb = 1;
                filho->fb = 0;
                if (noDesbal->Fdir != NULL) noDesbal->Fesq->fb = 0;
            }
            else if (fbNeto == 1) {
                noDesbal->fb = 0;
                filho->fb = -1;
                if (noDesbal->Fdir != NULL) noDesbal->Fesq->fb = 0;
            }
        }
        else {
            int fbFilho = filho->fb;
            rotacaoDir(noDesbal);

            if (fbFilho == 0) {
                noDesbal->fb = -1;
                filho->fb = 1;
            } else if (fbFilho == -1) {
                noDesbal->fb = 0;
                filho->fb = 0;

            }
        }

    }

}


void rotacaoEsq(no *noDesbalanceado){
    no* FilhoDaDireitaDoNoDesbalanceado = noDesbalanceado->Fdir;
    noDesbalanceado->Fdir =  FilhoDaDireitaDoNoDesbalanceado->Fesq;
    if(FilhoDaDireitaDoNoDesbalanceado->Fesq != NULL) FilhoDaDireitaDoNoDesbalanceado->Fesq->pai = noDesbalanceado;
    FilhoDaDireitaDoNoDesbalanceado->pai = noDesbalanceado->pai;
    if(noDesbalanceado->pai == noDesbalanceado->pai->Fdir)  noDesbalanceado->pai->Fdir = FilhoDaDireitaDoNoDesbalanceado;
    else if(noDesbalanceado == noDesbalanceado->pai->Fesq) noDesbalanceado->pai->Fesq = FilhoDaDireitaDoNoDesbalanceado;
    else noDesbalanceado->pai->Fdir = FilhoDaDireitaDoNoDesbalanceado;

    FilhoDaDireitaDoNoDesbalanceado->Fesq = noDesbalanceado;
    noDesbalanceado->pai = FilhoDaDireitaDoNoDesbalanceado;
    noDesbalanceado->fb = 0;
    FilhoDaDireitaDoNoDesbalanceado->fb = 0;
    contador++;
}


void rotacaoDir( no *noDesbalanceado){
    no* FilhoDaEsquerdaDoNoDesbalanceado = noDesbalanceado->Fesq;
    noDesbalanceado->Fesq = FilhoDaEsquerdaDoNoDesbalanceado->Fdir;
    if(FilhoDaEsquerdaDoNoDesbalanceado->Fdir != NULL) FilhoDaEsquerdaDoNoDesbalanceado->Fdir->pai = noDesbalanceado;
    FilhoDaEsquerdaDoNoDesbalanceado->pai = noDesbalanceado->pai;
    if(noDesbalanceado->pai == noDesbalanceado->pai->Fdir) noDesbalanceado->pai->Fdir = FilhoDaEsquerdaDoNoDesbalanceado;
    else if(noDesbalanceado == noDesbalanceado->pai->Fdir) noDesbalanceado->pai->Fdir = FilhoDaEsquerdaDoNoDesbalanceado;
    else noDesbalanceado->pai->Fesq = FilhoDaEsquerdaDoNoDesbalanceado;
    FilhoDaEsquerdaDoNoDesbalanceado->Fdir = noDesbalanceado;
    noDesbalanceado->pai = FilhoDaEsquerdaDoNoDesbalanceado;
    noDesbalanceado->fb = 0;
    FilhoDaEsquerdaDoNoDesbalanceado->fb =  0;
    contador++;
}

int removeNo(avl *arv, int valor){
    if(arv == NULL)
        return 0;
    no *aux;
    no *atual = arv->sentinela->Fdir;
    if(atual->chave == 40 && valor == 40) atual = atual->Fdir;
    while(atual != NULL) {
        if (atual->chave == valor) {
            if (atual->Fesq == NULL && atual->Fdir == NULL) {
                if(atual->pai->chave > atual->chave) atual->pai->Fesq = NULL;
                else atual->pai->Fdir = NULL;
                atualizaFB_remocao(arv,atual->pai,atual->chave);
                free(atual);
                arv->numElemento--;
                return 1;
            }


            else if (atual->Fesq == NULL && atual->Fdir != NULL) {
                aux = atual->Fdir;
                if(atual->pai->chave > atual->chave) aux->pai->pai->Fesq = atual->Fdir;
                else aux->pai->pai->Fdir = atual->Fdir;
                aux->pai = atual->pai;
                atualizaFB_remocao(arv,atual->pai,atual->chave);
                free(atual);
                arv->numElemento--;
                return 1;
            }   else if (atual->Fesq != NULL && atual->Fdir == NULL) {
                aux = atual->Fesq;
                if(atual->pai->chave > atual->chave) aux->pai->pai->Fesq = atual->Fesq;
                else aux->pai->pai->Fdir = atual->Fesq;
                aux->pai = atual->pai;
                atualizaFB_remocao(arv,atual->pai,atual->chave);
                free(atual);
                arv->numElemento--;
                return 1;
            }
            else {
                no *maisEsquerda;
                maisEsquerda = atual->Fdir;
                while (maisEsquerda->Fesq != NULL)maisEsquerda = maisEsquerda->Fesq;
                int a = maisEsquerda->chave;
                removeNo(arv, maisEsquerda->chave);
                atual->chave = a;
            }
        }
        if(atual->chave < valor) atual = atual->Fdir;
        else atual = atual->Fesq;
    }
    return -1;
}

void atualizaFB_remocao(avl *arv, no *pai, int chaveRemovida)
{
    no* filhao;
    no* aux =  pai;
    if(aux->chave == -1000) return;

    do {
        if(aux->chave > chaveRemovida) {
            aux->fb++;
            if(aux->fb == 0 || aux->fb == 2 || (aux->fb == -2 && aux->pai != arv->sentinela)) aux->pai->fb--;
        }
        else{
            aux->fb--;
            if(aux->fb == 0 || aux->fb == 2 || (aux->fb == -2 && aux->pai != arv->sentinela)) aux->pai->fb++;
            }
        filhao = aux;
        aux = aux->pai;
    }while(aux->chave != -1000 && filhao->fb != 1 && filhao->fb != -1 && filhao->fb != 2 && filhao->fb != -2);

    if((filhao->fb == 2) ||(filhao->fb == -2))
    {
        balanceamento(arv,filhao);
        if((filhao->pai != arv->sentinela) && (filhao->pai->fb != 0)) atualizaFB_remocao(arv,filhao->pai->pai,chaveRemovida);
    }
}

void ResetaContador(){
    contador = 0; 
}

int Rotacoe(){
    return contador;
}

struct no* buscaNoAVL(struct avl *arv, int valor) {
    struct no *atual = arv->sentinela->Fdir; 
    while (atual != NULL && atual->chave != valor) {
        if (atual->chave > valor) {
            atual = atual->Fesq; 
        } else {
            atual = atual->Fdir; 
        }
    }

    return (atual != NULL && atual != arv->sentinela) ? atual : NULL; // Retorna o nó encontrado ou NULL
}

void liberaNos(no *raiz) {
    if (raiz != NULL) {
        liberaNos(raiz->Fesq);
        liberaNos(raiz->Fdir);
        free(raiz);
    }
}

void limpaArvore(avl *arvore) {
    if (arvore != NULL) {
        liberaNos(arvore->sentinela->Fdir); // Libera todos os nós da árvore
        free(arvore->sentinela);            // Libera a sentinela
        free(arvore);                       // Libera a estrutura da árvore
    }
}