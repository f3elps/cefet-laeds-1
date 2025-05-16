#include <stdio.h>

int calculaValorOtimo(int valorItens[], int pesoItens[], int numeroItens, int capacidadeMochila) {
    int valorOtimo = 0;
    int matrizOtima[numeroItens + 1][capacidadeMochila + 1];

    for (int i = 0; i < numeroItens; i++) {
        for (int j = 0; j < capacidadeMochila; j++) {
            matrizOtima[i][j] = 0;
        }
    }

    for (int i = 0; i < numeroItens; i++) {
        for (int j = 0; j < capacidadeMochila; j++) {

        }
    }

    // valorOtimo = matrizOtima[numeroItens][capacidadeMochila];
    return valorOtimo;
}

int calculaValorTentativa(int solucoes[], int valorItens[], int pesoItens[], int numeroItens, int capacidadeMochila) {
    int valorTentativa = 0;
    int pesoTotal = 0;

    for (int i = 0; i < numeroItens; i++) {
        int valorTotalItem = solucoes[i] * valorItens[i];
        int pesoTotalItem = solucoes[i] * pesoItens[i];
        valorTentativa += valorTotalItem;
        pesoTotal += pesoTotalItem;
        if (pesoTotal > capacidadeMochila) return -1;
    }

    return valorTentativa;
}

int main () {
    int capacidadeMochila, numeroItens;
    scanf("%d", &capacidadeMochila);

    scanf("%d", &numeroItens);

    int pesoItens[numeroItens], valorItens[numeroItens], tentativa[numeroItens];

    for (int i = 0; i<numeroItens; i++) {
        scanf("%d %d", &pesoItens[i], &valorItens[i]);
    }

    for (int i = 0; i<numeroItens; i++) {
        scanf("%d", &tentativa[i]);
    }

    int valorTentativa = calculaValorTentativa(tentativa, valorItens, pesoItens, numeroItens, capacidadeMochila);

    if (valorTentativa == -1) {
        printf("Solucao inviavel.");
        return 0;
    }

    int valorOtimo = calculaValorOtimo(valorItens, pesoItens, numeroItens, capacidadeMochila);

    if (valorTentativa != valorOtimo) {
        printf("Solucao viavel mas nao otima.");
        return 0;
    } else {
        printf("Solucao otima.");
        return 0;
    }
}