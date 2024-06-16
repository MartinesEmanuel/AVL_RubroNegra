# Comparação entre Árvores Rubro-Negra e AVL

Este projeto compara o desempenho das estruturas de dados Árvore Rubro-Negra e AVL em diferentes operações, como inserção, remoção, busca e o número de rotações.

## Introdução

Árvores Rubro-Negras e AVL são estruturas de dados de árvores binárias balanceadas que mantêm suas propriedades balanceadas através de rotações. Cada uma tem suas vantagens e desvantagens, especialmente em relação ao desempenho e à eficiência em diferentes tipos de operações.

### Estruturas Comparadas

- **Árvore Rubro-Negra**: É uma árvore binária de busca balanceada, onde cada nó tem uma cor (vermelho ou preto) que satisfaz determinadas propriedades para manter o balanceamento.
  
- **Árvore AVL**: É uma árvore binária de busca balanceada em que a altura de subárvores esquerdas e direitas de cada nó difere em no máximo uma unidade.

## Resultados e Análise

Os gráficos abaixo mostram a comparação entre as árvores AVL e Rubro-Negra em termos de tempo de execução (em segundos) e número de rotações.

### Comparação de Tempo de Inserção

![insertion_times_comparison](https://github.com/MartinesEmanuel/AVL_RubroNegra/assets/104658309/78ddf585-27c6-4c6e-a373-54674cd86432)



### Comparação de Tempo de Remoção
![removal_times_comparison](https://github.com/MartinesEmanuel/AVL_RubroNegra/assets/104658309/1a3e89f6-1e37-40e2-bc06-1163df22e9b6)


### Comparação de Tempo de Busca

![search_times_comparison](https://github.com/MartinesEmanuel/AVL_RubroNegra/assets/104658309/c6264eaf-f465-41d6-84ba-6cd9bb82196a)


### Comparação de Rotações de Inserção

![insertion_rotations_comparison](https://github.com/MartinesEmanuel/AVL_RubroNegra/assets/104658309/970a65a1-36ed-4770-a1b1-2baa43a3c661)

### Comparação de Rotações de Remoção

![removal_rotations_comparison](https://github.com/MartinesEmanuel/AVL_RubroNegra/assets/104658309/0b34766c-e4ef-4fd0-97fa-84a242487452)

## Conclusão

Em resumo, a escolha entre uma árvore Rubro-Negra e uma árvore AVL depende das características específicas do seu uso. Se o tempo de inserção e remoção é crítico e a memória não é um problema, a árvore Rubro-Negra pode ser preferível. Se você precisa de um tempo de pesquisa mais rápido e pode tolerar tempos de inserção e remoção um pouco mais lentos, a árvore AVL pode ser a melhor escolha.

## Como Usar

1. Clone este repositório:

```bash
https://github.com/MartinesEmanuel/AVL_RubroNegra
