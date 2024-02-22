#include <stdio.h>
#include <stdlib.h>

//cria a struct 
typedef struct _node {
    struct _node *next;
    int item;
}node;

// usa pra iniciar astruct com null, oq serve pra parada depois 
node* create_linked_list()
{
return NULL;
}       

//essa de fato adciona os nós 
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

int main(){

    node *head = create_linked_list();
    
    int d;

    while(scanf("%d", &d) != EOF) {
        head = add(head, d);
    }     

    print_lista_encadeada(head);

    return 0;

}