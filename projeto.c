#include <stdio.h>
#include <stdlib.h>

typedef int TipoChave;

typedef struct {
  int Chave;
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

void FLVazia(TipoLista *Lista) {
  Lista->Primeiro = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Primeiro;
  Lista->Primeiro->Prox = NULL;
}

int Vazia(TipoLista Lista) {
  return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista) {
  Lista->Ultimo->Prox = (TipoApontador)malloc(sizeof(TipoCelula));
  Lista->Ultimo = Lista->Ultimo->Prox;
  Lista->Ultimo->Item = x;
  Lista->Ultimo->Prox = NULL;
}


// Função simples para impressão de uma lista até seu último elemento
// Foi necessária ao debugar o programa
void imprimeLista(TipoLista lista) {
    printf("\n");
    TipoApontador p = lista.Primeiro->Prox;
    while (p != NULL) {
        printf("%d", p->Item.Chave);
        if (p->Prox != NULL) {
        printf(" ");
        }
        p = p->Prox;
    }
    printf("\n");
}


// Modifiquei a função que detecta padrão para já retornar o ponto médio do padrão, se o padrão for encontrado
int detectaPadraoComPontoMedio(TipoLista *tipos) {
    TipoApontador p = tipos->Primeiro->Prox;
    int indice = 0;

    while (p && p->Prox && p->Prox->Prox && p->Prox->Prox->Prox && p->Prox->Prox->Prox->Prox) {
        int a = p->Item.Chave;
        int b = p->Prox->Item.Chave;
        int c = p->Prox->Prox->Item.Chave;
        int d = p->Prox->Prox->Prox->Item.Chave;
        int e = p->Prox->Prox->Prox->Prox->Item.Chave;

        // Verifica se o padrão das linhas é 1, 3, 2, 3, 1
        if (a == 1 && b == 3 && c == 2 && d == 3 && e == 1) {
            return indice + 2; // ponto médio do padrão
        }

        // O indice controla em que posição da linha está sendo verificado o padrão
        indice++;
        p = p->Prox;
    }

    return -1; // padrão não foi encontrado
}

int valorJaExiste(TipoLista *lista, int valor) {
    TipoApontador p = lista->Primeiro->Prox;
    while (p) {
        if (p->Item.Chave == valor)
        return 1;
        p = p->Prox;
    }
    return 0;
}

void ordenaLista(TipoLista *lista) {
    for (TipoApontador i = lista->Primeiro->Prox; i != NULL; i = i->Prox) {
        for (TipoApontador j = i->Prox; j != NULL; j = j->Prox) {
        if (j->Item.Chave < i->Item.Chave) {
            int tmp = i->Item.Chave;
            i->Item.Chave = j->Item.Chave;
            j->Item.Chave = tmp;
        }
        }
    }
}

void contaTipoSegmento(
    TipoLista *sequencia,
    TipoLista *tipos
) {
    TipoLista unicos, ordenado;
    FLVazia(&unicos);
    FLVazia(&ordenado);

    TipoApontador p = sequencia->Primeiro->Prox;
    TipoApontador ant = p;
    p = p->Prox;

    // Transforma o vetor em um vetor Singular, ou seja, cada segmento possui apenas um representante
    while (p != NULL) {
        if (p->Item.Chave != ant->Item.Chave) {
            if (!valorJaExiste(&unicos, ant->Item.Chave)) {
                Insere(ant->Item, &unicos);
            }
            ant = p;
        }
        p = p->Prox;
    }

    if (!valorJaExiste(&unicos, ant->Item.Chave)) {
        Insere(ant->Item, &unicos);
    }

    // Depois de transformar o vetor em singular, ordena ele
    // O vetor ordenado servirá como um guia para atribuir o tipo para o segmento
    TipoApontador q = unicos.Primeiro->Prox;
    while (q != NULL) {
        Insere(q->Item, &ordenado);
        q = q->Prox;
    }
    ordenaLista(&ordenado);

    
    p = sequencia->Primeiro->Prox;
    ant = p;
    p = p->Prox;

    while (p != NULL) {
        if (p->Item.Chave != ant->Item.Chave) {
            // descobre o tipo
            int tipo = 1;
            TipoApontador r = ordenado.Primeiro->Prox;
            while (r != NULL) {
                if (r->Item.Chave == ant->Item.Chave) break;
                tipo++;
                r = r->Prox;
            }
            TipoItem tipoItem;
            tipoItem.Chave = tipo;
            Insere(tipoItem, tipos);
            ant = p;
        }
        p = p->Prox;
    }

    // último segmento
    int tipo = 1;
    TipoApontador r = ordenado.Primeiro->Prox;
    while (r != NULL) {
        if (r->Item.Chave == ant->Item.Chave) break;
        tipo++;
        r = r->Prox;
    }
    TipoItem tipoItem;
    tipoItem.Chave = tipo;
    Insere(tipoItem, tipos);
}

// Função que esvazia a lista, será necessária para a verificação de se encontrou padrão em cada linha
// Evita vazamentos de memória
void liberaLista(TipoLista *lista) {
    TipoApontador atual = lista->Primeiro;
    while (atual != NULL) {
        TipoApontador proximo = atual->Prox;
        free(atual);
        atual = proximo;
    }
    lista->Primeiro = NULL;
    lista->Ultimo = NULL;
}

int main() {
    int l, k, valor;
    scanf("%d", &l);

    int linhasComPadrao = 0;

    TipoLista pontosMedios;
    FLVazia(&pontosMedios);

    // Percorre todas as linhas e escaneia todos os elementos de cada linha
    for (int i = 0; i < l; i++) {
        scanf("%d", &k);
        TipoLista sequencia, tipos;
        FLVazia(&sequencia);
        FLVazia(&tipos);

        for (int j = 0; j < k; j++) {
            scanf("%d", &valor);
            TipoItem item = { .Chave = valor };
            Insere(item, &sequencia);
        }

        // Para cada linha, verifica se o padrão foi encontrado.
        contaTipoSegmento(&sequencia, &tipos);
        int pontoMedio = detectaPadraoComPontoMedio(&tipos);
        if (pontoMedio != -1) {
            linhasComPadrao++;
            TipoItem pontoMedioASerInseridoNaLista;
            pontoMedioASerInseridoNaLista.Chave = pontoMedio;
            Insere(pontoMedioASerInseridoNaLista, &pontosMedios);
        }

        liberaLista(&sequencia);
        liberaLista(&tipos);
    }

    imprimeLista(pontosMedios);

    float proporcao = (float)linhasComPadrao / l;

    // É feita a verificação para garantir que pelo menos 70% das linhas encontraram padrão
    if (proporcao < 0.7f) {
        printf("Resultado: Formato da pista nao estimado.\n");
    } else {
        printf("Resultado: Padrao reconhecido em %.0f%% das linhas.\n", proporcao * 100);
    }

    return 0;
}