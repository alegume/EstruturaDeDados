#include<stdio.h>
#include<stdlib.h> // malloc

struct elemento {
	int dado;
	struct elemento *proximo, *anterior;
};

struct elemento *criar() {
	return NULL;
}

int tamanho(struct elemento *lista) {
	struct elemento *e = lista;
	int t = 0;

	if (lista == NULL)
		return 0;

	do {
		t++;
		e = e->proximo;
	} while (e != NULL);

	return t;
}

void insere(struct elemento **lista, int i) {
	struct elemento *e, *aux;

	e = malloc(sizeof(struct elemento));
	e->dado = i;

	if (*lista != NULL) {
		e->proximo = *lista; // Aponta para o restante da lista
		e->anterior = NULL; // Primeiro aponta pra NULL
		(*lista)->anterior = e; // Lista aponta para elemento
		*lista = e; // Novo elemento eh o primeiro da lista
	} else {
		e->anterior = NULL;
		e->proximo = NULL;
		*lista = e;
	}
}

void imprimir_it(struct elemento *fila) {
	while (fila != NULL) {
		printf("%d  ", fila->dado); // Imprime primeiro elemento
		fila = fila->proximo; // Aponta para o restante da fila
	}
	printf("\n"); // Apenas imprime uma linha em branco
}

void remove_elemento(struct elemento **fila, int i) {
	struct elemento *atual = *fila;

	while (atual != NULL) {
		if (atual->dado == i) { // Encontrou elemento i
			if (atual == *fila) { // Se for o primeiro elemento
				*fila = atual->proximo; // Segundo elemento passa a ser o primeiro
				(*fila)->anterior = NULL;
			} else {
				// O elem. anterior aponta para o posterior
				atual->anterior->proximo = atual->proximo;
				// O elem. posterior aponta para o anterior se nao for o ultimo
				if (atual->proximo != NULL)
					atual->proximo->anterior = atual->anterior;
			}
			free(atual); // Desaloca elemento
			return;
		}

		atual = atual->proximo; // Proximo elemento passa a ser o atual
	}
}

void destruir(struct elemento **fila) {
	struct elemento *e = *fila;

	while (e != NULL) {
		*fila = e->proximo;
		free(e);
		e = (*fila);
	}
}

int main() {
	struct elemento *lista;

	lista = criar();
	insere(&lista, 2);
	insere(&lista, 1);

	printf("Tamanho: %d\n", tamanho(lista));
	imprimir_it(lista);

	remove_elemento(&lista, 2);
	printf("\nTamanho: %d\n", tamanho(lista));
	imprimir_it(lista);

	destruir(&lista);

	return 0;
}