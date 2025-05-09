#include <stdio.h>

void decompor(int restante, int maximo, int combinacao[], int tamanho) {
    if (restante == 0) {
        for (int i = 0; i < tamanho; i++) {
            printf("%d", combinacao[i]);
            if (i < tamanho - 1) {
                printf(" + ");
            }
        }
        printf("\n");
        return;
    }

    for (int i = maximo; i >= 1; i--) {
        if (i <= restante) {
            combinacao[tamanho] = i;
            decompor(restante - i, i, combinacao, tamanho + 1);
        }
    }
}

int main () {
    int n;
    int combinacao[100];

    scanf("%d", &n);

    printf("Decomposicao:\n");

    decompor(n, n, combinacao, 0);

    return 0;
}
