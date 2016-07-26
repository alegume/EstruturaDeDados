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

	if (lista != NULL)
		return tamanho(lista->proximo) + 1;

	return 0;
}

int tamanho_it(struct elemento *lista) {
	int tamanho = 0;

	while (lista != NULL) {
		tamanho++;
		lista = lista->proximo;
	}

	return tamanho;
}

void insere_inicio(struct elemento **lista, int i) {
	struct elemento *e;

	e = malloc(sizeof(struct elemento));
	e->dado = i;
	e->proximo = *lista; // Aponta para o restante da lista

	*lista = e; // Novo elemento eh o primeiro da lista
}

void insere_final(struct elemento **lista, int i) {
	struct elemento *e, *ultimo = (*lista);

	if (*lista == NULL) { // Lista vazia
		insere_inicio(&(*lista), i);
		return;
	}

	e = malloc(sizeof(struct elemento));
	e->dado = i;
	e->proximo = NULL; // Ultimo elemento aponta para NULL

	while (ultimo->proximo != NULL) // Percorre elementos ate o ultimo
		ultimo = ultimo->proximo;

	ultimo->proximo = e; // Novo elemento eh o ultimo da lista
}

void insere_posicao(struct elemento **lista, int i, int pos) {
	struct elemento *e_novo, *e_pos = (*lista);

	if (pos > tamanho(*lista)) {
		insere_final(lista, i);
		return;
	}

	e_novo = malloc(sizeof(struct elemento));
	e_novo->dado = i;

	// Percorre elementos ate a posicao correta (pos - 1)
	while (e_pos != NULL && pos > 2) {
		e_pos = e_pos->proximo;
		pos--; // Decrementa a cada elemento percorrido
	}
	// Novo elemento aponta para o elemento posterior ao elemtno na posicao
	e_novo->proximo = e_pos->proximo; 
	e_pos->proximo = e_novo; // Elemento na posicao aponta para novo elemento
}

void imprimir(struct elemento *fila) {
	if (fila != NULL) {
		printf("%d  ", fila->dado); // Imprime primeiro elemento
		imprimir(fila->proximo); // Imprime restante da fila
	} else
		printf("\n"); // Apenas imprime uma linha em branco
}

void imprimir_inv(struct elemento *fila) {
	if (fila != NULL) {
		imprimir_inv(fila->proximo); // Imprime restante da fila
		printf("%d  ", fila->dado); // Imprime primeiro elemento
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
	struct elemento *atual = *fila, *anterior = *fila;

	while (atual != NULL) {
		if (atual->dado == i) { // Encontrou elemento i
			if (atual == *fila) { // Se for o primeiro elemento
				*fila = atual->proximo; // Segundo elemento passa a ser o primeiro
			} else {
				// O elemento anterior aponta para o posterior
				anterior->proximo = atual->proximo;
			}
			free(atual); // Desaloca elemento
			return;
		}

		anterior = atual; // Elemento atual passa a ser o anterio
		atual = (atual)->proximo; // Proximo elemento passa a ser o atual
	}
}

int listas_iguais(struct elemento *lista1, struct elemento *lista2) {
	struct elemento *l1 = lista1, *l2 = lista2; // Ponteiros para percorrer as listas

	for (; l1 != NULL && l2 != NULL; l1 = l1->proximo, l2 = l2->proximo) {
		if (l1->dado != l2->dado)
			return 0; // Listas diferentes
	}

	if (l1 != l2) // Apenas uma das listas chegou ao fim
		return 0; // Listas diferentes
	else
		return 1; // Listas iguais
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
	struct elemento *lista, *lista2;

	lista = criar();
	insere_inicio(&lista, 2);
	insere_inicio(&lista, 1);
	insere_final(&lista, 4);
	insere_posicao(&lista, 3, 3); // Insere 3 na terceira posicao

	printf("Tamanho: %d\n", tamanho(lista));
	imprimir(lista);
	imprimir_inv(lista);

	remove_elemento(&lista, 4);
	printf("\nTamanho: %d\n", tamanho(lista));
	imprimir_it(lista);

	printf("\n--- Lista 2 --- \n");
	lista2 = criar();

	insere_inicio(&lista2, 2);
	insere_final(&lista2, 3);
	insere_inicio(&lista2, 1);

	printf("Tamanho: %d\n", tamanho(lista2));
	imprimir(lista2);

	if (listas_iguais(lista, lista2))
		printf("Listas iguais\n");
	else
		printf("Listas diferentes\n");

	destruir(&lista);
	destruir(&lista2);

	return 0;
}