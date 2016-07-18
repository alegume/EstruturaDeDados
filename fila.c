#include<stdio.h>
#include<stdlib.h> // malloc

// Fila sera pequena para o exemplo didatico de fila circular
#define MAX_ELEMENTOS 2

struct fila {
	char elementos[MAX_ELEMENTOS];
	int primeiro, ultimo; // Necessario saber inicio e fim da fila
};

struct fila *criar() {
	struct fila *f;
	f = malloc(sizeof(struct fila));
	if (!f)
		exit(1); // Erro ao alocar memoria
	f->primeiro = 0;
	f->ultimo = 0;

	return f;
}

int tamanho_fila(struct fila *f) {
	int t = f->ultimo - f->primeiro;

	if (t < 0) // Verificacao lista circular
		t = MAX_ELEMENTOS + t + 1; // MAX_ELEMENTOS - t

	return t;
}

void emfileirar(struct fila *f, char c) {
	int t = tamanho_fila(f);

	if (t == MAX_ELEMENTOS) {
		printf("Fila atingiu o numero maximo de elementos\n");
		return;
	}

	f->ultimo++; // Incrementa final
	// Se elementos foram desempilhados (f->primeiro > 0)
	if (f->ultimo >= MAX_ELEMENTOS && f->primeiro > 0) 
		f->ultimo = 0; // Retorno da fila circular
	f->elementos[f->ultimo] = c; // Insere caractere no final
}

char desemfileirar(struct fila *f) {
	char c = f->elementos[f->primeiro];
	f->primeiro++; // Incrementa inicio da fila
	if (f->primeiro == MAX_ELEMENTOS)
		f->primeiro = 0; // Retorna ao inicio da fila circular

	return c;
}

void destruir(struct fila *f) {
	free(f);
}

int main() {
	struct fila *minha_fila;
	int tamanho;
	char c;

	minha_fila = criar();
	emfileirar(minha_fila, 'a');
	emfileirar(minha_fila, 'b');
	emfileirar(minha_fila, 'c'); // Nao ha' espaco
	c = desemfileirar(minha_fila); // Remove 'a'
	emfileirar(minha_fila, 'c'); // Agora ha' espaco no inicio da fila circular ;)
	tamanho = tamanho_fila(minha_fila);
	printf("Desemfileirando %d elementos \n", tamanho);
	for (int i = 0; i < tamanho; i++) {
		printf("%c \n", desemfileirar(minha_fila));
	}
	destruir(minha_fila);

	return 0;
}