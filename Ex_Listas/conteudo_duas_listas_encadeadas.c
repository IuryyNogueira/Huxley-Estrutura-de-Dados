#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    struct _node *next;
    int item;
}node;
    
node *add_node_no_final(node *head, int item)
{
    node *new_node = (node*) calloc(1, sizeof(node));
    new_node->item = item;
    
    new_node->next = NULL;

    if(head == NULL)
    {
        return new_node;
    }
    else
    {
        node *aux = head;

        while(aux->next != NULL)
        {
            aux = aux->next;
        }

        aux->next = new_node;

        return head;
    }
}

int B_sunconjunto_A(node *lista1, node *lista2, int t1, int t2)
{
    int cont = 0;
    node *aux1 = lista1, *aux2 = lista2; 

    while(aux2 != NULL)
    {
        while(aux1 != NULL)
        {
            if(aux1->item == aux2->item)
            {
                cont++;
                break;
            }

            aux1 = aux1->next;
        }

        aux1 = lista1;
        aux2 = aux2->next;
    }

    if(cont == t2) return 1;
    return 0;
}

int main(){

    int tam1, tam2;

    node *lista1 = NULL;
    node *lista2 = NULL;

    scanf("%d", &tam1);

    for(int i = 0; i < tam1; ++i)
    {
        int item;
        scanf("%d", &item);
        
        lista1 = add_node_no_final(lista1, item);
    }

    scanf("%d", &tam2);

    for(int i = 0; i < tam2; ++i)
    {
        int item;
        scanf("%d", &item);
        
        lista2 = add_node_no_final(lista2, item);
    }

    printf("%d\n",B_sunconjunto_A(lista1, lista2, tam1, tam2));

    return 0;
}