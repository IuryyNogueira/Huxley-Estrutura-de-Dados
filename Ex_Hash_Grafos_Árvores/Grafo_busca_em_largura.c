#include <stdio.h>
#include <stdlib.h>

typedef struct _no
{
    int item;
    struct _no *prox;

} no;

typedef struct _grafo
{
    no **lista_adjacencia;
    int *distancia;
    int *predecessor;
    int quantidade_vertices;

} grafo;

typedef struct _fila
{
    int *itens;
    int frente;
    int tras;
    int tamanho;
    int capacidade;
} fila;

fila *criar_fila(int n)
{
    fila *nova_fila = (fila *)calloc(1, sizeof(fila));

    nova_fila->itens = (int *)calloc(n, sizeof(int));
    nova_fila->frente = 0;
    nova_fila->tras = 0;
    nova_fila->tamanho = 0;
    nova_fila->capacidade = n;

    return nova_fila;
}

no *criar_no(int item)
{
    no *novo_no = (no *)calloc(1, sizeof(no));

    novo_no->item = item;
    novo_no->prox = NULL;

    return novo_no;
}

grafo *criar_grafo(int n)
{
    // aloca memória para o grafo
    grafo *novo_grafo = (grafo *)calloc(1, sizeof(grafo));
    // aloca memória para a lista de adjacência
    novo_grafo->lista_adjacencia = (no **)calloc(n, sizeof(no *));
    // aloca memória para o vetor de distâncias
    novo_grafo->distancia = (int *)calloc(n, sizeof(int));
    // aloca memória para o vetor de predecessores
    novo_grafo->predecessor = (int *)calloc(n, sizeof(int));
    // inicializa a quantidade de vértices
    novo_grafo->quantidade_vertices = n;

    // inicializa a lista de adjacência
    for (int i = 0; i < n; i++){
        novo_grafo->lista_adjacencia[i] = NULL;
        novo_grafo->distancia[i] = 0;   // inicializa todos os vértices como não visitados
        novo_grafo->predecessor[i] = 0; // inicializa todos os vértices sem predecessores
    }

    return novo_grafo;
}

int cheia(fila *fila)
{
    return fila->capacidade == fila->tamanho;
}

int vazia(fila *fila)
{
    return fila->tamanho == 0;
}

void enfileirar(fila *fila, int item)
{
    fila->itens[fila->tras] = item;
    fila->tras++;
    fila->tamanho++;
}

int desenfileirar(fila *fila)
{
    int item = fila->itens[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;

    return item;
}

void adicionar_aresta(grafo *grafo, int origem, int destino)
{
    no *novo_no = criar_no(destino);
    novo_no->item = destino;
    novo_no->prox = NULL;
    
    if (grafo->lista_adjacencia[origem] == NULL || destino <= grafo->lista_adjacencia[origem]->item)
    {
        novo_no->prox = grafo->lista_adjacencia[origem];

        grafo->lista_adjacencia[origem] = novo_no;

        return;
    }

    no *anterior = NULL;
    no *atual = grafo->lista_adjacencia[origem];

    while (atual && destino > atual->item)
    {
        anterior = atual;
        atual = atual->prox;
    }

    novo_no->prox = atual;
    anterior->prox = novo_no;

    return;
}

void bfs(grafo *grafo, int origem, int destino)
{
    int n = grafo->quantidade_vertices;

    fila *fila = criar_fila(n);

    for (int i = 0; i < n; i++)
    {
        grafo->distancia[i] = -1;
        grafo->predecessor[i] = -1;
    }

    grafo->distancia[origem] = 0;

    enfileirar(fila, origem);

    while (!vazia(fila))
    {
        int vertice_atual = desenfileirar(fila);

        printf("Iniciando busca em largura a partir de %d\n", vertice_atual);

        no *aux = grafo->lista_adjacencia[vertice_atual];

        while (aux != NULL)
        {
            int vertice_adjacente = aux->item;

            if (grafo->distancia[vertice_adjacente] == -1)
            {
                grafo->distancia[vertice_adjacente] = grafo->distancia[vertice_atual] + 1;
                grafo->predecessor[vertice_adjacente] = vertice_atual;
                enfileirar(fila, vertice_adjacente);
            }

            aux = aux->prox;
        }
    }
    puts("");
    // libera quant_arestas fila
    free(fila->itens);
    free(fila);
}

void imprimir_caminho(int predecessor[], int origem, int destino)
{
    if (origem == destino)
        printf("%d", origem);
    else
    {
        imprimir_caminho(predecessor, origem, predecessor[destino]);
        printf(" => %d", destino);
    }

    return;
}

int main()
{

    int quant_vertices, quant_arestas, quant_casos;
    scanf("%d %d %d", &quant_vertices, &quant_arestas, &quant_casos);

    grafo *grafo = criar_grafo(quant_vertices);

    for (int i = 1; i <= quant_arestas; i++)
    {

        int vert1, vert2;
        scanf("%d %d", &vert1, &vert2);

        adicionar_aresta(grafo, vert1, vert2);
    }

    // imprime
    for (int i = 1; i <= quant_casos; i++)
    {

        int origem, destino;
        scanf("%d %d", &origem, &destino);

        puts("");
        puts("--------");
        puts("");
        printf("Caso de Teste #%d - BFS(%d)\n", i, origem);
        puts("");

        // executa a busca em largura
        bfs(grafo, origem, destino);

        // 8 | - | -
        // 7 | 0 | -
        // 5 | 2 | 9

        for (int i = 0; i < quant_vertices; i++)
        {
            // 3 casos
            if (grafo->distancia[i] == -1)
                printf("%d | - | -\n", i);

            else if (grafo->distancia[i] == 0)
                printf("%d | %d | -\n", i, grafo->distancia[i]);

            else
                printf("%d | %d | %d\n", i, grafo->distancia[i], grafo->predecessor[i]);
        }

        // CASO NÃO EXISTA CAMINHO ENTRE ORIGEM E DESTINO
        if (grafo->distancia[destino] == -1)
            printf("\nSem caminho entre %d e %d\n", origem, destino);

        // CASO EXISTA CAMINHO ENTRE ORIGEM E DESTINO
        else
        {
            puts("");
            printf("Caminho entre %d e %d: ", origem, destino);
            imprimir_caminho(grafo->predecessor, origem, destino);
            puts("");
        }
    }

    puts("\n--------");

    return 0;
}
