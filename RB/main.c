#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rubroNegra.h"

#define NUM_ELEMENTS 10000

void benchmarkInsert(rb *tree, int *elements, int num_elements) {
    int rotations; 
    clock_t start = clock();
    for (int i = 0; i < num_elements; i++) {
        insereNo(tree, elements[i]);
    }
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    rotations = Rotations();
    printf("Tempo de inserção: %f segundos\nRotações: %d\n", time_taken, rotations);
    ResetaContador();
}

void benchmarkRemove(rb *tree, int *elements, int num_elements) {
    int rotations;
    clock_t start = clock();
    for (int i = 0; i < num_elements; i++) {
        removeNo(tree, elements[i]);
    }
    clock_t end = clock();
    rotations = Rotations();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de remoção: %f segundos\nRotações: %d\n", time_taken, rotations);
}

void benchmarkSearch(rb *tree, int *elements, int num_elements) {
    clock_t start = clock();
    for (int i = 0; i < num_elements; i++) {
        buscaNo(tree, elements[i]);
    }
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tempo gasto para buscar %d elementos: %f segundos\n", num_elements, time_spent);
}

int* criaVetor(int tamanho) {
    int intervalo = 5;
    int *elements = (int *)malloc(tamanho * sizeof(int));
    if (!elements) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }
    elements[0] = rand() % intervalo;
    for (int i = 1; i < tamanho; i++) {
        elements[i] = elements[i - 1] + (rand() % intervalo);
    }
    return elements;
}

int main() {
    srand(time(NULL));  // Inicializa o gerador de números aleatórios

    int* elements = criaVetor(NUM_ELEMENTS);
    int* lastOnes = elements + (NUM_ELEMENTS - 1000);

    rb *tree = criaArvore();

    printf("Benchmark de Inserção:\n");
    benchmarkInsert(tree, elements, NUM_ELEMENTS);

    printf("Benchmark de Remoção:\n");
    benchmarkRemove(tree, elements, NUM_ELEMENTS);
    limpaArvore(tree);

    tree = criaArvore();  // Recria a árvore para o benchmark de busca
    for (int i = 0; i < NUM_ELEMENTS; i++) {
        insereNo(tree, elements[i]);
    }

    printf("Benchmark de Busca:\n");
    benchmarkSearch(tree, lastOnes, 1000);

    free(elements);
    limpaArvore(tree);
    return 0;
}
