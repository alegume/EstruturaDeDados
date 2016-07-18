 #include<stdio.h>

void alterar(int x, int y) {
	x = 2;
	y = 4;
	printf("Valores alterados: %d - %d (escopo alterar)\n", x, y);
}

void incrementa(int *x) {
	(*x)++;
}

int main() {
	int a = 0, b = 1, i = 1;

	printf("Valores originais: %d - %d \n", a, b);
	alterar(a, b);
	printf("Valores alterados: %d - %d (escopo main) \n", a, b);
	printf("Valor original de i: %d \n", i);
	incrementa(&i);
	printf("Valor alterado de i: %d \n", i);

	return 0;
}