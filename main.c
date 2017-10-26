#include "dicionario.h"
void main(){
	trie raiz;

	raiz = cria_arvore(); // Iniciando a árvore
	le_entrada(raiz); // Lendo palavras do dicionário
	le_palavras(raiz); //Lendo palavras para comparação
	//imprime_palavras(raiz);
}