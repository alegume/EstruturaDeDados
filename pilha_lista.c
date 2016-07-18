#include<stdio.h>
#include<stdlib.h> // malloc

struct elemento {
	char dado;
	struct elemento *prox;
};

struct elemento *criar() {
	return NULL;
}

void empilhar(struct elemento **topo, char c) {
	struct elemento *no;

	no = malloc(sizeof(struct elemento));
	if (!no)
		exit(1); // Erro ao alocar memoria
	no->dado = c;
	no->prox = *topo; // aponta para o restante da pilha
	*topo = no; // Esse no passa a ser o topo
}

char desempilhar(struct elemento **topo) {
	struct elemento *aux; 
	char dado;

	if (*topo == NULL) {
		printf("Pilha vazia \n");
		return '\0';
	}
	aux = (*topo)->prox; // Armazena o restante da pilha
	dado = (*topo)->dado; // Elemento no topo a ser retornado
	free(*topo); // Remove topo da memoria
	*topo = aux; // Agora o topo eh o restante da apilha 

	return dado; 
}

void destruir(struct elemento **topo) {
	struct elemento *aux;

	while (*topo) { // Enquando topo nao for NULL
		aux = (*topo)->prox; // Armazena o restante da pilha
		free(*topo); // Remove topo
		*topo = aux; // Agora o topo eh o restante da apilha 
	}
}

int main() {
	struct elemento *minha_pilha;

	minha_pilha = criar();
	empilhar(&minha_pilha, 'a');
	empilhar(&minha_pilha, 'b');
	empilhar(&minha_pilha, 'c');

	printf("Desempilhando elementos \n");
	while (minha_pilha) {
		char dado;
		dado = desempilhar(&minha_pilha);
		printf("%c \n", dado);
	}
	destruir(&minha_pilha);

	return 0;
}