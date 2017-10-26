#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct nodo_trie *trie;

/* Árvore trie com 26 apontadores em cada nodo (representando o alfabeto) 
   e guardando a palavra no último nodo */

struct nodo_trie{ 
    char palavra[40];
    trie prox[27];
} no;

// Protótipos

trie cria_arvore();
trie cria_nodo(char palavra[]);
void insere_nova_letra(trie raiz, char palavra[], int indice);
void trie_add(trie raiz, char palavra[], int indice);
//void imprime_palavras(trie raiz);
void le_entrada(trie raiz);
void strlowcase (char *pal);
void le_palavras(trie raiz);
void compara_palavra(trie nodo, char palavra[], int indice, int i, int diferenca, int *virgula);