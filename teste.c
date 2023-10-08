#include <stdio.h>

int main() {

  int numero;
  // Lê o número com scanf
  scanf("%d", &numero);

  int c;

  // Loop para ler caractere a caractere com getchar()
  printf("Conteudo do buffer: \n");
  while((c = getchar()) != EOF) {

    // Imprime cada caractere lido
    putchar(c);

  }

  printf("\n");

  return 0;
}
