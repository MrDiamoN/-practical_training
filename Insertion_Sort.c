#include <stdio.h>
#define size 10

void sort(int vet[]) {
  int x, y, valor;

  for (x = 1; x < size; x++) {

    valor = vet[x];

    for (y = x - 1; y >= 0 && vet[y] > valor; y--) {
      vet[y + 1] = vet[y];
    }

    vet[y + 1] = valor;
  }
}

void sortchar(char vet[]) {
  int x, y;
  char let;

  for (x = 1; x < size; x++) {

    let = vet[x];

    for (y = x - 1; y >= 0 && vet[y] > let; y--) {
      vet[y + 1] = vet[y];
    }

    vet[y + 1] = let;
  }
}

void imprime(int vet[]) {

  for (int x = 0; x < size; x++) {
    printf("%d , ", vet[x]);
  }
  printf("\n\n");
}

void imprimechar(char letra[]) {

  for (int x = 0; x < size; x++) {
    printf("%c , ", letra[x]);
  }
  printf("\n\n");
}

int main(void) {

  printf("*** INSERTION SORT ***\n\n");

  int vet[size] = {9, 8, 1, 4, 2, 7, 5, 6, 3, 10};
  imprime(vet);
  sort(vet);
  imprime(vet);

  printf("***  ***\n\n");

  char letra[size] = {'c', 'd', 'e', 'a', 'b', 'h', 'g', 'f', 'j', 'i'};
  imprimechar(letra);
  sortchar(letra);
  imprimechar(letra);

  return 0;
}
