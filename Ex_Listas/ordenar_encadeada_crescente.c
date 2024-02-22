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
    while (head != NULL){
        printf("%d", head->item);
        printf(head->next == NULL ? "\n" : " ");
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

int main(){

    node *head = create_linked_list();
    
    int d;

    while(scanf("%d", &d) != EOF) {
        head = add(head, d);
    }     

    head = sort_lista_encadeada(head);
    print_lista_encadeada(head);

    return 0;

}