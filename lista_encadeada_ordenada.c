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

void inserir(struct elemento **fila, int i) {
	struct elemento *atual = *fila, *anterior = *fila, *novo;

	novo = malloc(sizeof(struct elemento));
	novo->dado = i;

	if (*fila == NULL) { // Se for o primeiro elemento
		novo->proximo = *fila; // Aponta para a fila
		*fila = novo; // Passa a ser o primeiro
		return;
	}

	while (atual != NULL) {
		if (atual->dado >= i) { // Encontrou posicao (elemento maior ou igual)
			if (atual == *fila) { // Se for o primeiro elemento
				novo->proximo = *fila; // Aponta para a fila
				*fila = novo; // Passa a ser o primeiro
			} else { // Se nao for o primeiro
				novo->proximo = atual->proximo; // Novo aponta para o proximo
				atual->proximo = novo; // Atual aponta para o novo 
			}

			return;
		// Se não encontrou elemento maior, insere no final
		} else if (atual->proximo == NULL) {
			novo->proximo = NULL; // Serah o ultimo
			atual->proximo = novo; // Ultimo da fila aponta para novo

			return;
		}

		anterior = atual; // Elemento atual passa a ser o anterio
		atual = (atual)->proximo; // Proximo elemento passa a ser o atual
	}
}

void imprimir(struct elemento *fila) {
	if (fila != NULL) {
		printf("%d  ", fila->dado); // Imprime primeiro elemento
		imprimir(fila->proximo); // Imprime restante da fila
	} else
		printf("\n"); // Apenas imprime uma linha em branco
}

void remover(struct elemento **fila, int i) {
	struct elemento *atual = *fila, *anterior = *fila;

	while (atual != NULL && atual->dado <= i) {
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

		anterior = atual; // Elemento atual passa a ser o anterior
		atual = (atual)->proximo; // Proximo elemento passa a ser o atual
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
	inserir(&lista, 2);
	inserir(&lista, 1);
	inserir(&lista, 3);

	printf("Tamanho: %d\n", tamanho(lista));
	imprimir(lista);

	remover(&lista, 2);
	printf("\nTamanho: %d\n", tamanho(lista));
	imprimir(lista);

	destruir(&lista);

	return 0;
}