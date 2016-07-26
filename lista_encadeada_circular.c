#include<stdio.h>
#include<stdlib.h> // malloc

struct elemento {
	int dado;
	struct elemento *proximo;
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
	} while (e != lista);

	return t;
}

struct elemento * ultimo_elemento(struct elemento *lista) {
	struct elemento *e = lista;

	do {
		e = e->proximo;
	} while (e->proximo != lista);

	return e;
}

void insere(struct elemento **lista, int i) {
	struct elemento *e, *ultimo;

	e = malloc(sizeof(struct elemento));
	e->dado = i;

	if (*lista != NULL) {
		e->proximo = *lista; // Aponta para o restante da lista
		ultimo = ultimo_elemento(*lista); // Encontra ultimo elemento da lista
		ultimo->proximo = e; // Aponta o ultimo para o primeiro
		*lista = e; // Novo elemento eh o primeiro da lista
	} else {
		e->proximo = e; // Aponta pra si pois eh unico o elemento
		*lista = e; // Elemento eh o primeiro
	}
}

void imprimir_it(struct elemento *fila) {
	struct elemento *e = fila;

	if (e != NULL) {
		do {
			printf("%d  ", e->dado); // Imprime primeiro elemento
			e = e->proximo; // Aponta para o restante da fila
		} while (e != fila);
	}
	printf("\n"); // Apenas imprime uma linha em branco
}

void remove_elemento(struct elemento **fila, int i) {
	struct elemento *atual = *fila, *anterior = *fila;

	if (atual == NULL)
		return;

	 do {
		if (atual->dado == i) { // Encontrou elemento i
			if (atual == *fila) { // Se for o primeiro elemento
				struct elemento *ultimo = ultimo_elemento(*fila);
				*fila = atual->proximo; // Segundo elemento passa a ser o primeiro
				ultimo->proximo = *fila; // Lista circular
			} else {
				// O elemento anterior aponta para o posterior
				anterior->proximo = atual->proximo;
			}

			free(atual); // Desaloca elemento
			return;
		}

		anterior = atual; // Elemento atual passa a ser o anterio
		atual = (atual)->proximo; // Proximo elemento passa a ser o atual
	} while (atual != *fila);
}

void destruir(struct elemento **fila) {
	struct elemento *e = *fila, *aux = *fila;

	if (e != NULL) { // Se a lista não for vazia
		do {
			aux = e->proximo; // Armazena segundo elemento
			free(e); // Desaloca primeiro elemento
			e = aux; // Segundo elemento passa a ser o primeiro
		} while (*fila != e); // Enquanto não voltar ao inicio
		*fila = NULL; // Fila vazia
	}
}

int main() {
	struct elemento *lista;

	lista = criar();
	insere(&lista, 2);
	insere(&lista, 1);

	printf("Tamanho: %d\n", tamanho(lista));
	imprimir_it(lista);

	//remove_elemento(&lista, 2);
	printf("\nTamanho: %d\n", tamanho(lista));
	imprimir_it(lista);

	destruir(&lista);
		printf("\nTamanho: %d\n", tamanho(lista));
	imprimir_it(lista);

	return 0;
}