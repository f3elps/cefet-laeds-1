#include <stdio.h>
#include <stdlib.h>

int detectaPadrao(int tipos[], int numeroSegmentos) {
    for (int i = 0; i < numeroSegmentos - 1; i++) {
        if (tipos[i] == 1 && tipos[i + 1] == 3 && tipos[i + 2] == 2 && tipos[i + 3] == 3 && tipos[i + 4] == 1) {
            return 1;
        }
    }
    return 0;
}

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

void contaTipoSegmento(int **matriz, int k, int vetor[], int numeroSegmentos) {
    int segmentoAtual = 0;
    int vetorSingular[numeroSegmentos];

    for (int i = 0; i < k - 1; i++) {
        if (vetor[i] != vetor[i + 1]) {
            vetorSingular[segmentoAtual] = vetor[i];
            segmentoAtual++;
        }
    }

    vetorSingular[numeroSegmentos-1] = vetor[k-1];

    int vetorSingularOrdenado[numeroSegmentos];
    int countOrdenado = 0;

    for (int i = 0; i < numeroSegmentos; i++) {
        int duplicado = 0;
        for (int j = 0; j < countOrdenado; j++) {
            if (vetorSingular[i] == vetorSingularOrdenado[j]) {
                duplicado = 1;
                break;
            }
        }
        if (!duplicado) {
            vetorSingularOrdenado[countOrdenado++] = vetorSingular[i];
        }
    }

    ordena(vetorSingularOrdenado, countOrdenado);

    for (int i = 0; i < numeroSegmentos; i++) {
        for (int j = 0; j < numeroSegmentos; j++) {
            if (vetorSingular[i] == vetorSingularOrdenado[j]) {
                matriz[0][i] = j + 1;
                break;
            }
        }
    }
}

void contarElementosSegmento(int **matriz, int k, int vetor[]) {
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

    scanf("%d", &k);

    int vetor[k];

    matriz = (int **)malloc(2 * sizeof(int *));


    for (int i = 0; i < k; i++) {
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
    
    int vetorSingular[numeroSegmentos];

    for (int i = 0; i < 2; i ++) {
        matriz[i] = (int *) malloc(numeroSegmentos * sizeof(int));
    }

    for (int i = 0; i < 2; i++) {
        for(int j = 0; j < numeroSegmentos; j++) {
            matriz[i][j] = 1;
        }
    }

    contarElementosSegmento(matriz, k, vetor);

    int vetorOrdenado[k];

    for (int i = 0; i < k; i++) {
        vetorOrdenado[i] = vetor[i];
    }

    ordena(vetorOrdenado, k);

    contaTipoSegmento(matriz, k, vetor, numeroSegmentos);

    int padraoDetectado = detectaPadrao(matriz[0], numeroSegmentos);

    if (padraoDetectado == 1) {
        printf("Resultado: Padrao encontrado.\n");
    } else {
        printf("Resultado: Padrao nao encontrado.\n");
    }
    
    // for (int j = 0; j < 2; j++) {
    //     for (int i = 0; i < numeroSegmentos; i++) {
    //         if (i == numeroSegmentos - 1) {
    //             printf("%d", matriz[j][i]);
    //         } else {
    //             printf("%d ", matriz[j][i]);
    //         }
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < 2; i++) {
        free(matriz[i]);
    }

    free(matriz);
}