#include <stdlib.h>
#include <stdio.h>
#define MAX 10
typedef struct TipoCelula *TipoApontador;
typedef int TipoChave;
typedef struct TipoItem {
 TipoChave Chave;
} TipoItem;
typedef struct TipoCelula {
 TipoItem Item;
 TipoApontador Prox;
} TipoCelula;
typedef struct TipoFila {
 TipoApontador Frente, Tras;
} TipoFila;
void FFVazia(TipoFila *Fila)
{ Fila->Frente = (TipoApontador) malloc(sizeof(TipoCelula));
 Fila->Tras = Fila->Frente;
 Fila->Frente->Prox = NULL;
}
int Vazia(TipoFila Fila)
{ return (Fila.Frente == Fila.Tras); }
void Enfileira(TipoItem x, TipoFila *Fila)
{ Fila->Tras->Prox = (TipoApontador) malloc(sizeof(TipoCelula));
 Fila->Tras = Fila->Tras->Prox;
 Fila->Tras->Item = x;
 Fila->Tras->Prox = NULL;
}
void Desenfileira(TipoFila *Fila, TipoItem *Item)
{ TipoApontador q;
 if (Vazia(*Fila)) { printf("Erro fila esta vazia\n"); return; }
 q = Fila->Frente;
 Fila->Frente = Fila->Frente->Prox;
 *Item = Fila->Frente->Item;
 free(q);
}
void Imprime(TipoFila Fila)
{ TipoApontador Aux;
 Aux = Fila.Frente->Prox;
 while (Aux != NULL)
 { printf("%d\n", Aux->Item.Chave);
 Aux = Aux->Prox;
 }
}
void AumentaPrioridade(TipoFila *Fila, TipoItem *ApontItem) 
{   
    if (Vazia(*Fila)) {
        printf("Erro: Fila vazia.\n");
        return;
    }

    TipoApontador Aux;
    Aux = Fila->Frente->Prox;
    TipoApontador ApontadorASerPriorizado = (TipoApontador)malloc(sizeof(TipoCelula));
    ApontadorASerPriorizado -> Item.Chave = ApontItem ->Chave;
    ApontadorASerPriorizado -> Prox = Aux;
    TipoApontador AuxAnterior;
    while (Aux -> Item.Chave != ApontItem -> Chave) {
        AuxAnterior = Aux;
        Aux = Aux -> Prox;
        if (Aux -> Item.Chave == ApontItem -> Chave) {
            AuxAnterior -> Prox = Aux -> Prox;      
        }
    }
    Fila -> Frente -> Prox = ApontadorASerPriorizado;
}

int main () {
    TipoFila * Fila;
    Fila = (TipoFila *)malloc(sizeof(TipoFila));
    FFVazia(Fila);
    TipoItem Item1, Item2, Item3;
    Item1.Chave = 1;
    Enfileira(Item1, Fila);
    Item2.Chave = 2;
    Enfileira(Item2, Fila);
    Item3.Chave = 3;
    Enfileira(Item3, Fila);
    printf("Fila antes da prioridade:\n");
    Imprime(*Fila);
    AumentaPrioridade(Fila, &Item3);
    printf("Fila apos aumentar prioridade:\n");
    Imprime(*Fila);
    ImprimeEndereço(*Fila);
    return 0;
}