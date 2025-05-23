#include <stdio.h>

int calculaMaximo(int a, int b) {
    return (a > b) ? a : b;
}

int calculaValorOtimo(int valorItens[], int pesoItens[], int numeroItens, int capacidadeMochila) {
    int valorOtimo = 0;
    int matrizOtima[numeroItens + 1][capacidadeMochila + 1];

    for (int i = 0; i <= numeroItens; i++) {
        for (int j = 0; j <= capacidadeMochila; j++) {
            if (i == 0 || j == 0) {
                matrizOtima[i][j] = 0;
            } else if (pesoItens[i - 1] <= j) {
                matrizOtima[i][j] = calculaMaximo(
                    valorItens[i - 1] + matrizOtima[i - 1][j - pesoItens[i - 1]],
                    matrizOtima[i - 1][j]
                );
            } else {
                matrizOtima[i][j] = matrizOtima[i - 1][j];
            }
        }
    }

    valorOtimo = matrizOtima[numeroItens][capacidadeMochila];
    return valorOtimo;
}

int calculaValorTentativa(int tentativa[], int valorItens[], int pesoItens[], int numeroItens, int capacidadeMochila) {
    int valorTentativa = 0;
    int pesoTotal = 0;

    for (int i = 0; i < numeroItens; i++) {
        int valorTotalItem = tentativa[i] * valorItens[i];
        int pesoTotalItem = tentativa[i] * pesoItens[i];
        valorTentativa += valorTotalItem;
        pesoTotal += pesoTotalItem;
        if (pesoTotal > capacidadeMochila) return -1;
    }

    return valorTentativa;
}

int main() {
    int capacidadeMochila, numeroItens;
    scanf("%d", &capacidadeMochila);
    scanf("%d", &numeroItens);

    int pesoItens[numeroItens], valorItens[numeroItens], tentativa[numeroItens];

    for (int i = 0; i < numeroItens; i++) {
        scanf("%d %d", &pesoItens[i], &valorItens[i]);
    }

    for (int i = 0; i < numeroItens; i++) {
        scanf("%d", &tentativa[i]);
    }

    int valorTentativa = calculaValorTentativa(tentativa, valorItens, pesoItens, numeroItens, capacidadeMochila);

    if (valorTentativa == -1) {
        printf("Solucao inviavel.\n");
        return 0;
    }

    int valorOtimo = calculaValorOtimo(valorItens, pesoItens, numeroItens, capacidadeMochila);

    if (valorTentativa != valorOtimo) {
        printf("Solucao viavel mas nao otima.\n");
    } else {
        printf("Solucao otima.\n");
    }

    return 0;
}
