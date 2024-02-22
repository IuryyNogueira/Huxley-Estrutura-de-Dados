#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int item;
    struct _node *next;
} node;

node *addnodeinicio(node *head, int item)
{
    node *new_node = (node *)calloc(1, sizeof(node));
    new_node->item = item;
    new_node->next = head;
    return new_node;
}

node *sum2linkedlists(node *list1, node *list2)
{
    node *result = NULL;
    int carry = 0;

    // Percorra ambas as listas enquanto houver elementos em ambas
    while (list1 != NULL || list2 != NULL)
    {
        int sum = carry;

        // Adicione os valores dos nós atuais, se existirem
        if (list1 != NULL)
        {
            sum += list1->item;
            list1 = list1->next;
        }
        if (list2 != NULL)
        {
            sum += list2->item;
            list2 = list2->next;
        }

        // Verifique se há transporte
        if (sum >= 10)
        {
            carry = 1;
            sum -= 10;
        }
        else
        {
            carry = 0;
        }

        // Adicione o novo nó à lista resultante
        result = addnodeinicio(result, sum);
    }

    // Se houver transporte no final, adicione um novo nó com valor 1
    if (carry > 0)
    {
        result = addnodeinicio(result, 1);
    }

    return result;
}

void printlinkedlist(node *head)
{
    if (head == NULL)
    {
        puts("Lista vazia!");
        return;
    }

    node *aux = head;
    while (aux->item == 0)
    {
        aux = aux->next;
    }

    while (aux != NULL)
    {
        printf("%d ", aux->item);
        aux = aux->next;
    }
    puts("");
}

int main()
{
    node *list1 = NULL;
    node *list2 = NULL;

    char letra;

    int list = 1;

    while (scanf(" %c", &letra) != EOF)
    {
        if (letra == '=')
            break;

        if (letra == '+')
            list = 2;

        if (list == 1 && letra != '+')
        {
            list1 = addnodeinicio(list1, letra - '0');
        }
        else if (list == 2 && letra != '+')
        {
            list2 = addnodeinicio(list2, letra - '0');
        }
    }

    // Some as listas ligadas
    node *result = sum2linkedlists(list1, list2);

    // Imprima o resultado
    printlinkedlist(result);

    return 0;
}
