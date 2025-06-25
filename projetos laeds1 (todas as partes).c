parte 1:

/*
              >>>>>>>>>>> CABEÇALHO <<<<<<<<<<<
    CENTRO FEDERAL DE EDUCAÇÃO TECNOLÓGICA DE MINAS GERAIS
    
    Projeto (parte I) - Busca por padrão em uma sequência
    Alunos: Caíque Gomes de Pádua e Hugo Daniel Amaral Oliveira =)
    Matéria: Laboratório de Algoritmos e Estruturas de Dados 1 -> 2024/2
    Professora: Natália Cosse Batista
    
*/

#include <stdio.h>
#include <stdlib.h>

//implementação de listas usando apontadores -> parte já cedida pela professora =)

/* DECALARAÇÃO DOS TIPOS DE DADOS */
//a estrutura 'TipoItem' representa cada segmento da linha de pixels
typedef struct {
    int Chave; //identificador único do segmento
    int Tipo; //tipo de cor do segmento (1 = preto, 2 = vermelho, 3 = branco) -> pós-conversão
    int NumElementos; //número de pixels que compõem o segmento
    int PontoMedio; //posição média do segmento na linha de pixels
} TipoItem;

//a estrutura 'TipoCelula' representa cada nó da lista encadeada
typedef struct TipoCelula *Apontador;

typedef struct TipoCelula {
    TipoItem Item; //dados armazenados no nó (um segmento)
    Apontador Prox; //ponteiro para o próximo nó da lista
} TipoCelula;

//a estrutura 'TipoLista' representa a lista encadeada
typedef struct {
    Apontador Primeiro, Ultimo; //ponteiros para o início e o final da lista
} TipoLista;

/* FUNÇÕES/OPERAÇÕES DE LISTAS */
//esta função cria uma lista vazia, inicializando os ponteiros para as posições iniciais e finais
void CriaLista(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc(sizeof(TipoCelula)); //cria um nó cabeça
    Lista->Ultimo = Lista->Primeiro; //inicialmente, o último nó é o nó cabeça
    Lista->Primeiro->Prox = NULL; //a lista começa vazia
}

//esta função verifica se a lista está vazia
int Vazia(TipoLista Lista) {
    return (Lista.Primeiro == Lista.Ultimo); //a lista está vazia se primeiro == último
}

//esta função insere um novo item no final da lista
void InsereListaUlt(TipoLista *Lista, TipoItem Item) {
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(TipoCelula)); //aloca memória para o novo nó
    Lista->Ultimo = Lista->Ultimo->Prox; //atualiza o ponteiro do último nó
    Lista->Ultimo->Item = Item; //armazena o item no novo nó
    Lista->Ultimo->Prox = NULL; //o próximo nó ainda não existe
}

//esta função percorre a lista e imprime os dados de cada item (útil para debug)
void PercorreLista(TipoLista Lista) {
    Apontador Aux = Lista.Primeiro->Prox; //inicia no primeiro elemento útil (após o nó cabeça)
    while (Aux != NULL) { //enquanto não atingir o final da lista
        printf("Chave: %d, Tipo: %d, NumElementos: %d, PontoMedio: %d\n",
               Aux->Item.Chave, Aux->Item.Tipo, Aux->Item.NumElementos, Aux->Item.PontoMedio);
        Aux = Aux->Prox; //avança para o próximo nó
    }
}

/* FUNÇÃO PRINCIPAL -> SOLUÇÃO DO PROBLEMA */
int main() {
    TipoLista lista;
    CriaLista(&lista); //cria uma lista encadeada vazia

    int qtd_pixels; //número de pixels
    //printf("Insira o numero de pixels da imagem: ");
    scanf("%d", &qtd_pixels); //lê o número de pixels na linha das 'imagens'

    int pixels[qtd_pixels]; //vetor para armazenar os valores dos pixels
    for (int i = 0; i < qtd_pixels; i++) {
        scanf("%d", &pixels[i]); //lê os valores de diversos pixels
    }
    
    if (qtd_pixels <= 0) {
        printf("Erro: o numero de pixels deve ser maior que zero (positivo).\n");
        return 1; //finaliza o programa com erro
    }

    //processar os pixels e identificar segmentos
    int segmentoInicio = 0, chave = 1; //variáveis para controlar o início do segmento e a chave única
    
    for (int i = 1; i <= qtd_pixels; i++) {
        //verifica se o segmento terminou (quando o valor do pixel muda ou chegamos ao final)
        if (i == qtd_pixels || pixels[i] != pixels[i - 1]) {
            //criar um segmento
            TipoItem item;
            item.Chave = chave++; //atribui uma chave única ao segmento e incrementa para o próximo

            //converter o valor de cada pixel em um tipo de cor identificável
            if (pixels[segmentoInicio] == 0) {
                item.Tipo = 1; //preto
            } else if (pixels[segmentoInicio] == 128) {
                item.Tipo = 2; //vermelho
            } else if (pixels[segmentoInicio] == 255) {
                item.Tipo = 3; //branco
            }

            item.NumElementos = i - segmentoInicio; //calcula o número de pixels no segmento
            item.PontoMedio = (segmentoInicio + (i - 1)) / 2; //calcula o ponto médio do segmento

            //inserir item no final da lista
            InsereListaUlt(&lista, item); //adiciona o segmento identificado à lista

            //atualizar o início do próximo segmento
            segmentoInicio = i; //define o novo início do segmento
        }
    }

    //verificar o padrão "1 3 2 3 1" ou "preto branco vermelho branco preto"
    int sequencia_padrao[5] = {1, 3, 2, 3, 1}; //criação de um vetor que contém o padrão a ser buscado -> servirá como base de comparação
    int i = 0; //índice que acompanha o progresso na busca do padrão
    
    Apontador percorre = lista.Primeiro->Prox; //inicia no primeiro elemento útil da lista
    
    //percorre toda a lista que foi criada, até que 'percorre' aponte para o vazio (fim da lista)
    while (percorre != NULL) {
        if (percorre->Item.Tipo == sequencia_padrao[i]) { //verifica se o tipo do segmento corresponde ao padrão
            i++; //avança para o próximo elemento do padrão
            
            //se todos os elementos do padrão forem descobertos
            if (i == 5) {
                printf("Resultado: Padrao encontrado.\n");
                return 0; //finaliza o programa -> basta que apenas uma sequência seja encontrada em todo o conjunto de dados dos pixels dessas 'imagens'
            }
        }
        
        //casos em que a sequência completa ainda não foi encontrada
        else {
            if (percorre->Item.Tipo == sequencia_padrao[0]) {
                i = 1; //reinicia a busca começando pelo primeiro elemento do padrão
            } else {
                i = 0; //reinicia a busca completamente
            }
        }
        
        percorre = percorre->Prox; //avança para o próximo segmento da lista
    }
    
    //ao sair do loop, significa que o padrão não está na sequência de pixels
    printf("Resultado: Padrao nao encontrado.\n");
    
    return 0; //finaliza o programa
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------
parte 2:
/*
              >>>>>>>>>>> CABEÇALHO <<<<<<<<<<<
    CENTRO FEDERAL DE EDUCAÇÃO TECNOLÓGICA DE MINAS GERAIS
    Projeto (parte II) - Estimativa do formato da pista
    Alunos: Caíque Gomes de Pádua e Hugo Daniel Amaral Oliveira =)
    Matéria: Laboratório de Algoritmos e Estruturas de Dados 1 -> 2024/2
    Professora: Natália Cosse Batista
    
*/

#include <stdio.h>
#include <stdlib.h>

//implementação de listas usando apontadores -> parte já cedida pela professora =)

/* DECLARAÇÃO DOS TIPOS DE DADOS */
typedef struct {
    int Chave; //identificador único
    int PontoMedio; //posição média do segmento
} TipoItem;

typedef struct TipoCelula *Apontador;

typedef struct TipoCelula {
    TipoItem Item; //dados armazenados no nó (um segmento)
    Apontador Prox; //ponteiro para o próximo nó da lista
} TipoCelula;

typedef struct {
    Apontador Primeiro, Ultimo; //ponteiros para o início e o final da lista
} TipoLista;

/* FUNÇÕES/OPERAÇÕES DE LISTAS */
//esta função cria uma lista vazia, inicializando os ponteiros para as posições iniciais e finais
void CriaLista(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc(sizeof(TipoCelula)); //cria um nó cabeça
    Lista->Ultimo = Lista->Primeiro; //inicialmente, o último nó é o nó cabeça
    Lista->Primeiro->Prox = NULL; //a lista começa vazia
}

//esta função verifica se a lista está vazia
int Vazia(TipoLista Lista) {
    return (Lista.Primeiro == Lista.Ultimo); //a lista está vazia se primeiro == último
}

//esta função insere um novo item no final da lista
void InsereListaUlt(TipoLista *Lista, TipoItem Item) {
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(TipoCelula)); //aloca memória para o novo nó
    Lista->Ultimo = Lista->Ultimo->Prox; //atualiza o ponteiro do último nó
    Lista->Ultimo->Item = Item; //armazena o item no novo nó
    Lista->Ultimo->Prox = NULL; //o próximo nó ainda não existe
}

/* >>>>>>>>>>> FUNÇÕES DA SOLUÇÃO DO PROBLEMA <<<<<<<<<<< */

#define proporcaoMinimaLinhasValidas 0.7  //70% de linhas válidas
#define desvioMaximoPontoMedio 0.5 //50% para validação da linha
#define deslocamentoMinimoTendencia 0.1 //10% para deslocamento significativo

//função para calcular a posição média dos pixels vermelhos (128) em uma linha da imagem
float calcularPontoMedio(int *pixels, int qtd_pixels) {
    //variáveis para armazenar a soma das posições e o número de pixels vermelhos encontrados
    int soma = 0, contador = 0;

    //percorre todos os pixels da linha
    for (int i = 0; i < qtd_pixels; i++) {
        if (pixels[i] == 128) { //verifica se o pixel atual é vermelho (valor 128)
            soma += i; //adiciona a posição do pixel à soma total
            contador++; //incrementa o contador de pixels vermelhos
        }
    }

    //se nenhum pixel vermelho foi encontrado, retorna -1 como indicador de linha inválida
    if (contador == 0) return -1;

    //caso contrário, calcula e retorna a posição média dos pixels vermelhos
    return (float)soma / contador;
}

//função que verifica se a variação entre o ponto médio atual e o anterior está dentro do limite aceitável (50%)
int ehLinhaValida(int pontoMedioAnterior, int pontoMedioAtual) {
    //calcula a variação relativa entre os dois pontos médios
    float variacao = (float)abs(pontoMedioAtual - pontoMedioAnterior) / pontoMedioAnterior;

    //se a variação for menor ou igual ao desvio máximo permitido, a linha é considerada válida
    return variacao <= desvioMaximoPontoMedio;
}

//função que analisa os deslocamentos entre os pontos médios das linhas válidas -> determina o formato da pista com base nas tendências (direita, esquerda ou reta)
char* determinarFormatoPista(TipoLista listaPontosMedios, int linhasValidas, int totalLinhas) {
    //verifica se a proporção de linhas válidas é suficiente para determinar o formato da pista
    if ((float)linhasValidas / totalLinhas < proporcaoMinimaLinhasValidas) {
        return "Formato da pista nao estimado.";
    }

    //inicializa contadores para as tendências de movimento
    int tendenciaDireita = 0, tendenciaEsquerda = 0, tendenciaReta = 0;

    //percorre a lista de pontos médios para calcular as tendências
    Apontador aux = listaPontosMedios.Primeiro->Prox;
    while (aux != NULL && aux->Prox != NULL) {
        //obtém os pontos médios da linha atual e da próxima linha
        int pontoAtual = aux->Item.PontoMedio;
        int pontoProx = aux->Prox->Item.PontoMedio;

        //calcula a diferença relativa entre os dois pontos médios
        float diferenca = (float)(pontoProx - pontoAtual) / pontoAtual;

        //classifica a tendência com base na diferença calculada
        if (diferenca > deslocamentoMinimoTendencia) {
            tendenciaDireita++; //incrementa a tendência para a direita
        } else if (diferenca < -deslocamentoMinimoTendencia) {
            tendenciaEsquerda++; //incrementa a tendência para a esquerda
        } else {
            tendenciaReta++; //incrementa a tendência para linha reta
        }

        aux = aux->Prox; //avança para o próximo nó da lista
    }

    //calcula o número total de tendências analisadas
    int totalTendencias = tendenciaDireita + tendenciaEsquerda + tendenciaReta;

    //verifica qual tendência é predominante e retorna o formato correspondente
    if ((float)tendenciaDireita / totalTendencias >= proporcaoMinimaLinhasValidas) {
        return "Curva a direita.";
    } else if ((float)tendenciaEsquerda / totalTendencias >= proporcaoMinimaLinhasValidas) {
        return "Curva a esquerda.";
    } else if ((float)tendenciaReta / totalTendencias >= proporcaoMinimaLinhasValidas) {
        return "Pista em linha reta.";
    } else {
        return "Formato da pista nao estimado.";
    }
}

//função principal que gerencia a leitura dos dados, o processamento e a exibição do resultado final
int main() {
    //variável que armazena o número total de linhas da imagem
    int L;
    
    //estrutura de lista para armazenar os pontos médios das linhas válidas
    TipoLista listaPontosMedios;
    CriaLista(&listaPontosMedios); //inicializa a lista encadeada

    //leitura do número de linhas fornecido como entrada
    scanf("%d", &L);

    //variável que armazena o ponto médio da última linha válida processada
    int pontoMedioAnterior = -1;

    //loop que processa cada linha da imagem
    for (int i = 0; i < L; i++) {
        //lê o número de pixels na linha atual
        int qtd_pixels;
        scanf("%d", &qtd_pixels);

        //aloca memória para armazenar os valores dos pixels da linha
        int *pixels = (int *)malloc(qtd_pixels * sizeof(int));
        for (int j = 0; j < qtd_pixels; j++) {
            scanf("%d", &pixels[j]); //lê o valor de cada pixel
        }

        //calcula o ponto médio dos pixels vermelhos na linha
        float pontoMedioAtual = calcularPontoMedio(pixels, qtd_pixels);
        free(pixels); //libera a memória alocada para os pixels

        //verifica se a linha é válida com base no ponto médio atual
        if (pontoMedioAtual >= 0 && (pontoMedioAnterior == -1 || ehLinhaValida(pontoMedioAnterior, pontoMedioAtual))) {
            //cria um novo item para armazenar o ponto médio válido
            TipoItem item;
            item.Chave = i + 1; //atribui um identificador único para a linha
            item.PontoMedio = (int)pontoMedioAtual; //armazena o ponto médio como inteiro
            InsereListaUlt(&listaPontosMedios, item); //insere o item na lista encadeada

            //atualiza o ponto médio anterior para o ponto médio atual
            pontoMedioAnterior = pontoMedioAtual;
        }
    }

    //conta o número de linhas válidas processadas
    int linhasValidas = 0;
    Apontador aux = listaPontosMedios.Primeiro->Prox;
    while (aux != NULL) {
        linhasValidas++;
        aux = aux->Prox;
    }

    //determina o formato da pista com base nos pontos médios das linhas válidas
    char *resultado = determinarFormatoPista(listaPontosMedios, linhasValidas, L);

    //exibe o resultado final
    printf("Resultado: %s\n", resultado);

    return 0;
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------
parte 3:

/*
              >>>>>>>>>>> CABEÇALHO <<<<<<<<<<<
    CENTRO FEDERAL DE EDUCAÇÃO TECNOLÓGICA DE MINAS GERAIS
    
    Projeto (Parte III) - Detecção de obstáculos/impedimentos na pista
    Alunos: Caíque Gomes de Pádua e Hugo Daniel Amaral Oliveira =)
    Matéria: Laboratório de Algoritmos e Estruturas de Dados 1 -> 2024/2
    Professora: Natália Cosse Batista
    
*/

#include <stdio.h>
#include <stdlib.h>

/* declaração dos tipos de dados */
typedef struct {
    int Chave; //identificador único do segmento na lista
    int Tipo; //tipo de cor do segmento (1 = preto, 2 = vermelho, 3 = branco)
    int NumElementos; //quantidade de pixels que compõem o segmento
    int PontoMedio; //posição média do segmento dentro da linha de pixels
} TipoItem;

typedef struct TipoCelula *Apontador;

typedef struct TipoCelula {
    TipoItem Item; //armazenamento dos dados do segmento
    Apontador Prox; //ponteiro para o próximo nó da lista encadeada
} TipoCelula;

typedef struct {
    Apontador Primeiro, Ultimo; //ponteiros para início e fim da lista encadeada
} TipoLista;

/* funções de manipulação de listas */
//cria uma lista encadeada vazia
void CriaLista(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc(sizeof(TipoCelula)); //aloca memória para nó cabeça
    Lista->Ultimo = Lista->Primeiro; //inicializa a lista com nó cabeça apontando para si mesmo
    Lista->Primeiro->Prox = NULL; //define que o próximo nó da cabeça é nulo (lista vazia)
}

//verifica se a lista está vazia
int Vazia(TipoLista Lista) {
    return (Lista.Primeiro == Lista.Ultimo); //se primeiro e último são iguais, a lista está vazia
}

//insere um item no final da lista
void InsereListaUlt(TipoLista *Lista, TipoItem Item) {
    Lista->Ultimo->Prox = (Apontador) malloc(sizeof(TipoCelula)); //aloca novo nó
    Lista->Ultimo = Lista->Ultimo->Prox; //atualiza o ponteiro para o novo último nó
    Lista->Ultimo->Item = Item; //atribui os valores do segmento ao novo nó
    Lista->Ultimo->Prox = NULL; //define que o próximo nó é nulo
}

//converte um valor de pixel para um tipo de segmento
int ConverterParaTipo(int valor) {
    if (valor == 0) return 1; //se for 0, representa preto
    if (valor == 128) return 2; //se for 128, representa vermelho
    return 3; //se for 255, representa branco
}

//processa uma linha de pixels e cria a lista encadeada de segmentos
void ProcessarPixels(int pixels[], int qtd_pixels, TipoLista *lista) {
    CriaLista(lista); //inicializa uma lista vazia
    
    int segmentoInicio = 0, chave = 1; //marca o início do primeiro segmento e inicializa a chave
    for (int i = 1; i <= qtd_pixels; i++) {
        if (i == qtd_pixels || ConverterParaTipo(pixels[i]) != ConverterParaTipo(pixels[i - 1])) {
            TipoItem item;
            item.Chave = chave++;
            item.Tipo = ConverterParaTipo(pixels[segmentoInicio]); //define o tipo do segmento
            item.NumElementos = i - segmentoInicio; //calcula o tamanho do segmento
            item.PontoMedio = (segmentoInicio + (i - 1)) / 2; //determina a posição média do segmento
            InsereListaUlt(lista, item); //insere o segmento na lista
            segmentoInicio = i; //atualiza o início do próximo segmento
        }
    }
}

//verifica se há impedimento na pista analisando a lista de segmentos
int VerificarImpedimento(TipoLista lista) {
    Apontador percorre = lista.Primeiro->Prox; //inicia a análise pelo primeiro segmento útil
    int encontrou_primeiro_2 = 0; //flag para identificar se já encontramos um segmento "2"
    int encontrou_valor_no_meio = 0; //flag para verificar se há valores entre os segmentos "2"
    
    while (percorre != NULL) {
        if (percorre->Item.Tipo == 2) {
            if (encontrou_primeiro_2 && encontrou_valor_no_meio) {
                return 1; //houve uma quebra real na região "2", então a pista está obstruída
            }
            encontrou_primeiro_2 = 1; //marca que encontramos o primeiro segmento "2"
            encontrou_valor_no_meio = 0; //reseta ao encontrar um novo segmento "2"
        } else if (encontrou_primeiro_2) {
            encontrou_valor_no_meio = 1; //marca que há um valor diferente entre dois "2"
        }
        percorre = percorre->Prox; //avança para o próximo segmento na lista
    }
    return 0; //se não encontrou divisão na região "2", a pista está livre
}

//função principal
int main() {
    int linhas, tem_impedimento = 0;
    scanf("%d", &linhas); //lê a quantidade de perfis (linhas) da imagem
    
    for (int i = 0; i < linhas; i++) {
        int qtd_pixels;
        scanf("%d", &qtd_pixels); //lê a quantidade de pixels da linha atual
        
        int pixels[qtd_pixels];
        for (int j = 0; j < qtd_pixels; j++) {
            scanf("%d", &pixels[j]); //lê os valores dos pixels da linha
        }
        
        TipoLista lista;
        ProcessarPixels(pixels, qtd_pixels, &lista); //processa os pixels e cria segmentos na lista
        
        if (VerificarImpedimento(lista)) {
            tem_impedimento = 1;
            break; //se um obstáculo for encontrado, podemos encerrar a análise
        }
    }
    
    printf("Resultado: %s\n", tem_impedimento ? "Pista com impedimento." : "Pista sem impedimento.");
    
    return 0;
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------