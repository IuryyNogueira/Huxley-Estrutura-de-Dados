#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    struct _node *next;
    int item;
}node;

node* create_linked_list()
{
return NULL;
}       

node* add(node *head, int item)
{
node *new_node = (node*) malloc(sizeof(node));
new_node->item = item;
new_node->next = head;
return new_node;
}

void print_lista_encadeada( node *head){
     if(head == NULL)
    {
        printf("VAZIO\n");
        return ;
    }
    while (head != NULL){
        printf("%d\n", head->item);
        //printf(head->next == NULL ? " " : "\n");
        head = head->next;
    }
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

node *sort_lista_encadeada( node *head){
   
    node *baixa_autoestima = head;
    int troca = 1;

    while(troca != 0){
        
        troca = 0;

        while(baixa_autoestima->next != NULL){
            if (baixa_autoestima->item > baixa_autoestima->next->item)
            {
                swap(&baixa_autoestima->item, &baixa_autoestima->next->item);
                troca = 1;
            }
            baixa_autoestima = baixa_autoestima->next;
        }

        baixa_autoestima = head;
    }
    return head;

}
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

int inrrepetivel(node *result, int item)
{
    node *aux = result;

    while(aux != NULL)
    {
        if(aux->item == item)
        {
            return 1;
        }

        aux = aux->next;
    }
    
    return 0;
}

node *intersecao(node *lista_1, node *lista_2)
{
    node *result = create_linked_list();
    
    while(lista_1 != NULL && lista_2 != NULL)
    {
        if(lista_1->item == lista_2->item)
        {
            if(inrrepetivel(result, lista_1->item) == 0) result = add_node_no_final(result, lista_1->item);

            lista_1 = lista_1->next;
            lista_2 = lista_2->next;

        }

        else if(lista_1->item > lista_2->item) lista_2 = lista_2->next;

        else lista_1 = lista_1->next; 
    }

    return result;   
}

int main(){

    node *first_list = create_linked_list();
    node *second_list = create_linked_list();

    for(int j = 0; j < 2; j++)
    {
        for(int i = 0; i < 20; i++)
        {
            int d;
            scanf("%d", &d);
            j == 0 ? (first_list = add(first_list, d)) : (second_list = add(second_list, d));


        }
    }

    first_list = sort_lista_encadeada(first_list);
    second_list = sort_lista_encadeada(second_list);

    
    print_lista_encadeada(intersecao(first_list, second_list));

    return 0;
}