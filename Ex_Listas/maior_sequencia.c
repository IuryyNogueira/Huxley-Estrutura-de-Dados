#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura de um nó da lista encadeada
typedef struct _node
{
    struct _node *next;
    int item;
} node;

// Função para imprimir a lista encadeada
void print_lista_encadeada(node *head)
{
    while (head != NULL)
    {
        printf("%d", head->item);
        printf(head->next == NULL ? "\n" : " ");
        head = head->next;
    }
}

// Função para adicionar um nó no final da lista encadeada
node *add_node_no_final(node *head, int item)
{
    // Alocando espaço para o novo nó
    node *new_node = (node *)calloc(1, sizeof(node));
    // Atribuindo o valor ao novo nó
    new_node->item = item;
    // Inicializando o próximo nó como NULL
    new_node->next = NULL;

    // Se a lista estiver vazia, o novo nó se torna a cabeça da lista
    if (head == NULL)
    {
        return new_node;
    }
    else
    {
        // Caso contrário, percorremos a lista até o último nó
        node *aux = head;
        while (aux->next != NULL)
        {
            aux = aux->next;
        }
        // Adicionamos o novo nó ao final da lista
        aux->next = new_node;
        return head;
    }
}

// Função para encontrar a maior sequência de zeros na lista encadeada
void maior_sequencia(node *head)
{
    int inicio_maximo = -1, fim_maximo = -1;
    int inicio_atual = -1, fim_atual = -1;
    int comprimento_maximo = 0, comprimento_atual = 0;
    int posicao = 0;

    node *atual = head;

    // Iterando sobre a lista encadeada
    while (atual != NULL)
    {
        // Verificando se o valor do nó atual é zero
        if (atual->item == 0)
        {
            // Se for o início de uma sequência de zeros
            if (inicio_atual == -1)
            {
                inicio_atual = posicao;
            }
            // Atualizando o fim da sequência atual
            fim_atual = posicao;
            // Calculando o comprimento da sequência atual
            comprimento_atual = fim_atual - inicio_atual + 1;

            // Verificando se a sequência atual é maior do que a máxima até agora
            if (comprimento_atual > comprimento_maximo)
            {
                inicio_maximo = inicio_atual;
                fim_maximo = fim_atual;
                comprimento_maximo = comprimento_atual;
            }
        }
        else
        {
            // Se o valor não for zero, redefinimos o início da sequência atual
            inicio_atual = -1;
        }

        // Movendo para o próximo nó
        atual = atual->next;
        posicao++;
    }

    // Se não houver uma sequência de zeros na lista, o programa termina
    if (inicio_maximo == 0 && fim_maximo == 0)
    {
        exit(0); // Sai do programa com status de sucesso
    }
    // Caso contrário, imprime a posição inicial e final da maior sequência de zeros
    else
    {
        printf("%d %d\n", inicio_maximo, fim_maximo);
    }
}

int main()
{
    char c;
    // Loop principal
    while (1)
    {
        node *head = NULL;

        // Lendo caracteres da entrada até encontrar uma nova linha ou o final do arquivo
        while (scanf("%c", &c) == 1)
        {
            if (c == '\n' || c == EOF)
            {
                break;
            }
            // Convertendo o caractere em um valor inteiro e adicionando à lista encadeada
            int item = c - '0';
            head = add_node_no_final(head, item);
        }

        // Se a lista encadeada não estiver vazia, encontra a maior sequência de zeros
        if (head != NULL)
        {
            maior_sequencia(head);
        }

        // Liberando a memória alocada para a lista encadeada
        node *temp;
        while (head != NULL)
        {
            temp = head;
            head = head->next;
            free(temp);
        }
    }

    return 0;
}
