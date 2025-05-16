#include <stdio.h>

int calculaMaximo(int a, int b) {
    if (a < b) return b;
    return a;
}

int calculaValorOtimo(int valorItens[], int pesoItens[], int numeroItens, int capacidadeMochila) {
    int valorOtimo = 0;
    int matrizOtima[numeroItens + 1][capacidadeMochila + 1];

    for (int i = 0; i < numeroItens; i++) {
        for (int j = 0; j < capacidadeMochila; j++) {
            // fazer programação dinâmica:
            // calcular qual o maior valor possível com a capacidade j e os do item 0 ate o i
            if (i == 0 || j == 0) {
                matrizOtima[i][j] = 0;
            } else if (pesoItens[i-1] <= j) {
                matrizOtima[i][j] = calculaMaximo(matrizOtima[i-1][j-1] + valorItens[i-1], matrizOtima[i-1][j]);
            } else {
                matrizOtima[i][j] = matrizOtima[i-1][j];
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

    printf("Valor otimo: %d", valorOtimo);
    printf("Valor Tentativa: %d", valorTentativa);

    if (valorTentativa != valorOtimo) {
        printf("Solucao viavel mas nao otima.");
        return 0;
    } else {
        printf("Solucao otima.");
        return 0;
    }
}