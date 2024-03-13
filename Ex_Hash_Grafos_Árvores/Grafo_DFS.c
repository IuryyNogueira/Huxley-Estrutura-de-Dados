#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMPRIMENTO_STRING 15
#define MAX_VERTICES 100

typedef struct no
{
    int numero_no;
    int indice_insercao;

    char item[MAX_COMPRIMENTO_STRING + 1];
    struct no *proximo;
} no;

typedef struct grafo_aciclico_direcionado
{
    int tamanho;
    no **lista_adjacencia;
} grafo_aciclico_direcionado;

grafo_aciclico_direcionado *criar_grafo()
{
    grafo_aciclico_direcionado *g = (grafo_aciclico_direcionado *)malloc(sizeof(grafo_aciclico_direcionado));

    g->tamanho = MAX_VERTICES;
    // Inicializa a lista de adjacência
    // A LISTA DE ADJACÊNCIA É UM ARRAY DE PONTEIROS PARA NÓS
    g->lista_adjacencia = (no **)malloc(MAX_VERTICES * sizeof(no *));

    for (int i = 0; i < MAX_VERTICES; i++)
    {
        g->lista_adjacencia[i] = NULL;
    }

    return g;
}

no *inserir_no_ordenado(no *cabeca, const char item[MAX_COMPRIMENTO_STRING + 1], int indice)
{
    no *novo_no = (no *)malloc(sizeof(no));
    // Atribui o índice de inserção
    novo_no->indice_insercao = indice;
    // Copia o item para o novo nó
    strcpy(novo_no->item, item);
    novo_no->proximo = NULL;

    if (cabeca == NULL)return novo_no;

    no *atual = cabeca;
    no *anterior = NULL;

    // Enquanto não chegar no final da lista e o item atual for menor que o item a ser inserido
    while (atual != NULL && strcmp(atual->item, item) < 0)
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (anterior == NULL)
    {
        novo_no->proximo = atual;
        cabeca = novo_no;
    }
    else
    {
        anterior->proximo = novo_no;
        novo_no->proximo = atual;
    }

    return cabeca;
}

// evita repetição de código
typedef int (*FuncaoComparacao)(no *, int);

no *remover_no_generico(no *cabeca, int item, FuncaoComparacao funcaoComparacao)
{
    if (cabeca == NULL)
    {
        return cabeca;
    }

    no *atual = cabeca;
    no *anterior = NULL;
   
    // Enquanto não chegar no final da lista e o item atual for diferente do item a ser removido
    while (atual != NULL && funcaoComparacao(atual, item))
    {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return cabeca;

    if (anterior == NULL)cabeca = cabeca->proximo;
    
    else anterior->proximo = atual->proximo;
    
    free(atual);
    return cabeca;
}

// Função para comparar o número do nó com o item
int comparar_pelo_numero_do_no(no *atual, int item)
{
    return atual->numero_no != item;
}

// Função para comparar o índice de inserção do nó com o item
int comparar_pelo_indice_de_insercao(no *atual, int item){
    return atual->indice_insercao != item;
}

void imprimir_nos(no *cabeca){
    no *temp = cabeca;
    while (temp != NULL)
    {
        printf("%s\n", temp->item);
        temp = temp->proximo;
    }
}

int obter_indice_item(no *cabeca, const char item[]){
    
    no *temp = cabeca;

    while (temp != NULL && (strcmp(temp->item, item) != 0))
    {
        temp = temp->proximo;
    }

    return (temp != NULL) ? temp->indice_insercao : -1;
}

// essa funcao é a busca em profundidade que é chamada para cada vértice do grafo
void busca_em_profundidade(grafo_aciclico_direcionado *g, no *nos_origem, int tamanho)
{
    // Enquanto houverem nós na lista de origem
    while (nos_origem != NULL)
    {
        no *aux_origem = nos_origem;
        no *nos_destino = NULL;

        while (aux_origem != NULL)
        {
            // Obtem o índice do item na lista de adjacência
            int indice = obter_indice_item(nos_origem, aux_origem->item);

            // Se o nó de destino não existe, insere
            if (g->lista_adjacencia[indice] == NULL)
                nos_destino = inserir_no_ordenado(nos_destino, aux_origem->item, indice);

            aux_origem = aux_origem->proximo;
        }

        imprimir_nos(nos_destino);

        aux_origem = nos_destino;

        while (aux_origem != NULL)
        {
            for (int i = 0; i < tamanho; i++){
                g->lista_adjacencia[i] = remover_no_generico(g->lista_adjacencia[i], aux_origem->indice_insercao, comparar_pelo_numero_do_no);
            }

            nos_origem = remover_no_generico(nos_origem, aux_origem->indice_insercao, comparar_pelo_indice_de_insercao);
            aux_origem = aux_origem->proximo;
        }
    }
}

void adicionar_aresta(grafo_aciclico_direcionado *g, int indiceA, int indiceB)
{
    no *novo_no = (no *)malloc(sizeof(no));

    novo_no->indice_insercao = 0;
    novo_no->numero_no = indiceB;
    novo_no->proximo = g->lista_adjacencia[indiceA];
    g->lista_adjacencia[indiceA] = novo_no;
}

int main()
{
    int n;
    // Enquanto houver entrada
    while (scanf("%d", &n) != EOF)
    {

        grafo_aciclico_direcionado *g = criar_grafo();
        char itemA[16], itemB[16];
        no *itens = NULL;

        int tamanho = 0;
        // Para cada aresta
        // Adiciona os itens na lista de adjacência
        for (int i = 0; i < n; i++)
        {
            scanf("%s %s", itemA, itemB);

            // manipula os nos
            int indiceA = obter_indice_item(itens, itemA);
            // Se o item não existe, insere
            if (indiceA == -1)
            {
                // Insere o item na lista de adjacência
                itens = inserir_no_ordenado(itens, itemA, tamanho);
                indiceA = tamanho;
                tamanho++;
            }

            int indiceB = obter_indice_item(itens, itemB);
            if (indiceB == -1)
            {
                itens = inserir_no_ordenado(itens, itemB, tamanho);
                indiceB = tamanho;
                tamanho++;
            }
            adicionar_aresta(g, indiceA, indiceB);
        }

        // FAZ A BUSCA EM PROFUNDIDADE PARA CADA VÉRTICE DO GRAFO
        // DFS
        busca_em_profundidade(g, itens, tamanho);
    }

    return 0;
}
