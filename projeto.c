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
int detectaPadrao(TipoLista *tipos) {
    TipoApontador p = tipos->Primeiro->Prox;

    while (p && p->Prox && p->Prox->Prox && p->Prox->Prox->Prox && p->Prox->Prox->Prox->Prox) {
        int a = p->Item.Chave;
        int b = p->Prox->Item.Chave;
        int c = p->Prox->Prox->Item.Chave;
        int d = p->Prox->Prox->Prox->Item.Chave;
        int e = p->Prox->Prox->Prox->Prox->Item.Chave;

        // Verifica se o padrão das linhas é 1, 3, 2, 3, 1
        if (a == 1 && b == 3 && c == 2 && d == 3 && e == 1) return 1;

        p = p->Prox;
    }

    return 0; // padrão não foi encontrado
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

void contaTipoSegmento(TipoLista *sequencia, TipoLista *tipos) {
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

    // Mapeia os segmentos da sequência para tipos ordenados
    p = sequencia->Primeiro->Prox;
    ant = p;
    p = p->Prox;

    while (p != NULL) {
        int tipo = 1;
        if (p->Item.Chave != ant->Item.Chave) {
            if (ant->Item.Chave == 0) {
                tipo = 1;
            } else if (ant->Item.Chave == 128) {
                tipo = 2;
            } else if (ant->Item.Chave == 255) {
                tipo = 3;
            }
            // Inserir opção para obstáculos
            TipoItem tipoItem = { .Chave = tipo };
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
    TipoItem tipoItem = { .Chave = tipo };
    Insere(tipoItem, tipos);

    // Libera listas auxiliares
    liberaLista(&unicos);
    liberaLista(&ordenado);
}

// Calcula ponto médio pela média das posições dos pixels vermelhos (128)
int calcularPontoMedio(int *l, int k) {
    int indice = 0;
    int pixeis128 = 0;
    for (int i = 0; i < k; i++) {
        if (l[i] == 128) {
            indice += i;
            pixeis128++;
        }
    }
    if (pixeis128 == 0) return -1;
    printf("\n\nPonto Medio: %d\n\n", indice / pixeis128);
    return indice / pixeis128;
}

// Procura por obstáculos na pista
// Um obstáculo é encontrado se houver qualquer padrão entres 2 segmentos do tipo 2 (128)
int encontraObstaculos(int *l, int k) {
    
}


int determinarFormatoPista(TipoLista listaPontosMedios, int linhasValidas, int totalLinhas) {
    int direita = 0, esquerda = 0, reta = 0;
    TipoApontador atual = listaPontosMedios.Primeiro->Prox;
    int contaLinhas = 0;

    while (atual != NULL && atual->Prox != NULL) {
        contaLinhas++;
        int pontoAtual = atual->Item.Chave;
        int pontoSeguinte = atual->Prox->Item.Chave;

        // Calcula a diferença entre os pontos médios, de forma que, se a diferenca for de mais de 5%, é classificada uma tendência para um dos lados
        float diferenca = (float)(pontoSeguinte - pontoAtual) / pontoAtual;
        if (diferenca > 0.04f) {
            esquerda++;
        } else if (diferenca < -0.03f) {
            direita++;
        } else {
            reta++;
        }

        atual = atual->Prox;
    }

    if ((float)direita > (float) esquerda && (float)direita > (float)reta) {
        return 1; // Curva à direita
    } else if ((float)esquerda > (float)direita && (float)esquerda > (float)reta) {
        return 2; // Curva à esquerda
    } else if ((float)reta > (float)direita && (float)reta > (float)esquerda) {
        return 3; // Linha reta
    } else {
        return 0; // Formato não estimado
    }
}


int main() {
    int l, k, valor;
    scanf("%d", &l);

    int linhasComPadrao = 0;
    TipoLista pontosMedios;
    FLVazia(&pontosMedios);

    for (int i = 0; i < l; i++) {
        scanf("%d", &k);
        TipoLista sequencia, tipos;
        FLVazia(&sequencia);
        FLVazia(&tipos);

        int *linhaCompleta = malloc(sizeof(int) * k);

        for (int j = 0; j < k; j++) {
            scanf("%d", &valor);
            linhaCompleta[j] = valor;
            TipoItem item = { valor };
            Insere(item, &sequencia);
        }

        contaTipoSegmento(&sequencia, &tipos);

        if (detectaPadrao(&tipos)) {
            linhasComPadrao++;
            int ponto = calcularPontoMedio(linhaCompleta, k);

            if (ponto != -1) {
                TipoItem pontoItem = { ponto };
                Insere(pontoItem, &pontosMedios);
            }
        }

        free(linhaCompleta);
        liberaLista(&sequencia);
        liberaLista(&tipos);
    }


    float proporcao = (float)linhasComPadrao / l;

    if (proporcao < 0.7f) {
        printf("Resultado: Formato da pista nao estimado.\n");
    } else {
        int formato = determinarFormatoPista(pontosMedios, linhasComPadrao, l);
        if (formato == 1) {
            printf("Resultado: Curva a direita.\n");
        } else if (formato == 2) {
            printf("Resultado: Curva a esquerda.\n");
        } else if (formato == 3) {
            printf("Resultado: Pista em linha reta.\n");
        }
    }

    return 0;
}