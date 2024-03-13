#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int chave;
    struct node *prox;
} no;

typedef struct
{
    no **tabela;
    int capacidade;
    int tamanho;
} tabela_hash;

// fucoes:

int funcao_hash(int chave, int capacidade);

tabela_hash *criar_tabela_hash();

int inserir(tabela_hash *th, int chave, int *comparacoes);

int remover(tabela_hash *th, int chave, int *comparacoes);

int contem(tabela_hash *th, int chave, int *comparacoes);

int obter_comprimento_maximo(tabela_hash *th);

void redimensionar(tabela_hash *th);

void liberar_tabela(tabela_hash *th);


int main()
{
    tabela_hash *th = criar_tabela_hash();
    int numero_operacao = 0;
    char operacao[4];
    int chave, resultado, comparacoes;

    while (scanf("%s", operacao) > 0)
    {
        // se a operação for de impressão, imprime os dados da tabela e pula para a próxima iteração
        if (operacao[0] == 'P')
        {
            printf("%d %d %d %d\n", numero_operacao, th->capacidade, th->tamanho, obter_comprimento_maximo(th));
            numero_operacao++;
            continue;
        }
        else
        {
            scanf("%d", &chave);
            // A = inserir, D = remover, H = contem o elemento
            switch (operacao[0])
            {
            case 'A':
                resultado = inserir(th, chave, &comparacoes);

                if ((float)th->tamanho / th->capacidade >= 0.75)
                {
                    redimensionar(th);
                }
                break;
            case 'D':
                resultado = remover(th, chave, &comparacoes);
                break;
            case 'H':
                resultado = contem(th, chave, &comparacoes);
                break;
            default:
                break;
            }

            printf("%d %d %d\n", numero_operacao, resultado, comparacoes);
            numero_operacao++;
        }
    }

    liberar_tabela(th);

    return 0;
}

int funcao_hash(int chave, int capacidade)
{
    return chave % capacidade;
}

tabela_hash *criar_tabela_hash()
{
    tabela_hash *th = (tabela_hash *)malloc(sizeof(tabela_hash));
    // capacidade inicial da tabela, o numero 7 é arbitrário e pode ser alterado
    th->capacidade = 7;
    th->tamanho = 0;
    th->tabela = (no **)malloc(th->capacidade * sizeof(no *));

    for (int i = 0; i < th->capacidade; i++)
    {
        th->tabela[i] = NULL;
    }

    return th;
}

int inserir(tabela_hash *th, int chave, int *comparacoes)
{
    int indice = funcao_hash(chave, th->capacidade);
    no *atual = th->tabela[indice];

    *comparacoes = 0;
    // percorre a lista encadeada até encontrar a chave ou chegar no final da lista
    while (atual != NULL)
    {
        (*comparacoes)++;
        // se a chave já estiver na tabela, retorna 0
        if (atual->chave == chave)
        {
            return 0;
        }

        atual = atual->prox;
    }
    // insere a chave na posição correta
    no *novo_no = (no *)malloc(sizeof(no));
    novo_no->chave = chave;
    novo_no->prox = th->tabela[indice];

    // insere o novo nó na posição correta
    th->tabela[indice] = novo_no;
    th->tamanho++;

    return 1;
}

int remover(tabela_hash *th, int chave, int *comparacoes)
{
    int indice = funcao_hash(chave, th->capacidade);
    no *atual = th->tabela[indice];
    no *anterior = NULL;

    *comparacoes = 0;
    // percorre a lista encadeada até encontrar a chave ou chegar no final da lista
    while (atual != NULL)
    {
        (*comparacoes)++;
        // se a chave estiver na lista, remove a chave
        if (atual->chave == chave)
        {
            if (anterior == NULL)
            {
                th->tabela[indice] = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual);
            th->tamanho--;
            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}
// Função que verifica se a chave está na tabela hash
int contem(tabela_hash *th, int chave, int *comparacoes)
{
    int indice = funcao_hash(chave, th->capacidade);
    no *atual = th->tabela[indice];

    *comparacoes = 0;

    while (atual != NULL)
    {
        (*comparacoes)++;

        if (atual->chave == chave)
        {
            return 1;
        }

        atual = atual->prox;
    }

    return 0;
}
// essa funcao retorna o comprimento máximo da lista encadeada, atraves de um loop que percorre a tabela hash
int obter_comprimento_maximo(tabela_hash *th)
{
    int maximo = 0;

    for (int i = 0; i < th->capacidade; i++)
    {
        int comprimento_atual = 0;
        no *atual = th->tabela[i];

        while (atual != NULL)
        {
            comprimento_atual++;
            atual = atual->prox;
        }

        if (comprimento_atual > maximo)
        {
            maximo = comprimento_atual;
        }
    }

    return maximo;
}
// essa funcao redimensiona a tabela hash, dobrando a capacidade e realocando os elementos
void redimensionar(tabela_hash *th)
{
    int nova_capacidade = 2 * th->capacidade - 1;
    // cria uma nova tabela hash com a nova capacidade
    no **nova_tabela = (no **)malloc(nova_capacidade * sizeof(no *));

    for (int i = 0; i < nova_capacidade; i++)
    {
        nova_tabela[i] = NULL;
    }
    // realoca os elementos da tabela hash
    for (int i = 0; i < th->capacidade; i++)
    {
        no *atual = th->tabela[i];
        // percorre a lista encadeada e realoca os elementos
        while (atual != NULL)
        {
            no *proximo = atual->prox;
            int novo_indice = funcao_hash(atual->chave, nova_capacidade);

            atual->prox = nova_tabela[novo_indice];
            nova_tabela[novo_indice] = atual;
            atual = proximo;
        }
    }

    free(th->tabela);
    th->tabela = nova_tabela;
    th->capacidade = nova_capacidade;
}

void liberar_tabela(tabela_hash *th)
{
    for (int i = 0; i < th->capacidade; i++)
    {
        no *atual = th->tabela[i];

        while (atual != NULL)
        {
            no *proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }

    free(th->tabela);
    free(th);
}