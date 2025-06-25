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

void imprimeLista(TipoLista lista) {
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


int detectaPadrao(TipoLista *tiposDeSegmentos) {
    TipoApontador p = tiposDeSegmentos->Primeiro->Prox;

    if (Vazia(*tiposDeSegmentos) || tiposDeSegmentos->Ultimo == tiposDeSegmentos->Primeiro)
        return 0; // lista vazia ou sem segmentos
    // Verifica se a sequência de tipos é 1, 3, 2, 3, 1
    while (p && p->Prox && p->Prox->Prox && p->Prox->Prox->Prox && p->Prox->Prox->Prox->Prox) {
        int a = p->Item.Chave;
        int b = p->Prox->Item.Chave;
        int c = p->Prox->Prox->Item.Chave;
        int d = p->Prox->Prox->Prox->Item.Chave;
        int e = p->Prox->Prox->Prox->Prox->Item.Chave;
        if (a == 1 && b == 3 && c == 2 && d == 3 && e == 1)
        return 1;
        p = p->Prox;
    }
    return 0;
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

int main() {
    // K é a quantidade de pixels e L é a quantidade de linhas
    int k, valor, l;
    scanf("%d", &l);
    scanf("%d", &k);

    TipoLista sequencia, linha, encontrouSequenciaLinha, tiposSegmentosLinha;
    FLVazia(&sequencia);
    FLVazia(&encontrouSequenciaLinha);
    FLVazia(&tiposSegmentosLinha);

    // Preenche a lista com k elementos
    for (int i = 0; i < k; i++) {
        scanf("%d", &valor);
        TipoItem item;
        item.Chave = valor;
        Insere(item, &sequencia);
    }
    
    // Separa as linhas e, para cada linha, verifica se o padrão foi encontrado e armazena o resultado na lista encontrouSequenciaLinha
    TipoApontador atual = sequencia.Primeiro->Prox;

    for(int i = 0; i < k / l; i++) {
        FLVazia(&linha);
        FLVazia(&tiposSegmentosLinha); // reinicializa para cada linha

        for (int j = 0; j < l && atual != NULL; j++) {
            Insere(atual->Item, &linha);
            atual = atual->Prox;
        }

        contaTipoSegmento(&linha, &tiposSegmentosLinha);
        int padrao = detectaPadrao(&tiposSegmentosLinha);
        TipoItem item;
        item.Chave = padrao;
        Insere(item, &encontrouSequenciaLinha);
    }


    imprimeLista(encontrouSequenciaLinha);

    // Análise de segmentos
    TipoLista segmentos, segmentosOrdenados, tipos;
    FLVazia(&segmentos);
    FLVazia(&segmentosOrdenados);
    FLVazia(&tipos);

    contaTipoSegmento(&sequencia, &tipos);

    int padrao = detectaPadrao(&tipos);
    if (padrao) {
        printf("Resultado: Padrao encontrado.\n");
    } else {
        printf("Resultado: Padrao nao encontrado.\n");
    }

    return 0;
}
