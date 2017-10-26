#include "dicionario.h"

trie cria_arvore(){
 return(cria_nodo("\0")); // Nodo raíz tem "\0" como palavra
}
 
trie cria_nodo(char palavra[]){

	trie nodo = malloc(sizeof(*nodo));
 	
 	strcpy (nodo->palavra, palavra);

	return (nodo);
}

void trie_add(trie nodo, char palavra[], int indice){
	int letra_nova = 1; /* Variável para verificar se a letra atual
					       de palavra[] já não está inserida na árvore */
	
	/* Como os 26 apontadores da árvore representam o alfabeto, para adequa-los
	  a tabela ASCII é necessário subtrair 97 (que corresponde ao caractere 'a') 
	  da letra atualmente sendo checada */

	if(nodo->prox[palavra[indice] -97] != NULL) letra_nova = 0;

	if(letra_nova){
		insere_nova_letra(nodo, palavra, indice);
		return;
	}
	
	nodo = nodo->prox[palavra[indice]-'a']; //Percorrendo a árvore
	indice++; //Indice para percorrer o vetor palavra[]
	trie_add(nodo, palavra, indice);
}

void insere_nova_letra(trie raiz, char palavra[], int indice){
	char aux = 'a'; trie nodo = raiz;

	while(palavra[indice] != '\0'){ // Percorre a árvore criando nodos com "\o" até o nodo final que armazena a palavra
		if(aux == palavra[indice]){
			nodo->prox[aux-'a'] = cria_nodo("\0");
			nodo = nodo->prox[aux-'a'];
			aux = 'a';
			indice++;
		}
	aux++;
	}
	strcpy(nodo->palavra, palavra);
}

/* Função para imprimir as palavras inseridas na árvore

void imprime_palavras(trie raiz){
	trie nodo = raiz; int i;

	if(nodo->palavra[0] != '\0') printf("%s\n", nodo->palavra);

	for(i = 0; i < 26; i++)
		if(nodo->prox[i]) imprime_palavras(nodo->prox[i]); 
} */ 

void le_entrada(trie raiz){
	char palavra[40];
	FILE *dicionario;

	//Abre o dic.txt
	dicionario = fopen("./dic.txt", "r+");

	if (dicionario == NULL) printf("NULL");

	//Percorre o dic.txt até o fim inserindo cada palavra na árvore
	while(!feof(dicionario)){
		fscanf(dicionario, "%s", palavra);
		strlowcase(palavra);
		trie_add(raiz, palavra, 0);
	}
	fclose(dicionario);
}

void strlowcase (char *pal){ //Função para transformar todas as letras em mínusculas
 while (*pal){
  (*pal) = tolower (*pal);
  pal++;
 }
}

void le_palavras(trie raiz){
	char palavra[40]; int i; //Le o arquivo de entrada e compara cada palavra com o dicionário

	while(scanf("%s", palavra) != EOF){
		scanf("%d", &i);
		strlowcase(palavra);
		printf("%s:", palavra);
		int virgula = 0;
		compara_palavra(raiz, palavra, 0, i, 0, &virgula); //Chamando a função para comparar
		printf("\n");
	}
}

void compara_palavra(trie nodo, char palavra[], int indice, int i, int diferenca, int *virgula){
	int n, k, indiceaux = indice + 1, dif = diferenca + 1; //Variáveis auxiliares
	trie aux; //Nodo auxiliar para não modificar o original

	if((nodo->palavra[0] != '\0')&&(diferenca <= i)) { //Verifica se está num nodo palavra e se a diferença não extrapolou o limite
		if (*virgula){ //verifica se ja foi impressa alguma palavra, para colocar virgula
                if(*virgula < 20){ //verifica se foram impressas 20 palavras, para interromper busca
                    printf(", %s", nodo->palavra);
                    virgula++;
                }
                else return;
        }
		else {
			printf("%s", nodo->palavra);
			*virgula = 1;
		}
	}
	if(diferenca > i) return; //Se já extrapolou, somente volta
		
	for(n = 0; n < 26; n++){ //Loop para verificar todos ponteiros (letras do alfabeto) de um nodo
		if((nodo->prox[n] != NULL)){ //Verificando se o prox não é NULL, ou seja, contem palavra
			aux = nodo->prox[n];
			// if para verificar se a letra está no dicionário
			if(n+'a' == palavra[indice])compara_palavra(aux, palavra, indiceaux, i, diferenca, virgula);
			else{ //loop para testar palavras com letra faltando
				for (k = 0; k < 26; k++) {
					if((aux->prox[k] != NULL) && (k + 'a' == palavra[indice]))
						compara_palavra(aux, palavra, indice, i, dif+1, virgula);
					}
					// Verifica letras diferentes
						compara_palavra(aux, palavra, indiceaux, i, dif, virgula);
			}
		}
	}
}
