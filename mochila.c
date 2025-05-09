#include <stdio.h>

int calculaValorOtimo(int valorItens[], int pesoItens[], int numeroItens, int capacidadeMochila) {
    int valorOtimo = 0;

    for (int i = 0; i < numeroItens; i++) {

    }
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
}

int main () {
    int capacidadeMochila, numeroItens;
    scanf("%d\n", &capacidadeMochila);

    scanf("%d\n", &numeroItens);

    int pesoItens[numeroItens], valorItens[numeroItens], solucoes[numeroItens];

    for (int i = 0; i<numeroItens; i++) {
        scanf("%d %d\n", &pesoItens[i], &valorItens[i]);
    }

    for (int i = 0; i<numeroItens; i++) {
        scanf("%d\n", &solucoes[i]);
    }

    int valorTentativa = calculaValorTentativa(solucoes, pesoItens, valorItens, numeroItens, capacidadeMochila);

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