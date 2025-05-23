#include <stdio.h>
#include <stdlib.h>

void ordena (int v[],int n){
 int i, j;
 
 for (i=0; i<n-1; i++){
    int min = i;
    for (j = i+1; j < n; j++){
        if (v[j] < v[min]){
        //troca v[min] e v[j]
        int x = v[min];
        v[min] = v[j];
        v[j] = x;
    }
    }
 }
}

void contarElementosSegmento(int **matriz, int k, int vetor[], int numeroSegmentos) {
    int segmentoAtual = 0;
    for (int i = 0; i < k - 1; i++) {
        if (vetor[i] != vetor[i + 1]) {
            segmentoAtual++;
        } else {
            matriz[1][segmentoAtual]++;
        }
    }
}

int main () {
    int **matriz, k;

    printf("Digite o número de elementos: ");
    scanf("%d", &k);

    int vetor[k];

    matriz = (int **)malloc(2 * sizeof(int *));


    for (int i = 0; i < k; i++) {
        printf("Digite o %d° elemento: \n", i + 1);
        scanf("%d", &vetor[i]);
    }

    int numeroSegmentos = 0;

    for (int i = 0; i < k - 1; i++) {
        if (vetor[i] != vetor[i + 1]) {
            numeroSegmentos++;
        }
    }
    // O primeiro segmento sempre existe
    numeroSegmentos++;
    
    printf("Numero de segmentos: %d\n", numeroSegmentos);

    int vetorSingular[numeroSegmentos];

    ordena(vetor, k);

    for (int i = 0; i < 2; i ++) {
        matriz[i] = (int *) malloc(numeroSegmentos * sizeof(int));
    }

    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < numeroSegmentos; j++) {
            matriz[i][j] = 1;
        }
    }

    contarElementosSegmento(matriz, k, vetor, numeroSegmentos);
    
    for (int j = 0; j < 2; j++) {
        for (int i = 0; i < numeroSegmentos; i++) {
            printf("%d ", matriz[j][i]);
        }
        printf("\n");
    }

    for (int i = 0; i < 2; i++) {
        free(matriz[i]);
    }

    free(matriz);
}