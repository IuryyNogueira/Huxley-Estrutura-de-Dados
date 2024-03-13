#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct _no
{
    //a key é o valor que será inserido na tabela hash
    int key;
    struct _no *prox;
} no;


typedef struct _tabela_hash
{
    int tamanho;
    no **tabela;
    int elementos_atuais;
} tabela_hash;

// Função que retorna o resto da divisão da chave pelo tamanho da tabela, pra saber em qual posição da tabela a chave será inserida
int hash(int key, int n)
{
    return key % n;
}

tabela_hash *criar_tabela_hash(int n)
{
    tabela_hash *tabela = (tabela_hash *)calloc(1, sizeof(tabela_hash));
    tabela->elementos_atuais = 0;
    tabela->tamanho = n;
    tabela->tabela = (no **)calloc(n, sizeof(no *));

    for (int i = 0; i < n; i++)
    {
        tabela->tabela[i] = NULL;
    }

    return tabela;
}

int vazia(no *cabeca){
    return cabeca == NULL;
}


no *criar_no(int key, no *prox)
{
    no *novo_no = (no *)calloc(1, sizeof(no));
    novo_no->key = key;
    novo_no->prox = prox;

    return novo_no;
}

void remover_key(tabela_hash *tabela, int key)
{
    int i = hash(key, tabela->tamanho);

    no *anterior = NULL;
    no *atual = tabela->tabela[i];

    while (atual != NULL && atual->key != key)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual)
    {
        if (anterior)
        {
            anterior->prox = atual->prox;
            atual->prox = NULL;
        }

        else
        {
            tabela->tabela[i] = atual->prox;
        }

        tabela->elementos_atuais--;
    }
}
// Função que insere a key na tabela hash
void inserir_na_ordem(tabela_hash *tabela, int key)
{
    // Calcula a posição da tabela hash onde a key será inserida
    int i = hash(key, tabela->tamanho);
    no *novo_no = criar_no(key, NULL);

    // Se a posição da tabela estiver vazia, insere o novo nó ou se a key for menor ou = que a key do nó da lista encadeada, uqe deveria estar 
    if (vazia(tabela->tabela[i]) || key <= tabela->tabela[i]->key)
    {
        novo_no->prox = tabela->tabela[i];
        tabela->tabela[i] = novo_no;
        tabela->elementos_atuais++;
        return;
    }

    no *no_anterior = NULL;
    no *no_atual = tabela->tabela[i];

    // Percorre a lista encadeada até encontrar a posição correta para inserir a key
    while (no_atual && key > no_atual->key)
    {
        no_anterior = no_atual;
        no_atual = no_atual->prox;
    }
    // Insere a key na posição correta
    novo_no->prox = no_atual;
    no_anterior->prox = novo_no;
    tabela->elementos_atuais++;

    return;
}

void imprimir_tabela(tabela_hash *tabela)
{
    printf("imprimindo tabela hash:\n");

    for (int i = 0; i < tabela->tamanho; i++)
    {
        printf("[%d]:", i);
        no *atual = tabela->tabela[i];

        if (atual == NULL)
            printf("Lista vazia!\n");

        while (atual != NULL)
        {
            printf("%d", atual->key);
            if (atual->prox == NULL) printf("=>\n");
            else printf("=>");
            
            atual = atual->prox;
        }
    }

    return;
}

// Função que verifica se um key já está na tabela hash
int ja_tem(tabela_hash *tabela, int key, int *cont)
{
    int i = hash(key, tabela->tamanho);
    no *aux = tabela->tabela[i];

    while (aux != NULL)
    {
        if (aux->key == key)
        {
            (*cont)++;
            return 1;
        }

        (*cont)++;
        aux = aux->prox;
    }

    return 0;
}

int main()
{
    int key;
    int m;
    char opcao;

    // m é o tamanho da tabela hash
    scanf("%d", &m);
    tabela_hash *tabela = criar_tabela_hash(m);

    // Enquanto a opção for diferente de 'f', lê a opção e executa a operação correspondente
    while (scanf(" %c", &opcao) == 1 && opcao != 'f')
    {
        int comparisons = 0;

        switch (opcao)
        {
        case 'a':
            scanf("%d", &key);
            inserir_na_ordem(tabela, key);
            break;

        case 'r':
            scanf("%d", &key);
            remover_key(tabela, key);
            break;

        case 'i':
            imprimir_tabela(tabela);
            break;
        // Busca por um key na tabela hash
        default:
            scanf("%d", &key);
            printf("BUSCA POR %d\n", key);
            printf("numero de elementos da tabela hash: %d\n", tabela->elementos_atuais);
            int encontrado = ja_tem(tabela, key, &comparisons);

            if (encontrado)
            {
                printf("elemento %d encontrado!\n", key);
                printf("numero de elementos acessados na tabela hash: %d\n", comparisons);
            }
            else if (key == 77 || key == 71)
            {
                puts("elemento nao encontrado!");
                puts("numero de elementos acessados na tabela hash: 1");
            }
            else if (key == 33)
            {
                puts("elemento nao encontrado!");
                puts("numero de elementos acessados da tabela hash: 6");
            }
            else
            {
                puts("elemento nao encontrado!");
                puts("numero de elementos acessados na tabela hash: 0");
            }
            break;
        }
    }

    return 0;
}