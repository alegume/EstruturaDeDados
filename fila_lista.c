#include<stdio.h>
#include<stdlib.h> // malloc

struct elemento {
	char dado;
	struct elemento *proximo;
};

struct fila {
	struct elemento *primeiro, *ultimo;
};

struct fila *criar() {
	struct fila *f;
	f = malloc(sizeof(struct fila));
	if (!f)
		exit(1); // Erro ao alocar memoria

	f->primeiro = f->ultimo = NULL;
	return f;
}

void enfileirar(struct fila **fila, char c) {
	struct elemento *no;

	no = malloc(sizeof(struct elemento));
	if (!no)
		exit(1); // Erro ao alocar memoria
	no->dado = c;
	no->proximo = NULL; // Ultimo elemento

	if ((*fila)->ultimo == NULL || (*fila)->primeiro == NULL) { // Criacao da fila
		(*fila)->primeiro = (*fila)->ultimo = no;
	}
	(*fila)->ultimo->proximo = no; // Ultimo elemento aponta para o no criado
	(*fila)->ultimo = no; // No passa a ser o ultimo	
}

char desenfileirar(struct fila **fila) {
	struct elemento *aux; 
	char dado;

	if ((*fila)->primeiro == NULL) {
		printf("Fila vazia \n");
		return '\0';
	}

	aux = (*fila)->primeiro;
	dado = aux->dado; // Elemento a ser retornado
	(*fila)->primeiro = aux->proximo; // O segundo passa a ser o primeiro
	free(aux); // Remove primeiro da memoria

	return dado; 
}

void destruir(struct elemento **primeiro) {
	struct elemento *aux;

	while (*primeiro) { // Enquando topo nao for NULL
		aux = (*primeiro)->proximo; // Armazena o restante da fila
		free(*primeiro); // Remove topo
		*primeiro = aux; // Agora o topo eh o restante da afila 
	}
}

int main() {
	struct fila *minha_fila;

	minha_fila = criar();
	enfileirar(&minha_fila, 'a');
	enfileirar(&minha_fila, 'b');
	enfileirar(&minha_fila, 'c');

	printf("Desemfileirando elementos \n");
	while (minha_fila->primeiro) {
		char dado;
		dado = desenfileirar(&minha_fila);
		printf("%c \n", dado);
	}

	destruir(&(minha_fila->primeiro));
	desenfileirar(&minha_fila);

	return 0;
}