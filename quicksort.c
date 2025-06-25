#include <stdio.h>

typedef struct {
    char Chave;
} TipoItem;

typedef int TipoIndice;

void Particao(TipoIndice Esq, TipoIndice Dir,
 TipoIndice *i, TipoIndice *j, TipoItem *A)
{ TipoItem x, w;
    *i = Esq; *j = Dir;
    x = A[(*i + *j) / 2]; /* obtem o pivo x */
 do
 { while (x.Chave > A[*i].Chave) (*i)++;
 while (x.Chave < A[*j].Chave) (*j)--;
 if (*i <= *j)
 { w = A[*i];
 A[*i] = A[*j];
 A[*j] = w;
 (*i)++; (*j)--;
 }
 } while (*i <= *j);
}

void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i, j;
 Particao(Esq, Dir, &i, &j, A);
 if (Esq < j) Ordena(Esq, j, A);
 if (i < Dir) Ordena(i, Dir, A);
}

void QuickSort(TipoItem *A, TipoIndice n)
{ Ordena(0, n, A);
}


int main () {
    TipoItem A[100];
    int k;

    printf("Digite o número de elementos a serem ordenados: ");
    scanf("%d", &k);

    for (int i; i < 6; i++) {
        printf("Digite o elemento %d: ", i + 1);
        scanf(" %c", &A[i].Chave);
    }

    QuickSort(A, 3);

    for (int i = 0; i < 6; i++) {
        printf("%c ", A[i].Chave);
    }
}